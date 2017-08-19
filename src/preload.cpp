#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <limits.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include "preload.h"
#include "Utils/util.h"
#include "Utils/xorstring.h"

// Derived from: http://haxelion.eu/article/LD_NOT_PRELOADED_FOR_REAL/
// "I asked the Author (haxelion) permission to re-license under GPLv3. He said it was totally okay." -- LWSS

char *sopath; // abs path to so
char *soname; // name of so

// Hook Prototypes
// We will have to cast types to dlsym's return-value because C++ is a meme.
int (*orig_open)(const char*, int oflag) = NULL;
char* (*orig_getenv)(const char *) = NULL;
int (*orig_execve)(const char *path, char *const argv[], char *const envp[]) = NULL;
FILE* (*orig_fopen)(const char*, const char*) = NULL;

/* Hooks getenv(). Confirmed Working */
char* getenv(const char *name) throw()
{
	if(!orig_getenv)
		orig_getenv = (char* (*)(const char*))dlsym(RTLD_NEXT, "getenv"); // RTLD_NEXT finds the next occurrence. We are the first.

	if(strcmp(name, "LD_PRELOAD") == 0)
	{
		FILE *log = fopen(XORSTR("/tmp/hooks.log"), "a");
		fprintf(log, XORSTR("[Hooks] getenv() : CSGO Requested $LD_PRELOAD. Gave NULL\n"));
		fclose(log);
		return NULL; // hey there bud, LD_PRELOAD isn't here.
	}

	// CSGO does not need to be writing to the TMPDIR.
	// You could perhaps change it to write to a custom folder and auditctl it.
	// Note that the lock file uses hardcoded "/tmp/source_engine_xxxxxxxx.lock" while other things do not.

	if(strcmp(name, "TMPDIR") == 0)
	{
		FILE *log = fopen(XORSTR("/tmp/hooks.log"), "a");
		fprintf(log, XORSTR("[Hooks] getenv() : CSGO Requested $TMPDIR. Gave \"/dev/null\"\n"));
		fclose(log);
		return const_cast<char*>("/dev/null");
	}

	return orig_getenv(name);

}
/* Hooks open(). Confirmed Working */
int open(const char *path, int oflag, ...)
{
	char real_path[PATH_MAX];
	if(!orig_open)
	{
		orig_open = (int (*)(const char*, int))dlsym(RTLD_NEXT, "open");
	}

	realpath(path, real_path);

	/*
	// Causes Intense Menu lag for some reason.
	if(strstr(real_path, "Fuzion") != NULL)
	{
		FILE *log = fopen("/tmp/hooks.log", "a");
		fprintf(log, "[Hooks] open() : CSGO Attempted to open a Fuzion-related path\npath -> %s\n", real_path);
		fclose(log);
		errno = ENOENT;
		return -1; // No Fuzion-related content here.
	}
	 */

	if(strcmp(real_path, "/etc/ld.so.preload") == 0)
	{
		FILE *log = fopen(XORSTR("/tmp/hooks.log"), "a");
		fprintf(log, XORSTR("[Hooks] open() : CSGO Attempted to open our /etc/ld.so.preload file\npath -> %s\n"), real_path);
		fclose(log);
		errno = ENOENT;
		return -1; // no /etc/ld.so.preload here.
	}

	return orig_open(path, oflag);

}

/* Replace the current process, executing PATH with arguments ARGV and
   	environment ENVP.  ARGV and ENVP are terminated by NULL pointers.  */
int execve(const char *path, char *const argv[], char *const envp[]) throw()
{
	FILE *log = fopen(XORSTR("/tmp/hooks.log"), "a");
	fprintf(log, XORSTR("[Hooks] execve() : path -> %s\n"), path);
	for(int i = 0; argv[i]; i++)
	{
		fprintf(log, XORSTR("Argv[%d] -> %s\n"), i, argv[i]);
	}
	for(int i = 0; envp[i]; i++)
	{
		fprintf(log, XORSTR("Envp[%d] -> %s\n"), i, envp[i]);
	}
	fclose(log);

	int i, j, ldi = -1;
	char ** new_env;
	if(!orig_execve)
		orig_execve = (int (*)(const char*, char* const*, char* const*))dlsym(RTLD_NEXT, "execve");
	// look for LD_PRELOAD
	for(i = 0; envp[i]; i++)
	{
		if(strstr(envp[i], "LD_PRELOAD"))
			ldi = i;
	}
	// if not found, add it to the end.
	if(ldi == -1)
	{
		ldi = i;
		i++;
	}
	// Create a new environment
	new_env = (char**) malloc((i+1)*sizeof(char*));
	// copy the old environment into the new one, except for LD_PRELOAD
	for(j = 0; j < i; j++)
	{
		// overwrite or create the LD_PRELOAD variable.
		if(j == ldi)
		{
			new_env[j] = (char*) malloc(256);
			strcpy(new_env[j], "LD_PRELOAD=");
			strcat(new_env[j], sopath);
		}
		else
			new_env[j] = (char*) envp[j];
	}
	// NULL terminate string
	new_env[i] = NULL;
	int r = orig_execve(path, argv, new_env);
	free(new_env[ldi]);
	free(new_env);
	return r;
}

