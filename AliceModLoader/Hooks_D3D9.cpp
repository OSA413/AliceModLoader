#include "Hooks_D3D9.h"
//#include <d3d9.h>


// D3D9 (For S4E2)
void* (WINAPI* Direct3DCreate9Ptr)(UINT SDKVersion);
void* WINAPI Direct3DCreate9(UINT SDKVersion)
{
#pragma EXPORT
	if (!Direct3DCreate9Ptr) HookD3D9();
	return Direct3DCreate9Ptr(SDKVersion);
}

// D3D9Ex (For S4E1)
HRESULT* (WINAPI* Direct3DCreate9ExPtr)(UINT SDKVersion, void** d3d);
HRESULT* WINAPI Direct3DCreate9Ex(UINT SDKVersion, void** d3d)
{
#pragma EXPORT
	if (!Direct3DCreate9ExPtr) HookD3D9();
	return Direct3DCreate9ExPtr(SDKVersion, d3d);
}


// Responsible for running AML tasks & loading the real d3d9 module
static void HookD3D9()
{
	if (AliceLoader::waitForDebugger)
	{
		printf("Waiting for debugger to attach... (Press ESCAPE to skip)\n\n");
		while (!::IsDebuggerPresent())
		{
			// Cancel if user presses the escape key
			if (GetAsyncKeyState(VK_ESCAPE) & 1)
			{
				AliceLoader::waitForDebugger = false;
				goto SkipWait;
			}
			::Sleep(100);
		}
	}

SkipWait:
	if (AliceLoader::skipCodeModules)
		printf("Loading of external modules is disabled, skipping...\n");
	else
		AliceLoader::LoadCodeMods();

	// Start AMBPatcher process
	AliceLoader::LaunchExternalPatcher();

	// Redirect the hooked function calls to the *actual* d3d9.dll
	wchar_t windir[MAX_PATH];
	GetSystemDirectoryW(windir, MAX_PATH);
	wchar_t d3dpath[MAX_PATH];

	_snwprintf(d3dpath, MAX_PATH, L"%s\\d3d9.dll", windir);
	const HMODULE d3d9_module = LoadLibraryW(d3dpath);
	Direct3DCreate9Ptr = (decltype(Direct3DCreate9Ptr))GetProcAddress(d3d9_module, "Direct3DCreate9");
	Direct3DCreate9ExPtr = (decltype(Direct3DCreate9ExPtr))GetProcAddress(d3d9_module, "Direct3DCreate9Ex");
}
