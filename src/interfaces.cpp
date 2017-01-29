#include <unordered_map>
#include <set>
#include "interfaces.h"
#include "hooker.h"

void Interfaces::dumpInterfaces()
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