static void fakeMaps(char *original_path, char *fake_path, char *pattern)
{
	FILE *original, *fake;
	char buffer[PATH_MAX];
	original = orig_fopen(original_path, "r");
	fake = orig_fopen(fake_path, "w");
	// Copy original in fake but discard the lines containing pattern
	while(fgets(buffer, PATH_MAX, original))
		if(strstr(buffer, pattern) == NULL)
			fputs(buffer, fake);
	fclose(fake);
	fclose(original);
}

/* Hooks fopen(). Confirmed Working */
FILE* fopen(const char *path, const char *mode)
{
	char real_path[PATH_MAX], maps_path[PATH_MAX];
	pid_t pid = getpid();
	if(!orig_fopen)
		orig_fopen = (FILE* (*)(const char*, const char*))dlsym(RTLD_NEXT, "fopen");

	realpath(path, real_path);
	snprintf(maps_path, PATH_MAX, "/proc/%d/maps", pid);
	if( (strcmp(real_path, maps_path) == 0) || (strcmp(real_path, "/proc/self/maps") == 0) )
	{
		FILE *log = orig_fopen(XORSTR("/tmp/hooks.log"), "a");
		fprintf(log, XORSTR("[Hooks] fopen() : CSGO Attempted to Access our /proc/xxx/maps file. Spoofing.\n"));
		fclose(log);
		snprintf(maps_path, PATH_MAX, XORSTR("/tmp/%d-fakemaps"), pid);
		// Create a file in tmp containing our fake map
		fakeMaps(real_path, maps_path, soname);
		return orig_fopen(maps_path, mode);
	}
	// Everything is ok, call the real open
	return orig_fopen(path, mode);
}


/* Find Functions to Hook. True on all found. False if one was not found */
bool Preload::Startup(char buildID[])
{
	soname = buildID;
	orig_getenv = (char* (*)(const char*))dlsym(RTLD_NEXT, "getenv"); // RTLD_NEXT finds the next occurrence. We are the first.
	orig_open = (int (*)(const char*, int))dlsym(RTLD_NEXT, "open");
	orig_execve = (int (*)(const char*, char* const*, char* const*))dlsym(RTLD_NEXT, "execve");
	orig_fopen = (FILE* (*)(const char*, const char*))dlsym(RTLD_NEXT, "fopen");
	// True if all found. False if any of these = NULL.
	return !( !orig_getenv || !orig_open || !orig_execve || !orig_fopen);
}
/* Clean the memory space that holds information about environment variables */
/* This also cleans it when checked externally ( see: cat /proc/$(pidof csgo_linux64)/environ ) */
void Preload::CleanEnvironment()
{
	int i, j;
	bool found = true;
	static const char *ldpreload = "LD_PRELOAD";
	// save value of LD_PRELOAD to sopath
	size_t len = strlen(orig_getenv(ldpreload));
	sopath = (char*) malloc(len+1);
	strcpy(sopath, orig_getenv(ldpreload));

	// search for LD_PRELOAD in environment memory
	for(i = 0; environ[i]; i++)
	{
		for(j = 0; ldpreload[j] != '\0' && environ[i][j] != '\0'; j++)
		{
			found = true;
			if(ldpreload[j] != environ[i][j])
			{
				found = false;
				break;
			}
		}
		if( found )
		{
			// Zero out the environment memory
			for(int j = 0; environ[i][j] != '\0'; j++)
			{
				environ[i][j] = '\0';
			}
			//free((void*)environ[i]);
			break;
		}
	}
	if( found )
	{
		// remove string pointer from environment memory
		for(int j = i; environ[j]; j++)
			environ[j] = environ[j+1];
	}
}

void Preload::Cleanup()
{
	/* remove fakemap file */
	pid_t pid = getpid();
	char maps_path[PATH_MAX];
	snprintf(maps_path, PATH_MAX, XORSTR("/tmp/%d-fakemaps"), pid);
	remove(maps_path);

}