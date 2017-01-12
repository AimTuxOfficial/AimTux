#pragma once

class IMaterialVar;
typedef uint64_t VertexFormat_t;

enum MaterialVarFlags_t
{
	MATERIAL_VAR_DEBUG = ( 1 << 0 ),
	MATERIAL_VAR_NO_DEBUG_OVERRIDE = ( 1 << 1 ),
	MATERIAL_VAR_NO_DRAW = ( 1 << 2 ),
	MATERIAL_VAR_USE_IN_FILLRATE_MODE = ( 1 << 3 ),

	MATERIAL_VAR_VERTEXCOLOR = ( 1 << 4 ),
	MATERIAL_VAR_VERTEXALPHA = ( 1 << 5 ),
	MATERIAL_VAR_SELFILLUM = ( 1 << 6 ),
	MATERIAL_VAR_ADDITIVE = ( 1 << 7 ),
	MATERIAL_VAR_ALPHATEST = ( 1 << 8 ),
	//	MATERIAL_VAR_UNUSED					  = (1 << 9),
	MATERIAL_VAR_ZNEARER = ( 1 << 10 ),
	MATERIAL_VAR_MODEL = ( 1 << 11 ),
	MATERIAL_VAR_FLAT = ( 1 << 12 ),
	MATERIAL_VAR_NOCULL = ( 1 << 13 ),
	MATERIAL_VAR_NOFOG = ( 1 << 14 ),
	MATERIAL_VAR_IGNOREZ = ( 1 << 15 ),
	MATERIAL_VAR_DECAL = ( 1 << 16 ),
	MATERIAL_VAR_ENVMAPSPHERE = ( 1 << 17 ), // OBSOLETE
	//	MATERIAL_VAR_UNUSED					  = (1 << 18),
	MATERIAL_VAR_ENVMAPCAMERASPACE = ( 1 << 19 ), // OBSOLETE
	MATERIAL_VAR_BASEALPHAENVMAPMASK = ( 1 << 20 ),
	MATERIAL_VAR_TRANSLUCENT = ( 1 << 21 ),
	MATERIAL_VAR_NORMALMAPALPHAENVMAPMASK = ( 1 << 22 ),
	MATERIAL_VAR_NEEDS_SOFTWARE_SKINNING = ( 1 << 23 ), // OBSOLETE
	MATERIAL_VAR_OPAQUETEXTURE = ( 1 << 24 ),
	MATERIAL_VAR_ENVMAPMODE = ( 1 << 25 ), // OBSOLETE
	MATERIAL_VAR_SUPPRESS_DECALS = ( 1 << 26 ),
	MATERIAL_VAR_HALFLAMBERT = ( 1 << 27 ),
	MATERIAL_VAR_WIREFRAME = ( 1 << 28 ),
	MATERIAL_VAR_ALLOWALPHATOCOVERAGE = ( 1 << 29 ),
	MATERIAL_VAR_ALPHA_MODIFIED_BY_PROXY = ( 1 << 30 ),
	MATERIAL_VAR_VERTEXFOG = ( 1 << 31 ),

	// NOTE: Only add flags here that either should be read from
	// .vmts or can be set directly from client code. Other, internal
	// flags should to into the flag enum in IMaterialInternal.h
};

enum PreviewImageRetVal_t
{
	MATERIAL_PREVIEW_IMAGE_BAD = 0,
	MATERIAL_PREVIEW_IMAGE_OK,
	MATERIAL_NO_PREVIEW_IMAGE,
};

enum ImageFormat {
	IMAGE_FORMAT_UNKNOWN = -1,
	IMAGE_FORMAT_RGBA8888 = 0,
	IMAGE_FORMAT_ABGR8888,
	IMAGE_FORMAT_RGB888,
	IMAGE_FORMAT_BGR888,
	IMAGE_FORMAT_RGB565,
	IMAGE_FORMAT_I8,
	IMAGE_FORMAT_IA88,
	IMAGE_FORMAT_P8,
	IMAGE_FORMAT_A8,
	IMAGE_FORMAT_RGB888_BLUESCREEN,
	IMAGE_FORMAT_BGR888_BLUESCREEN,
	IMAGE_FORMAT_ARGB8888,
	IMAGE_FORMAT_BGRA8888,
	IMAGE_FORMAT_DXT1,
	IMAGE_FORMAT_DXT3,
	IMAGE_FORMAT_DXT5,
	IMAGE_FORMAT_BGRX8888,
	IMAGE_FORMAT_BGR565,
	IMAGE_FORMAT_BGRX5551,
	IMAGE_FORMAT_BGRA4444,
	IMAGE_FORMAT_DXT1_ONEBITALPHA,
	IMAGE_FORMAT_BGRA5551,
	IMAGE_FORMAT_UV88,
	IMAGE_FORMAT_UVWQ8888,
	IMAGE_FORMAT_RGBA16161616F,
	IMAGE_FORMAT_RGBA16161616,
	IMAGE_FORMAT_UVLX8888,
	IMAGE_FORMAT_R32F,            // Single-channel 32-bit floating point
	IMAGE_FORMAT_RGB323232F,    // NOTE: D3D9 does not have this format
	IMAGE_FORMAT_RGBA32323232F,
	IMAGE_FORMAT_RG1616F,
	IMAGE_FORMAT_RG3232F,
	IMAGE_FORMAT_RGBX8888,

