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


template <class T, typename F>
inline int VtableIndex(F f)
{
    struct VtableCounter
    {
	virtual int Get0() { return 0; }
	virtual int Get1() { return 1; }
	virtual int Get2() { return 2; }
	virtual int Get3() { return 3; }
	virtual int Get4() { return 4; }
	virtual int Get5() { return 5; }
	virtual int Get6() { return 6; }
	virtual int Get7() { return 7; }
	virtual int Get8() { return 8; }
	virtual int Get9() { return 9; }
	virtual int Get10() { return 10; }
	virtual int Get11() { return 11; }
	virtual int Get12() { return 12; }
	virtual int Get13() { return 13; }
	virtual int Get14() { return 14; }
	virtual int Get15() { return 15; }
	virtual int Get16() { return 16; }
	virtual int Get17() { return 17; }
	virtual int Get18() { return 18; }
	virtual int Get19() { return 19; }
	virtual int Get20() { return 20; }
	virtual int Get21() { return 21; }
	virtual int Get22() { return 22; }
	virtual int Get23() { return 23; }
	virtual int Get24() { return 24; }
	virtual int Get25() { return 25; }
	virtual int Get26() { return 26; }
	virtual int Get27() { return 27; }
	virtual int Get28() { return 28; }
	virtual int Get29() { return 29; }
	virtual int Get30() { return 30; }
	virtual int Get31() { return 31; }
	virtual int Get32() { return 32; }
	virtual int Get33() { return 33; }
	virtual int Get34() { return 34; }
	virtual int Get35() { return 35; }
	virtual int Get36() { return 36; }
	virtual int Get37() { return 37; }
	virtual int Get38() { return 38; }
	virtual int Get39() { return 39; }
	virtual int Get40() { return 40; }
	virtual int Get41() { return 41; }
	virtual int Get42() { return 42; }
	virtual int Get43() { return 43; }
	virtual int Get44() { return 44; }
	virtual int Get45() { return 45; }
	virtual int Get46() { return 46; }
	virtual int Get47() { return 47; }
	virtual int Get48() { return 48; }
	virtual int Get49() { return 49; }
	virtual int Get50() { return 50; }
	virtual int Get51() { return 51; }
	virtual int Get52() { return 52; }
	virtual int Get53() { return 53; }
	virtual int Get54() { return 54; }
	virtual int Get55() { return 55; }
	virtual int Get56() { return 56; }
	virtual int Get57() { return 57; }
	virtual int Get58() { return 58; }
	virtual int Get59() { return 59; }
	virtual int Get60() { return 60; }
	virtual int Get61() { return 61; }
	virtual int Get62() { return 62; }
	virtual int Get63() { return 63; }
	virtual int Get64() { return 64; }
	virtual int Get65() { return 65; }
	virtual int Get66() { return 66; }
	virtual int Get67() { return 67; }
	virtual int Get68() { return 68; }
	virtual int Get69() { return 69; }
	virtual int Get70() { return 70; }
	virtual int Get71() { return 71; }
	virtual int Get72() { return 72; }
	virtual int Get73() { return 73; }
	virtual int Get74() { return 74; }
	virtual int Get75() { return 75; }
	virtual int Get76() { return 76; }
	virtual int Get77() { return 77; }
	virtual int Get78() { return 78; }
	virtual int Get79() { return 79; }
	virtual int Get80() { return 80; }
	virtual int Get81() { return 81; }
	virtual int Get82() { return 82; }
	virtual int Get83() { return 83; }
	virtual int Get84() { return 84; }
	virtual int Get85() { return 85; }
	virtual int Get86() { return 86; }
	virtual int Get87() { return 87; }
	virtual int Get88() { return 88; }
	virtual int Get89() { return 89; }
	virtual int Get90() { return 90; }
	virtual int Get91() { return 91; }
	virtual int Get92() { return 92; }
	virtual int Get93() { return 93; }
	virtual int Get94() { return 94; }
	virtual int Get95() { return 95; }
	virtual int Get96() { return 96; }
	virtual int Get97() { return 97; }
	virtual int Get98() { return 98; }
	virtual int Get99() { return 99; }
	virtual int Get100() { return 100; }
	// Is your vfunc bigger than 100? Well too bad!
    } vt;

    T* t = reinterpret_cast<T*>(&vt);

    typedef int (T::*GetIndex)();
    GetIndex getIndex = (GetIndex)f;
    return (t->*getIndex)();
}