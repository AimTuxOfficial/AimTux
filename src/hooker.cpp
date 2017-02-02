#include "hooker.h"

bool* bSendPacket = nullptr;
int* nPredictionRandomSeed = nullptr;
CMoveData* g_MoveData = nullptr;

VMT* panelVMT = nullptr;
VMT* clientVMT = nullptr;
VMT* modelRenderVMT = nullptr;
VMT* clientModeVMT = nullptr;
VMT* gameEventsVMT = nullptr;
VMT* viewRenderVMT = nullptr;
VMT* inputInternalVMT = nullptr;
VMT* materialVMT = nullptr;
VMT* surfaceVMT = nullptr;
VMT* launcherMgrVMT = nullptr;
VMT* engineVGuiVMT = nullptr;
VMT* soundVMT = nullptr;

uintptr_t* GetCSWpnData_address = nullptr;

uintptr_t oSwapWindow;
uintptr_t* swapWindowJumpAddress = nullptr;

uintptr_t oPollEvent;
uintptr_t* polleventJumpAddress = nullptr;

MsgFunc_ServerRankRevealAllFn MsgFunc_ServerRankRevealAll;
SendClanTagFn SendClanTag;
IsReadyCallbackFn IsReadyCallback;

RecvVarProxyFn fnSequenceProxyFn;

StartDrawingFn StartDrawing;
FinishDrawingFn FinishDrawing;

GetLocalClientFn GetLocalClient;

LineGoesThroughSmokeFn LineGoesThroughSmoke;
InitKeyValuesFn InitKeyValues;
LoadFromBufferFn LoadFromBuffer;

std::unordered_map<const char*, uintptr_t> Hooker::GetProcessLibraries()
{
	std::unordered_map<const char*, uintptr_t> modules;

	dl_iterate_phdr([](struct dl_phdr_info* info, size_t size, void* data) {
		reinterpret_cast<std::unordered_map<const char*, uintptr_t>*>(data)->insert({ info->dlpi_name, reinterpret_cast<uintptr_t>(info->dlpi_addr + info->dlpi_phdr[0].p_vaddr) });
		return 0;
	}, &modules);

	return modules;
}

uintptr_t Hooker::GetLibraryAddress(const char* moduleName)
{
	std::unordered_map<const char*, uintptr_t> modules = GetProcessLibraries();

	for (auto module : modules)
		if (strcasestr(module.first, moduleName))
			return module.second;

	return 0;
}

void Hooker::InitializeVMHooks()
{
	panelVMT = new VMT(panel);
	clientVMT = new VMT(client);
	modelRenderVMT = new VMT(modelRender);
	gameEventsVMT = new VMT(gameEvents);
	viewRenderVMT = new VMT(viewRender);
	inputInternalVMT = new VMT(inputInternal);
	materialVMT = new VMT(material);
	surfaceVMT = new VMT(surface);
	launcherMgrVMT = new VMT(launcherMgr);
	engineVGuiVMT = new VMT(engineVGui);
	soundVMT = new VMT(sound);
}

bool Hooker::HookRecvProp(const char* className, const char* propertyName, std::unique_ptr<RecvPropHook>& recvPropHook)
{
	// FIXME: Does not search recursively.. yet.
	for (ClientClass* pClass = client->GetAllClasses(); pClass; pClass = pClass->m_pNext)
	{
		if (strcmp(pClass->m_pNetworkName, className) == 0)
		{
			RecvTable* pClassTable = pClass->m_pRecvTable;

			for (int nIndex = 0; nIndex < pClassTable->m_nProps; nIndex++)
			{
				RecvProp* pProp = &pClassTable->m_pProps[nIndex];

				if (!pProp || strcmp(pProp->m_pVarName, propertyName) != 0)
					continue;

				recvPropHook = std::make_unique<RecvPropHook>(pProp);

				return true;
			}

			break;
		}
	}

	return false;
}

void Hooker::FindIClientMode()
{
	uintptr_t hudprocessinput = reinterpret_cast<uintptr_t>(getvtable(client)[10]);
	GetClientModeFn GetClientMode = reinterpret_cast<GetClientModeFn>(GetAbsoluteAddress(hudprocessinput + 11, 1, 5));

	clientMode = GetClientMode();
	clientModeVMT = new VMT(clientMode);
}

void Hooker::FindGlobalVars()
{
	uintptr_t HudUpdate = reinterpret_cast<uintptr_t>(getvtable(client)[11]);
	globalVars = *reinterpret_cast<CGlobalVars**>(GetAbsoluteAddress(HudUpdate + 13, 3, 7));
}

