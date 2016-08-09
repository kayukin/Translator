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
	if (!GetClassInfoEx(m_hInstance, m_window_class.c_str(), &wcex))
	{
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
	else
	{
		return TRUE;
	}
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
		case IDC_COMBO:
			if (wmEvent == CBN_EDITCHANGE)
			{
				onComboChange();
			}
		case IDC_BUTTON_TRANSLATE:
			onTranslateButtonClick();
			break;
		case IDC_BUTTON_SEARCH:
			onSearchButtonClick();
			break;
		case IDC_BUTTON_CHANGE:
			onChangeButtonClick();
			break;
		case ID_FILE_OPEN:
			onOpenFile();
			break;
		case IDM_ABOUT:
			onAbout();
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
		onPaint(&hdc);
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
	
	m_hListBox = CreateWindowEx(WS_EX_CLIENTEDGE, WC_LISTBOX, L"", WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_AUTOVSCROLL, 10, 40, 300, 150, m_hWnd, reinterpret_cast<HMENU>(IDC_LIST_BOX), m_hInstance, NULL);

	m_hCombo = CreateWindow(WC_COMBOBOX, TEXT(""), CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 10, 10, 300, 500, m_hWnd, reinterpret_cast<HMENU>(IDC_COMBO), m_hInstance, NULL);

	m_hEditResult = CreateWindowEx(WS_EX_CLIENTEDGE, WC_EDIT, L"", WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, 10, 250, 300, 20, m_hWnd, reinterpret_cast<HMENU>(IDC_EDIT_RESULT), m_hInstance, NULL);
	m_hButtonChange = CreateWindowEx(NULL, WC_BUTTON, cur_lang.c_str(), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10, 300, 140, 24, m_hWnd, reinterpret_cast<HMENU>(IDC_BUTTON_CHANGE), m_hInstance, NULL);
	CreateWindowEx(NULL, WC_BUTTON, L"Translate", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 160, 300, 100, 24, m_hWnd, reinterpret_cast<HMENU>(IDC_BUTTON_TRANSLATE), m_hInstance, NULL);
	CreateWindowEx(NULL, WC_BUTTON, L"Search", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 90, 200, 150, 24, m_hWnd, reinterpret_cast<HMENU>(IDC_BUTTON_SEARCH), m_hInstance, NULL);
	SendMessage(m_hEditResult, EM_SETREADONLY, TRUE, NULL);
	DestroyWindow(splash);
}

void Window::onDestroy()
{

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
	int edit_length = GetWindowTextLength(m_hCombo);
	LPTSTR buf = new TCHAR[edit_length + 1];
	GetWindowText(m_hCombo, buf, edit_length + 1);
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

void Window::onOpenFile()
{
	OPENFILENAME ofn;       // common dialog box structure
	TCHAR szFile[260];       // buffer for file name

	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = m_hWnd;
	ofn.lpstrFile = szFile;
	// Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
	// use the contents of szFile to initialize itself.
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = L"All\0*.*\0Text\0*.TXT\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Display the Open dialog box. 

	if (GetOpenFileName(&ofn) == TRUE)
	{
		m_controller->loadDict(ofn.lpstrFile);
	}
}

void Window::onAbout()
{
	DialogBox(m_hInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), m_hWnd, Window::About);
}

void Window::onPaint(HDC* pHdc)
{

}

void Window::onComboChange()
{
	int edit_length = GetWindowTextLength(m_hCombo);
	LPTSTR buf = new TCHAR[edit_length + 1];
	GetWindowText(m_hCombo, buf, edit_length + 1);
	std::wstring edit_text(buf);
	delete[] buf;
	auto words_with_prefix = m_controller->find_by_prefix(edit_text);
	while (ComboBox_GetCount(m_hCombo) > 0)
	{
		ComboBox_DeleteString(m_hCombo, 0);
	}
	for (auto& word : words_with_prefix)
	{
		ComboBox_AddString(m_hCombo, word.c_str());
	}
	ComboBox_ShowDropdown(m_hCombo, TRUE);
}

INT_PTR CALLBACK Window::About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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