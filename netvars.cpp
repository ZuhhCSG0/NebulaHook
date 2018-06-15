#include "sdk.h"
#include <stdio.h>
#include "xor.h"
CNetVars *g_pNetVars = 0;

CNetVars::CNetVars(void)
{
	m_tables.clear();

	ClientClass *clientClass = g_pClient->GetAllClasses();
	if (!clientClass)
		return;

	while (clientClass)
	{
		RecvTable *recvTable = clientClass->m_pRecvTable;
		m_tables.push_back(recvTable);

		clientClass = clientClass->m_pNext;
	}
}

void LogNet(const char* szString)
{
	FILE* stream;

	errno_t pFile = fopen_s(&stream, XorStr("NetVarDump.txt"), XorStr("a"));
	fprintf(stream, szString);
	fclose(stream);
}

// calls GetProp wrapper to get the absolute offset of the prop
int CNetVars::GetOffset(const char *tableName, const char *propName)
{
	int offset = this->GetProp(tableName, propName);
	if (!offset)
	{
		//g_pCVar->ConsoleColorPrintf(Color::Red(), "%s not found!\n", propName);
		Msg(XorStr("%s not found!\n"), propName);
		return 0;
	}
	//g_pCVar->ConsoleColorPrintf(Color::Green(), "%s: 0x%02X\n", propName, offset);
	Msg(XorStr("%s: 0x%02X\n"), propName, offset);
	return offset;
}


// calls GetProp wrapper to get prop and sets the proxy of the prop
bool CNetVars::HookProp(const char *tableName, const char *propName, RecvVarProxyFn fun)
{
	RecvProp *recvProp = 0;
	this->GetProp(tableName, propName, &recvProp);
	if (!recvProp)
		return false;

	recvProp->m_ProxyFn = fun;

	return true;
}


// wrapper so we can use recursion without too much performance loss
int CNetVars::GetProp(const char *tableName, const char *propName, RecvProp **prop)
{
	RecvTable *recvTable = GetTable(tableName);
	if (!recvTable)
		return 0;

	int offset = this->GetProp(recvTable, propName, prop);
	if (!offset)
		return 0;

	return offset;
}


// uses recursion to return a the relative offset to the given prop and sets the prop param
int CNetVars::GetProp(RecvTable *recvTable, const char *propName, RecvProp **prop)
{
	int extraOffset = 0;
	for (int i = 0; i < recvTable->m_nProps; ++i)
	{
		RecvProp *recvProp = &recvTable->m_pProps[i];
		RecvTable *child = recvProp->m_pDataTable;

		if (child && (child->m_nProps > 0))
		{
			int tmp = this->GetProp(child, propName, prop);
			if (tmp)
				extraOffset += (recvProp->m_Offset + tmp);
		}

		if (_stricmp(recvProp->m_pVarName, propName))
			continue;

		if (prop)
			*prop = recvProp;

		return (recvProp->m_Offset + extraOffset);
	}

	return extraOffset;
}


RecvTable *CNetVars::GetTable(const char *tableName)
{
	if (m_tables.empty())
		return 0;

	for each (RecvTable *table in m_tables)
	{
		if (!table)
			continue;

		if (_stricmp(table->m_pNetTableName, tableName) == 0)
			return table;
	}

	return 0;
}

void CNetVars::DumpTable(RecvTable *table, bool log)
{
	/*for (int i = 0; i < table->m_nProps; i++)
	{
		RecvProp *prop = &table->m_pProps[i];
		if (!strcmp(prop->m_pVarName, "baseclass"))
		{
			//g_pCVar->ConsoleColorPrintf(Color::Green(), "--> baseclass: %s\n", prop->GetDataTable()->GetName());
			//if (log)
			//{
			//	char msg[999];
			//	sprintf(msg, "--> baseclass: %s\n", prop->GetDataTable()->GetName());
			//	LogNet(msg);
			//}
			//continue;
		}

		g_pCVar->ConsoleColorPrintf(Color::Green(), "----> %s [0x%02X]\n", prop->GetName(), prop->GetOffset());
		if (log)
		{
			char msg[999];
			sprintf(msg, "----> %s[0x % 02X]\n", prop->GetName(), prop->GetOffset());
			LogNet(msg);
		}
		if (prop->GetDataTable())
		{
			DumpTable(prop->GetDataTable(), log); //recursive call 
		}
	}*/
}

void CNetVars::DumpNetvars(bool log)
{
	/*g_pCVar->ConsoleColorPrintf(Color::Green(), "CSGO Dumper by VC-Xer0");
	if (log)
	{
		LogNet("CSGO Dumper by VC-Xer0");
	}
	for (ClientClass *pClass = clientdll->GetAllClasses(); pClass != NULL; pClass = pClass->m_pNext)
	{
		RecvTable *table = pClass->m_pRecvTable;
		g_pCVar->ConsoleColorPrintf(Color::Green(), "\n\t> %s <", pClass->m_pRecvTable->m_pNetTableName);
		if (log)
		{
			char msg[999];
			sprintf(msg, "\n\t> %s <", pClass->m_pRecvTable->m_pNetTableName);
			LogNet(msg);
		}
		DumpTable(table, log);
	}*/
}



