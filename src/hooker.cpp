#include "hooker.h"

bool* bSendPacket = nullptr;
int* nPredictionRandomSeed = nullptr;
CMoveData* g_MoveData = nullptr;
bool* s_bOverridePostProcessingDisable = nullptr;
uint8_t* CrosshairWeaponTypeCheck = nullptr;
uint8_t* CamThinkSvCheatsCheck = nullptr;

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

//RandomSeedFn RandomSeed;
//RandomFloatFn RandomFloat;
//RandomFloatExpFn RandomFloatExp;
//RandomIntFn RandomInt;
//RandomGaussianFloatFn RandomGaussianFloat;

SetNamedSkyBoxFn SetNamedSkyBox;

std::vector<dlinfo_t> libraries;

// taken form aixxe's cstrike-basehook-linux
bool Hooker::GetLibraryInformation(const char* library, uintptr_t* address, size_t* size) {
	if (libraries.size() == 0) {
		dl_iterate_phdr([] (struct dl_phdr_info* info, size_t, void*) {
			dlinfo_t library_info = {};

			library_info.library = info->dlpi_name;
			library_info.address = info->dlpi_addr + info->dlpi_phdr[0].p_vaddr;
			library_info.size = info->dlpi_phdr[0].p_memsz;

			libraries.push_back(library_info);

			return 0;
		}, nullptr);
	}

	for (const dlinfo_t& current: libraries) {
		if (!strcasestr(current.library, library))
			continue;

		if (address)
			*address = current.address;

		if (size)
			*size = current.size;

		return true;
	}

	return false;
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
	// Recursion is a meme, stick to reddit mcswaggens.
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
	uintptr_t instruction_addr = PatternFinder::FindPatternInModule(XORSTR("client_client.so"),
																	(unsigned char*) XORSTR("\xE8\x00\x00\x00\x00\x48\x8B\x3D\x00\x00\x00\x00\xBE\x01\x00\x00\x00\xC7"),
																	XORSTR("x????xxx????xxxxxx"));

	glowManager = reinterpret_cast<GlowObjectManagerFn>(GetAbsoluteAddress(instruction_addr, 1, 5))();
}

void Hooker::FindPlayerResource()
{
	uintptr_t instruction_addr = PatternFinder::FindPatternInModule(XORSTR("client_client.so"),
																	(unsigned char*) XORSTR("\x48\x8B\x05\x00\x00\x00\x00\x55\x48\x89\xE5\x48\x85\xC0\x74\x10\x48"),
																	XORSTR("xxx????xxxxxxxxxx"));

	csPlayerResource = reinterpret_cast<C_CSPlayerResource**>(GetAbsoluteAddress(instruction_addr, 3, 7));
}

void Hooker::FindGameRules()
{
	uintptr_t instruction_addr = PatternFinder::FindPatternInModule(XORSTR("client_client.so"),
																	(unsigned char*) XORSTR("\x48\x8B\x05\x00\x00\x00\x00\x48\x8B\x00\x0F\x84\xA1\x01"),
																	XORSTR("xxx????xx?xxxx"));

	csGameRules = *reinterpret_cast<C_CSGameRules***>(GetAbsoluteAddress(instruction_addr, 3, 7));
}

void Hooker::FindRankReveal()
{
	uintptr_t func_address = PatternFinder::FindPatternInModule(XORSTR("client_client.so"),
																(unsigned char*) XORSTR("\x55\x48\x89\xE5\x53\x48\x89\xFB\x48\x83\xEC\x08\xE8\x00\x00\x00\x00\x48\x8D\x00\x00\x00\x00\x00\x48\x8B\x10\x48\x89\xC7\xFF\x52\x28"),
																XORSTR("xxxxxxxxxxxxx????xx?????xxxxxxxxx"));

	MsgFunc_ServerRankRevealAll = reinterpret_cast<MsgFunc_ServerRankRevealAllFn>(func_address);
}

void Hooker::FindSendClanTag()
{
	uintptr_t func_address = PatternFinder::FindPatternInModule(XORSTR("engine_client.so"),
																(unsigned char*) XORSTR( "\x55\x48\x89\xE5\x48\x89\x5D\xE8\x4C\x89\x65\xF0\x49\x89\xFC\xBF\x48\x00\x00\x00\x4C\x89\x6D\xF8\x48\x83\xEC\x20\x49"),
																XORSTR("xxxxxxxxxxxxxxxxxxxxxxxxxxxxx"));

	SendClanTag = reinterpret_cast<SendClanTagFn>(func_address);
}

void Hooker::FindViewRender()
{
	uintptr_t func_address = PatternFinder::FindPatternInModule(XORSTR("client_client.so"),
																(unsigned char*) XORSTR("\xB8\xFF\xFF\x7F\x7F\x31\xD2\x55\x89\x05\x00\x00\x00\x00\x48\x8D\x3D\x00\x00\x00\x00"),
																XORSTR("xxxxxxxxxx????xxx????"));

	viewRender = reinterpret_cast<CViewRender*>(GetAbsoluteAddress(func_address + 14, 3, 7));
}

