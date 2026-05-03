#pragma once
#include "AliceLoader.h"


namespace Hooks
{
	constexpr int32_t TEXTCOLOR_CYAN  = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
	constexpr int32_t TEXTCOLOR_WHITE = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;

	// Redirect file loading if a match exists in the ./#Work/ directory
	HOOK(HANDLE, __stdcall, _CreateFileA, PROC_ADDRESS("Kernel32.dll", "CreateFileA"), LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)
	{
		std::string oldPath = lpFileName;
		std::string workFolderPath = "\\#Work\\" + oldPath;
		std::string newPath = FileService::GetModuleDir().c_str() + workFolderPath;

		// Debug
		if (AliceLoader::isDebug)
			printf("File read: \"%s\"\n", oldPath.c_str());

		// Redirect file read if it exists in the #Work folder
		if (FileService::FileExists(newPath.c_str()))
		{
			const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, TEXTCOLOR_CYAN);
			printf("Redirect: \"\\%s\" --> \"%s\"\n", oldPath.c_str(), workFolderPath.c_str());
			SetConsoleTextAttribute(hConsole, TEXTCOLOR_WHITE);

			return CreateFileW(std::wstring(newPath.begin(), newPath.end()).c_str(), dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
		}
		
		return CreateFileW(std::wstring(oldPath.begin(), oldPath.end()).c_str(), dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
	}


	static void InstallGenericHooks()
	{
		INSTALL_HOOK(_CreateFileA);
	}
}
