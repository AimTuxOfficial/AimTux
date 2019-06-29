#pragma once

class bf_write
{
public:
    char pad_0000[12]; //0x0000
    int32_t m_nDataBytes; //0x000C
    int32_t m_nDataBits; //0x0010
    int32_t m_iCurBit; //0x0014
    bool m_bOverflow; //0x0018
    bool m_bAssertOnOverflow; //0x0019
    char pad_001A[2]; //0x001A
    char* m_pDebugName; //0x001C
}; //Size: 0x0024