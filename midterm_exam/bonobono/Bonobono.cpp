#include <windows.h>
#include <stdio.h>
#include "BonobonoDraw.h"
//#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console") 

bool isShapeVisible = false;
ShapeType currentShape = NONE;
POINT ptStart, ptEnd, ptOffset, ptMoveStart;
HWND hDrawingArea;
int isMouseRButtonPressed = 0;
HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0)); // ������ �ڽ�
HBRUSH clear = CreateSolidBrush(RGB(255, 255, 255)); // ���
RECT rect;
bool isEyesClosed = false;

// ������ ���ν���
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case 1: // ù ��° ��ư Ŭ��
            currentShape = BOX;
            break;
        case 2: // �� ��° ��ư Ŭ��
            currentShape = CIRCLE;
            break;
        case 3:
            currentShape = BONOBONO;
            ptStart.x = 400;
            ptStart.y = 240;
            ptEnd.x = 400;
            ptEnd.y = 240;

            isShapeVisible = FALSE;	// ���� �׸��� ����
            InvalidateRect(hDrawingArea, NULL, TRUE);
            SetFocus(hDrawingArea);
            break;
        case 4:
            currentShape = RYAN;
            break;
        case 5:
            currentShape = NONE;
            InvalidateRect(hDrawingArea, NULL, TRUE);
            break;
        }
        break;

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        //DrawShape(hWnd, hdc);
        EndPaint(hWnd, &ps);
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK DrawingProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    switch (Msg)
    {
    case WM_KEYDOWN:
        // �����̽��ٰ� ������ ��
        if (wParam == VK_SPACE && !isEyesClosed) {
            isEyesClosed = true;

            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;

    case WM_KEYUP:
        // �����̽��ٰ� ������ ��
        if (wParam == VK_SPACE && isEyesClosed) {
            isEyesClosed = false;

            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;

    case WM_LBUTTONDOWN:	// ���콺 ���� Ŭ��
        ptStart.x = LOWORD(lParam);
        ptStart.y = HIWORD(lParam);
        isShapeVisible = TRUE;	// ���� �׸��� ����
        printf("%d %d\n", ptStart.x, ptStart.y);
        break;

    case WM_MOUSEMOVE: {
        int mouseX = LOWORD(lParam);
        int mouseY = HIWORD(lParam);

        if (isMouseRButtonPressed) {
            int offsetX = mouseX - ptMoveStart.x;
            int offsetY = mouseY - ptMoveStart.y;
            static int sumX = 0;
            static int sumY = 0;
            sumX += offsetX;
            sumY += offsetY;
            printf("ptOffset : mouseX = %d, mouseY = %d\n", offsetX, offsetY);
            printf("sum : sumX = %d, sumY = %d\n", sumX, sumY);

            rect = { ptStart.x, ptStart.y, ptEnd.x, ptEnd.y };

            if (currentShape == CIRCLE) {
                rect.right += offsetX;
                rect.bottom += offsetY;

                //if (currentShape == CIRCLE && (sumX >= 100 || sumY >= 100)) {
                //ptStart.x += 4;
                ptStart.y += 4;
                //ptEnd.x += 4;
                ptEnd.y += 4;
                sumX = 0; sumY = 0;
                //}
            }
            else {

                OffsetRect(&rect, offsetX, offsetY);
                printf("pt %d %d %d %d\n", ptStart.x, ptStart.y, ptEnd.x, ptEnd.y);
                printf("%d %d %d %d\n", rect.left, rect.top, rect.right, rect.bottom);

            }
            ptMoveStart.x = LOWORD(lParam);
            ptMoveStart.y = HIWORD(lParam);

            InvalidateRect(hDrawingArea, NULL, TRUE);
        }
        else {

            if (isShapeVisible) {
                ptEnd.x = mouseX;
                ptEnd.y = mouseY;


                printf("move %d %d\n", ptEnd.x, ptEnd.y);
                InvalidateRect(hDrawingArea, NULL, TRUE);
            }
        }
        break;
    }
    case WM_LBUTTONUP:
        ptEnd.x = LOWORD(lParam);
        ptEnd.y = HIWORD(lParam);

        if (isShapeVisible)
            isShapeVisible = FALSE;	// ���� �׸��� ����
        InvalidateRect(hDrawingArea, NULL, TRUE);
        break;

    case WM_RBUTTONDOWN:
    {
        int mouseX = LOWORD(lParam);
        int mouseY = HIWORD(lParam);

        if (mouseX >= ptStart.x && mouseX <= ptEnd.x && mouseY >= ptStart.y && mouseY <= ptEnd.y) {
            isMouseRButtonPressed = 1;
            ptMoveStart.x = mouseX;
            ptMoveStart.y = mouseY;
            printf("WM_RBUTTONDOWN : ptMove.x = %d, ptMove.y = %d\n", ptMoveStart.x, ptMoveStart.y);
        }
    }
    break;

    case WM_RBUTTONUP:
    {
        isMouseRButtonPressed = 0;
        InvalidateRect(hWnd, NULL, TRUE);
    }
    break;

    case WM_PAINT:
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        if (!isMouseRButtonPressed) {
            printf("1 wm_paint\n");
            DrawShape(hWnd, hdc);

        }
        else {
            printf("2 wm_paint\n");

            RECT rect1 = { 0, 0, 800, 480 };
            FillRect(hdc, &rect1, clear);
            if (currentShape == CIRCLE)
                Ellipse(hdc, rect.left, rect.top, rect.right, rect.bottom);
            else {
                Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
            }
            ptStart.x = rect.left;
            ptStart.y = rect.top;
            ptEnd.x = rect.right;
            ptEnd.y = rect.bottom;
        }
        EndPaint(hWnd, &ps);
        break;
    }
    return DefWindowProc(hWnd, Msg, wParam, lParam); // Call Default Window Procedure.
}

// ���α׷� ������
int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {

    HWND hWnd;
    HWND hButtonBox, hButtonCircle, hButtonTriangle, hButtonLine, hButtonStop;
    HBRUSH hBrush[2] = { 0,0 };
    hBrush[0] = CreateSolidBrush(RGB(255, 240, 200));
    hBrush[1] = CreateSolidBrush(RGB(255, 255, 255));

    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = hBrush[0];
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"ButtonWindowClass";
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex)) {
        return 1;
    }

    wcex.lpfnWndProc = DrawingProc;
    wcex.hbrBackground = hBrush[1];
    wcex.hCursor = LoadCursor(NULL, IDC_CROSS);
    wcex.lpszClassName = TEXT("DrawingWindow");

    if (!RegisterClassEx(&wcex)) {
        return 1;
    }

    hWnd = CreateWindow(
        L"ButtonWindowClass", L"Midterm Exam(������)", WS_OVERLAPPED | WS_SYSMENU,
        CW_USEDEFAULT, 0, 912, 628, NULL, NULL, hInstance, NULL);

    if (!hWnd) {
        return FALSE;
    }


    hButtonBox = CreateWindow(
        L"BUTTON", L"Box", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        16, 16, 160, 64, hWnd, (HMENU)1, hInstance, NULL);

    hButtonCircle = CreateWindow(
        L"BUTTON", L"Circle", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        192, 16, 160, 64, hWnd, (HMENU)2, hInstance, NULL);

    hButtonTriangle = CreateWindow(
        L"BUTTON", L"Bonobono", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        368, 16, 160, 64, hWnd, (HMENU)3, hInstance, NULL);

    hButtonLine = CreateWindow(
        L"BUTTON", L"Ryan", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        544, 16, 160, 64, hWnd, (HMENU)4, hInstance, NULL);

    hButtonStop = CreateWindow(
        L"BUTTON", L"Cube", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        720, 16, 160, 64, hWnd, (HMENU)5, hInstance, NULL);

    hDrawingArea = CreateWindow(
        L"DrawingWindow", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER,
        16, 96, 800, 480, hWnd, NULL, hInstance, NULL);


    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    DeleteObject(hBrush[0]);
    DeleteObject(hBrush[1]);

    return (int)msg.wParam;
}
