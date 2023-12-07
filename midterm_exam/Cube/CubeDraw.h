#pragma once
HRGN Drawcube(HWND hWnd, HDC hdc, int left, int top, int right, int bottom); // 큐브그리기 

void Movecube(POINT* minPoint, POINT* maxPoint, int deltaX, int deltaY);//큐브이동

void Scalecube(POINT* minPoint, POINT* maxPoint, int deltaX, int deltaY);//큐브키우기