#pragma once


typedef void (InitFunc_t)();

class AliceLoader
{
	static std::string exePath;
public:
	enum class EGame : uint32_t
	{
		episode1,
		episode2,
		episode2beta,
		unknown
	};

	// AML
	static bool enableConsole;
	static bool waitForDebugger;
	static bool isDebug;
	static bool skipCodeModules;
	static bool useModList;

	static EGame detectedGame; 
	static std::string patcherDir;

	// Episode 1 Specific
	static float ep1Width;
	static float ep1Height;

	// Episode 2 Specific
	static float ep2FPSTarget;
	

	static void TestFunc();
	static void InitLoader();
	static void LaunchExternalPatcher();
	static void IdentifyApp();

	static void ReadList();
	static void ApplyPatches();
	static void LoadCodeMods();

	static void LoadExternalModule(std::string file, std::string relativePath = "", std::string modName = "");
	static void LoadExternalModule_Direct(const std::string& filePath);
};