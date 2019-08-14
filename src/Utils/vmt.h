#pragma once

#include "MemoryProtection.h"

#include <cstdint>
#include <vector>

class VMT;
extern std::vector<VMT*> createdVMTs;

inline uint32_t CountVMs( void* interface )
{
	uintptr_t** vmt = reinterpret_cast<uintptr_t**>(interface);

	uint32_t methodCount = 0;

	while ( vmt && (*vmt)[methodCount] && ( MemoryProtection::GetProtectionFlags( (*vmt)[methodCount] ) & PF_X ) )
		methodCount++;

	return methodCount;
}

class VMT
{
public:
    uintptr_t* vmt;
    uintptr_t** interface = nullptr;
    uintptr_t* original_vmt = nullptr;
    size_t method_count = 0;
    bool hasRTTI = false;
    int32_t rttiPrefix = 0;

    ~VMT( ){
        ReleaseVMT();
        delete[] vmt;
    }
    // rttiPrefix 2??? Wtf? Yeah read this: https://web.archive.org/web/20170701021444/https://spockwangs.github.io/2011/01/31/cpp-object-model.html
    explicit VMT(void* interface, bool copyRTTI = true, int32_t rttiPrefixAmount = 2)
    {
        this->interface = reinterpret_cast<uintptr_t**>(interface);

        method_count = CountVMs(interface) + 2 + rttiPrefixAmount;

        original_vmt = *this->interface;

        // Copy the Original Vtable.
        if( copyRTTI ){
            vmt = new uintptr_t[method_count + 1];
            memcpy(vmt, &original_vmt[-rttiPrefixAmount], (sizeof(uintptr_t) * method_count) + sizeof(uintptr_t));
            hasRTTI = true;
            rttiPrefix = rttiPrefixAmount;
        } else {
            vmt = new uintptr_t[method_count];
            memcpy(vmt, original_vmt, sizeof(uintptr_t) * method_count);
        }

        // Make sure to "NULL terminate" our new array of pointers.
        memset(&vmt[method_count], 0, sizeof(uintptr_t));

        createdVMTs.push_back(this);
    }

    // Hook virtual method
    template <typename func>
    void HookVM(func method, size_t methodIndex)
    {
        vmt[hasRTTI ? methodIndex + rttiPrefix : methodIndex] = reinterpret_cast<uintptr_t>(method);
    }

    template<typename Fn>
    Fn GetOriginalMethod(size_t methodIndex)
    {
        return reinterpret_cast<Fn>(original_vmt[methodIndex]);
    }

    void ApplyVMT()
    {
        if( hasRTTI ) {
            *this->interface = &vmt[rttiPrefix];
        } else {
            *this->interface = vmt;
        }
    }

    void ReleaseVMT()
    {
        if( !this->interface )
            return;
        if( *this->interface && original_vmt )
            *this->interface = original_vmt;
    }
};

