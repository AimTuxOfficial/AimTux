#pragma once

struct surfacephysicsparams_t
{
	float friction;
	float elasticity;
	float density;
	float thickness;
	float dampening;
};

struct surfaceaudioparams_t
{
	float reflectivity;
	float hardnessFactor;
	float roughnessFactor;
	float roughThreshold;
	float hardThreshold;
	float hardVelocityThreshold;
};

struct surfacesoundnames_t
{
	unsigned short stepleft;
	unsigned short stepright;
	unsigned short impactSoft;
	unsigned short impactHard;
	unsigned short scrapeSmooth;
	unsigned short scrapeRough;
	unsigned short bulletImpact;
	unsigned short rolling;
	unsigned short breakSound;
	unsigned short strainSound;
};

struct surfacegameprops_t
{
public:
	float maxSpeedFactor;
	float jumpFactor;
	char pad00[0x4];
	float flPenetrationModifier;
	float flDamageModifier;
	unsigned short material;
	char pad01[0x3];
};

struct surfacedata_t
{
	surfacephysicsparams_t physics;
	surfaceaudioparams_t audio;
	surfacesoundnames_t sounds;
	surfacegameprops_t game;
};

class IPhysicsSurfaceProps
{
public:
	virtual ~IPhysicsSurfaceProps(void) {}

	// parses a text file containing surface prop keys
	virtual int ParseSurfaceData(const char *pFilename, const char *pTextfile) = 0;

	// current number of entries in the database
	virtual int SurfacePropCount(void) const = 0;

	virtual int GetSurfaceIndex(const char *pSurfacePropName) const = 0;

	virtual void GetPhysicsProperties(int surfaceDataIndex, float *density, float *thickness, float *friction, float *elasticity) const = 0;

	virtual surfacedata_t *GetSurfaceData(int surfaceDataIndex) = 0;

	virtual const char *GetString(unsigned short stringTableIndex) const = 0;

	virtual const char *GetPropName(int surfaceDataIndex) const = 0;

	// sets the global index table for world materials
	// UNDONE: Make this per-CPhysCollide
	virtual void SetWorldMaterialIndexTable(int *pMapArray, int mapSize) = 0;

	// NOTE: Same as GetPhysicsProperties, but maybe more convenient
	virtual void GetPhysicsParameters(int surfaceDataIndex, surfacephysicsparams_t *pParamsOut) const = 0;
};