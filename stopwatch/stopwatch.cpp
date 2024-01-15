#include <windows.h>
#include <tchar.h>

// Global variables
HWND hwndStartButton, hwndStopButton, hwndResetButton, hwndTimeLabel;
UINT_PTR timerID = 1;
int seconds = 0;

// Function Declarations
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
void AddControls(HWND);
void UpdateTimeLabel(HWND);
VOID CALLBACK TimerProc(HWND, UINT, UINT_PTR, DWORD);

// WinMain
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
    WNDCLASSW wc = { 0 };

    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = L"myWindowClass";
    wc.lpfnWndProc = WindowProcedure;

    if (!RegisterClassW(&wc))
        return -1;

    CreateWindowW(L"myWindowClass", L"Stopwatch Application", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 350, 200, NULL, NULL, NULL, NULL);

    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

// Function Definitions
void AddControls(HWND hwnd) {
    hwndStartButton = CreateWindowW(L"Button", L"Start", WS_VISIBLE | WS_CHILD, 50, 50, 80, 40, hwnd, (HMENU)1, NULL, NULL);
    hwndStopButton = CreateWindowW(L"Button", L"Stop", WS_VISIBLE | WS_CHILD, 140, 50, 80, 40, hwnd, (HMENU)2, NULL, NULL);
    hwndResetButton = CreateWindowW(L"Button", L"Reset", WS_VISIBLE | WS_CHILD, 230, 50, 80, 40, hwnd, (HMENU)3, NULL, NULL);
    hwndTimeLabel = CreateWindowW(L"Static", L"00:00", WS_VISIBLE | WS_CHILD | SS_CENTER, 100, 100, 150, 40, hwnd, (HMENU)4, NULL, NULL);
}

void UpdateTimeLabel(HWND hwnd) {
    wchar_t timeString[9];
    wsprintfW(timeString, L"%02d:%02d", seconds / 60, seconds % 60);
    SetWindowTextW(hwndTimeLabel, timeString);
}

VOID CALLBACK TimerProc(HWND hwnd, UINT message, UINT_PTR iTimerID, DWORD dwTime) {
    seconds++;
    UpdateTimeLabel(hwnd);
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_COMMAND:
        switch (LOWORD(wp)) {
        case 1: // Start Button
            if (!IsWindowVisible(hwndStopButton)) {
                ShowWindow(hwndStopButton, SW_SHOW);
            }
            SetTimer(hwnd, timerID, 1000, (TIMERPROC)TimerProc);
            break;
        case 2: // Stop Button
            KillTimer(hwnd, timerID);
            break;
        case 3: // Reset Button
            KillTimer(hwnd, timerID);
            seconds = 0;
            UpdateTimeLabel(hwnd);
            break;
        }
        break;
    case WM_CREATE:
        AddControls(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:

        return DefWindowProcW(hwnd, msg, wp, lp);
    }
    return 0;
}
