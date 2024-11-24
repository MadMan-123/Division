
#include "platform.h"

#if _WIN32 

#include <windows.h>
#include <windowsx.h>  // param input extraction 
#include <stdio.h>
#include "../Systems/graphics.h"

static double clockFrequency;
static LARGE_INTEGER startTime;

int cWidth, cHeight;
RECT windowRect;


struct InternalState
{
	HDC deviceContext;
	HWND consoleHandle;
	HINSTANCE currentHandle;
	HANDLE hConsole;
};

LRESULT CALLBACK win32ProcessMessage(HWND hwnd, UINT32 msg, WPARAM w_param, LPARAM l_param);


bool platformStart(PlatformState* state, const char* name,int width, int height)
{
	state->internalState = malloc(sizeof(InternalState));
	state->graphicsState = malloc(sizeof(GraphicsState));
	//cold cast
	InternalState* iState = (InternalState*)(state->internalState);
	if (iState == NULL)
	{
		return false;
	}

	//create window specific 
	//current instance
	iState->currentHandle = GetModuleHandleA(0);
	
	WNDCLASSA wc;

		
	memset(&wc, 0, sizeof(wc));
	wc.style = CS_DBLCLKS;  // Get double-clicks
    wc.lpfnWndProc = win32ProcessMessage;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
	wc.hInstance = iState->currentHandle;
	wc.lpszClassName = "WindowsStateClass";
	windowRect = { 0, 0, width, height };

	if(!RegisterClassA(&wc))
	{
		return false;
	}
	UINT32 windowStyle = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION;
	UINT32 windowExStyle = WS_EX_APPWINDOW;

	windowStyle |= WS_MAXIMIZEBOX;
	windowStyle |= WS_MINIMIZEBOX;
	windowStyle |= WS_THICKFRAME;
	AdjustWindowRectEx(&windowRect, windowStyle, FALSE, windowExStyle);

	HWND handle = CreateWindowExA(
		windowExStyle,
		"WindowsStateClass",
		name,
		windowStyle,
		CW_USEDEFAULT, CW_USEDEFAULT,
		windowRect.right - windowRect.left, windowRect.bottom - windowRect.top,
		0,
		0,
		iState->currentHandle,
		0
	);

	iState->hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (handle == 0)
	{
		MessageBoxA(NULL, "Window Creation failed", "Error!", MB_ICONEXCLAMATION | MB_OK);
			return false;
	}
	else
	{
		iState->consoleHandle = handle;
	}

	ShowWindow(iState->consoleHandle, SW_SHOW);

	//set the name of the window
	SetWindowTextA(iState->consoleHandle, name);
	
	SMALL_RECT windowSize = { 10,10,(SHORT)width,(SHORT)height };
	if (!SetConsoleWindowInfo(iState->hConsole, TRUE, &windowSize))
	{
		printf("Console wasnt able to set info correctly");
		return false;
	}


	//todo:  clock setup
		// Clock setup
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	clockFrequency = 1.0 / (double)frequency.QuadPart;
	QueryPerformanceCounter(&startTime);

	SetWindowLongPtr(iState->consoleHandle, GWLP_USERDATA, (LONG_PTR)state->graphicsState);

	
	cWidth = width;
	cHeight = height;


	return true;
}
bool platformUpdate(PlatformState* state)
{
	MSG message;
	while (PeekMessageA(&message, NULL, 0, 0, PM_REMOVE))
	{

		TranslateMessage(&message);
		DispatchMessageA(&message);
	}
	// Post custom message to trigger WM_PAINT
	InternalState * iState = (InternalState*)state->internalState;
	InvalidateRect(iState->consoleHandle, NULL, FALSE);
	UpdateWindow(iState->consoleHandle);


	return true;
}

void platformCleanUp(PlatformState* state)
{

	//cold 
	auto iState = (InternalState*)(state->internalState);

	CloseWindow(iState->consoleHandle);
	DestroyWindow(iState->consoleHandle);
	free(state->internalState);
	free(state->graphicsState);



}
LRESULT CALLBACK win32ProcessMessage(HWND hwnd, UINT32 msg, WPARAM w_param, LPARAM l_param)
{

	switch (msg) {
	case WM_ERASEBKGND:
		return 1;
	case WM_CLOSE:
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_KEYDOWN:

	case WM_SYSKEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP: {
		// Key pressed/released
		// pressed = (msg == WM_KEYDOWN || msg == WM_SYSKEYDOWN);
		// TODO: input processing


	} break;
	case WM_MOUSEMOVE: {
		// Mouse move
		// x_position = GET_X_LPARAM(l_param);
		// y_position = GET_Y_LPARAM(l_param);
		// TODO: input processing.
	} break;
	case WM_MOUSEWHEEL: {
		//  z_delta = GET_WHEEL_DELTA_WPARAM(w_param);
		// if (z_delta != 0) {
		//     // Flatten the input to an OS-independent (-1, 1)
		//     z_delta = (z_delta < 0) ? -1 : 1;
		//     // TODO: input processing.
		// }
	} break;
	case WM_LBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_MBUTTONUP:
	case WM_RBUTTONUP: {
		//b8 pressed = msg == WM_LBUTTONDOWN || msg == WM_RBUTTONDOWN || msg == WM_MBUTTONDOWN;
		// TODO: input processing.PAINTSTRUCT ps;

	} break;
	case WM_PAINT: {
		GraphicsState* state = (GraphicsState*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		if (state != nullptr && state->shouldRender)
		{
			
			//DRAW HERE


			BITMAPINFO bmi = { 0 };

			bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
			bmi.bmiHeader.biWidth = state->width;
			//top down
			bmi.bmiHeader.biHeight = -state->height;  
			bmi.bmiHeader.biPlanes = 1;
			bmi.bmiHeader.biBitCount = 32;
			bmi.bmiHeader.biCompression = BI_RGB;

			// Create a temporary buffer
			void* buffer = malloc(state->width * state->height * 4);
			DWORD* pixels = (DWORD*)buffer;

			for (int y = 0; y < state->height; y++)
			{
				for (int x = 0; x < state->width; x++)
				{
					Colour current = state->front[y][x];
					if (pixels == nullptr)
						break;
					pixels[y * state->width + x] = (current.a << 24) | (current.r << 16) | (current.g << 8) | current.b;
					
				}
			}

			


			// Draw the entire buffer at once
			StretchDIBits(hdc,
				0, 0, state->width, state->height,
				0, 0, state->width, state->height,
				buffer, &bmi, DIB_RGB_COLORS, SRCCOPY);


			free(buffer);

			state->shouldRender = false;

		}
		EndPaint(hwnd, &ps);




	} break;
	}

	return DefWindowProcA(hwnd, msg, w_param, l_param);
}


double platformGetAbsoluteTime()
{
	LARGE_INTEGER nowTime;
	QueryPerformanceCounter(&nowTime);
	return (double)nowTime.QuadPart * clockFrequency;
}

void platformSleep(unsigned long long ms)
{
	Sleep(ms);
}


#endif