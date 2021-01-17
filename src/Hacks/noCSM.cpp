#include "noCSM.h"

#include "../settings.h"
#include "../interfaces.h"

void NoCSM::CreateMove(CUserCmd* cmd)
{
    cl_csm_enabled->SetValue( !Settings::NoCSM::enabled );
}