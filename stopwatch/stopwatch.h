#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <windows.h>

// Forward declarations of functions
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
void AddControls(HWND);
void UpdateTimeLabel(HWND);
VOID CALLBACK TimerProc(HWND, UINT, UINT_PTR, DWORD);

#endif // STOPWATCH_H
