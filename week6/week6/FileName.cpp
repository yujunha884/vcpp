//#define DEBUG
#ifdef UNICODE
#ifdef DEBUG
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:WINDOWS")
#endif // DEBUG
#else
#ifdef DEBUG
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:WINDOWS")
#endif // DEBUG
#endif

#include <windows.h>

POINT startPoint = { 0 };
POINT endPoint = { 0 };
int isKeyPressed = 0;

RECT rect_user = { 5, 5, 10, 10 }; // ���� ��� ��ǥ (50, 50)���� ������ �ϴ� ��ǥ (150, 150)������ �簢��
RECT rect_target = { 50, 50, 150, 150 }; // ���� ��� ��ǥ (50, 50)���� ������ �ϴ� ��ǥ (150, 150)������ �簢��
int dx = 0;
int dy = 0;
// �������� �̺�Ʈ�� ó���ϴ� �ݹ�(Callback) �Լ�.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc = GetDC(hwnd);

	HBRUSH hBrush_user = CreateSolidBrush(RGB(0, 0, 255));
	HBRUSH hBrush_target = CreateSolidBrush(RGB(255, 0, 255));
	HBRUSH hBrush_eraser = CreateSolidBrush(RGB(255, 255, 255));
	const wchar_t* text = L"Crash!!!";

	switch (uMsg)
	{
	case WM_KEYDOWN:
		if (isKeyPressed == 0) {
			isKeyPressed = 1;
			if (wParam == VK_RIGHT) {
				dx = 1; // ���������� �̵�
			}
			else if (wParam == VK_LEFT) {
				dx = -1; // �������� �̵�
			}
			else if (wParam == VK_UP) {
				dy = -1; // ���� �̵�
			}
			else if (wParam == VK_DOWN) {
				dy = 1; // �Ʒ��� �̵�
			}
			SetTimer(hwnd, 1, 10, NULL); // �������� �̵��� ���� Ÿ�̸� ����
		}	
		break;
	
	case WM_TIMER:
		// �������� �̵��� ó���ϴ� Ÿ�̸� �ڵ鸵
		rect_user.left += dx;
		rect_user.right += dx;
		rect_user.top += dy;
		rect_user.bottom += dy;
		InvalidateRect(hwnd, NULL, TRUE);
		break;

	case WM_KEYUP:
		isKeyPressed = 0;
		dx = 0;
		dy = 0;
		KillTimer(hwnd, 1); // Ÿ�̸� ����
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		RECT rcClient;
		GetClientRect(hwnd, &rcClient);  // Get the size of the client area

		// Create an off-screen DC for double-buffering
		HDC hdcMem = CreateCompatibleDC(hdc);
		HBITMAP hbmMem = CreateCompatibleBitmap(hdc, rcClient.right, rcClient.bottom); // Use client area size
		HGDIOBJ hOld = SelectObject(hdcMem, hbmMem);

		// Draw to hdcMem here...
		BOOL isCollision = (rect_user.left >= rect_target.left && rect_user.right <= rect_target.right &&
			rect_user.top >= rect_target.top && rect_user.bottom <= rect_target.bottom);

		// Erase the background
		FillRect(hdcMem, &rcClient, (HBRUSH)(COLOR_WINDOW + 1));

		// Draw rectangles
		FillRect(hdcMem, &rect_target, hBrush_target);  // First draw the pink box
		FillRect(hdcMem, &rect_user, hBrush_user);  // Then draw the blue box on top

		if (isCollision)
		{
			TextOut(hdcMem, 10, 10, text, lstrlen(text));
		}

		// Transfer the off-screen DC to the screen
		BitBlt(hdc, 0, 0, rcClient.right, rcClient.bottom, hdcMem, 0, 0, SRCCOPY);

		// Clean up
		SelectObject(hdcMem, hOld);
		DeleteObject(hbmMem);
		DeleteDC(hdcMem);

		EndPaint(hwnd, &ps);

		break;
	}
	break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	DeleteObject(hBrush_user);
	DeleteObject(hBrush_target);
	DeleteObject(hBrush_eraser);
	ReleaseDC(hwnd, hdc);

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
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
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
		TEXT("�ļ� Application"),
		WS_OVERLAPPEDWINDOW,
		0, 0,
		width, height,
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

	// �޽��� ó��.
	while (msg.message != WM_QUIT)
	{
		if (GetMessage(&msg, NULL, 0, 0))
		{
			// �޽��� �ؼ�����.
			TranslateMessage(&msg);
			// �޽����� ó���ؾ��� ���� ��������.
			DispatchMessage(&msg);
		}
		//if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		//{
		//	// �޽��� �ؼ�����.
		//	TranslateMessage(&msg);
		//	// �޽����� ó���ؾ��� ���� ��������.
		//	DispatchMessage(&msg);
		//} // PM_REMOVE�� �ڸ��� �� �޼����� ���� ��Ұų�.�� �ǹ��ε� ����ٴ� ����.
		//else{}
	}

	UnregisterClass(wc.lpszClassName, wc.hInstance);

	//���� �޽��� ������
	return (int)msg.wParam;

}