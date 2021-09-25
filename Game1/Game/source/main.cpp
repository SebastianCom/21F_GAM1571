
#include "Framework.h"
#include "Game.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	fw::FWCore fwcore;

	Game game( fwcore);

	fwcore.Init( 600, 600 );
	game.Init();
	fwcore.Run( game );

	fwcore.Shutdown();
}