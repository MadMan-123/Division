#include "input.h"

#include <windows.h>

/*
bool isKeyPressed(int key)
{
    return GetAsyncKeyState(key) & 0x8000;
}

bool isKeyReleased(int key)
{
    return GetAsyncKeyState(key) & 0x4000;
}

bool isMouseButtonPressed(int button)
{
    return GetAsyncKeyState(button) & 0x8000;
}

bool isMouseButtonReleased(int button)
{
    return GetAsyncKeyState(button) & 0x4000;
}

*/
//realistically this should be the only one

bool isInputPressed(int key)
{
    return GetAsyncKeyState(key) & 0x8000;
}

bool isInputReleased(int key)
{
    return GetAsyncKeyState(key) & 0x4000;
    
}

