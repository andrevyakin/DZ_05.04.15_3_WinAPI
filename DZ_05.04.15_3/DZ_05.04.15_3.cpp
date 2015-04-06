/*3.	В нижней части клиентской области окна отобразить кнопку с надписью «Показать»,
в верхней части окна – статическую надпись «Введите текст».
После нажатия на кнопку в средней части окна отображается многострочный редактор
с исходным текстом «Нажмите правую клавишу мыши».
После нажатия правой клавиши мыши скрыть редактор.*/

#include<Windows.h>
#include<tchar.h>

static TCHAR WindowsClass[] = L"win32app";
static TCHAR Title[] = L"MyApp";
HINSTANCE hinst;
RECT desktop;

#define ID_BUTTON1 1001

#define ID_EDIT1 1004

HWND button1, edit1;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hinstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hinstance;
	wcex.hIcon = LoadIcon(hinstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	/*wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);*/
	wcex.hbrBackground = CreateSolidBrush(RGB(150, 70, 150));
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = WindowsClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL, L"Call faild!", L"MyApp", NULL);
		return 1;
	}

	hinst = hinstance;
	GetWindowRect(GetDesktopWindow(), &desktop);
	HWND hWnd = CreateWindow(
		WindowsClass,
		Title,
		WS_OVERLAPPEDWINDOW,
		desktop.right/4,
		desktop.bottom/6,
		desktop.right/2,
		desktop.bottom/2,
		NULL,
		NULL,
		hinst,
		NULL);

	if (!hWnd)
	{
		MessageBox(NULL, L"Create window faild!", L"MyApp", NULL);
		return 1;
	}
	SetTimer(hWnd, 1, 100, NULL);
	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return(int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rect;
	COLORREF colorText = RGB(0, 0, 255); // задаём цвет текста
	
	switch (message)
	{

	case WM_COMMAND:

	case BN_CLICKED:

		if (LOWORD(wParam) == ID_BUTTON1)
		{
			
			GetClientRect(hWnd, &rect);
			edit1 = CreateWindowEx(
				WS_EX_CLIENTEDGE,
				L"edit",
				L"Нажмите правую клавишу мыши",
				WS_CHILD | WS_VISIBLE | EM_FMTLINES,
				rect.right / 4,									/*координаты по X*/
				rect.bottom / 4,								/*координаты по Y*/
				rect.right / 2,									/*Ширина окошка*/
				rect.bottom / 2,
				hWnd,
				(HMENU)ID_EDIT1,
				hinst,
				NULL);
		
		}
		
		break;

	case WM_RBUTTONDOWN:
			
			ShowWindow(edit1, SW_HIDE);
			break;

	case WM_CREATE:

		GetClientRect(hWnd, &rect);
				
		button1 = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			L"button",
			L"Показать",
			WS_CHILD | WS_VISIBLE,
			rect.right / 2 - ARRAYSIZE(L"Показать") * 4 - 10,		/*координаты по X*/
			rect.bottom - 30,						/*координаты по Y*/
			ARRAYSIZE(L"Показать") * 10,						/*Ширина окошка*/
			25,
			hWnd,
			(HMENU)ID_BUTTON1,
			hinst,
			NULL);

		
		break;

	case WM_PAINT:

		hdc = BeginPaint(hWnd, &ps); // инициализируем контекст устройства
		GetClientRect(hWnd, &rect); // получаем ширину и высоту области для рисования
		SetTextColor(hdc, colorText); // устанавливаем цвет контекстного устройства
		
		
				DrawText(hdc, L"В в е д и т е   т е к с т", -1, &rect, DT_SINGLELINE | DT_CENTER); // рисуем текст
			
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}