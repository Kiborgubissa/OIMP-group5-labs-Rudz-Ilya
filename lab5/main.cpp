#include <iostream>
#include <windows.h>
#include <clocale>

using namespace std;

//лаба демонстрация сортировки

HANDLE hConsole;

// 7 — белый, 12 — красный, 10 — зелёный, 14 — жёлтый
const WORD WHITE = 7;
const WORD RED = 12;
const WORD GREEN = 10;
const WORD YELLOW = 14;

void gotoxy(int x, int y)
{
    COORD c = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hConsole, c);
}

// left  — индекс левого в паре (красный)
// right — индекс правого в паре (зелёный)
// sortedFrom — с какого индекса элементы уже на месте (жёлтые)
void drawArray(const int arr[], int n, int left = -1, int right = -1, int sortedFrom = -1)
{
    gotoxy(0, 1);
    for (int i = 0; i < n; i++)
    {
        WORD color = WHITE;
        if (sortedFrom != -1 && i >= sortedFrom) color = YELLOW;
        if (i == left)  color = RED;
        if (i == right) color = GREEN;

        SetConsoleTextAttribute(hConsole, color);
        cout << " " << arr[i] << " ";
    }
    SetConsoleTextAttribute(hConsole, WHITE);
}

void bubbleSort(int arr[], int n)
{
    for (int i = 0; i < n-1; i++)
    {
        for (int j = 0; j < n-1-i; j++)
        {
            drawArray(arr, n, j, j+1, n-i);   // пара: j красный, j+1 зелёный
            Sleep(200);

            if (arr[j] > arr[j+1])
            {
                swap(arr[j], arr[j+1]);
                drawArray(arr, n, j, j+1, n-i);   // значения переехали под цветами
                Sleep(200);
            }
        }
        drawArray(arr, n, -1, -1, n-1-i);   // +1 жёлтый справа
        Sleep(200);
    }
    drawArray(arr, n, -1, -1, 0);   // всё жёлтое
}

int main()
{
    setlocale(LC_ALL, "Russian");

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO ci;                  
    GetConsoleCursorInfo(hConsole, &ci);
    ci.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &ci);

    int arr[] = { 7, 2, 9, 4, 1, 8, 3, 6, -10, 0, -20, 5 };
    int n = 12;

    cout << "Сортировка пузырьком:";
    drawArray(arr, n);
    Sleep(1000);

    bubbleSort(arr, n);

    gotoxy(0, 3);
    cout << "Массив отсортирован";

    return 0;
}
