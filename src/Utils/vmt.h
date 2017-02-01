#pragma once

#include <cstdint>
#include <cstddef>

class VMT
{
private:
	uintptr_t* vmt;
public:
	// New virtual method table
	uintptr_t** interface = nullptr;

	uintptr_t* original_vmt = nullptr;

	uint32_t methodCount = 0;

	VMT(void* interface)
	{
		this->interface = reinterpret_cast<uintptr_t**>(interface);

		size_t method_count = 0;

		while (reinterpret_cast<uintptr_t*>(*this->interface)[method_count])
			method_count++;

		original_vmt = *this->interface;

		vmt = new uintptr_t[sizeof(uintptr_t) * method_count];

		memcpy(vmt, original_vmt, sizeof(uintptr_t) * method_count);
	}

	// Hook virtual method
	void HookVM(void* method, size_t methodIndex)
	{
		vmt[methodIndex] = reinterpret_cast<uintptr_t>(method);
	}

	template<typename Fn>
	Fn GetOriginalMethod(size_t methodIndex)
	{
		return reinterpret_cast<Fn>(original_vmt[methodIndex]);
	}

	void ApplyVMT()
	{
		*this->interface = vmt;
	}

	void ReleaseVMT()
	{
		*this->interface = original_vmt;
	}
};