void Hooker::FindCInput()
{
	uintptr_t IN_ActivateMouse = reinterpret_cast<uintptr_t>(getvtable(client)[15]);
	input = **reinterpret_cast<CInput***>(GetAbsoluteAddress(IN_ActivateMouse, 3, 7));
}

void Hooker::FindGlowManager()
{
	uintptr_t instruction_addr = FindPattern(GetLibraryAddress("client_client.so"), 0xFFFFFFFFF, (unsigned char*) GLOWOBJECT_SIGNATURE, GLOWOBJECT_MASK);

	glowManager = reinterpret_cast<GlowObjectManagerFn>(GetAbsoluteAddress(instruction_addr, 1, 5))();
}

void Hooker::FindPlayerResource()
{
	uintptr_t instruction_addr = FindPattern(GetLibraryAddress("client_client.so"), 0xFFFFFFFFF, (unsigned char*) PLAYERRESOURCES_SIGNATURE, PLAYERRESOURCES_MASK);

	csPlayerResource = reinterpret_cast<C_CSPlayerResource**>(GetAbsoluteAddress(instruction_addr, 3, 7));
}

void Hooker::FindGameRules()
{
	uintptr_t instruction_addr = FindPattern(GetLibraryAddress("client_client.so"), 0xFFFFFFFFF, (unsigned char*) GAMERULES_SIGNATURE, GAMERULES_MASK);

	csGameRules = *reinterpret_cast<C_CSGameRules***>(GetAbsoluteAddress(instruction_addr, 3, 7));
}

void Hooker::FindRankReveal()
{
	uintptr_t func_address = FindPattern(GetLibraryAddress("client_client.so"), 0xFFFFFFFFF, (unsigned char*) MSGFUNC_SERVERRANKREVEALALL_SIGNATURE, MSGFUNC_SERVERRANKREVEALALL_MASK);

	MsgFunc_ServerRankRevealAll = reinterpret_cast<MsgFunc_ServerRankRevealAllFn>(func_address);
}

void Hooker::FindSendClanTag()
{
	uintptr_t func_address = FindPattern(GetLibraryAddress("engine_client.so"), 0xFFFFFFFFF, (unsigned char*) SENDCLANTAG_SIGNATURE, SENDCLANTAG_MASK);

	SendClanTag = reinterpret_cast<SendClanTagFn>(func_address);
}

void Hooker::FindViewRender()
{
	uintptr_t func_address = FindPattern(GetLibraryAddress("client_client.so"), 0xFFFFFFFFF, (unsigned char*) VIEWRENDER_SIGNATURE, VIEWRENDER_MASK);

	viewRender = reinterpret_cast<CViewRender*>(GetAbsoluteAddress(func_address + 14, 3, 7));
}

void Hooker::FindSendPacket()
{
	uintptr_t bool_address = FindPattern(GetLibraryAddress("engine_client.so"), 0xFFFFFFFFF, (unsigned char*) BSENDPACKET_SIGNATURE, BSENDPACKET_MASK);
	bool_address = GetAbsoluteAddress(bool_address, 2, 1);

	bSendPacket = reinterpret_cast<bool*>(bool_address);
	Util::ProtectAddr(bSendPacket, PROT_READ | PROT_WRITE | PROT_EXEC);
}

void Hooker::FindPrediction()
{
	uintptr_t seed_instruction_addr = FindPattern(GetLibraryAddress("client_client.so"), 0xFFFFFFFFF, (unsigned char*) PREDICTION_RANDOM_SEED_SIGNATURE, PREDICTION_RANDOM_SEED_MASK);
	uintptr_t helper_instruction_addr = FindPattern(GetLibraryAddress("client_client.so"), 0xFFFFFFFFF, (unsigned char*) CLIENT_MOVEHELPER_SIGNATURE, CLIENT_MOVEHELPER_MASK);
	uintptr_t movedata_instruction_addr = FindPattern(GetLibraryAddress("client_client.so"), 0xFFFFFFFFF, (unsigned char*) CLIENT_MOVEDATA_SIGNATURE, CLIENT_MOVEDATA_MASK);

	nPredictionRandomSeed = *reinterpret_cast<int**>(GetAbsoluteAddress(seed_instruction_addr, 3, 7));
	moveHelper = *reinterpret_cast<IMoveHelper**>(GetAbsoluteAddress(helper_instruction_addr + 1, 3, 7));
	g_MoveData = **reinterpret_cast<CMoveData***>(GetAbsoluteAddress(movedata_instruction_addr, 3, 7));
}

