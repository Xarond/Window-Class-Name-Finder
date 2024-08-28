#include <windows.h>
#include <tchar.h>
#include <iostream>
#include <vector>
#include <string>


BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam) {
    DWORD windowProcessId;
    GetWindowThreadProcessId(hWnd, &windowProcessId);

    if (windowProcessId == (DWORD)lParam) {
        TCHAR className[256];
        GetClassName(hWnd, className, sizeof(className) / sizeof(TCHAR));
        std::wcout << L"Window Class Name: " << className << std::endl;
    }

    return TRUE;
}

int main() {
    std::wcout << L"Enter the process ID (PID): ";
    DWORD processId;
    std::wcin >> processId;

    if (processId == 0) {
        std::wcerr << L"Invalid process ID." << std::endl;
        std::wcin.get();
        return 1;
    }

    if (!EnumWindows(EnumWindowsProc, (LPARAM)processId)) {
        std::wcerr << L"Failed to enumerate windows." << std::endl;
    }

    std::wcout << L"\nPress Enter to exit...";
    std::wcin.ignore();
    std::wcin.get();

    return 0;
}