void Hooker::FindSendPacket()
{
	uintptr_t bool_address = PatternFinder::FindPatternInModule(XORSTR("engine_client.so"),
																(unsigned char*) XORSTR("\x41\xBD\x01\x00\x00\x00\xE9\x2A\xFE"),
																XORSTR("xxx???xxx"));
	bool_address = GetAbsoluteAddress(bool_address, 2, 1);

	bSendPacket = reinterpret_cast<bool*>(bool_address);
	Util::ProtectAddr(bSendPacket, PROT_READ | PROT_WRITE | PROT_EXEC);
}

void Hooker::FindPrediction()
{
	uintptr_t seed_instruction_addr = PatternFinder::FindPatternInModule(XORSTR("client_client.so"),
																		 (unsigned char*) XORSTR("\x48\x8B\x05\x00\x00\x00\x00\xF3\x0F\x11\x45\xDC\xF3"),
																		 XORSTR("xxx????xxxxxx"));
	uintptr_t helper_instruction_addr = PatternFinder::FindPatternInModule(XORSTR("client_client.so"),
																		   (unsigned char*) XORSTR("\x00\x48\x89\x3D\x00\x00\x00\x00\xC3"),
																		   XORSTR("xxxx????x"));
	uintptr_t movedata_instruction_addr = PatternFinder::FindPatternInModule(XORSTR("client_client.so"),
																			 (unsigned char*) XORSTR("\x48\x8B\x0D\x00\x00\x00\x00\x4C\x89\xF2"),
																			 XORSTR("xxx????xxx"));

	nPredictionRandomSeed = *reinterpret_cast<int**>(GetAbsoluteAddress(seed_instruction_addr, 3, 7));
	moveHelper = *reinterpret_cast<IMoveHelper**>(GetAbsoluteAddress(helper_instruction_addr + 1, 3, 7));
	g_MoveData = **reinterpret_cast<CMoveData***>(GetAbsoluteAddress(movedata_instruction_addr, 3, 7));
}

void Hooker::FindIsReadyCallback()
{
	uintptr_t func_address = PatternFinder::FindPatternInModule(XORSTR("client_client.so"),
																(unsigned char*) XORSTR("\x48\x83\x3D\x00\x00\x00\x00\x00\x55\x48\x89\xE5\x41"),
																XORSTR("xxx????xxxxxx"));

	IsReadyCallback = reinterpret_cast<IsReadyCallbackFn>(func_address);
}

void Hooker::FindSurfaceDrawing()
{
	uintptr_t start_func_address = PatternFinder::FindPatternInModule(XORSTR("vguimatsurface_client.so"),
																	  (unsigned char*) XORSTR("\x55\x48\x89\xE5\x53\x48\x89\xFB\x48\x83\xEC\x28\x80"),
																	  XORSTR("xxxxxxxxxxxxx"));
	StartDrawing = reinterpret_cast<StartDrawingFn>(start_func_address);

	uintptr_t finish_func_address = PatternFinder::FindPatternInModule(XORSTR("vguimatsurface_client.so"),
																	   (unsigned char*) XORSTR("\x55\x31\xFF\x48\x89"),
																	   XORSTR("xxxxx"));
	FinishDrawing = reinterpret_cast<FinishDrawingFn>(finish_func_address);
}

void Hooker::FindGetLocalClient()
{
	uintptr_t GetLocalPlayer = reinterpret_cast<uintptr_t>(getvtable(engine)[12]);
	GetLocalClient = reinterpret_cast<GetLocalClientFn>(GetAbsoluteAddress(GetLocalPlayer + 9, 1, 5));
}

void Hooker::FindLineGoesThroughSmoke()
{
	uintptr_t func_address = PatternFinder::FindPatternInModule(XORSTR("client_client.so"),
																(unsigned char*) XORSTR("\x55\x40\x0F\xB6\xFF"),
																XORSTR("xxxxx"));
	LineGoesThroughSmoke = reinterpret_cast<LineGoesThroughSmokeFn>(func_address);
}

void Hooker::FindInitKeyValues()
{
	uintptr_t func_address = PatternFinder::FindPatternInModule(XORSTR("client_client.so"),
																(unsigned char*) XORSTR("\x81\x27\x00\x00\x00\xFF\x55\x48\x89\xE5\x5D"),
																XORSTR("xx???xxxxxx"));
	InitKeyValues = reinterpret_cast<InitKeyValuesFn>(func_address);
}

