#include "interfaces.h"

#include "Utils/util.h"
#include "Utils/xorstring.h"

#include <set>
#include <fstream>
#include <link.h> // dl_iterate_phdr
#include <sstream>

IBaseClientDLL* client = nullptr;
IClientMode* clientMode = nullptr;
ICommandLine* commandline = nullptr;
C_CSGameRules** csGameRules = nullptr;
C_CSPlayerResource** csPlayerResource = nullptr;
ICvar* cvar = nullptr;
IVDebugOverlay* debugOverlay = nullptr;
CEffects* effects = nullptr;
IEngineClient* engine = nullptr;
IEngineVGui* engineVGui = nullptr;
IClientEntityList* entityList = nullptr;
IGameEventManager2* gameEvents = nullptr;
IGameMovement* gameMovement = nullptr;
CGlobalVars* globalVars = nullptr;
CGlowObjectManager* glowManager = nullptr;
CInput* input = nullptr;
IInputInternal* inputInternal = nullptr;
IInputSystem* inputSystem = nullptr;
ILauncherMgr* launcherMgr = nullptr;
ILocalize* localize = nullptr;
IMaterialSystem* material = nullptr;
IVModelInfo* modelInfo = nullptr;
IVModelRender* modelRender = nullptr;
IMoveHelper* moveHelper = nullptr;
IVPanel* panel = nullptr;
IPhysicsSurfaceProps* physics = nullptr;
IPrediction* prediction = nullptr;
IEngineSound* sound = nullptr;
ISurface* surface = nullptr;
IEngineTrace* trace = nullptr;
CViewRender* viewRender = nullptr;
IPanoramaUIEngine* panoramaEngine = nullptr;
IFileSystem* fileSystem = nullptr;
IGameTypes* gameTypes = nullptr;
CItemSystem* itemSystem = nullptr;


void Interfaces::FindInterfaces()
{
	client = GetInterface<IBaseClientDLL>(XORSTR("./csgo/bin/linux64/client_client.so"), XORSTR("VClient"));
	engine = GetInterface<IEngineClient>(XORSTR("./bin/linux64/engine_client.so"), XORSTR("VEngineClient"));
	entityList = GetInterface<IClientEntityList>(XORSTR("./csgo/bin/linux64/client_client.so"), XORSTR("VClientEntityList"));
	surface = GetInterface<ISurface>(XORSTR("./bin/linux64/vguimatsurface_client.so"), XORSTR("VGUI_Surface"));
	panel = GetInterface<IVPanel>(XORSTR("./bin/linux64/vgui2_client.so"), XORSTR("VGUI_Panel"));
	debugOverlay = GetInterface<IVDebugOverlay>(XORSTR("./bin/linux64/engine_client.so"), XORSTR("VDebugOverlay"));
	modelInfo = GetInterface<IVModelInfo>(XORSTR("./bin/linux64/engine_client.so"), XORSTR("VModelInfoClient"));
	modelRender = GetInterface<IVModelRender>(XORSTR("./bin/linux64/engine_client.so"), XORSTR("VEngineModel"));
	trace = GetInterface<IEngineTrace>(XORSTR("./bin/linux64/engine_client.so"), XORSTR("EngineTraceClient"));
	inputSystem = GetInterface<IInputSystem>(XORSTR("./bin/linux64/inputsystem_client.so"), XORSTR("InputSystemVersion"));
	inputInternal = GetInterface<IInputInternal>(XORSTR("./bin/linux64/vgui2_client.so"), XORSTR("VGUI_InputInternal"));
	material = GetInterface<IMaterialSystem>(XORSTR("./bin/linux64/materialsystem_client.so"), XORSTR("VMaterialSystem"));
	cvar = GetInterface<ICvar>(XORSTR("./bin/linux64/materialsystem_client.so"), XORSTR("VEngineCvar"));
	effects = GetInterface<CEffects>(XORSTR("./bin/linux64/engine_client.so"), XORSTR("VEngineEffects"));
	gameEvents = GetInterface<IGameEventManager2>(XORSTR("./bin/linux64/engine_client.so"), XORSTR("GAMEEVENTSMANAGER002"), true);
	physics = GetInterface<IPhysicsSurfaceProps>(XORSTR("./bin/linux64/vphysics_client.so"), XORSTR("VPhysicsSurfaceProps"));
	prediction = GetInterface<IPrediction>(XORSTR("./csgo/bin/linux64/client_client.so"), XORSTR("VClientPrediction001"), true);
	gameMovement = GetInterface<IGameMovement>(XORSTR("./csgo/bin/linux64/client_client.so"), XORSTR("GameMovement"));
	engineVGui = GetInterface<IEngineVGui>(XORSTR("./bin/linux64/engine_client.so"), XORSTR("VEngineVGui"));
	sound = GetInterface<IEngineSound>(XORSTR("./bin/linux64/engine_client.so"), XORSTR("IEngineSoundClient"));
	localize = GetInterface<ILocalize>(XORSTR("./bin/linux64/localize_client.so"), XORSTR("Localize_"));
	commandline = GetSymbolAddress<CommandLineFn>(XORSTR("./bin/linux64/libtier0_client.so"), XORSTR("CommandLine"))();
    panoramaEngine = GetInterface<IPanoramaUIEngine>(XORSTR("./bin/linux64/panorama_client.so"), XORSTR("PanoramaUIEngine001"), true);
	fileSystem = GetInterface<IFileSystem>( XORSTR( "./bin/linux64/filesystem_stdio_client.so" ), XORSTR( "VFileSystem" ) );
	gameTypes = GetInterface<IGameTypes>(XORSTR("./csgo/bin/linux64/matchmaking_client.so"), XORSTR("VENGINE_GAMETYPES_VERSION002"), true);
}

void Interfaces::DumpInterfaces()
{
	std::stringstream ss;

	std::vector<const char*> modules;

	dl_iterate_phdr([](struct dl_phdr_info* info, size_t size, void* data) {
		reinterpret_cast<std::vector<const char*>*>(data)->push_back(info->dlpi_name);
		return 0;
	}, &modules);

	for (auto module : modules)
	{
		void* library = dlopen(module, RTLD_NOLOAD | RTLD_NOW);

		if (!library)
			continue;

		void* interfaces_sym = dlsym(library, XORSTR("s_pInterfaceRegs"));

		if (!interfaces_sym)
		{
			dlclose(library);
			continue;
		}

		dlclose(library);

		InterfaceReg* interfaces = *reinterpret_cast<InterfaceReg**>(interfaces_sym);

		InterfaceReg* cur_interface;

		std::set<const char*> interface_name;

		for (cur_interface = interfaces; cur_interface; cur_interface = cur_interface->m_pNext){
            cvar->ConsoleDPrintf("%s - %p\n", cur_interface->m_pName, (void*)cur_interface->m_CreateFn);
            interface_name.insert(cur_interface->m_pName);
        }

		if (interface_name.empty())
			continue;

		ss << module << '\n';

		for (auto interface : interface_name)
			ss << '\t' << interface << '\n';

		ss << '\n';
	}

	std::string interfacesPath = XORSTR("/tmp/csgointerfaces.txt");

	std::ofstream(interfacesPath) << ss.str();
}
