#pragma once

#define MAX_DLIGHTS 32

enum
{
	DLIGHT_NO_WORLD_ILLUMINATION = 0x1,
	DLIGHT_NO_MODEL_ILLUMINATION = 0x2,

	// NOTE: These two features are used to dynamically tweak the alpha on displacements
	// which is a special effect for selecting which texture to use. If
	// we ever change how alpha is stored for displacements, we'll have to kill this feature
	DLIGHT_ADD_DISPLACEMENT_ALPHA = 0x4,
	DLIGHT_SUBTRACT_DISPLACEMENT_ALPHA = 0x8,
	DLIGHT_DISPLACEMENT_MASK = (DLIGHT_ADD_DISPLACEMENT_ALPHA | DLIGHT_SUBTRACT_DISPLACEMENT_ALPHA),
};

struct ColorRGBExp32
{
	unsigned char r, g, b;
	signed char exponent;
};

struct dlight_t {
	int flags;
	Vector origin;
	float radius;
	ColorRGBExp32 color;      // Light color with exponent
	float die;                // stop lighting after this time
	float decay;              // drop this each second
	float minlight;           // don't add when contributing less
	int key;
	int style;                // lightstyle

	// For spotlights. Use m_OuterAngle == 0 for point lights
	Vector m_Direction;       // center of the light cone
	float m_InnerAngle;
	float m_OuterAngle;

	// see comments above about HL2_BROKEN_MIN_LIGHTING_VALUE and MIN_LIGHTING_VALUE
	// THIS SHOULD ONLY GET CALLED FROM THE ENGINE
	float GetRadius() const {
		// return FastSqrt( radius * radius * ( HL2_BROKEN_MIN_LIGHTING_VALUE / MIN_LIGHTING_VALUE ) );
		return radius;
	}

	// see comments above about HL2_BROKEN_MIN_LIGHTING_VALUE and MIN_LIGHTING_VALUE
	// THIS SHOULD ONLY GET CALLED FROM THE ENGINE
	float GetRadiusSquared() const
	{
		// return radius * radius * ( HL2_BROKEN_MIN_LIGHTING_VALUE / MIN_LIGHTING_VALUE );
		return radius * radius;
	}

	// THIS SHOULD ONLY GET CALLED FROM THE ENGINE
	float IsRadiusGreaterThanZero() const
	{
		// don't bother calculating the new radius if you just want to know if it is greater than zero.
		return radius > 0.0f;
	}
};

struct model_t;
struct color32;
class IMaterial;

class CEffects
{
public:
	// Retrieve decal texture index from decal by name
	virtual int Draw_DecalIndexFromName(char *name) = 0;

	// Apply decal
	virtual void DecalShoot(int textureIndex, int entity, const model_t *model, const Vector& model_origin, const QAngle& model_angles, const Vector& position, const Vector *saxis, int flags) = 0;

	// Apply colored decal
	virtual void DecalColorShoot(int textureIndex, int entity, const model_t *model, const Vector& model_origin, const QAngle& model_angles, const Vector& position, const Vector *saxis, int flags, const color32 &rgbaColor) = 0;

	virtual void PlayerDecalShoot(IMaterial* material, void *userdata, int entity, const model_t *model, const Vector& model_origin, const QAngle& model_angles, const Vector& position, const Vector *saxis, int flags, const color32 &rgbaColor) = 0;

	// Allocate a dynamic world light ( key is the entity to whom it is associated )
	virtual dlight_t* CL_AllocDlight(int key) = 0;

	// Allocate a dynamic entity light ( key is the entity to whom it is associated )
	virtual dlight_t* CL_AllocElight(int key) = 0;

	// Get a list of the currently-active dynamic lights.
	virtual int CL_GetActiveDLights(dlight_t *pList[MAX_DLIGHTS]) = 0;

	// Retrieve decal texture name from decal by index
	virtual const char* Draw_DecalNameFromIndex(int nIndex) = 0;

	// Given an elight key, find it. Does not search ordinary dlights. May return NULL.
	virtual dlight_t* GetElightByKey(int key) = 0;
};