void Hooker::FindLoadFromBuffer()
{
	uintptr_t func_address = PatternFinder::FindPatternInModule(XORSTR("client_client.so"),
																(unsigned char*) XORSTR("\x55\x48\x89\xE5\x48\x89\x5D\xD8\x48\x89\xD3\x4C\x89\x65\xE0\x4D\x89\xCC"),
																XORSTR("xxxxxxxxxxxxxxxxxx"));
	LoadFromBuffer = reinterpret_cast<LoadFromBufferFn>(func_address);
}
/*
void Hooker::FindVstdlibFunctions()
{
	void* handle = dlopen(XORSTR("./bin/linux64/libvstdlib_client.so"), RTLD_NOLOAD | RTLD_NOW);

	RandomSeed = reinterpret_cast<RandomSeedFn>(dlsym(handle, XORSTR("RandomSeed")));
	RandomFloat = reinterpret_cast<RandomFloatFn>(dlsym(handle, XORSTR("RandomFloat")));
	RandomFloatExp = reinterpret_cast<RandomFloatExpFn>(dlsym(handle, XORSTR("RandomFloatExp")));
	RandomInt = reinterpret_cast<RandomIntFn>(dlsym(handle, XORSTR("RandomInt")));
	RandomGaussianFloat = reinterpret_cast<RandomGaussianFloatFn>(dlsym(handle, XORSTR("RandomGaussianFloat")));

	dlclose(handle);
}
 */

void Hooker::FindOverridePostProcessingDisable()
{
	uintptr_t bool_address = PatternFinder::FindPatternInModule(XORSTR("client_client.so"),
																(unsigned char*) XORSTR("\x80\x3D\x00\x00\x00\x00\x00\x0F\x85\x00\x00\x00\x00\x85\xC9"),
																XORSTR("xx????xxx????xx"));
	bool_address = GetAbsoluteAddress(bool_address, 2, 7);

	s_bOverridePostProcessingDisable = reinterpret_cast<bool*>(bool_address);
}

void Hooker::FindCrosshairWeaponTypeCheck()
{
	uintptr_t byte_address = PatternFinder::FindPatternInModule(XORSTR("client_client.so"),
																(unsigned char*) XORSTR("\x83\xF8\x05\x0F\x84\x00\x00\x00\x00\x49\x8B\x07"),
																XORSTR("xxxxx????xxx"));

	CrosshairWeaponTypeCheck = reinterpret_cast<uint8_t*>(byte_address + 2);
	Util::ProtectAddr(CrosshairWeaponTypeCheck, PROT_READ | PROT_WRITE | PROT_EXEC);
}

void Hooker::FindCamThinkSvCheatsCheck()
{
	uintptr_t byte_address = PatternFinder::FindPatternInModule(XORSTR("client_client.so"),
																(unsigned char*) XORSTR("\x74\x00\x49\x83\x00\x00\x00\x00\x00\x00\x00\x0F\x84\x00\x00\x00\x00\x49\x8B"),
																XORSTR("x?xx??????xxx????xx"));

	CamThinkSvCheatsCheck = reinterpret_cast<uint8_t*>(byte_address);

	for (ptrdiff_t off = 0; off < 0x2; off++)
		Util::ProtectAddr(CamThinkSvCheatsCheck + off, PROT_READ | PROT_WRITE | PROT_EXEC);
}

void Hooker::HookSwapWindow()
{
	uintptr_t swapwindowFn = reinterpret_cast<uintptr_t>(dlsym(RTLD_NEXT, XORSTR("SDL_GL_SwapWindow")));
	swapWindowJumpAddress = reinterpret_cast<uintptr_t*>(GetAbsoluteAddress(swapwindowFn, 3, 7));
	oSwapWindow = *swapWindowJumpAddress;
	*swapWindowJumpAddress = reinterpret_cast<uintptr_t>(&SDL2::SwapWindow);
}

void Hooker::HookPollEvent()
{
	uintptr_t polleventFn = reinterpret_cast<uintptr_t>(dlsym(RTLD_NEXT, XORSTR("SDL_PollEvent")));
	polleventJumpAddress = reinterpret_cast<uintptr_t*>(GetAbsoluteAddress(polleventFn, 3, 7));
	oPollEvent = *polleventJumpAddress;
	*polleventJumpAddress = reinterpret_cast<uintptr_t>(&SDL2::PollEvent);
}

void Hooker::FindSDLInput()
{
	uintptr_t func_address = PatternFinder::FindPatternInModule(XORSTR("launcher_client.so"),
																(unsigned char*) XORSTR("\x55\x48\x89\xE5\x53\x48\x83\xEC\x18"),
																XORSTR("xxxxxxxxx"));

	launcherMgr = reinterpret_cast<ILauncherMgrCreateFn>(func_address)();
}

void Hooker::FindSetNamedSkybox()
{
	uintptr_t func_address = PatternFinder::FindPatternInModule(XORSTR("engine_client.so"),
																(unsigned char*) XORSTR("\x55\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x48\x89\xE5\x41\x55\x41\x54\x49\x89\xFD"),
																XORSTR("x??????????????xxxxxxxxxx"));

	SetNamedSkyBox = reinterpret_cast<SetNamedSkyBoxFn>(func_address);
}
