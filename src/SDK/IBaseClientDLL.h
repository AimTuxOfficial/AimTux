#ifndef __IBASECLIENTDLL_H
#define __IBASECLIENTDLL_H

struct RecvProp;

struct RecvTable
{
	RecvProp *m_pProps;
	int m_nProps;
	void *m_pDecoder;
	char *m_pNetTableName;
	bool m_bInitialized;
	bool m_bInMainList;
};

struct RecvProp
{
	char *m_pVarName;
	int m_RecvType;
	int m_Flags;
	int m_StringBufferSize;
	bool m_bInsideArray;
	const void *m_pExtraData;
	RecvProp *m_pArrayProp;
	void* m_ArrayLengthProxy;
	void* m_ProxyFn;
	void* m_DataTableProxyFn;
	RecvTable  *m_pDataTable;
	int m_Offset;
	int m_ElementStride;
	int m_nElements;
	const char *m_pParentArrayPropName;
};

struct ClientClass
{
	void *m_pCreateFn;
	void *m_pCreateEventFn;
	char *m_pNetworkName;
	RecvTable *m_pRecvTable;
	ClientClass *m_pNext;
	int m_ClassID;
};

class IBaseClientDLL
{
public:
	ClientClass* GetAllClasses()
	{
		typedef ClientClass*(* OriginalFn)(void*);
		getvfunc<OriginalFn>(this, 8)(this);
	}
};

#endif
