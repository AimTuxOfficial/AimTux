#pragma once

inline void**& getvtable(void* inst, size_t offset = 0)
{
	return *reinterpret_cast<void***>((size_t)inst + offset);
}
inline const void** getvtable(const void* inst, size_t offset = 0)
{
	return *reinterpret_cast<const void***>((size_t)inst + offset);
}
template< typename Fn >
inline Fn getvfunc(const void* inst, size_t index, size_t offset = 0)
{
	return reinterpret_cast<Fn>(getvtable(inst, offset)[index]);
}

template <typename interface> interface* GetInterface(const char* filename, const char* version)
{
	void* library = dlopen(filename, RTLD_NOLOAD | RTLD_NOW);

	if (!library)
		return nullptr;

	void* createinterface_sym = dlsym(library, "CreateInterface");

	if (!createinterface_sym)
		return nullptr;

	CreateInterfaceFn factory = reinterpret_cast<CreateInterfaceFn>(createinterface_sym);

	return reinterpret_cast<interface*>(factory(version, nullptr));
}

inline uintptr_t GetAbsoluteAddress(uintptr_t instruction_ptr, int offset, int size)
{
	return instruction_ptr + *reinterpret_cast<uint32_t*>(instruction_ptr + offset) + size;
};