#include "pch.h"
#include "main.h"
#include "AppDelegate.h"

#ifdef _DEBUG
#include <vld.h>
#endif

int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// create the application instance
	AppDelegate app;
	return Application::getInstance()->run();
}