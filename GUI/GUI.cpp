#include "stdafx.h"
#include "resource.h"
#include <Dictionary.h>
#include <fstream>

#define MAX_LOADSTRING 100
#define IDC_BUTTON_TRANSLATE 30000
#define IDC_EDIT 30001
#define IDC_EDIT_RESULT 30002
#define IDC_BUTTON_CHANGE 30003
#define IDC_LIST_BOX 30004
#define IDC_BUTTON_SEARCH 30005

HINSTANCE hInst;
TCHAR szTitle[MAX_LOADSTRING];
TCHAR szWindowClass[MAX_LOADSTRING];
WNDPROC defEditProc;

ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK subEditProc(HWND, UINT, WPARAM, LPARAM);
std::wstring LoadFromRes(unsigned int id);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	MSG msg;
	HACCEL hAccelTable;

	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_GUI, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

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

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GUI));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_GUI);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance;
	int width = 340;
	int height = 400;
	int x = GetSystemMetrics(SM_CXSCREEN) / 2 - width;
	int y = GetSystemMetrics(SM_CYSCREEN) / 2 - height / 2;
	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, x, y, width, height, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hEdit, hEditResult, hButtonChange, hListBox;
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	static Dictionary::IDictionaryController* controller;
	static std::shared_ptr<Dictionary::ISettings> settings;

	switch (message)
	{
	case WM_CREATE:
	{
		settings = Dictionary::SettingsFactory::create();
		auto controller_switch_callback = [&]()
		{
			std::wstring cur_lang = controller->getDirectionText();
			SendMessage(hButtonChange, WM_SETTEXT, 0, reinterpret_cast<LPARAM>(cur_lang.c_str()));
			SendMessage(hListBox, LB_RESETCONTENT, NULL, NULL);
			SetWindowText(hEditResult, L""); 
		};
		HWND splash = CreateDialog(hInst, MAKEINTRESOURCE(IDD_SPLASH), hWnd, NULL);
		Dictionary::DictionaryFactory factory;
		std::wstring dict_filename = L"dictionary.dat";
#ifdef _DEBUG
		dict_filename = L"debugdict.dat";
#endif
		std::shared_ptr<Dictionary::IDictionary> dict = factory.create(dict_filename);
		controller = new Dictionary::DictionaryController(dict, controller_switch_callback, settings->load());

		hListBox = CreateWindowEx(WS_EX_CLIENTEDGE, L"LISTBOX", L"", WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_AUTOVSCROLL, 10, 40, 300, 150, hWnd, reinterpret_cast<HMENU>(IDC_LIST_BOX), hInst, NULL);
		hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, 10, 10, 300, 20, hWnd, reinterpret_cast<HMENU>(IDC_EDIT), hInst, NULL);
		defEditProc = (WNDPROC)SetWindowLongPtr(hEdit, GWLP_WNDPROC, (LONG_PTR)subEditProc);
		hEditResult = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, 10, 250, 300, 20, hWnd, reinterpret_cast<HMENU>(IDC_EDIT_RESULT), hInst, NULL);
		hButtonChange = CreateWindowEx(NULL, L"BUTTON", controller->getDirectionText().c_str(), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 50, 300, 100, 24, hWnd, reinterpret_cast<HMENU>(IDC_BUTTON_CHANGE), hInst, NULL);
		CreateWindowEx(NULL, L"BUTTON", LoadFromRes(IDS_TRANSLATE_BUTTON).c_str(), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 160, 300, 100, 24, hWnd, reinterpret_cast<HMENU>(IDC_BUTTON_TRANSLATE), hInst, NULL);
		CreateWindowEx(NULL, L"BUTTON", LoadFromRes(IDS_SEARCH_BUTTON).c_str(), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 90, 200, 150, 24, hWnd, reinterpret_cast<HMENU>(IDC_BUTTON_SEARCH), hInst, NULL);
		SendMessage(hEditResult, EM_SETREADONLY, TRUE, NULL);
		DestroyWindow(splash);
		break;
	}
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		switch (wmId)
		{
		case IDC_BUTTON_TRANSLATE:
		{
			int selected_index = (int)SendMessage(hListBox, LB_GETCURSEL, NULL, NULL);
			if (selected_index != LB_ERR)
			{
				int text_len = (int)SendMessage(hListBox, LB_GETTEXTLEN, static_cast<WPARAM>(selected_index), NULL);
				TCHAR* buf = new TCHAR[text_len + 1];
				SendMessage(hListBox, LB_GETTEXT, static_cast<WPARAM>(selected_index), reinterpret_cast<LPARAM>(buf));
				std::wstring selected_word(buf);
				delete[] buf;
				std::wstring translation = controller->getDictionary()->translate(selected_word, controller->getDirection());
				SetWindowText(hEditResult, translation.c_str());
			}
			break;
		}
		case IDC_BUTTON_SEARCH:
		{
			int edit_length = GetWindowTextLength(hEdit);
			LPTSTR buf = new TCHAR[edit_length + 1];
			GetWindowText(hEdit, buf, edit_length + 1);
			std::wstring edit_text(buf);
			delete[] buf;
			controller->detectDirection(edit_text);
			auto words = controller->getDictionary()->find(edit_text, 2, controller->getDirection());
			SendMessage(hListBox, LB_RESETCONTENT, NULL, NULL);
			for (auto word : words)
			{
				SendMessage(hListBox, LB_ADDSTRING, NULL, reinterpret_cast<LPARAM>(word.c_str()));
			}
			break;
		}
		case IDC_BUTTON_CHANGE:
		{
			controller->switchDirection();
			break;
		}
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_MOUSEWHEEL:
		SendMessage(hListBox, message, wParam, lParam);
		break;
	case WM_DESTROY:
		settings->save(controller->getDirection());
		delete controller;
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

LRESULT CALLBACK subEditProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_RETURN:
			HWND parentHandle = GetParent(wnd);
			SendMessage(parentHandle, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_SEARCH, 0), 0);
			break;
		}
		break;
	default:
		return CallWindowProc(defEditProc, wnd, msg, wParam, lParam);
	}
	return 0;
}

std::wstring LoadFromRes(unsigned int id)
{
	TCHAR* buf = new TCHAR[100];
	LoadString(hInst, id, buf, 100);
	std::wstring res(buf);
	delete[] buf;
	return res;
}