	IMAGE_FORMAT_NULL,            // Dummy format which takes no video memory

	// Compressed normal map formats
	IMAGE_FORMAT_ATI2N,            // One-surface ATI2N / DXN format
	IMAGE_FORMAT_ATI1N,            // Two-surface ATI1N format

	IMAGE_FORMAT_RGBA1010102,    // 10 bit-per component render targets
	IMAGE_FORMAT_BGRA1010102,
	IMAGE_FORMAT_R16F,            // 16 bit FP format

	// Depth-stencil texture formats
	IMAGE_FORMAT_D16,
	IMAGE_FORMAT_D15S1,
	IMAGE_FORMAT_D32,
	IMAGE_FORMAT_D24S8,
	IMAGE_FORMAT_LINEAR_D24S8,
	IMAGE_FORMAT_D24X8,
	IMAGE_FORMAT_D24X4S4,
	IMAGE_FORMAT_D24FS8,
	IMAGE_FORMAT_D16_SHADOW,    // Specific formats for shadow mapping
	IMAGE_FORMAT_D24X8_SHADOW,    // Specific formats for shadow mapping

	// supporting these specific formats as non-tiled for procedural cpu access (360-specific)
	IMAGE_FORMAT_LINEAR_BGRX8888,
	IMAGE_FORMAT_LINEAR_RGBA8888,
	IMAGE_FORMAT_LINEAR_ABGR8888,
	IMAGE_FORMAT_LINEAR_ARGB8888,
	IMAGE_FORMAT_LINEAR_BGRA8888,
	IMAGE_FORMAT_LINEAR_RGB888,
	IMAGE_FORMAT_LINEAR_BGR888,
	IMAGE_FORMAT_LINEAR_BGRX5551,
	IMAGE_FORMAT_LINEAR_I8,
	IMAGE_FORMAT_LINEAR_RGBA16161616,

	IMAGE_FORMAT_LE_BGRX8888,
	IMAGE_FORMAT_LE_BGRA8888,

	NUM_IMAGE_FORMATS
};

enum MaterialPropertyTypes_t
{
	MATERIAL_PROPERTY_NEEDS_LIGHTMAP = 0,					// bool
	MATERIAL_PROPERTY_OPACITY,								// int (enum MaterialPropertyOpacityTypes_t)
	MATERIAL_PROPERTY_REFLECTIVITY,							// vec3_t
	MATERIAL_PROPERTY_NEEDS_BUMPED_LIGHTMAPS				// bool
};

class IMaterial
{
public:
	const char* GetName()
	{
		typedef const char* (* oGetName)(void*);
		return getvfunc<oGetName>(this, 0)(this);
	}

	const char* GetTextureGroupName()
	{
		typedef const char* (* oGetTextureGroupName)(void*);
		return getvfunc<oGetTextureGroupName>(this, 1)(this);
	}

	void AlphaModulate(float alpha)
	{
		typedef void (* oAlphaModulate)(void*, float);
		return getvfunc<oAlphaModulate>(this, 27)(this, alpha);
	}

	void ColorModulate(float r, float g, float b)
	{
		typedef void (* oColorModulate)(void*, float, float, float);
		return getvfunc<oColorModulate>(this, 28)(this, r, g, b);
	}

	void ColorModulate(Color color)
	{
		typedef void (* oColorModulate)(void*, float, float, float);
		return getvfunc<oColorModulate>(this, 28)(this, color.r / 255.0f, color.g / 255.0f, color.b / 255.0f);
	}

	void ColorModulate(ImColor color)
	{
		typedef void (* oColorModulate)(void*, float, float, float);
		return getvfunc<oColorModulate>(this, 28)(this, color.Value.x, color.Value.y, color.Value.z);
	}

	void SetMaterialVarFlag(MaterialVarFlags_t flag, bool on)
	{
		typedef void (* oSetMaterialVarFlag)(void*, MaterialVarFlags_t, bool);
		return getvfunc<oSetMaterialVarFlag>(this, 29)(this, flag, on);
	}

	float GetAlphaModulation()
	{
		typedef float (* oGetAlphaModulation)(void*);
		return getvfunc<oGetAlphaModulation>(this, 44)(this);
	}

	void GetColorModulate(float *r, float *g, float *b)
	{
		typedef void (* oGetColorModulate)(void*, float*, float*, float*);
		return getvfunc<oGetColorModulate>(this, 45)(this, r, g, b);
	}
};