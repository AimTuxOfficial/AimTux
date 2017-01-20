#include "hooker.h"

IBaseClientDLL* client = nullptr;
ISurface* surface = nullptr;
IVPanel* panel = nullptr;
IEngineClient* engine = nullptr;
IClientEntityList* entitylist = nullptr;
IVDebugOverlay* debugOverlay = nullptr;
IVModelInfo* modelInfo = nullptr;
IVModelRender* modelRender = nullptr;
IClientMode* clientMode = nullptr;
IEngineTrace* trace = nullptr;
IInputSystem* input = nullptr;
IInputInternal* inputInternal = nullptr;
IMaterialSystem* material = nullptr;
ICvar* cvar = nullptr;
CGlobalVars* globalvars = nullptr;
CEffects* effects = nullptr;
IGameEventManager2* gameevents = nullptr;
IPhysicsSurfaceProps* physics = nullptr;
CViewRender* viewrender = nullptr;
IPrediction* prediction = nullptr;
IGameMovement* gamemovement = nullptr;
IMoveHelper* movehelper = nullptr;
ILauncherMgr* launchermgr = nullptr;
CGlowObjectManager* glowmanager = nullptr;
C_CSPlayerResource** csPlayerResource = nullptr;
C_CSGameRules** csGameRules = nullptr;
IEngineVGui* enginevgui = nullptr;
IEngineSound* sound = nullptr;
ILocalize* localize = nullptr;
ICommandLine* commandline = nullptr;

VMT* panel_vmt = nullptr;
VMT* client_vmt = nullptr;
VMT* modelRender_vmt = nullptr;
VMT* clientMode_vmt = nullptr;
VMT* gameEvents_vmt = nullptr;
VMT* viewRender_vmt = nullptr;
VMT* inputInternal_vmt = nullptr;
VMT* material_vmt = nullptr;
VMT* surface_vmt = nullptr;
VMT* launchermgr_vmt = nullptr;
VMT* enginevgui_vmt = nullptr;
VMT* sound_vmt = nullptr;

bool* bSendPacket = nullptr;
int* nPredictionRandomSeed = nullptr;
CMoveData* g_MoveData = nullptr;

uintptr_t* GetCSWpnData_address = nullptr;

uintptr_t original_swap_window;
uintptr_t* swap_window_jump_address = nullptr;

uintptr_t original_pollevent;
uintptr_t* pollevent_jump_address = nullptr;

MsgFunc_ServerRankRevealAllFn MsgFunc_ServerRankRevealAll;
SendClanTagFn SendClanTag;
IsReadyCallbackFn IsReadyCallback;

RecvVarProxyFn fnSequenceProxyFn;

StartDrawingFn StartDrawing;
FinishDrawingFn FinishDrawing;

ForceFullUpdateFn ForceFullUpdate;
GetClientStateFn GetClientState;

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

void Hooker::FindInterfaces()
{
	client = GetInterface<IBaseClientDLL>("./csgo/bin/linux64/client_client.so", "VClient");
	engine = GetInterface<IEngineClient>("./bin/linux64/engine_client.so", "VEngineClient");
	entitylist = GetInterface<IClientEntityList>("./csgo/bin/linux64/client_client.so", "VClientEntityList");
	surface = GetInterface<ISurface>("./bin/linux64/vguimatsurface_client.so", "VGUI_Surface");
	panel = GetInterface<IVPanel>("./bin/linux64/vgui2_client.so", "VGUI_Panel");
	debugOverlay = GetInterface<IVDebugOverlay>("./bin/linux64/engine_client.so", "VDebugOverlay");
	modelInfo = GetInterface<IVModelInfo>("./bin/linux64/engine_client.so", "VModelInfoClient");
	modelRender = GetInterface<IVModelRender>("./bin/linux64/engine_client.so", "VEngineModel");
	trace = GetInterface<IEngineTrace>("./bin/linux64/engine_client.so", "EngineTraceClient");
	input = GetInterface<IInputSystem>("./bin/linux64/inputsystem_client.so", "InputSystemVersion");
	inputInternal = GetInterface<IInputInternal>("./bin/linux64/vgui2_client.so", "VGUI_InputInternal");
	material = GetInterface<IMaterialSystem>("./bin/linux64/materialsystem_client.so", "VMaterialSystem");
	cvar = GetInterface<ICvar>("./bin/linux64/materialsystem_client.so", "VEngineCvar");
	effects = GetInterface<CEffects>("./bin/linux64/engine_client.so", "VEngineEffects");
	gameevents = GetInterface<IGameEventManager2>("./bin/linux64/engine_client.so", "GAMEEVENTSMANAGER002", true);
	physics = GetInterface<IPhysicsSurfaceProps>("./bin/linux64/vphysics_client.so", "VPhysicsSurfaceProps");
	prediction = GetInterface<IPrediction>("./csgo/bin/linux64/client_client.so", "VClientPrediction");
	gamemovement = GetInterface<IGameMovement>("./csgo/bin/linux64/client_client.so", "GameMovement");
	enginevgui = GetInterface<IEngineVGui>("./bin/linux64/engine_client.so", "VEngineVGui");
	sound = GetInterface<IEngineSound>("./bin/linux64/engine_client.so", "IEngineSoundClient");
	localize = GetInterface<ILocalize>("./bin/linux64/localize_client.so", "Localize_");
	commandline = GetSymbolAddress<CommandLineFn>("./bin/linux64/libtier0_client.so", "CommandLine")();

}

