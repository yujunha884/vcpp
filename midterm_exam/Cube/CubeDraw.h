#pragma once
HRGN Drawcube(HWND hWnd, HDC hdc, int left, int top, int right, int bottom); // ť��׸��� 

void Movecube(POINT* minPoint, POINT* maxPoint, int deltaX, int deltaY);//ť���̵�

void Scalecube(POINT* minPoint, POINT* maxPoint, int deltaX, int deltaY);//ť��Ű���