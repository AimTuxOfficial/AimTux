#ifndef __IMATERIALSYSTEM_H
#define __IMATERIALSYSTEM_H

class IMaterialSystem
{
public:
	IMaterial *FindMaterial(char const *pMaterialName, const char *pTextureGroupName, bool complain = true, const char *pComplainPrefix = NULL)
	{
		typedef void (* oFindMaterial)(void*, char const*, const char*, bool, const char*);
		getvfunc<oFindMaterial>(this, 84)(this, pMaterialName, pTextureGroupName, complain, pComplainPrefix);
	}
};

#endif
