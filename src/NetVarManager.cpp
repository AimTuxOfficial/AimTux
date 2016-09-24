#include "NetVarManager.h"

std::vector<HLClient::RecvTable *> NetVarManager::getTables()
{
	std::vector<HLClient::RecvTable *> tables;

	HLClient::ClientClass *clientClass = client->GetAllClasses();
	if (!clientClass)
		return std::vector<HLClient::RecvTable*>();

	while (clientClass)
	{
		HLClient::RecvTable *recvTable = clientClass->m_pRecvTable;
		tables.push_back(recvTable);

		clientClass = clientClass->m_pNext;
	}

	return tables;
}

HLClient::RecvTable* NetVarManager::getTable(std::vector<HLClient::RecvTable *> tables, const char *tableName)
{
	if (tables.empty())
		return NULL;

	for (int i = 0; i < tables.size(); i++)
	{
		HLClient::RecvTable *table = tables[i];

		if (!table)
			continue;

		if (strcasecmp(table->m_pNetTableName, tableName) == 0)
			return table;
	}

	return NULL;
}

int NetVarManager::getOffset(std::vector<HLClient::RecvTable *> tables, const char *tableName, const char *propName)
{
	int offset = getProp(tables, tableName, propName);

	if (!offset) {
		return 0;
	}

	return offset;
}

int NetVarManager::getProp(std::vector<HLClient::RecvTable *> tables, const char *tableName, const char *propName, HLClient::RecvProp **prop)
{
	HLClient::RecvTable *recvTable = getTable(tables, tableName);
	if (!recvTable)
		return 0;

	int offset = getProp(tables, recvTable, propName, prop);
	if (!offset)
		return 0;

	return offset;
}

int NetVarManager::getProp(std::vector<HLClient::RecvTable *> tables, HLClient::RecvTable *recvTable, const char *propName, HLClient::RecvProp **prop)
{
	int extraOffset = 0;

	for (int i = 0; i < recvTable->m_nProps; ++i) {
		HLClient::RecvProp *recvProp = &recvTable->m_pProps[i];
		HLClient::RecvTable *child = recvProp->m_pDataTable;

		if (child && (child->m_nProps > 0))
		{
			int tmp = getProp(tables, child, propName, prop);
			if (tmp)
				extraOffset += (recvProp->m_Offset + tmp);
		}

		if (strcasecmp(recvProp->m_pVarName, propName))
			continue;

		if (prop)
			*prop = recvProp;

		return (recvProp->m_Offset + extraOffset);
	}

	return extraOffset;
}

std::string NetVarManager::dumpTable(HLClient::RecvTable *table, int depth)
{
	std::string pre("");
	std::stringstream ss;

	for (int i = 0; i < depth; i++)
		pre.append("\t");

	ss << pre << table->m_pNetTableName << "\n";

	for (int i = 0; i < table->m_nProps; i++) {
		HLClient::RecvProp *prop = &table->m_pProps[i];
		if (!prop)
			continue;

		std::string varName(prop->m_pVarName);

		if (varName.find("baseclass") == 0 || varName.find("0") == 0 || varName.find("1") == 0 || varName.find("2") == 0)
			continue;

		ss << pre << "\t" << varName << " [0x" << prop->m_Offset << "]\n";

		if (prop->m_pDataTable)
			dumpTable(prop->m_pDataTable, depth + 1);
	}

	return ss.str();
}

void NetVarManager::dumpNetvars()
{
	std::stringstream ss;
	std::ofstream file;

	for (HLClient::ClientClass *pClass = client->GetAllClasses(); pClass != NULL; pClass = pClass->m_pNext)
	{
		HLClient::RecvTable *table = pClass->m_pRecvTable;
		ss << NetVarManager::dumpTable(table, 0);
	}

	struct passwd *pw = getpwuid(getuid());
	const char *homedir = pw->pw_dir;

	char* netvarsPath;
	asprintf(&netvarsPath, "%s/%s", homedir, ".steam/steam/steamapps/common/Counter-Strike Global Offensive/netvars.txt");

	file.open(netvarsPath);
	file << ss.str();
	file.close();
}