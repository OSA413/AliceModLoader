#pragma once


class ModList
{
public:
	struct ModInfo
	{
		std::string CodeModule = {};
		std::string ModName = {};
		bool UsesCustomSave = false;
	};

	static void ReadList();
	static ModInfo GetModInfo(const std::string& in_ModIni);
};
