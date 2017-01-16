#pragma once

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

#include "../SDK/SDK.h"
#include "../interfaces.h"

namespace NetVarManager {
	std::vector<RecvTable *> getTables();
	RecvTable* getTable(std::vector<RecvTable *> tables, const char *tableName);
	int getOffset(std::vector<RecvTable *> tables, const char *tableName, const char *propName);
	int getProp(std::vector<RecvTable *> tables, const char *tableName, const char *propName, RecvProp **prop = 0);
	int getProp(std::vector<RecvTable *> tables, RecvTable *recvTable, const char *propName, RecvProp **prop = 0);
	bool HookProp(const char* tableName, const char* propName, RecvVarProxyFn f);
	std::string dumpTable(RecvTable *table, int depth);
	void dumpNetvars();
}
