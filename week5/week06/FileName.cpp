#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#include <windows.h>
#include <stdio.h>

POINT startPoint = { 0 };
POINT endPoint = { 0 };
POINT nowPoint = { 0 };
int isMouseLButtonPressed = 0;
int isMouseRButtonPressed = 0;


HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255)); // ��ȫ��
HBRUSH clear = CreateSolidBrush(RGB(255, 255, 255)); // ���
HBRUSH black = CreateSolidBrush(RGB(0, 0, 0)); // ������

// �������� �̺�Ʈ�� ó���ϴ� �ݹ�(Callback) �Լ�.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_LBUTTONDOWN: // ���콺 ��ư�� ������ ��
	{
		startPoint.x = LOWORD(lParam); // ���� ����
		startPoint.y = HIWORD(lParam); // ���� ����
		isMouseLButtonPressed = 1;
	}
	break;

	case WM_LBUTTONUP: // ���콺 ��ư ������ ��
	{
		if (isMouseLButtonPressed)
		{
			endPoint.x = LOWORD(lParam);
			endPoint.y = HIWORD(lParam);
			isMouseLButtonPressed = 0;
			// WM_PAINT �޽����� �����Ͽ� �׸� ȭ�鿡 �׸��ϴ�.
			InvalidateRect(hwnd, NULL, TRUE);
		}
	}
	break;

	case WM_RBUTTONDOWN:
	{
		int mouseX = LOWORD(lParam);
		int mouseY = HIWORD(lParam);

		if (mouseX >= startPoint.x && mouseX <= endPoint.x && mouseY >= startPoint.y && mouseY <= endPoint.y) {
			isMouseRButtonPressed = 1;
			nowPoint.x = mouseX;
			nowPoint.y = mouseY;
			InvalidateRect(hwnd, NULL, TRUE);
		}
	}
	break;

	case WM_RBUTTONUP:
	{
		isMouseRButtonPressed = 0;
		InvalidateRect(hwnd, NULL, TRUE);
	}
	break;

	case WM_MOUSEMOVE:
	{

		HDC hdc = GetDC(hwnd);

		int mouseX = LOWORD(lParam);
		int mouseY = HIWORD(lParam);

		if (isMouseRButtonPressed) {
			nowPoint.x = mouseX;
			nowPoint.y = mouseY;
			InvalidateRect(hwnd, NULL, TRUE);
		}
	}
	break;

	case WM_PAINT:
	{
		HDC hdc = GetDC(hwnd);

		if (!isMouseLButtonPressed && !isMouseRButtonPressed)
		{
			RECT rect = { startPoint.x, startPoint.y, endPoint.x, endPoint.y };
			FrameRect(hdc, &rect, black);
			FillRect(hdc, &rect, hBrush);
			MoveToEx(hdc, startPoint.x, startPoint.y, NULL);
		}
		else if (isMouseRButtonPressed) {
			int mouseX = nowPoint.x - endPoint.x;
			int mouseY = nowPoint.y - endPoint.y;
			startPoint.x += mouseX;
			startPoint.y += mouseY;
			endPoint.x += mouseX;
			endPoint.y += mouseY;

			RECT rect = { 0, 0, 800, 600 };
			FillRect(hdc, &rect, clear);

			rect = { startPoint.x, startPoint.y, endPoint.x, endPoint.y };
			FillRect(hdc, &rect, hBrush);
		}
		else
		{
			RECT rect = { 0, 0, 800, 600 };
			FillRect(hdc, &rect, clear);
		}
		ReleaseDC(hwnd, hdc);
	}
	break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return S_OK;
}


#ifdef UNICODE
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
#else
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR pCmdLine, _In_ int nCmdShow)
#endif
{
	/* ������ Ŭ���� ����.*/
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(wc));	// ��� 0���� �ʱ�ȭ.

	// ������ Ŭ���� �� ����
	wc.hInstance = hInstance;
	wc.lpszClassName = TEXT("Computer Software");
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_CROSS);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;

	// ������ Ŭ���� ���.
	if (RegisterClass(&wc) == 0)
	{
		MessageBox(NULL, L"RegisterClass failed!", L"Error", MB_ICONERROR);
		exit(-1);	//����
	}

	// Window viewport ���� ����
	RECT rect = { 150, 100, 800, 600 };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	// ������ ����
	HWND hwnd = CreateWindow(
		wc.lpszClassName,
		TEXT("202207027 ������"),
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		0, 0,
		800, 600,
		NULL, NULL,
		hInstance,
		NULL
	);

	// ���� �˻�.
	if (hwnd == NULL)
	{
		MessageBox(NULL, L"CreateWindow failed!", L"Error", MB_ICONERROR);
		exit(-1);
	}

	// â ���̱�.
	ShowWindow(hwnd, SW_SHOW); // â ����
	UpdateWindow(hwnd); // ������Ʈ�ؾ� ����. �� ������ ���ٰ� ���� ��.



	// �޽��� ó�� ����.
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		// �޽��� ó��.
		if (GetMessage(&msg, hwnd, 0, 0))
			//if (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE)) // PM_REMOVE�� �ڸ��� �� �޼����� ���� ��Ұų�.�� �ǹ��ε� ����ٴ� ����.
		{

			// �޽��� �ؼ�����.
			TranslateMessage(&msg);
			// �޽����� ó���ؾ��� ���� ��������.
			DispatchMessage(&msg);

		}
		/*else
		{

		}*/
	}

	//���� �޽��� ������
	return (int)msg.wParam;

}