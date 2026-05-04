#include "HookContainer.h"
#include "Hooks_D3D9.h"
#include "Hooks_Generic.h"


void HookContainer::InstallHooks()
{
	Hooks::InstallGenericHooks();
	Hooks::InstallD3D9Hooks();
	//Hooks::InstallCriFSHooks();
}