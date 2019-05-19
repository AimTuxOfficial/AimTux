#include "hooks.h"

#include "../interfaces.h"

#include "../Hacks/grenadeprediction.h"

std::queue<RenderView::RenderRequest> RenderView::renderQueue;

static void RenderQueue() {
	IMatRenderContext* renderCtx;

	if ( RenderView::renderQueue.empty() )
		return;

	renderCtx = material->GetRenderContext();
	if ( !renderCtx ) {
		return;
	}

	while ( !RenderView::renderQueue.empty() ) {
		RenderView::RenderRequest req = RenderView::renderQueue.front();
		renderCtx->DrawScreenSpaceRectangle( req.mat, req.destX, req.destY, req.width, req.height,
											 0.0f, 0.0f, float( req.width ), float( req.height ),
											 req.tex->GetActualWidth(), req.tex->GetActualHeight(),
											 NULL, 1, 1 );

		RenderView::renderQueue.pop();
	}
	renderCtx->Release();
}

void Hooks::RenderView(void* thisptr, CViewSetup& setup, CViewSetup& hudViewSetup, unsigned int nClearFlags, int whatToDraw)
{
    GrenadePrediction::RenderView( thisptr, setup, hudViewSetup, nClearFlags, whatToDraw );
	viewRenderVMT->GetOriginalMethod<RenderViewFn>(6)(thisptr, setup, hudViewSetup, nClearFlags, whatToDraw);

    // The Idea behind this is let the game render the original scene last
    // so that it can leave the view matrix in a clean state for when we Paint UI.
    // The RenderView functions will Render what they want, add the image to the queue, and then here we draw.
    RenderQueue();
}