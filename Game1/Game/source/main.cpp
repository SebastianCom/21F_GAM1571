
#include "Framework.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	fw::FWCore fwcore;

	fwcore.Init( 600, 600 );
	fwcore.Run();

	fwcore.Shutdown();
}