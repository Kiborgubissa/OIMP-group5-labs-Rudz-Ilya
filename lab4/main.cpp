#include <iostream>

using std::cin;
using std::cout;

int main()
{
    std::setlocale(LC_ALL, "Russian");

    cout << "Поиск количества вхождений массива B в А.\n\n";

    int n, m;
    cout << "Введите количество элементов в массиве A: ";
    cin >> n;

    if (n <= 0)
    {
        cout << "Ошибка: n должно быть больше 0\n";
        return 0;
    }

    cout << "Введите количество элементов в массиве B (образец): ";
    cin >> m;

    if (m <= 0)
    {
        cout << "Ошибка: m должно быть больше 0\n";
        return 0;
    }

    if (m > n)
    {
        cout << "Ошибка: массив B больше массива А, вхождений быть не может\n";
        return 0;
    }

    int* A = new int[n];
    int* B = new int[m];

    cout << "Введите " << n << " чисел для A:\n";
    for (int i = 0; i < n; ++i)
    {
        cin >> A[i];
    }

    cout << "Введите " << m << " чисел для B:\n";
    for (int i = 0; i < m; ++i)
    {
        cin >> B[i];
    }

    int cnt = 0;
    for (int i = 0; i <= n-m; ++i)
    {
        bool matched = true;

        for (int j = 0; j < m; ++j)
        {
            if (A[i+j] != B[j])
            {
                matched = false;
                break;
            }
        }

        if (matched)
            cnt++;
    }

    cout << "Количество вхождений: " << cnt << '\n';

    delete[] A;
    delete[] B;

    return 0;
}
