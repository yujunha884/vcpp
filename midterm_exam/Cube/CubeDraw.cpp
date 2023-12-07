#include <Windows.h>

HRGN Drawcube(HWND hWnd, HDC hdc, int left, int top, int right, int bottom) 
{
	// �߾Ӽ� ���߿� �����
	MoveToEx(hdc, 376, 0, NULL);
	LineTo(hdc, 376, 480);
	MoveToEx(hdc, 0, 188, NULL);
	LineTo(hdc, 800, 188);

	int width = abs(left - right);
	int height = abs(top - bottom);
	int centerX = width / 2;
	int centerY = height / 2;

	POINT MINPOINT = { 0 };
	POINT MAXPOINT = { 0 };

	MINPOINT.x = min(left, right);
	MINPOINT.y = min(top, bottom);
	MAXPOINT.x = max(left, right);
	MAXPOINT.y = max(top, bottom);

	POINT centerPoint = { MINPOINT.x + centerX, MINPOINT.y + centerY };

	if (MINPOINT.x <= 376 && MINPOINT.y < 188) {//�»�
		MoveToEx(hdc, MINPOINT.x, MAXPOINT.y, NULL); //�ظ� �ݽð��
		LineTo(hdc, MAXPOINT.x - centerX / 2, MAXPOINT.y);
		LineTo(hdc, MAXPOINT.x, MAXPOINT.y - centerY / 2);
		LineTo(hdc, MINPOINT.x + centerX / 2, MAXPOINT.y - centerY / 2);
		LineTo(hdc, MINPOINT.x, MAXPOINT.y);

		MoveToEx(hdc, MAXPOINT.x, MAXPOINT.y - centerY / 2, NULL); // �ո� �ݽð��
		LineTo(hdc, MAXPOINT.x, MINPOINT.y);
		LineTo(hdc, MINPOINT.x + centerX / 2, MINPOINT.y);
		LineTo(hdc, MINPOINT.x + centerX / 2, MAXPOINT.y - centerY / 2);

		MoveToEx(hdc, MINPOINT.x + centerX / 2, MINPOINT.y, NULL); // ���� ���Ͻ��� �ݽð�
		LineTo(hdc, MINPOINT.x, MINPOINT.y + centerY / 2);
		LineTo(hdc, MINPOINT.x, MAXPOINT.y);

		POINT hexaPoints[6] = {
		   {MINPOINT.x, MAXPOINT.y}, // 1�� ������
		   {MAXPOINT.x - centerX / 2, MAXPOINT.y}, // 2�� ������
		   {MAXPOINT.x, MAXPOINT.y - centerY / 2}, // 3�� ������
		   {MAXPOINT.x, MINPOINT.y}, // 4�� ������
		   {MINPOINT.x + centerX / 2, MINPOINT.y}, // 5�� ������
		   {MINPOINT.x, MINPOINT.y + centerY / 2}  // 6�� ������
		};
		HRGN Hexa = CreatePolygonRgn(hexaPoints, 6, WINDING);
		return Hexa;
	}
	if (MINPOINT.x <= 376 && MINPOINT.y >= 188) {//����
		MoveToEx(hdc, MINPOINT.x, MINPOINT.y, NULL); //�ظ�
		LineTo(hdc, MINPOINT.x + centerX / 2, MINPOINT.y + centerY / 2);
		LineTo(hdc, MAXPOINT.x, MINPOINT.y + centerY / 2);
		LineTo(hdc, MAXPOINT.x - centerX / 2, MINPOINT.y);
		LineTo(hdc, MINPOINT.x, MINPOINT.y);//����

		MoveToEx(hdc, MINPOINT.x + centerX / 2, MINPOINT.y + centerY / 2, NULL); // �ո�
		LineTo(hdc, MINPOINT.x + centerX / 2, MAXPOINT.y);
		LineTo(hdc, MAXPOINT.x, MAXPOINT.y);
		LineTo(hdc, MAXPOINT.x, MINPOINT.y + centerY / 2);
		LineTo(hdc, MINPOINT.x + centerX / 2, MINPOINT.y + centerY / 2);//�ϳ��� �̹� ������ �׷��� ����

		MoveToEx(hdc, MINPOINT.x, MINPOINT.y, NULL); // ����
		LineTo(hdc, MINPOINT.x, MAXPOINT.y - centerY / 2);
		LineTo(hdc, MINPOINT.x + centerX / 2, MAXPOINT.y);

		POINT hexaPoints[6] = {
		   {MINPOINT.x, MINPOINT.y}, // 1�� ������
		   {MINPOINT.x, MAXPOINT.y - centerY / 2}, // 2�� ������
		   {MINPOINT.x + centerX / 2, MAXPOINT.y}, // 3�� ������
		   {MAXPOINT.x, MAXPOINT.y}, // 4�� ������
		   {MAXPOINT.x, MINPOINT.y + centerY / 2}, // 5�� ������
		   {MAXPOINT.x - centerX / 2, MINPOINT.y}  // 6�� ������
		};
		HRGN Hexa = CreatePolygonRgn(hexaPoints, 6, WINDING);
		return Hexa;
	}
	if (MINPOINT.x > 376 && MINPOINT.y < 188) {//���
		MoveToEx(hdc, MINPOINT.x, MAXPOINT.y - centerY / 2, NULL); //�ظ� �ݽð��
		LineTo(hdc, MINPOINT.x + centerX / 2, MAXPOINT.y);
		LineTo(hdc, MAXPOINT.x, MAXPOINT.y);
		LineTo(hdc, MAXPOINT.x - centerX / 2, MAXPOINT.y - centerY / 2);
		LineTo(hdc, MINPOINT.x, MAXPOINT.y - centerY / 2);

		MoveToEx(hdc, MAXPOINT.x - centerX / 2, MAXPOINT.y - centerY / 2, NULL); // �ո� �ݽð��
		LineTo(hdc, MAXPOINT.x - centerX / 2, MINPOINT.y);
		LineTo(hdc, MINPOINT.x, MINPOINT.y);
		LineTo(hdc, MINPOINT.x, MAXPOINT.y - centerY / 2);

		MoveToEx(hdc, MAXPOINT.x, MAXPOINT.y, NULL); // ���� ���Ͻ��� �ݽð�
		LineTo(hdc, MAXPOINT.x, MINPOINT.y + centerY / 2);
		LineTo(hdc, MAXPOINT.x - centerX / 2, MINPOINT.y);

		POINT hexaPoints[6] = {
		   {MINPOINT.x, MINPOINT.y}, // 1�� ������
		   {MINPOINT.x, MAXPOINT.y - centerY / 2}, // 2�� ������
		   {MINPOINT.x + centerX / 2, MAXPOINT.y}, // 3�� ������
		   {MAXPOINT.x, MAXPOINT.y}, // 4�� ������
		   {MAXPOINT.x, MINPOINT.y + centerY / 2}, // 5�� ������
		   {MAXPOINT.x - centerX / 2, MINPOINT.y}  // 6�� ������
		};
		HRGN Hexa = CreatePolygonRgn(hexaPoints, 6, WINDING);
		return Hexa;
	}
	if (MINPOINT.x > 376 && MINPOINT.y >= 188) {//����
		MoveToEx(hdc, MINPOINT.x + centerX / 2, MINPOINT.y, NULL); //�ظ�
		LineTo(hdc, MINPOINT.x, MINPOINT.y + centerY / 2);
		LineTo(hdc, MAXPOINT.x - centerX / 2, MINPOINT.y + centerY / 2);
		LineTo(hdc, MAXPOINT.x, MINPOINT.y);
		LineTo(hdc, MINPOINT.x + centerX / 2, MINPOINT.y);

		MoveToEx(hdc, MINPOINT.x, MINPOINT.y + centerY / 2, NULL); // �ո�
		LineTo(hdc, MINPOINT.x, MAXPOINT.y);
		LineTo(hdc, MAXPOINT.x - centerX / 2, MAXPOINT.y);
		LineTo(hdc, MAXPOINT.x - centerX / 2, MINPOINT.y + centerY / 2);//�ϳ��� �̹� ������ �׷��� ����

		MoveToEx(hdc, MAXPOINT.x, MINPOINT.y, NULL); // ����
		LineTo(hdc, MAXPOINT.x, MAXPOINT.y - centerY / 2);
		LineTo(hdc, MAXPOINT.x - centerX / 2, MAXPOINT.y);

		POINT hexaPoints[6] = {
		   {MINPOINT.x + centerX / 2, MINPOINT.y}, // 1�� ������
		   {MINPOINT.x, MINPOINT.y + centerY / 2}, // 2�� ������
		   {MINPOINT.x, MAXPOINT.y}, // 3�� ������
		   {MAXPOINT.x - centerX / 2, MAXPOINT.y}, // 4�� ������
		   {MAXPOINT.x, MAXPOINT.y - centerY / 2}, // 5�� ������
		   {MAXPOINT.x, MINPOINT.y}  // 6�� ������
		};
		HRGN Hexa = CreatePolygonRgn(hexaPoints, 6, WINDING);
		return Hexa;
	}
}

