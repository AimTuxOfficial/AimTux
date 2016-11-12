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

VMT* panel_vmt = nullptr;
VMT* client_vmt = nullptr;
VMT* modelRender_vmt = nullptr;
VMT* clientMode_vmt = nullptr;
VMT* gameEvents_vmt = nullptr;
VMT* viewRender_vmt = nullptr;
VMT* inputInternal_vmt = nullptr;

bool* bSendPacket = nullptr;
int* nPredictionRandomSeed = nullptr;
CMoveData* g_MoveData = nullptr;

GlowObjectManagerFn GlowObjectManager;
MsgFunc_ServerRankRevealAllFn MsgFunc_ServerRankRevealAll;
SendClanTagFn SendClanTag;
RecvVarProxyFn fnSequenceProxyFn;

std::unordered_map<const char*, uintptr_t> GetProcessLibraries() {
	std::unordered_map<const char*, uintptr_t> modules;

	dl_iterate_phdr([](struct dl_phdr_info* info, size_t size, void* data) {
		reinterpret_cast<std::unordered_map<const char*, uintptr_t>*>(data)->insert({ info->dlpi_name, reinterpret_cast<uintptr_t>(info->dlpi_addr + info->dlpi_phdr[0].p_vaddr) });
		return 0;
	}, &modules);

	return modules;
}

uintptr_t GetLibraryAddress(const char* moduleName)
{
	std::unordered_map<const char*, uintptr_t> modules = GetProcessLibraries();

	for (auto module : modules)
		if (strcasestr(module.first, moduleName))
			return module.second;

	return 0;
}

void Hooker::HookInterfaces()
{
	client = BruteforceInterface<IBaseClientDLL>("./csgo/bin/linux64/client_client.so", "VClient");
	engine = BruteforceInterface<IEngineClient>("./bin/linux64/engine_client.so", "VEngineClient");
	entitylist = BruteforceInterface<IClientEntityList>("./csgo/bin/linux64/client_client.so", "VClientEntityList");
	surface = BruteforceInterface<ISurface>("./bin/linux64/vguimatsurface_client.so", "VGUI_Surface");
	panel = BruteforceInterface<IVPanel>("./bin/linux64/vgui2_client.so", "VGUI_Panel");
	debugOverlay = BruteforceInterface<IVDebugOverlay>("./bin/linux64/engine_client.so", "VDebugOverlay");
	modelInfo = BruteforceInterface<IVModelInfo>("./bin/linux64/engine_client.so", "VModelInfoClient");
	modelRender = BruteforceInterface<IVModelRender>("./bin/linux64/engine_client.so", "VEngineModel");
	trace = BruteforceInterface<IEngineTrace>("./bin/linux64/engine_client.so", "EngineTraceClient");
	input = BruteforceInterface<IInputSystem>("./bin/linux64/inputsystem_client.so", "InputSystemVersion");
	inputInternal = BruteforceInterface<IInputInternal>("./bin/linux64/vgui2_client.so", "VGUI_InputInternal");
	material = BruteforceInterface<IMaterialSystem>("./bin/linux64/materialsystem_client.so", "VMaterialSystem");
	cvar = BruteforceInterface<ICvar>("./bin/linux64/libvstdlib_client.so", "VEngineCvar");
	effects = BruteforceInterface<CEffects>("./bin/linux64/engine_client.so", "VEngineEffects");
	gameevents = GetInterface<IGameEventManager2>("./bin/linux64/engine_client.so", "GAMEEVENTSMANAGER002");
	physics = BruteforceInterface<IPhysicsSurfaceProps>("./bin/linux64/vphysics_client.so", "VPhysicsSurfaceProps");
	prediction = BruteforceInterface<IPrediction>("./csgo/bin/linux64/client_client.so", "VClientPrediction");
	gamemovement = BruteforceInterface<IGameMovement>("./csgo/bin/linux64/client_client.so", "GameMovement");
}

void Hooker::HookVMethods()
{
	panel_vmt = new VMT(panel);
	client_vmt = new VMT(client);
	modelRender_vmt = new VMT(modelRender);
	gameEvents_vmt = new VMT(gameevents);
	viewRender_vmt = new VMT(viewrender);
	inputInternal_vmt = new VMT(inputInternal);
}

