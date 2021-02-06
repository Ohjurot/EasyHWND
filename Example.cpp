#include "EasyHWND.h"

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
			MessageBox(hwnd, L"DONT YOU CLOSE ME", L"FU** NO", MB_ICONEXCLAMATION | MB_OK);
			return true;
		}

		// Call parent!
		return EasyHWND::Window::handleWindowMessage(ptrLRESULT, hwnd, msg, wParam, lParam);
	}
};

// Main entry point
int main(int argc, char** argv) {
	EasyHWND::WindowClass wc(L"MyWindowClass", CS_OWNDC, NULL, NULL, CreateSolidBrush(RGB(255, 0, 0)));
	if (wc) {
		MyAngryWindow w(wc, L"MyWindow", 100, 100, 500, 500, WS_OVERLAPPEDWINDOW);
		
		if (w) {
			unsigned int width = 500;
			unsigned int height = 500;
			w.adjustSizeForWindow(&width, &height);
			w.setWindowSize(width, height);

			w.setWindowVisibility(true);

			MSG msg = {};
			while (!w.checkWindowCloseFlag()) {
				if (PeekMessage(&msg, (HWND)w, 0, 0, PM_REMOVE)) {
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
		}
	}


	return 0;
}
