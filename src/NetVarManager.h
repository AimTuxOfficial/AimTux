#ifndef __NETVARMANAGER_H_
#define __NETVARMANAGER_H_

#include <vector>
#include <string>
#include <vector>
#include <strings.h>
#include <string>
#include <ios>
#include <iomanip>
#include <pwd.h>
#include <zconf.h>
#include <fstream>

#include "SDK.h"
#include "interfaces.h"

namespace NetVarManager {
	std::vector<HLClient::RecvTable *> getTables();
	HLClient::RecvTable* getTable(std::vector<HLClient::RecvTable *> tables, const char *tableName);
	int getOffset(std::vector<HLClient::RecvTable *> tables, const char *tableName, const char *propName);
	int getProp(std::vector<HLClient::RecvTable *> tables, const char *tableName, const char *propName, HLClient::RecvProp **prop = 0);
	int getProp(std::vector<HLClient::RecvTable *> tables, HLClient::RecvTable *recvTable, const char *propName, HLClient::RecvProp **prop = 0);
	std::string dumpTable(HLClient::RecvTable *table, int depth);
	void dumpNetvars();
}

#endif