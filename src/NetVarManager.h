#ifndef NETVARMANAGER_H_INCLUDED
#define NETVARMANAGER_H_INCLUDED

#include "SDK.h"
#include <vector>

namespace NetVarManager {
	std::vector<HLClient::RecvTable *> getTables();
	HLClient::RecvTable* getTable(std::vector<HLClient::RecvTable *> tables, const char *tableName);
	int getOffset(std::vector<HLClient::RecvTable *> tables, const char *tableName, const char *propName);
	int getProp(std::vector<HLClient::RecvTable *> tables, const char *tableName, const char *propName, HLClient::RecvProp **prop = 0);
	int getProp(std::vector<HLClient::RecvTable *> tables, HLClient::RecvTable *recvTable, const char *propName, HLClient::RecvProp **prop = 0);
	void dumpTable(HLClient::RecvTable *table, int depth);
	void dumpTables();
}

#endif