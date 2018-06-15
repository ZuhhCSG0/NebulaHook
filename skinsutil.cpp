#include "skinsutil.h"
#include <string>
#include <Shlobj.h>
#include "sdk.h"

std::unordered_map<std::string, int> SkinsUtil::data;

DynSkin::Skins::CSkins* SkinsUtil::pSkins = new DynSkin::Skins::CSkins();

string GetModuleFilePath(HMODULE hModule)
{
	string ModuleName = "";
	char szFileName[MAX_PATH] = { 0 };

	if (GetModuleFileNameA(hModule, szFileName, MAX_PATH))
		ModuleName = szFileName;

	return ModuleName;
}


string GetModuleBaseDir(HMODULE hModule)
{
	string ModulePath = GetModuleFilePath(hModule);
	return ModulePath.substr(0, ModulePath.find_last_of("\\/"));
}

void SkinsUtil::ParseSkins()
{
	char filename[MAX_PATH];
	GetModuleFileName(NULL, filename, MAX_PATH);
	std::string filestr(filename);
	std::string filepath = filestr.substr(0, filestr.size() - 4);


	Msg(filepath.c_str());


	string CsgoPatch = GetModuleBaseDir(0) + "\\csgo";

	if (pSkins->Load(CsgoPatch, "csgo"))
	{
		pSkins->Dump(std::ofstream("D:\\skins.txt"));	
	}

	for (auto& w : pSkins->GetSkinInfo())
	{
		data.insert(std::pair<std::string, int>(w.first, 0));
	}
}

void SkinsUtil::SaveSkins()
{
	static TCHAR szPath[MAX_PATH];
	static char szFolder[MAX_PATH];
	static char szFile[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, szPath)))
	{
		sprintf_s(szFolder, "%s\\phoenix\\", szPath);
		sprintf_s(szFile, "%s\\phoenix\\%s.ini", szPath, "skins");
	}

	CreateDirectory(szFolder, NULL);

	for (auto& skin : data)
	{
		WritePrivateProfileString("Skins", skin.first.c_str(), std::to_string(skin.second).c_str(), szFile);
	}
}

void SkinsUtil::LoadSkins()
{
	static TCHAR szPath[MAX_PATH];
	static char szFolder[MAX_PATH];
	static char szFile[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, szPath)))
	{
		sprintf_s(szFolder, "%s\\phoenix\\", szPath);
		sprintf_s(szFile, "%s\\phoenix\\%s.ini", szPath, "skins");
	}

	CreateDirectory(szFolder, NULL);

	char szValue[16];

	for (auto& skin : data)
	{
		GetPrivateProfileString("Skins", skin.first.c_str(), "", szValue, 16, szFile);
		skin.second = atoi(szValue);
	}
}

void SkinsUtil::DumpSkinConfig()
{
	for (auto skin : data)
	{
		Msg("%s -> %d\n", skin.first.c_str(), skin.second);
	}
}