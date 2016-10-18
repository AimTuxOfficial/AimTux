#ifndef __IENGINETRACE_H
#define __IENGINETRACE_H

enum TraceType_t
{
	TRACE_EVERYTHING = 0,
	TRACE_WORLD_ONLY,
	TRACE_ENTITIES_ONLY,
	TRACE_EVERYTHING_FILTER_PROPS,
};

struct cplane_t
{
	Vector normal;
	float dist;
	unsigned char type;
	unsigned char signbits;
	unsigned char pad[2];
};

struct csurface_t
{
	const char* name;
	short surfaceProps;
	unsigned short flags;
};

struct trace_t
{
	Vector startpos;
	Vector endpos;
	cplane_t plane;

	float fraction;

	int contents;
	unsigned int dispFlags;

	bool allsolid;
	bool startsolid;

	float fractionleftsolid;

	csurface_t surface;

	int hitgroup;
	short physicsbone;

	unsigned short worldSurfaceIndex;
	C_BaseEntity* m_pEntityHit;
	int hitbox;
};

struct Ray_t
{
	VectorAligned m_Start;
	VectorAligned m_Delta;
	VectorAligned m_StartOffset;
	VectorAligned m_Extents;

	const matrix3x4_t* m_pWorldAxisTransform;

	bool m_IsRay;
	bool m_IsSwept;

	Ray_t() : m_pWorldAxisTransform(NULL) { }

	void Init(Vector vecStart, Vector vecEnd)
	{
		m_Delta = vecEnd - vecStart;

		m_IsSwept = (m_Delta.LengthSqr() != 0);

		m_Extents.x = m_Extents.y = m_Extents.z = 0.0f;

		m_pWorldAxisTransform = NULL;

		m_IsRay = true;

		m_StartOffset.x = m_StartOffset.y = m_StartOffset.z = 0.0f;

		m_Start = vecStart;
	}
};

class ITraceFilter
{
public:
	virtual bool ShouldHitEntity(C_BaseEntity *pEntity, int contentsMask) = 0;
	virtual TraceType_t GetTraceType() const = 0;
};

class CTraceFilter : public ITraceFilter
{
public:
	bool ShouldHitEntity(C_BaseEntity* pEntityHandle, int contentsMask)
	{
		return !(pEntityHandle == pSkip);
	}

	virtual TraceType_t GetTraceType() const
	{
		return TRACE_EVERYTHING;
	}

	void* pSkip;
};

class IEngineTrace
{
public:
	void TraceRay(const Ray_t &ray, unsigned int fMask, CTraceFilter *pTraceFilter, trace_t *pTrace)
	{
		typedef void (* oTraceRay)(void*, const Ray_t&, unsigned int, CTraceFilter *, trace_t*);
		getvfunc<oTraceRay>(this, 5)(this, ray, fMask, pTraceFilter, pTrace);
	}
	
	int	GetPointContents(const Vector &vecAbsPosition, int contentsMask = MASK_ALL, IHandleEntity** ppEntity = NULL)
	{
		typedef int (* oGetPointContents)(void*, const Vector &vecAbsPosition, int contentsMask, IHandleEntity** ppEntity);
		getvfunc<oGetPointContents>(this, 1)(this, vecAbsPosition, contentsMask, ppEntity);
	}
};

#endif
