#include "thirdperson.h"

#include "../settings.h"
#include "../interfaces.h"

bool Settings::ThirdPerson::enabled = false;
float Settings::ThirdPerson::distance = 30.f;

void ThirdPerson::OverrideView(CViewSetup *pSetup)
{
	if (!Settings::ThirdPerson::enabled) {
		input->m_fCameraInThirdPerson = false;
		return;
	}

	C_BasePlayer *localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
	if(!localplayer || !localplayer->GetAlive())
		return;

	QAngle *view = localplayer->GetVAngles();
	trace_t tr;
	Ray_t ray;

	Vector desiredCamOffset = Vector(cos(DEG2RAD(view->y)) * Settings::ThirdPerson::distance,
								  sin(DEG2RAD(view->y)) * Settings::ThirdPerson::distance,
								  sin(DEG2RAD(-view->x)) * Settings::ThirdPerson::distance
							);

	//cast a ray from the Current camera Origin to the Desired 3rd person Camera origin
	ray.Init(localplayer->GetEyePosition(), (localplayer->GetEyePosition() - desiredCamOffset));
	CTraceFilter traceFilter;
	traceFilter.pSkip = localplayer;
	trace->TraceRay(ray, MASK_SHOT, &traceFilter, &tr);

	Vector diff = localplayer->GetEyePosition() - tr.endpos;

	float distance2D = diff.Length2D();

	bool horOK = distance2D > (Settings::ThirdPerson::distance - 2.0f);
	bool vertOK = (abs(diff.z) - abs(desiredCamOffset.z) < 3.0f);

	float cameraDistance;

	if( horOK && vertOK )  // If we are clear of obstacles
	{
		cameraDistance= Settings::ThirdPerson::distance; // go ahead and set the distance to the setting
	}
	else
	{
		if( vertOK ) // if the Vertical Axis is OK
		{
			cameraDistance = distance2D * 0.95f;
		}
		else// otherwise we need to move closer to not go into the floor/ceiling
		{
			cameraDistance = abs(diff.z) * 0.95f;
		}
	}
	cvar->ConsoleDPrintf("Input @ %p\n", (void*)input);
	input->m_fCameraInThirdPerson = true;
	input->m_vecCameraOffset.z = cameraDistance;
/*
	Vector temp = Vector(cos(DEG2RAD(view.y)) * Settings::ThirdPerson::distance,
						 sin(DEG2RAD(view.y)) * Settings::ThirdPerson::distance,
						 -view.x );

	pSetup->origin -= temp;

*/

}

