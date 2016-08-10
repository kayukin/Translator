#include "stdafx.h"
#pragma once
#include "resource.h"
#include <memory>
#include "../Translator/TranslatorAPI.h"
#include "Combobox.h"

class Window :public Dictionary::IView
{
	//Controls id
	static const int IDC_BUTTON_TRANSLATE = 30000;
	static const int IDC_COMBO = 30001;
	static const int IDC_EDIT_RESULT = 30002;
	static const int IDC_BUTTON_CHANGE = 30003;
	static const int IDC_LIST_BOX = 30004;
	static const int IDC_BUTTON_SEARCH = 30005;
	//end

	//Controls handles
	Combobox m_hCombo;
	HWND m_hEditResult;
	HWND m_hButtonChange;
	HWND m_hListBox;
	//end

	HINSTANCE m_hInstance;
	HWND m_hWnd;
	std::wstring m_title;
	std::wstring m_window_class;
	ATOM registerClass();
	LRESULT CALLBACK wndProc(HWND, UINT, WPARAM, LPARAM);

	std::weak_ptr<Dictionary::ITranslatorController> m_controller;
public:
	Window(HINSTANCE hInst, std::shared_ptr<Dictionary::ITranslatorController> controller);
	~Window();
	BOOL init(int nCmdShow);
	
	static LRESULT CALLBACK msgRouter(HWND, UINT, WPARAM, LPARAM);
	static INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

	virtual void onCreate();
	virtual void onDestroy();
	virtual void onTranslateButtonClick();
	virtual void onSearchButtonClick();
	virtual void onChangeButtonClick();
	virtual void onMouseWheel(WPARAM, LPARAM);
	virtual void onOpenFile();
	virtual void onAbout();
	virtual void onPaint(HDC* pHdc);
	virtual void onComboChange();

	void onSwitchState() override;
};

