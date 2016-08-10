#include "stdafx.h"
#include "resource.h"
#include <fstream>
#include "../Translator/TranslatorAPI.h"
#include "Window.h"
#include "../Translator/Locator.h"



int APIENTRY _tWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPTSTR lpCmdLine, _In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	MSG msg;
	HACCEL hAccelTable;

	auto controller = Dictionary::Locator::Instance().createTranslatorController();
	controller->createTranslator();
	
	std::shared_ptr<Window> window(new Window(hInstance, controller));

	controller->setView(std::shared_ptr<Dictionary::IView>(window));
	window->init(nCmdShow);

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GUI));
	
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return (int)msg.wParam;
}