void Hooker::FindIsReadyCallback()
{
	uintptr_t func_address = FindPattern(GetLibraryAddress("client_client.so"), 0xFFFFFFFFF, (unsigned char*) ISREADY_CALLBACK_SIGNATURE, ISREADY_CALLBACK_MASK);

	IsReadyCallback = reinterpret_cast<IsReadyCallbackFn>(func_address);
}

void Hooker::FindSurfaceDrawing()
{
	uintptr_t start_func_address = FindPattern(GetLibraryAddress("vguimatsurface_client.so"), 0xFFFFFFFFF, (unsigned char*) CMATSYSTEMSURFACE_STARTDRAWING_SIGNATURE, CMATSYSTEMSURFACE_STARTDRAWING_MASK);
	StartDrawing = reinterpret_cast<StartDrawingFn>(start_func_address);

	uintptr_t finish_func_address = FindPattern(GetLibraryAddress("vguimatsurface_client.so"), 0xFFFFFFFFF, (unsigned char*) CMATSYSTEMSURFACE_FINISHDRAWING_SIGNATURE, CMATSYSTEMSURFACE_FINISHDRAWING_MASK);
	FinishDrawing = reinterpret_cast<FinishDrawingFn>(finish_func_address);
}

void Hooker::FindGetLocalClient()
{
	uintptr_t GetLocalPlayer = reinterpret_cast<uintptr_t>(getvtable(engine)[12]);
	GetLocalClient = reinterpret_cast<GetLocalClientFn>(GetAbsoluteAddress(GetLocalPlayer + 9, 1, 5));
}

void Hooker::FindLineGoesThroughSmoke()
{
	uintptr_t func_address = FindPattern(GetLibraryAddress("client_client.so"), 0xFFFFFFFFF, (unsigned char*) LINEGOESTHROUGHSMOKE_SIGNATURE, LINEGOESTHROUGHSMOKE_MASK);
	LineGoesThroughSmoke = reinterpret_cast<LineGoesThroughSmokeFn>(func_address);
}

void Hooker::FindInitKeyValues()
{
	uintptr_t func_address = FindPattern(GetLibraryAddress("client_client.so"), 0xFFFFFFFFF, (unsigned char*) INITKEYVALUES_SIGNATURE, INITKEYVALUES_MASK);
	InitKeyValues = reinterpret_cast<InitKeyValuesFn>(func_address);
}

void Hooker::FindLoadFromBuffer()
{
	uintptr_t func_address = FindPattern(GetLibraryAddress("client_client.so"), 0xFFFFFFFFF, (unsigned char*) LOADFROMBUFFER_SIGNATURE, LOADFROMBUFFER_MASK);
	LoadFromBuffer = reinterpret_cast<LoadFromBufferFn>(func_address);
}

void Hooker::FindGetCSWpnData()
{
	uintptr_t func_address = FindPattern(GetLibraryAddress("client_client.so"), 0xFFFFFFFFF, (unsigned char*) GETCSWPNDATA_SIGNATURE, GETCSWPNDATA_MASK);
	GetCSWpnData_address = reinterpret_cast<uintptr_t*>(func_address);
}

void Hooker::HookSwapWindow()
{
	uintptr_t swapwindowFn = reinterpret_cast<uintptr_t>(dlsym(RTLD_NEXT, "SDL_GL_SwapWindow"));
	swapWindowJumpAddress = reinterpret_cast<uintptr_t*>(GetAbsoluteAddress(swapwindowFn, 3, 7));
	oSwapWindow = *swapWindowJumpAddress;
	*swapWindowJumpAddress = reinterpret_cast<uintptr_t>(&SDL2::SwapWindow);
}

void Hooker::HookPollEvent()
{
	uintptr_t polleventFn = reinterpret_cast<uintptr_t>(dlsym(RTLD_NEXT, "SDL_PollEvent"));
	polleventJumpAddress = reinterpret_cast<uintptr_t*>(GetAbsoluteAddress(polleventFn, 3, 7));
	oPollEvent = *polleventJumpAddress;
	*polleventJumpAddress = reinterpret_cast<uintptr_t>(&SDL2::PollEvent);
}

void Hooker::FindSDLInput()
{
	uintptr_t func_address = FindPattern(GetLibraryAddress("launcher_client.so"), 0xFFFFFFFFF, (unsigned char*) GETSDLMGR_SIGNATURE, GETSDLMGR_MASK);

	launcherMgr = reinterpret_cast<ILauncherMgrCreateFn>(func_address)();
}