void Hooker::HookIClientMode()
{
	uintptr_t init_address = FindPattern(GetLibraryAddress("client_client.so"), 0xFFFFFFFFF, (unsigned char*) CCSMODEMANAGER_INIT_SIGNATURE, CCSMODEMANAGER_INIT_MASK);

	if (!init_address)
		return;

	uint32_t offset = *reinterpret_cast<uint32_t*>(init_address + 3);
	clientMode = reinterpret_cast<IClientMode*>(init_address + offset + 7);
	
	clientMode_vmt = new VMT(clientMode);
}

void Hooker::HookGlobalVars()
{
	uintptr_t hudupdate = reinterpret_cast<uintptr_t>(getvtable(client)[11]);
	globalvars = *reinterpret_cast<CGlobalVars**>(GetAbsoluteAddress(hudupdate + 13, 3, 7));
}

void Hooker::HookGlowManager()
{
	uintptr_t instruction_addr = FindPattern(GetLibraryAddress("client_client.so"), 0xFFFFFFFFF, (unsigned char*) GLOWOBJECT_SIGNATURE, GLOWOBJECT_MASK);

	GlowObjectManager = reinterpret_cast<GlowObjectManagerFn>(GetAbsoluteAddress(instruction_addr, 1, 5));
}

void Hooker::HookRankReveal()
{
	uintptr_t func_address = FindPattern(GetLibraryAddress("client_client.so"), 0xFFFFFFFFF, (unsigned char*) MSGFUNC_SERVERRANKREVEALALL_SIGNATURE, MSGFUNC_SERVERRANKREVEALALL_MASK);

	MsgFunc_ServerRankRevealAll = reinterpret_cast<MsgFunc_ServerRankRevealAllFn>(func_address);
}

void Hooker::HookSendClanTag()
{
	uintptr_t func_address = FindPattern(GetLibraryAddress("engine_client.so"), 0xFFFFFFFFF, (unsigned char*) SENDCLANTAG_SIGNATURE, SENDCLANTAG_MASK);

	SendClanTag = reinterpret_cast<SendClanTagFn>(func_address);
}

void Hooker::HookViewRender()
{
	uintptr_t func_address = FindPattern(GetLibraryAddress("client_client.so"), 0xFFFFFFFFF, (unsigned char*) VIEWRENDER_SIGNATURE, VIEWRENDER_MASK);

	viewrender = reinterpret_cast<CViewRender*>(GetAbsoluteAddress(func_address + 14, 3, 7));
}

void Hooker::HookSendPacket()
{
	uintptr_t bool_address = FindPattern(GetLibraryAddress("engine_client.so"), 0xFFFFFFFFF, (unsigned char*) BSENDPACKET_SIGNATURE, BSENDPACKET_MASK);
	bool_address = GetAbsoluteAddress(bool_address, 2, 1);

	bSendPacket = reinterpret_cast<bool*>(bool_address);
	Util::ProtectAddr(bSendPacket, PROT_READ | PROT_WRITE | PROT_EXEC);
}

void Hooker::HookPrediction()
{
	uintptr_t seed_instruction_addr = FindPattern(GetLibraryAddress("client_client.so"), 0xFFFFFFFFF, (unsigned char*) PREDICTION_RANDOM_SEED_SIGNATURE, PREDICTION_RANDOM_SEED_MASK);
	uintptr_t helper_instruction_addr = FindPattern(GetLibraryAddress("client_client.so"), 0xFFFFFFFFF, (unsigned char*) CLIENT_MOVEHELPER_SIGNATURE, CLIENT_MOVEHELPER_MASK);
	uintptr_t movedata_instruction_addr = FindPattern(GetLibraryAddress("client_client.so"), 0xFFFFFFFFF, (unsigned char*) CLIENT_MOVEDATA_SIGNATURE, CLIENT_MOVEDATA_MASK);

	nPredictionRandomSeed = *reinterpret_cast<int**>(GetAbsoluteAddress(seed_instruction_addr, 3, 7));
	movehelper = *reinterpret_cast<IMoveHelper**>(GetAbsoluteAddress(helper_instruction_addr + 1, 3, 7));
	g_MoveData = **reinterpret_cast<CMoveData***>(GetAbsoluteAddress(movedata_instruction_addr, 3, 7));
}