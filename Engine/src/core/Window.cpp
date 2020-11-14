#include "Window.h"
#include "Keyboard.h"
#include "Mouse.h"
#include <shellapi.h>

HINSTANCE Window::WindowClass::hInstance = GetModuleHandleW(nullptr);
LPWSTR Window::WindowClass::className = (wchar_t*)L"Window Class";

Window::WindowClass Window::wndClass;

Window::WindowClass::WindowClass()
{
    WNDCLASSEX wndClass;
    wndClass.cbSize = sizeof(WNDCLASSEX);
    wndClass.style = CS_OWNDC;
    wndClass.lpfnWndProc = HandleMsgSetup;
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hInstance = hInstance;
    wndClass.hIcon = static_cast<HICON>(LoadImageW(hInstance, L"AppIcon.ico", IMAGE_ICON, 32, 32, LR_LOADFROMFILE));
    wndClass.hIconSm = static_cast<HICON>(LoadImageW(hInstance, L"AppIcon.ico", IMAGE_ICON, 16, 16, LR_LOADFROMFILE));
    wndClass.hCursor = nullptr;
    wndClass.hbrBackground = nullptr;
    wndClass.lpszMenuName = className;
    wndClass.lpszClassName = className;
    RegisterClassExW(&wndClass);
}

Window::WindowClass::~WindowClass()
{
    UnregisterClass(className, hInstance);
}

Window::Window(LPWSTR wndName, UINT w, UINT h)
    :
    windowWidth(w),
    windowHeight(h),
    bCursorEnabled(true)
{
    RECT wndRect = { 0, 0, (LONG)w, (LONG)h };
    AdjustWindowRect(&wndRect, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);
    
    hWnd = CreateWindowW(
        WindowClass::className, wndName,
        WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
        (GetSystemMetrics(SM_CXFULLSCREEN) - (wndRect.right - wndRect.left)) / 2,
        (GetSystemMetrics(SM_CYFULLSCREEN) - (wndRect.bottom - wndRect.top)) / 2,
        wndRect.right - wndRect.left, wndRect.bottom - wndRect.top,
        nullptr, nullptr, WindowClass::hInstance, this
    );

    if (hWnd == NULL)
    {
        MessageBox(nullptr, L"Failed To Create Window", L"ERROR", MB_OK);
        PostQuitMessage(0);
    }
#pragma warning (disable : 6387)
    ShowWindow(hWnd, SW_SHOW);

    pGFX = std::make_unique<Graphics>(hWnd, w, h);
    CenterCursor();

    if (RegisterRawMouse() == false)
    {
        MessageBox(nullptr, L"Failed To Register Raw Input Mouse", L"ERROR", MB_OK);
        PostQuitMessage(0);
    }
}

Window::~Window()
{
    DestroyWindow(hWnd);
}

void Window::CenterCursor() const
{
    UINT hWndFrame = 8u;
    UINT vWndFrame = 31u;

    Mouse::SetPosX(int(pGFX->GetWidth() / 2.0f - hWndFrame));
    Mouse::SetPosY(int(pGFX->GetHeight() / 2.0f - vWndFrame));

    RECT rtWindow;
    GetWindowRect(hWnd, &rtWindow);
     SetCursorPos(
        rtWindow.left + pGFX->GetWidth() / 2,
        rtWindow.top + pGFX->GetHeight() / 2
    );
}

void Window::EnableCursor()
{
    bCursorEnabled = true;
    while (ShowCursor(TRUE) < 0);
}

void Window::DisableCursor()
{
    bCursorEnabled = false;
    while (ShowCursor(FALSE) >= 0);
}

bool Window::IsCursorEnabled() const
{
    return bCursorEnabled;
}

