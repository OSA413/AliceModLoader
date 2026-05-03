#include "ModList.h"
#include "Config.h"


void ModList::ReadList()
{
	
}


ModList::ModInfo GetModInfo()
{
	ModList::ModInfo info;
	info.CodeModule = "";
    info.ModName = "";
	return info;
}


ModList::ModInfo GetModInfo(const std::string& in_ModIni)
{
	ModList::ModInfo info = {};
	
	if (Config::configPath.empty())
		Config::GetAliceFolder();

	printf("Reading mod info...\n");

	const INIReader reader(Config::configPath + in_ModIni);

	if (reader.ParseError() != 0)
	{
		printf("Could not load mod.ini!");
		return info;
	}

	info.CodeModule = reader.Get("Mod", "Module", "");
	info.ModName = reader.Get("Description", "Title", "");

	return info;
}