#include "stdafx.h"
#pragma once

class Combobox
{
	WNDPROC m_Defaul_cb_proc;
	HWND m_handle;
public:
	void Create(int x, int y, int width, int height, int id, HWND parent);
	Combobox();
	~Combobox();
	void clear();
	void add(std::wstring str);
	std::wstring getText();
	void showDropdown(bool show);
	void reset();
	static LRESULT CALLBACK wndProc(HWND, UINT, LPARAM, WPARAM);
};