void Hooker::InitializeVMHooks()
{
	panel_vmt = new VMT(panel);
	client_vmt = new VMT(client);
	modelRender_vmt = new VMT(modelRender);
	gameEvents_vmt = new VMT(gameevents);
	viewRender_vmt = new VMT(viewrender);
	inputInternal_vmt = new VMT(inputInternal);
	material_vmt = new VMT(material);
	surface_vmt = new VMT(surface);
	launchermgr_vmt = new VMT(launchermgr);
	enginevgui_vmt = new VMT(enginevgui);
	sound_vmt = new VMT(sound);
}

void Hooker::FindIClientMode()
{
	uintptr_t hudprocessinput = reinterpret_cast<uintptr_t>(getvtable(client)[10]);
	GetClientModeFn GetClientMode = reinterpret_cast<GetClientModeFn>(GetAbsoluteAddress(hudprocessinput + 11, 1, 5));

	clientMode_vmt = new VMT(GetClientMode());
}

void Hooker::FindGlobalVars()
{
	uintptr_t hudupdate = reinterpret_cast<uintptr_t>(getvtable(client)[11]);
	globalvars = *reinterpret_cast<CGlobalVars**>(GetAbsoluteAddress(hudupdate + 13, 3, 7));
}

void Hooker::FindGlowManager()
{
	uintptr_t instruction_addr = FindPattern(GetLibraryAddress("client_client.so"), 0xFFFFFFFFF, (unsigned char*) GLOWOBJECT_SIGNATURE, GLOWOBJECT_MASK);

	glowmanager = reinterpret_cast<GlowObjectManagerFn>(GetAbsoluteAddress(instruction_addr, 1, 5))();
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

	viewrender = reinterpret_cast<CViewRender*>(GetAbsoluteAddress(func_address + 14, 3, 7));
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
	movehelper = *reinterpret_cast<IMoveHelper**>(GetAbsoluteAddress(helper_instruction_addr + 1, 3, 7));
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

void Hooker::FindForceFullUpdate()
{
	uintptr_t forcefullupdate_func_address = FindPattern(GetLibraryAddress("engine_client.so"), 0xFFFFFFFFF, (unsigned char*) FORCEFULLUPDATE_SIGNATURE, FORCEFULLUPDATE_MASK);
	ForceFullUpdate = reinterpret_cast<ForceFullUpdateFn>(forcefullupdate_func_address);

	uintptr_t getclientstate_instruction_address = FindPattern(GetLibraryAddress("engine_client.so"), 0xFFFFFFFFF, (unsigned char*) GETCLIENTSTATE_SIGNATURE, GETCLIENTSTATE_MASK);
	uintptr_t getclientstate_func_address = GetAbsoluteAddress(getclientstate_instruction_address, 1, 5);
	GetClientState = reinterpret_cast<GetClientStateFn>(getclientstate_func_address);
}

void Hooker::FindLineGoesThroughSmoke()
{
	uintptr_t func_address = FindPattern(GetLibraryAddress("client_client.so"), 0xFFFFFFFFF, (unsigned char*) LINEGOESTHROUGHSMOKE_SIGNATURE, LINEGOESTHROUGHSMOKE_MASK);
	LineGoesThroughSmoke = reinterpret_cast<LineGoesThroughSmokeFn>(func_address);
}

void Hooker::FindInitKeyValues()
{
	uintptr_t func_address = FindPattern(GetLibraryAddress("client_client.so"), 0xFFFFFFFFF, (unsigned char*) INITKEVALUES_SIGNATURE, INITKEVALUES_MASK);
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
	uintptr_t swapwindow_fn = reinterpret_cast<uintptr_t>(dlsym(RTLD_NEXT, "SDL_GL_SwapWindow"));
	swap_window_jump_address = reinterpret_cast<uintptr_t*>(GetAbsoluteAddress(swapwindow_fn, 3, 7));
	original_swap_window = *swap_window_jump_address;
	*swap_window_jump_address = reinterpret_cast<uintptr_t>(&SDL2::SwapWindow);
}

void Hooker::HookPollEvent()
{
	uintptr_t pollevent_fn = reinterpret_cast<uintptr_t>(dlsym(RTLD_NEXT, "SDL_PollEvent"));
	pollevent_jump_address = reinterpret_cast<uintptr_t*>(GetAbsoluteAddress(pollevent_fn, 3, 7));
	original_pollevent = *pollevent_jump_address;
	*pollevent_jump_address = reinterpret_cast<uintptr_t>(&SDL2::PollEvent);
}

void Hooker::FindSDLInput()
{
	uintptr_t func_address = FindPattern(GetLibraryAddress("launcher_client.so"), 0xFFFFFFFFF, (unsigned char*) GETSDLMGR_SIGNATURE, GETSDLMGR_MASK);

	launchermgr = reinterpret_cast<ILauncherMgrCreateFn>(func_address)();
}