netvar_system netvars;

void netvar_system::initialize()
{
	database.clear();

	for (auto clientclass = g_pClient->GetAllClasses();
		clientclass != nullptr;
		clientclass = clientclass->m_pNext) {
		if (clientclass->m_pRecvTable) {
			database.emplace_back(load_table(clientclass->m_pRecvTable));
		}
	}
}

netvar_system::netvar_table netvar_system::load_table(RecvTable* recvTable)
{
	auto table = netvar_table{};

	table.offset = 0;
	table.name = recvTable->m_pNetTableName;

	for (auto i = 0; i < recvTable->m_nProps; ++i) {
		auto prop = &recvTable->m_pProps[i];

		if (!prop || isdigit(prop->m_pVarName[0]))
			continue;
		if (strcmp("baseclass", prop->m_pVarName) == 0)
			continue;

		if (prop->m_RecvType == DPT_DataTable && prop->m_pDataTable) {
			table.child_tables.emplace_back(load_table(prop->m_pDataTable));
			table.child_tables.back().offset = prop->m_Offset;
			table.child_tables.back().prop = prop;
		}
		else {
			table.child_props.emplace_back(prop);
		}
	}
	return table;
}

void netvar_system::dump()
{
	auto s = std::ofstream("netvar_dump.txt");
	dump(s);
}
void netvar_system::dump(std::ostream& stream)
{
	for (const auto& table : database) {
		if (table.child_props.empty() && table.child_tables.empty())
			continue;
		stream << table.name << '\n';
		dump_table(stream, table, 1);
		stream << '\n';
	}

	stream << std::endl;
}

void netvar_system::dump_table(std::ostream& stream, const netvar_table& table, uint32_t indentation)
{
	char line_buffer[1024];

	for (const auto& prop : table.child_props) {
		sprintf_s(line_buffer, "%*c%*s: 0x%08X", indentation * 4, ' ', -(50 - (int)indentation * 4), prop->m_pVarName, prop->m_Offset);
		stream << line_buffer << '\n';
	}
	for (const auto& child : table.child_tables) {
		sprintf_s(line_buffer, "%*c%*s: 0x%08X", indentation * 4, ' ', -(50 - (int)indentation * 4), child.prop->m_pVarName, child.prop->m_Offset);
		stream << line_buffer << '\n';
		dump_table(stream, child, indentation + 1);
	}
}

uint32_t netvar_system::find(const std::string& tableName, const std::string& propName)
{
	auto result = 0u;
	for (const auto& table : database) {
		if (table.name == tableName) {
			result = find(table, propName);
			if (result != 0)
				return result;
		}
	}
	return 0;
}

uint32_t netvar_system::find(const netvar_system::netvar_table& table, const std::string& propName)
{
	for (const auto& prop : table.child_props) {
		if (strncmp(prop->m_pVarName, propName.data(), propName.size()) == 0) {
			return table.offset + prop->m_Offset;
		}
	}
	for (const auto& child : table.child_tables) {
		auto prop_offset = find(child, propName);
		if (prop_offset != 0)
			return table.offset + prop_offset;
	}
	for (const auto& child : table.child_tables) {
		if (strncmp(child.prop->m_pVarName, propName.data(), propName.size()) == 0) {
			return table.offset + child.offset;
		}
	}
	return 0;
}
RecvVarProxyFn netvar_system::hook_prop(const std::string& tableName, const std::string& propName, void* hkFunc, RecvVarProxyFn oldFn)
{
	RecvProp* recvProp = get_prop(tableName, propName);

	if (!recvProp)
		return nullptr;

	oldFn = (RecvVarProxyFn)recvProp->m_ProxyFn;
	recvProp->m_ProxyFn = (RecvVarProxyFn)hkFunc;
	return oldFn;
}
RecvProp* netvar_system::get_prop(const std::string& tableName, const std::string& propName)
{
	RecvProp* result = nullptr;
	for (const auto& table : database) {
		if (table.name == tableName) {
			result = get_prop(table, propName);
		}
	}
	return result;
}

RecvProp* netvar_system::get_prop(const netvar_system::netvar_table& table, const std::string& propName)
{
	for (const auto& prop : table.child_props) {
		if (strncmp(prop->m_pVarName, propName.data(), propName.size()) == 0) {
			return prop;
		}
	}
	for (const auto& child : table.child_tables) {
		auto prop = get_prop(child, propName);
		if (prop != 0)
			return prop;
	}
	for (const auto& child : table.child_tables) {
		if (strncmp(child.prop->m_pVarName, propName.data(), propName.size()) == 0) {
			return child.prop;
		}
	}
	return nullptr;
}