#pragma once

/* Inspired by DucaRii: https://www.unknowncheats.me/forum/counterstrike-global-offensive/336557-easily-getting-itemdefinitionindex.html */

class CEconItemDefinition
{
public:
    virtual int GetDefinitionIndex() = 0;
    virtual const char * GetPrefabName() = 0;
    virtual const char * GetItemBaseName() = 0;
    virtual const char * GetItemTypeName() = 0;
    virtual const char * GetItemDesc() = 0;
    virtual const char * GetInventoryImage() = 0;

    void *rawDefinition;
    int m_iItemDefinitionIndex;
    int pad;
    void *_pads[13]; // some sticker pointers, idk

    const char *m_szItemBaseName;
    void *_pad2;
    const char *m_szItemTypeName;
    void *unkptr;
    const char *m_szItemDescription;
    void *_pad3[2];
    const char *m_szInventoryImage;
    void *_pad4[6];
    const char * m_szModel;
    void *_pad5;
    const char *m_szWorldModel;
    const char *m_szWorldModelDropped;

};

class CEconItemDefHashMapEntry
{
public:
    CEconItemDefinition *definition;
    int size;
    int unk;
    int index;
    int unk2;
};
class CEconItemDefHashMap
{
public:
    void *pad;
    CEconItemDefHashMapEntry entries[2048];
};

class CItemSystem
{
public:
    virtual void sub_CAB600() = 0;
    virtual void sub_CCB300() = 0;
    virtual void sub_CD3FC0() = 0;
    virtual int GetItemDefinitionCount( void ) = 0;
    virtual void sub_CD56F0() = 0;
    virtual void sub_CD3EC0() = 0;
    virtual void sub_CD3FD0() = 0;
    virtual void sub_CD3FE0() = 0;
    virtual void sub_CD3FF0() = 0;
    virtual void sub_CD4000() = 0;
    virtual void sub_CD4010() = 0;
    virtual void sub_CD4020() = 0;
    virtual void sub_CD4030() = 0;
    virtual void sub_CD4040() = 0;
    virtual void loc_CC08E0() = 0;
    virtual void sub_CA5C10() = 0;
    virtual void sub_CA66B0() = 0;
    virtual void sub_CD3FA0() = 0;
    virtual void sub_CD3EF0() = 0;
    virtual void sub_CAE8A0() = 0;
    virtual void sub_CA8AB0() = 0;
    virtual void sub_CD3F00() = 0;
    virtual void sub_CAE6F0() = 0;
    virtual void sub_CAE750() = 0;
    virtual void sub_CAE780() = 0;
    virtual void sub_CAE7B0() = 0;
    virtual void sub_CA8BE0() = 0;
    virtual void sub_CD3F10() = 0;
    virtual void sub_CD3EE0() = 0;
    virtual void sub_CA6780() = 0;
    virtual void sub_CD8C40() = 0;
    virtual void sub_CD7870() = 0;
    virtual void sub_CD4B00() = 0;
    virtual void sub_CD7880() = 0;
    virtual void sub_CD3ED0() = 0;
    virtual void sub_CAE4F0() = 0;
    virtual void sub_CC0A00() = 0;
    virtual void loc_CC8630() = 0;
    virtual void sub_CCA2C0() = 0;
    virtual void sub_CC5E90() = 0;
    virtual void loc_CC5950() = 0;
    virtual void* GetItemDefinitionByName( const char *name ) = 0;

    CEconItemDefHashMap* GetItemDefinitionMap()
    {
        return ( *reinterpret_cast<CEconItemDefHashMap**>(uintptr_t(this) + 0x120) );
    }

    CEconItemDefinition* GetItemDefinitionByIndex( int i )
    {
        if( i < 0 || i >= GetItemDefinitionCount() )
            return nullptr;

        return this->GetItemDefinitionMap()->entries[i].definition;
    }
};