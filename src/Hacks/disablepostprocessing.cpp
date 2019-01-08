#include "disablepostprocessing.h"

#include "../settings.h"
#include "../interfaces.h"

bool Settings::DisablePostProcessing::enabled = false;

void DisablePostProcessing::BeginFrame()
{
	*s_bOverridePostProcessingDisable = Settings::DisablePostProcessing::enabled;
}