void Movecube(POINT* MINPOINT, POINT* MAXPOINT, int deltaX, int deltaY) {
	MINPOINT->x += deltaX; // MINPOINT�� X ��ǥ �̵�
	MINPOINT->y += deltaY; // MINPOINT�� Y ��ǥ �̵�
	MAXPOINT->x += deltaX; // MAXPOINT�� X ��ǥ �̵�
	MAXPOINT->y += deltaY; // MAXPOINT�� Y ��ǥ �̵�
}

void Scalecube(POINT* minPoint, POINT* maxPoint, int deltaX, int deltaY) {
	double scaleFactor = 1;
	if (deltaX > 0) {
		scaleFactor = 1.0 + static_cast<double>(deltaX) / 100.0;  // ���������� �̵��� ������ ũ�⸦ ������ŵ�ϴ�.
	}
	else if (deltaX < 0) {
		scaleFactor = 1.0 / (1.0 - static_cast<double>(deltaX) / 100.0);  // �������� �̵��� ������ ũ�⸦ ���ҽ�ŵ�ϴ�.
	}
	else {
		scaleFactor = 1.0;  // ���� �̵��� ���� ��� ũ��� ������ �ʽ��ϴ�.
	}
	int width = maxPoint->x - minPoint->x;
	int height = maxPoint->y - minPoint->y;
	int centerX = minPoint->x + width / 2;
	int centerY = minPoint->y + height / 2;

	width = static_cast<int>(width * scaleFactor);
	height = static_cast<int>(height * scaleFactor);

	minPoint->x = centerX - width / 2;
	minPoint->y = centerY - height / 2;
	maxPoint->x = minPoint->x + width;
	maxPoint->y = minPoint->y + height;
}