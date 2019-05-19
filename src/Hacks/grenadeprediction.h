#pragma once
#include "../Hooks/hooks.h"

#include "../SDK/CViewRender.h"
#include "../SDK/IInputSystem.h"

namespace GrenadePrediction
{
    extern float cameraHeight;
    // Hooks
    void OverrideView( CViewSetup* pSetup );
    void Paint();
    void RenderView( void* thisptr, CViewSetup& setup, CViewSetup& hudViewSetup, unsigned int nClearFlags, int whatToDraw );
    void CreateMove( CUserCmd *cmd ); // For not allowing Jumps via Scroll wheel
}