#include <iostream>
#include <clocale>

using std::cin;
using std::cout;

int main()
{
    std::setlocale(LC_ALL, "Russian");

    int a[100];
    int n;

    cout << "Введите размер массива n (0 <= n <= 100):\n";
    cin >> n;

    if (n < 0 || n > 100)
    {
        cout << "Вы ввели некорректное n! (0 <= n <= 100)\n";
        return 0;
    }

    cout << "Введите элементы массива:\n";
    for (int i = 0; i < n; ++i)
    {
        cin >> a[i];
        a[i] *= 2;
    }

    cout << "Измененный массив:\n";
    for (int i = 0; i < n; ++i)
    {
        cout << a[i] << " ";
    }

    return 0;
}
