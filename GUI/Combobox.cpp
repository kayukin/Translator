#include "stdafx.h"
#include "Combobox.h"


Combobox::Combobox()
{
}


Combobox::~Combobox()
{
}

void Combobox::Create(int x, int y, int width, int height, int id, HWND parent)
{
	m_handle = CreateWindow(WC_COMBOBOX, TEXT(""), CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, x, y, width, height, parent, reinterpret_cast<HMENU>(id), NULL, NULL);
	SetWindowLongPtr(m_handle, GWLP_USERDATA, (LONG)this);
	m_Defaul_cb_proc = (WNDPROC)(m_handle, GWLP_WNDPROC, (LONG)Combobox::wndProc);
}

LRESULT CALLBACK Combobox::wndProc(HWND hWnd, UINT message, LPARAM lParam, WPARAM wParam)
{
	Combobox* self = reinterpret_cast<Combobox*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	switch (message)
	{
	default:
		return CallWindowProc(self->m_Defaul_cb_proc, hWnd, message, wParam, lParam);
	}
	return 0;
}

void Combobox::clear()
{
	while (ComboBox_GetCount(m_handle) > 0)
	{
		ComboBox_DeleteString(m_handle, 0);
	}
}

std::wstring Combobox::getText()
{
	int edit_length = GetWindowTextLength(m_handle);
	LPTSTR buf = new TCHAR[edit_length + 1];
	GetWindowText(m_handle, buf, edit_length + 1);
	std::wstring edit_text(buf);
	delete[] buf;
	return edit_text;
}

void Combobox::add(std::wstring str)
{
	ComboBox_AddString(m_handle, str.c_str());
}

void Combobox::showDropdown(bool show)
{
	ComboBox_ShowDropdown(m_handle, TRUE);
}