bool Window::ProceedMessage()
{
    MSG msg;
    while (true)
    {
        if (PeekMessageW(&msg, nullptr, 0u, 0u, PM_REMOVE))
        {
            if (msg.message == WM_QUIT) return false;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else break;
    }

    Keyboard::Update();
    Mouse::Update();
    return true;
}

HWND Window::GetWND() const
{
    return hWnd;
}

Graphics& Window::GetGFX() const
{
    return *pGFX.get();
}

UINT Window::GetWidth() const
{
    return windowWidth;
}

UINT Window::GetHeight() const
{
    return windowHeight;
}

bool Window::RegisterRawMouse() const
{
    RAWINPUTDEVICE rid;
    rid.usUsagePage = 0x01;
    rid.usUsage = 0x02;
    rid.dwFlags = 0u;
    rid.hwndTarget = nullptr;
    return RegisterRawInputDevices(&rid, 1u, sizeof(rid));
}

LRESULT Window::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (msg == WM_NCCREATE)
    {
        const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
        Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
        SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(Window::HandleMsgThunk));
        return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
    }
    else return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT Window::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
}

LRESULT Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    /*********** Keyboard Messages ***********/
    case WM_SYSKEYDOWN:
    case WM_KEYDOWN:
        if (!(lParam & 0x40000000) || Keyboard::bAutoRepeat)
            Keyboard::OnKeyPress((DWORD)wParam);
        break;
    case WM_KEYUP:
    case WM_SYSKEYUP:
        Keyboard::OnKeyRelease((DWORD)wParam);
        break;
    /********* End Keyboard Messages *********/


    /************* Mouse Messages *************/
    case WM_LBUTTONDOWN:
        SetForegroundWindow(hWnd);
        Mouse::OnLBPressed();
        break;
    case WM_LBUTTONUP:
        Mouse::OnLBRelease();
        break;
    case WM_RBUTTONDOWN:
        Mouse::OnRBPressed();
        break;
    case WM_RBUTTONUP:
        Mouse::OnRBRelease();
        break;
    case WM_MOUSEMOVE:
        const POINTS pt = MAKEPOINTS(lParam);
        RECT rt;
        GetClientRect(hWnd, &rt);

        if (pt.x >= 0 && pt.x < rt.right && pt.y >= 0 && pt.y < rt.bottom)
        {
            Mouse::OnMove(pt.x, pt.y);
            if (!Mouse::bInWindow) {
                SetCapture(hWnd);
                Mouse::bInWindow = true;
            }
        }
        else {
            if (wParam & (MK_LBUTTON | MK_RBUTTON)) Mouse::OnMove(pt.x, pt.y);
            else ReleaseCapture();
            Mouse::bInWindow = false;
        }
        break;
    case WM_MOUSEWHEEL:
        Mouse::OnWheelScroll(GET_WHEEL_DELTA_WPARAM(wParam));
        break;
    /*********** End Mouse Messages ***********/


    /*********** Raw Mouse Messages ***********/
    case WM_INPUT:
    {
        if (bCursorEnabled) break;

        UINT size = 0u;
        // get raw input size
        if (GetRawInputData(
            reinterpret_cast<HRAWINPUT>(lParam),
            RID_INPUT,
            nullptr,
            &size,
            sizeof(RAWINPUTHEADER)) == -1)
        {
            break;
        }

        rawBuffer.resize(size);

        // check if the size is matching
        if (GetRawInputData(
            reinterpret_cast<HRAWINPUT>(lParam),
            RID_INPUT,
            rawBuffer.data(),
            &size,
            sizeof(RAWINPUTHEADER)) != size)
        {
            break;
        }

        auto& ri = reinterpret_cast<const RAWINPUT&>(*rawBuffer.data());
        if (ri.header.dwType == RIM_TYPEMOUSE &&
            (ri.data.mouse.lLastX != 0 || ri.data.mouse.lLastY != 0))
        {
            Mouse::OnRawMove(ri.data.mouse.lLastX, ri.data.mouse.lLastY);
        }
        break;
    }
    /********* End Raw Mouse Messages *********/

    case WM_KILLFOCUS:
        Keyboard::Clear();
        Mouse::Clear();
        break;
    case WM_CLOSE:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}