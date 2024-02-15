// TimeCounter.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "TimeCounter.h"

#include <iostream>
#include <process.h>
#include <Psapi.h>

#include "TextManager.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TIMECOUNTER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TIMECOUNTER));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TIMECOUNTER));
    wcex.hCursor        = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
    wcex.hbrBackground  = (HBRUSH)(COLOR_DESKTOP +1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TIMECOUNTER);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable
   HWND hWnd = CreateWindowW(
     szWindowClass, 
     szTitle,
     WS_OVERLAPPEDWINDOW | WS_VSCROLL,
     CW_USEDEFAULT, 
     CW_USEDEFAULT,
     CW_USEDEFAULT, 
     CW_USEDEFAULT,
     nullptr, 
     nullptr, 
     hInstance, 
     nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            CreateWindow(_T("EDIT"), 0, WS_BORDER | WS_CHILD | WS_VISIBLE, 56, 50, 50, 18, hWnd, 0, hInst, 0);
            auto temp = CreateWindow(_T("BUTTON"), 0, WS_BORDER | WS_CHILD | WS_VISIBLE, 50, 100, 50, 18, hWnd, 0, hInst, 0);
            
            TextManager* textManager = new TextManager();
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            // TODO: Add any drawing code that uses hdc here...
            //DWORD aProcesses[1024], cbNeeded, cProcesses;
            //EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded);
            //cProcesses = cbNeeded / sizeof(DWORD);
            //for (int i = 0; i < cProcesses; i++)
            //{
            //  if (aProcesses[i] != 0)
            //  {
            //    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, aProcesses[i]);
            //    if (hProcess == NULL)
            //      continue;
            //    TCHAR nameProc[MAX_PATH];

            //    //Test with GetProcessImageFileName
            //    /*GetProcessImageFileName(hProcess, nameProc, sizeof(nameProc));
            //    TCHAR s[256];
            //    swprintf_s(s, _T("GetProcessImageFileName - Process' %d Name = %s \n"), i, nameProc);
            //    OutputDebugString(s);*/

            //    //Test with GetModuleBaseName
            //    HMODULE hMod;
            //    if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded))
            //    {
            //      GetModuleBaseName(hProcess, hMod, nameProc, sizeof(nameProc) / sizeof(TCHAR));
            //    }
            //    TCHAR bufferModuleBaseName[256];
            //    swprintf_s(bufferModuleBaseName, _T("GetModuleBaseName - Process' %d Name = %s \n"), i, nameProc);
            //    OutputDebugString(bufferModuleBaseName);
            //    textManager->AddText(hdc, nameProc);
            //  }
            //}

            EndPaint(hWnd, &ps);
            delete textManager;
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
