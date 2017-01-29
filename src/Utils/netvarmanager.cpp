#include "netvarmanager.h"

std::vector<RecvTable *> NetVarManager::getTables()
{
	std::vector<RecvTable *> tables;

	ClientClass *clientClass = client->GetAllClasses();
	if (!clientClass)
		return std::vector<RecvTable*>();

	while (clientClass)
	{
		RecvTable *recvTable = clientClass->m_pRecvTable;
		tables.push_back(recvTable);

		clientClass = clientClass->m_pNext;
	}

	return tables;
}

RecvTable* NetVarManager::getTable(std::vector<RecvTable *> tables, const char *tableName)
{
	if (tables.empty())
		return NULL;

	for (unsigned long i = 0; i < tables.size(); i++)
	{
		RecvTable *table = tables[i];

		if (!table)
			continue;

		if (strcasecmp(table->m_pNetTableName, tableName) == 0)
			return table;
	}

	return NULL;
}

int NetVarManager::getOffset(std::vector<RecvTable *> tables, const char *tableName, const char *propName)
{
	int offset = getProp(tables, tableName, propName);
	if (!offset)
		return 0;

	return offset;
}

int NetVarManager::getProp(std::vector<RecvTable *> tables, const char *tableName, const char *propName, RecvProp **prop)
{
	RecvTable *recvTable = getTable(tables, tableName);
	if (!recvTable)
		return 0;

	int offset = getProp(tables, recvTable, propName, prop);
	if (!offset)
		return 0;

	return offset;
}

int NetVarManager::getProp(std::vector<RecvTable *> tables, RecvTable *recvTable, const char *propName, RecvProp **prop)
{
	int extraOffset = 0;

	for (int i = 0; i < recvTable->m_nProps; ++i) {
		RecvProp *recvProp = &recvTable->m_pProps[i];
		RecvTable *child = recvProp->m_pDataTable;

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

std::string NetVarManager::dumpTable(RecvTable *table, int depth)
{
	std::string pre("");
	std::stringstream ss;

	for (int i = 0; i < depth; i++)
		pre.append("\t");

	ss << pre << table->m_pNetTableName << "\n";

	for (int i = 0; i < table->m_nProps; i++) {
		RecvProp *prop = &table->m_pProps[i];
		if (!prop)
			continue;

		std::string varName(prop->m_pVarName);

		if (varName.find("baseclass") == 0 || varName.find("0") == 0 || varName.find("1") == 0 || varName.find("2") == 0)
			continue;

		ss << pre << "\t" << varName << " [0x" << std::hex << prop->m_Offset << "]\n";

		if (prop->m_pDataTable)
			ss << dumpTable(prop->m_pDataTable, depth + 1);
	}

	return ss.str();
}

void NetVarManager::dumpNetvars()
{
	std::stringstream ss;
	char cwd[1024];

	for (ClientClass *pClass = client->GetAllClasses(); pClass != NULL; pClass = pClass->m_pNext)
	{
		RecvTable *table = pClass->m_pRecvTable;
		ss << NetVarManager::dumpTable(table, 0);
	}

	getcwd(cwd, sizeof(cwd));

	std::string netvarsPath = std::string(cwd) + "/netvars.txt";

	std::ofstream(netvarsPath) << ss.str();
}
