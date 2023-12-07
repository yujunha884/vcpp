#pragma once
enum ShapeType { NONE, BOX, CIRCLE, BONOBONO, RYAN };
void DrawBonobono(HDC hdc, int x, int y);
void DrawRyan(HDC hdc, int x, int y, int k, int j);
void DrawShape(HWND hWnd, HDC hdc);

