#pragma once

extern "C"{
	// Environment data. resolved at link-time.
	extern char **environ;
}


// Hook Prototypes
extern int (*orig_open)(const char*, int oflag);
extern char* (*orig_getenv)(const char *);
extern int (*orig_execve)(const char *path, char *const argv[], char *const envp[]);
extern FILE* (*orig_fopen)(const char*, const char*);

extern "C"{
	char* getenv(const char *name);

	// We do not need to hook most of the exec variants for fork()/system()

	/* Execute PATH with all arguments after PATH until
	a NULL pointer and environment from `environ'.  */
	// execl gets environment from environ.
    //int execl (const char *__path, const char *__arg, ...);

	/* Execute PATH with all arguments after PATH until a NULL pointer,
	and the argument after that for environment.  */
	// The execle function behind the scenes calls the execve function for you.
	// Since we have hooked that function already, no need to hook.
	//int execle(const char *__path, const char *__arg, ...);

	/* Execute FILE, searching in the `PATH' environment variable if
   	it contains no slashes, with all arguments after FILE until a
	NULL pointer and environment from `environ'.  */
	// execlp gets environment from environ.
	//int execlp (const char *__file, const char *__arg, ...);

	/* Replace the current process, executing PATH with arguments ARGV and
   	environment ENVP.  ARGV and ENVP are terminated by NULL pointers.  */
	int execve(const char *path, char *const argv[], char *const envp[]);

	/* Execute FILE, searching in the `PATH' environment variable if it contains
	no slashes, with arguments ARGV and environment from `environ'.  */
	// execvp gets environment from environ.
	//int execvp (const char *__file, char *const __argv[]);

	int open(const char *path, int oflag, ...);
	FILE* fopen(const char *path, const char *mode);
}


namespace Preload
{
	bool Startup(char buildID[]);
	void CleanEnvironment();
	void Cleanup();
}