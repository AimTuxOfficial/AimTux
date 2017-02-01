#include <unordered_map>
#include <set>
#include "interfaces.h"
#include "hooker.h"

void Interfaces::FindInterfaces()
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
	inputSystem = GetInterface<IInputSystem>("./bin/linux64/inputsystem_client.so", "InputSystemVersion");
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

void Interfaces::DumpInterfaces()
{
	std::stringstream ss;
	char cwd[1024];

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

		void* interfaces_sym = dlsym(library, "s_pInterfaceRegs");

		if (!interfaces_sym)
		{
			dlclose(library);
			continue;
		}

		dlclose(library);

		InterfaceReg* interfaces = *reinterpret_cast<InterfaceReg**>(interfaces_sym);

		InterfaceReg* cur_interface;

		std::set<const char*> interface_name;

		for (cur_interface = interfaces; cur_interface; cur_interface = cur_interface->m_pNext)
			interface_name.insert(cur_interface->m_pName);

		if (interface_name.empty())
			continue;

		ss << std::string(module) << "\n";

		for (auto interface : interface_name)
			ss << "\t" << interface << "\n";

		ss << '\n';
	}

	getcwd(cwd, sizeof(cwd));

	std::string interfacesPath = std::string(cwd) + "/interfaces.txt";

	std::ofstream(interfacesPath) << ss.str();
}
