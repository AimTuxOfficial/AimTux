#pragma once

typedef unsigned short ModelInstanceHandle_t;

struct model_t
{
	char name[255];
};

struct ModelRenderInfo_t
{
	Vector origin;
	QAngle angles;
	void *pRenderable;
	const model_t *pModel;
	const matrix3x4_t* pModelToWorld;
	const matrix3x4_t* pLightingOffset;
	const Vector *pLightingOrigin;
	int flags;
	int entity_index;
	int skin;
	int body;
	int hitboxset;
	ModelInstanceHandle_t instance;
	ModelRenderInfo_t()
	{
		pModelToWorld = NULL;
		pLightingOffset = NULL;
		pLightingOrigin = NULL;
	}
};

class IVModelRender
{
public:
	void ForcedMaterialOverride(IMaterial* mat)
	{
		typedef void (* oForcedMaterialOverride)(void*, IMaterial*, int, int);
		return getvfunc<oForcedMaterialOverride>(this, 1)(this, mat, 0, 0);
	}

	void DrawModelExecute(void* ctx, void *state, const ModelRenderInfo_t &pInfo, matrix3x4_t* pCustomBoneToWorld = NULL)
	{
		typedef void (* oDrawModelExecute)(void*, void* ctx, void *state, const ModelRenderInfo_t &pInfo, matrix3x4_t* pCustomBoneToWorld);
		return getvfunc<oDrawModelExecute>(this, 21)(this, ctx, state, pInfo, pCustomBoneToWorld);
	}
};
