#pragma once

#include <cstdint>
#include <cstddef>
#include <vector>

class VMT;
extern std::vector<VMT*> createdVMTs;

class VMT
{
private:
	uintptr_t* vmt;
public:
	// New virtual method table
	uintptr_t** interface = nullptr;

	uintptr_t* original_vmt = nullptr;

	uint32_t methodCount = 0;

	~VMT( ){
		ReleaseVMT();
		delete[] vmt;
	}
	VMT(void* interface)
	{
		this->interface = reinterpret_cast<uintptr_t**>(interface);

		size_t method_count = 0;

		while (reinterpret_cast<uintptr_t*>(*this->interface)[method_count])
			method_count++;

		original_vmt = *this->interface;

		vmt = new uintptr_t[method_count];

		memcpy(vmt, original_vmt, sizeof(uintptr_t) * method_count);

		createdVMTs.push_back(this);
	}

	// Hook virtual method
	template <typename func>
	void HookVM(func method, size_t methodIndex)
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
