#include <iostream>
#include <clocale>
#include <windows.h>

using std::cin;
using std::cout;
using std::string;

int SCREEN_WIDTH = 0;
int SCREEN_HEIGHT = 0;

void gotoxy(int x, int y)
{
    COORD c = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void ReadConsoleSize()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;

    if (GetConsoleScreenBufferInfo(hOut, &info))
    {
        SCREEN_WIDTH = info.srWindow.Right - info.srWindow.Left + 1;
        SCREEN_HEIGHT = info.srWindow.Bottom - info.srWindow.Top + 1;
    }
}

// Ввод целого числа в диапазоне [minV, maxV]
// Повторяет запрос пока не введется корректное число
int readInt(string name, int minV, int maxV)
{
    int value;
    while (true)
    {
        cout << name << " (" << minV << ".." << maxV << "): ";
        cin >> value;

        if (cin && value >= minV && value <= maxV)
            return value;

        cout << "  Ошибка: нужно целое число от " << minV
            << " до " << maxV << ". Попробуйте снова.\n";
    }
}

void drawRectangle(int x, int y, int width, int height)
{
    for (int i = 0; i < height; ++i)
    {
        gotoxy(x, y + i);

        if (i == 0 || i == height - 1)
        {
            for (int j = 0; j < width; ++j)
                cout << '*';
        }
        else
        {
            cout << '*';
            gotoxy(x + width - 1, y + i);
            cout << '*';
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");

    ReadConsoleSize();

    int rectCount = readInt("Число прямоугольников", 1, 10);

    int xs[10], ys[10], widths[10], heights[10];

    for (int k = 0; k < rectCount; ++k)
    {
        cout << "\nПрямоугольник #" << k + 1 << ":\n";

        xs[k] = readInt("x", 0, SCREEN_WIDTH - 1);
        ys[k] = readInt("y", 0, SCREEN_HEIGHT - 1);

        widths[k] = readInt("ширина прямоугольника", 1, SCREEN_WIDTH - xs[k]);
        heights[k] = readInt("высота прямоугольника", 1, SCREEN_HEIGHT - ys[k]);
    }

    system("cls");

    for (int k = 0; k < rectCount; ++k)
        drawRectangle(xs[k], ys[k], widths[k], heights[k]);

    gotoxy(0, SCREEN_HEIGHT-1);


    return 0;
}
