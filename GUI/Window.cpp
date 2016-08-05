#include "stdafx.h"
#include "Window.h"

Window::Window(HINSTANCE hInst, Dictionary::ITranslatorController* controller) :m_hInstance(hInst), m_controller(controller)
{
	const int MAX_LOADSTRING = 100;
	TCHAR buf[MAX_LOADSTRING];
	LoadString(m_hInstance, IDS_APP_TITLE, buf, MAX_LOADSTRING);
	m_title = buf;
	LoadString(m_hInstance, IDC_GUI, buf, MAX_LOADSTRING);
	m_window_class = buf;

	registerClass();
}


Window::~Window()
{
}

ATOM Window::registerClass()
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = Window::msgRouter;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hInstance;
	wcex.hIcon = LoadIcon(m_hInstance, MAKEINTRESOURCE(IDI_GUI));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_GUI);
	wcex.lpszClassName = m_window_class.c_str();
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

BOOL Window::init(int nCmdShow)
{
	int width = 340;
	int height = 400;
	int x = GetSystemMetrics(SM_CXSCREEN) / 2 - width;
	int y = GetSystemMetrics(SM_CYSCREEN) / 2 - height / 2;
	m_hWnd = CreateWindow(m_window_class.c_str(), m_title.c_str(), WS_OVERLAPPEDWINDOW, x, y, width, height, NULL, NULL, m_hInstance, this);

	if (!m_hWnd)
	{
		return FALSE;
	}

	ShowWindow(m_hWnd, nCmdShow);
	UpdateWindow(m_hWnd);

	return TRUE;
}

LRESULT CALLBACK Window::msgRouter(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_NCCREATE)
	{
		CREATESTRUCT * pcs = (CREATESTRUCT*)lParam;
		Window* wnd = reinterpret_cast<Window*>(pcs->lpCreateParams);
		wnd->m_hWnd = hWnd;
		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG)pcs->lpCreateParams);
		return TRUE;
	}
	else
	{
		Window* wnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
		if (wnd)
		{
			return wnd->wndProc(hWnd, message, wParam, lParam);
		}
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT CALLBACK Window::wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	static std::shared_ptr<Dictionary::ITranslatorController> controller;



	switch (message)
	{
	case WM_CREATE:
	{
		onCreate();
		break;
	}
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		switch (wmId)
		{
		case IDC_BUTTON_TRANSLATE:
		{
			onTranslateButtonClick();
			break;
		}
		case IDC_BUTTON_SEARCH:
		{
			onSearchButtonClick();
			break;
		}
		case IDC_BUTTON_CHANGE:
		{
			onChangeButtonClick();
			break;
		}
		case ID_FILE_SETTINGS:
			DialogBox(m_hInstance, MAKEINTRESOURCE(IDD_PROP), m_hWnd, NULL);
			break;
		case IDM_ABOUT:
			DialogBox(m_hInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), m_hWnd, Window::About);
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
		onMouseWheel(wParam, lParam);
		break;
	case WM_DESTROY:
		onDestroy();
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void Window::onCreate()
{
	HWND splash = CreateDialog(m_hInstance, MAKEINTRESOURCE(IDD_SPLASH), m_hWnd, NULL);

	auto state = m_controller->getState();
	std::wstring cur_lang = state.getFrom().getName() + L"->" + state.getTo().getName();

	m_hListBox = CreateWindowEx(WS_EX_CLIENTEDGE, L"LISTBOX", L"", WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_AUTOVSCROLL, 10, 40, 300, 150, m_hWnd, reinterpret_cast<HMENU>(IDC_LIST_BOX), m_hInstance, NULL);
	m_hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, 10, 10, 300, 20, m_hWnd, reinterpret_cast<HMENU>(IDC_EDIT), m_hInstance, NULL);
	m_hEditResult = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"", WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, 10, 250, 300, 20, m_hWnd, reinterpret_cast<HMENU>(IDC_EDIT_RESULT), m_hInstance, NULL);
	m_hButtonChange = CreateWindowEx(NULL, L"BUTTON", cur_lang.c_str(), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10, 300, 140, 24, m_hWnd, reinterpret_cast<HMENU>(IDC_BUTTON_CHANGE), m_hInstance, NULL);
	CreateWindowEx(NULL, L"BUTTON", L"Translate", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 160, 300, 100, 24, m_hWnd, reinterpret_cast<HMENU>(IDC_BUTTON_TRANSLATE), m_hInstance, NULL);
	CreateWindowEx(NULL, L"BUTTON", L"Search", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 90, 200, 150, 24, m_hWnd, reinterpret_cast<HMENU>(IDC_BUTTON_SEARCH), m_hInstance, NULL);
	SendMessage(m_hEditResult, EM_SETREADONLY, TRUE, NULL);
	DestroyWindow(splash);
}

void Window::onDestroy()
{
	//settings->save(controller->getDirection());
	//delete controller;
}

void Window::onTranslateButtonClick()
{
	int selected_index = (int)SendMessage(m_hListBox, LB_GETCURSEL, NULL, NULL);
	if (selected_index != LB_ERR)
	{
		int text_len = (int)SendMessage(m_hListBox, LB_GETTEXTLEN, static_cast<WPARAM>(selected_index), NULL);
		TCHAR* buf = new TCHAR[text_len + 1];
		SendMessage(m_hListBox, LB_GETTEXT, static_cast<WPARAM>(selected_index), reinterpret_cast<LPARAM>(buf));
		std::wstring selected_word(buf);
		delete[] buf;
		auto translations = m_controller->translate(selected_word);
		std::wstring str;
		for (auto translation : translations)
		{
			str += translation + L", ";
		}
		str.pop_back();
		str.pop_back();
		SetWindowText(m_hEditResult, str.c_str());
	}
}

void Window::onSearchButtonClick()
{
	int edit_length = GetWindowTextLength(m_hEdit);
	LPTSTR buf = new TCHAR[edit_length + 1];
	GetWindowText(m_hEdit, buf, edit_length + 1);
	std::wstring edit_text(buf);
	delete[] buf;

	auto words = m_controller->find(edit_text, 2);
	SendMessage(m_hListBox, LB_RESETCONTENT, NULL, NULL);
	for (auto word : words)
	{
		SendMessage(m_hListBox, LB_ADDSTRING, NULL, reinterpret_cast<LPARAM>(word.c_str()));
	}
}

void Window::onChangeButtonClick()
{
	m_controller->switchState();
}

void Window::onMouseWheel(WPARAM wParam, LPARAM lParam)
{
	SendMessage(m_hListBox, WM_MOUSEWHEEL, wParam, lParam);
}

void Window::onSwitchState()
{
	auto state = m_controller->getState();
	std::wstring cur_lang = state.getFrom().getName() + L"->" + state.getTo().getName();
	SendMessage(m_hButtonChange, WM_SETTEXT, 0, reinterpret_cast<LPARAM>(cur_lang.c_str()));
	SendMessage(m_hListBox, LB_RESETCONTENT, NULL, NULL);
	SetWindowText(m_hEditResult, L"");
}

INT_PTR CALLBACK Window::About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}