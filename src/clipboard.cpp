#include "clipboard.h"


void ErrorExit(LPTSTR lpszFunction)
{
    // Retrieve the system error message for the last-error code

    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError();

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&lpMsgBuf,
        0, NULL);

    // Display the error message and exit the process

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
        (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
    StringCchPrintf((LPTSTR)lpDisplayBuf,
        LocalSize(lpDisplayBuf) / sizeof(TCHAR),
        TEXT("%s failed with error %d: %s"),
        lpszFunction, dw, lpMsgBuf);
    MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
    ExitProcess(dw);
}



cbd::Clipboard::Clipboard()
{

}

bool cbd::Clipboard::set_image(const char* imagePath)
{
    if (!OpenClipboard(nullptr)) {
        ErrorExit(LPTSTR("OpenClipboard"));
        return false;
    }

    EmptyClipboard();

    HBITMAP hBitmap = (HBITMAP)LoadImage(nullptr, imagePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    if (hBitmap == nullptr) {
        ErrorExit(LPTSTR("LoadImage"));
        CloseClipboard();
        std::cout << 2 << "\n";
        return false;
    }

    SetClipboardData(CF_BITMAP, hBitmap);

    CloseClipboard();

    return true;
}