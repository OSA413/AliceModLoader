#pragma once
#include "AliceLoader.h"


void HookD3D9();

namespace Hooks
{
	// (These are properly defined at the bottom of this file)
	//void* (WINAPI* Direct3DCreate9Ptr)(UINT SDKVersion);
	//HRESULT* (WINAPI* Direct3DCreate9ExPtr)(UINT SDKVersion, void** d3d);


	//// Responsible for running AML tasks & loading the real d3d9 module
	//static void HookD3D9()
	//{
	//	if (AliceLoader::waitForDebugger)
	//	{
	//		printf("Waiting for debugger to attach... (Press ESCAPE to skip)\n\n");
	//		while (!::IsDebuggerPresent())
	//		{
	//			// Cancel if user presses the escape key
	//			if (GetAsyncKeyState(VK_ESCAPE) & 1)
	//			{
	//				AliceLoader::waitForDebugger = false;
	//				goto SkipWait;
	//			}
	//			::Sleep(100);
	//		}
	//	}

	//SkipWait:
	//	if (AliceLoader::skipCodeModules)
	//		printf("Loading of external modules is disabled, skipping...\n");
	//	else
	//		AliceLoader::LoadCodeMods();

	//	// Start AMBPatcher process
	//	AliceLoader::LaunchExternalPatcher();

	//	// Redirect the hooked function calls to the *actual* d3d9.dll
	//	wchar_t windir[MAX_PATH];
	//	GetSystemDirectoryW(windir, MAX_PATH);
	//	wchar_t d3dpath[MAX_PATH];

	//	_snwprintf(d3dpath, MAX_PATH, L"%s\\d3d9.dll", windir);
	//	const HMODULE d3d9_module = LoadLibraryW(d3dpath);
	//	Direct3DCreate9Ptr = (decltype(Direct3DCreate9Ptr))GetProcAddress(d3d9_module, "Direct3DCreate9");
	//	Direct3DCreate9ExPtr = (decltype(Direct3DCreate9ExPtr))GetProcAddress(d3d9_module, "Direct3DCreate9Ex");
	//}


	//// D3D9 Stuff
	//VTABLE_HOOK(HRESULT, WINAPI, IDirect3DDevice9, Reset, D3DPRESENT_PARAMETERS* pPresentationParameters)
	//{
	//	//::GpuDeviceReset();
	//	return originalIDirect3DDevice9Reset(This, pPresentationParameters);
	//}
	//VTABLE_HOOK(HRESULT, WINAPI, IDirect3DDevice9, Present, RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion)
	//{
	//	//::OnFrame(); // Process OnFrame events for loaded code mods (NOT IMPL)
	//	return originalIDirect3DDevice9Present(This, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
	//}


	//// [[ EPISODE 2 ONLY - Do not use in AML! ]]
	//// This gets called when the UserConfig.cfg gets parsed in GsEnvInit()
	//HOOK(void, __fastcall, sub_6C8F70, 0x6C8F70, DWORD32* This)
	//{
	//	// S4E2 stores the window handle and D3D9 device pointer at a static address, which is super nice!
	//	//HWND* window = (HWND*)0x890910;
	//	IDirect3DDevice9** pDevice = (IDirect3DDevice9**)0x890950;

	//	static bool is_init = false;
	//	if (*pDevice)
	//	{
	//		if (!is_init)
	//		{
	//			INSTALL_VTABLE_HOOK(IDirect3DDevice9, *pDevice, Reset, 16);
	//			INSTALL_VTABLE_HOOK(IDirect3DDevice9, *pDevice, Present, 17);
	//		}
	//		is_init = true;
	//	}

	//	return originalsub_6C8F70(This);
	//}


	static void InstallD3D9Hooks()
	{
        switch (AliceLoader::detectedGame)
        {
            case AliceLoader::EGame::episode1:
			    break;

		    case AliceLoader::EGame::episode2:
			    //INSTALL_HOOK(sub_6C8F70); // This hook will only work for S4E2.
			    break;

		    case AliceLoader::EGame::episode2beta:
			    break;

		    case AliceLoader::EGame::unknown:
            default:
			    break;
        }
	}
}


//// D3D9 (For S4E2)
//void* (WINAPI* Direct3DCreate9Ptr)(UINT SDKVersion);
//void* WINAPI Direct3DCreate9(UINT SDKVersion)
//{
//#pragma EXPORT
//	if (!Direct3DCreate9Ptr) Hooks::HookD3D9();
//	return Direct3DCreate9Ptr(SDKVersion);
//}
//
//// D3D9Ex (For S4E1)
//HRESULT* (WINAPI* Direct3DCreate9ExPtr)(UINT SDKVersion, void** d3d);
//HRESULT* WINAPI Direct3DCreate9Ex(UINT SDKVersion, void** d3d)
//{
//#pragma EXPORT
//	if (!Direct3DCreate9ExPtr) Hooks::HookD3D9();
//	return Direct3DCreate9ExPtr(SDKVersion, d3d);
//}

//IDirect3DDevice9
//D3DPRESENT_PARAMETERS*