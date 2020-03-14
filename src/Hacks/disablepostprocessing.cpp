#include "disablepostprocessing.h"

#include "../settings.h"
#include "../interfaces.h"

void DisablePostProcessing::BeginFrame()
{
	*s_bOverridePostProcessingDisable = Settings::DisablePostProcessing::enabled;
}
