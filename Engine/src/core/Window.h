#pragma once
#include "LightWindows.h"
#include "Graphics.h"
#include <vector>
#include <memory>

class Graphics;

class Window
{
private:
	class WindowClass
	{
	public:
		static HINSTANCE hInstance;
		static LPWSTR className;

	public:
		WindowClass();
		~WindowClass();
	};

private:
	static WindowClass wndClass;
	HWND hWnd;

	UINT windowWidth;
	UINT windowHeight;

	std::unique_ptr<Graphics> pGFX;

	std::vector<BYTE> rawBuffer;
	bool bCursorEnabled;

public:
	Window(LPWSTR wndName, UINT w, UINT h);
	virtual ~Window();
	Window(const Window&) = delete;
	Window& operator =(const Window&) = delete;

protected:
	bool ProceedMessage();
	HWND GetWND() const;
	Graphics& GetGFX() const;

	UINT GetWidth() const;
	UINT GetHeight() const;

	void CenterCursor() const;
	void EnableCursor();
	void DisableCursor();
	bool IsCursorEnabled() const;

private:
	bool RegisterRawMouse() const;

	static LRESULT WINAPI HandleMsgSetup(HWND, UINT, WPARAM, LPARAM);
	static LRESULT WINAPI HandleMsgThunk(HWND, UINT, WPARAM, LPARAM);
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};