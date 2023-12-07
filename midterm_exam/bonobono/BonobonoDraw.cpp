#include <windows.h>
#include <stdio.h>
#include "BonobonoDraw.h"

// 도형을 나타내는 변수
extern bool isShapeVisible;
extern ShapeType currentShape;
extern POINT ptStart, ptEnd, ptOffset, ptMoveStart;
extern int isMouseRButtonPressed;
extern RECT rect;
extern bool isEyesClosed;


// 도형 그리기 함수
void DrawBonobono(HDC hdc, int x, int y) {
    HBRUSH hSkinBrush = CreateSolidBrush(RGB(127, 200, 255));
    SelectObject(hdc, hSkinBrush);
    Ellipse(hdc, x - 100, y - 100, x + 100, y + 100);

    HBRUSH hMouthBrush = CreateSolidBrush(RGB(255, 150, 255));
    SelectObject(hdc, hMouthBrush);
    Ellipse(hdc, x - 15, y + 10, x + 15, y + 50);

    HBRUSH hNoseBrush = CreateSolidBrush(RGB(255, 255, 255));
    SelectObject(hdc, hNoseBrush);
    Ellipse(hdc, x - 1, y - 10, x + 33, y + 23);
    Ellipse(hdc, x - 33, y - 10, x + 1, y + 23);

    HBRUSH hBeardBrush = CreateSolidBrush(RGB(0, 0, 0));
    SelectObject(hdc, hBeardBrush);
    Ellipse(hdc, x - 15, y - 25, x + 15, y + 2);
    MoveToEx(hdc, x + 20, y, NULL);
    LineTo(hdc, x + 45, y - 8);
    MoveToEx(hdc, x + 20, y + 10, NULL);
    LineTo(hdc, x + 47, y + 14);
    MoveToEx(hdc, x - 20, y, NULL);
    LineTo(hdc, x - 45, y - 8);
    MoveToEx(hdc, x - 20, y + 10, NULL);
    LineTo(hdc, x - 47, y + 14);


    HBRUSH hEyeBrush = CreateSolidBrush(RGB(0, 0, 0));
    SelectObject(hdc, hEyeBrush);
    if (!isEyesClosed) {
        Ellipse(hdc, x - 80, y - 30, x - 65, y - 15);
        Ellipse(hdc, x + 65, y - 30, x + 80, y - 15);

        HBRUSH hEyeBallBrush = CreateSolidBrush(RGB(255, 255, 255));
        SelectObject(hdc, hEyeBallBrush);
        Ellipse(hdc, x - 78, y - 20, x - 70, y - 27);
        Ellipse(hdc, x + 70, y - 27, x + 78, y - 20);

        DeleteObject(hEyeBallBrush);
    }
    else {
        MoveToEx(hdc, x - 70, y - 20, NULL);
        LineTo(hdc, x - 80, y - 28);
        MoveToEx(hdc, x - 70, y - 18, NULL);
        LineTo(hdc, x - 80, y - 10);

        MoveToEx(hdc, x + 80, y - 28, NULL);
        LineTo(hdc, x + 70, y - 18);
        MoveToEx(hdc, x + 80, y - 10, NULL);
        LineTo(hdc, x + 70, y - 18);
    }
    DeleteObject(hSkinBrush);
    DeleteObject(hEyeBrush);
    DeleteObject(hNoseBrush);
    DeleteObject(hMouthBrush);
    DeleteObject(hBeardBrush);

}

void DrawRyan(HDC hdc, int x, int y, int k, int j) {
    HBRUSH hSkinBrush = CreateSolidBrush(RGB(255, 200, 15));
    SelectObject(hdc, hSkinBrush);
    Ellipse(hdc, x - 100, y - 100, x + 100, y + 100);

    HBRUSH hNoseBrush = CreateSolidBrush(RGB(255, 255, 255));
    SelectObject(hdc, hNoseBrush);
    Ellipse(hdc, x - 30, y + 5, x + 0, y + 35);
    Ellipse(hdc, x + 0, y + 5, x + 30, y + 35);

    HBRUSH hEyeBrush = CreateSolidBrush(RGB(0, 0, 0));
    SelectObject(hdc, hEyeBrush);

    Ellipse(hdc, x - 50, y - 20, x - 60, y - 10);
    Ellipse(hdc, x + 60, y - 20, x + 50, y - 10);


    DeleteObject(hSkinBrush);
    DeleteObject(hEyeBrush);
    DeleteObject(hNoseBrush);
}

void DrawShape(HWND hWnd, HDC hdc) {
    // 박스 그리기
    HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0)); // 빨간색 박스
    SelectObject(hdc, hBrush);
    switch (currentShape) {
    case BOX:
        Rectangle(hdc, ptStart.x, ptStart.y, ptEnd.x, ptEnd.y);
        break;
    case CIRCLE:
        Ellipse(hdc, ptStart.x, ptStart.y, ptEnd.x, ptEnd.y);
        break;
    case BONOBONO: {
        DrawBonobono(hdc, ptStart.x, ptEnd.y);
        break;
    }
    case RYAN:
        //DrawRyan(hdc, ptStart.x, ptEnd.y);
        DrawRyan(hdc, ptStart.x, ptEnd.y, ptEnd.x, ptStart.x);
        break;
    }
    DeleteObject(hBrush);
}