# EasyHWND
### Never ever write your windows window-framework from scratch again!

This library provides a basic window framework implementation / abstraction to fit the C++ Object Orientated design. This library is meant to be the starting point for your applications window framework. Just create a class  that inherits from `EasyHWND::Window` and you can customize anything you want. Just look at the header (it is not complicated) and the example code.

```c++
int main(int argc, char** argv) {
    EasyHWND::WindowClass wc(L"MyWindowClass", CS_OWNDC, NULL, NULL, CreateSolidBrush(RGB(255, 0, 0)));
    EasyHWND::Window w(wc, L"MyWindow", 100, 100, 500, 500, WS_OVERLAPPEDWINDOW);
	
    MSG msg = {};
    while (!w.checkWindowCloseFlag()) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    
    return 0;
}
```

But I want my fu**ing HWND back! Well no problem:

```c++
EasyHWND::Window window(wc, L"MyWindow", 100, 100, 500, 500, WS_OVERLAPPEDWINDOW);
HWND stolenHwnd = (HWND)window;
```

Do anything you want to that HWND but don't you dare trying to call `DestoyWindow(stolenHwnd)`.

### How to inherit from EasyHWND::Window

```c++
class MyAngryWindow : public EasyHWND::Window {
public:
    // Make it construct
    MyAngryWindow(EasyHWND::WindowClass& refWndClass, EASYHWND_STR windowTitle, INT posX, INT posY, UINT width, UINT height,
        DWORD style, DWORD exStyle = NULL, HMENU menue = NULL, HWND parentWindow = NULL, HINSTANCE hInstance = NULL) :
        EasyHWND::Window(refWndClass, windowTitle, posX, posY, width, height, style, exStyle, menue, parentWindow, hInstance)
    {}

protected:
    virtual bool handleWindowMessage(LRESULT* ptrLRESULT, HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) override {
        // I hate to be closed and will yell at you
        if (msg == WM_CLOSE) {
            MessageBox(hwnd, L"DONT YOU CLOSE ME!", L"FU** NO", MB_ICONEXCLAMATION | MB_OK);
            return true;
        }
    e    
        // Call parent!
        return EasyHWND::Window::handleWindowMessage(ptrLRESULT, hwnd, msg, wParam, lParam);
    }
};
```

But the framework let me resize the window I don't want that! No problem just start the virtual madness and override that function too! Just define `#define EASYHWND_VIRTUAL_MADNESS` and several function will turn into virtual ones just like magic!