#include "disablepostprocessing.h"

bool Settings::DisablePostProcessing::enabled = false;

void DisablePostProcessing::BeginFrame()
{
	*s_bOverridePostProcessingDisable = Settings::DisablePostProcessing::enabled;
}
