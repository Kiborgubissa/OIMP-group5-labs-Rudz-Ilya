#include <iostream>
#include <algorithm>
#include <vector>
#include <clocale>
#include <iomanip>
#include <string>
#include <ctime> // Для простой паузы через clock()

using std::cout;
using std::cin;
using std::endl;

// ---------- Вспомогательные функции ----------

// Очистка экрана
void clearScreen() {
    cout << "\033[2J\033[H";
}

// Простая пауза без потоков (просто ждем, пока не пройдет время)
void sleep_ms(int ms) {
    clock_t start_time = clock();
    // Ждем, пока разница во времени не достигнет нужного количества миллисекунд
    while (clock() < start_time + ms * CLOCKS_PER_SEC / 1000) {
        // Пустой цикл (программа просто "крутится" здесь)
    }
}

// Визуализация одного массива (для сортировок)
void drawBars(const std::vector<int>& arr, int hl1 = -1, int hl2 = -1, const std::string& title = "") {
    clearScreen();
    if (!title.empty()) cout << title << "\n\n";
    if (arr.empty()) return;

    int maxVal = *std::max_element(arr.begin(), arr.end());
    const int maxBarWidth = 50;

    for (size_t i = 0; i < arr.size(); ++i) {
        int len = (maxVal == 0) ? 0 : (arr[i] * maxBarWidth / maxVal);
        if (len < 1 && arr[i] != 0) len = 1;
        cout << std::setw(3) << i << " | ";
        bool hl = (static_cast<int>(i) == hl1 || static_cast<int>(i) == hl2);
        for (int j = 0; j < len; ++j) {
            if (hl) cout << "\033[31m*\033[0m";
            else    cout << "*";
        }
        cout << " " << arr[i] << "\n";
    }
    cout << endl;
}

void drawBars(int arr[], int n, int hl1 = -1, int hl2 = -1, const std::string& title = "") {
    std::vector<int> v(arr, arr + n);
    drawBars(v, hl1, hl2, title);
}

// Специальная визуализация для слияния: показываем оба массива и результат
void drawMergeVisual(int arr1[], int n1, int i,
    const std::vector<int>& arr2, int j,
    const std::vector<int>& result, int k,
    const std::string& title) {
    clearScreen();
    cout << title << "\n\n";

    // Найдем максимум для красивого масштабирования столбцов
    int maxVal = 0;
    for (int x = 0; x < n1; ++x) maxVal = std::max(maxVal, arr1[x]);
    for (int x : arr2) maxVal = std::max(maxVal, x);
    const int maxBarWidth = 40;

    // 1. Первый массив
    cout << "Массив 1:\n";
    for (int x = 0; x < n1; ++x) {
        int len = (maxVal == 0) ? 0 : (arr1[x] * maxBarWidth / maxVal);
        if (len < 1 && arr1[x] != 0) len = 1;
        cout << std::setw(3) << x << " | ";
        for (int c = 0; c < len; ++c) {
            if (x == i) cout << "\033[31m*\033[0m"; // Красный - текущий сравниваемый
            else if (x < i) cout << " ";            // Прошедшие элементы не рисуем
            else cout << "*";
        }
        if (x == i) cout << "  <-- текущий";
        cout << "\n";
    }

    // 2. Второй массив
    cout << "\nМассив 2:\n";
    for (size_t x = 0; x < arr2.size(); ++x) {
        int len = (maxVal == 0) ? 0 : (arr2[x] * maxBarWidth / maxVal);
        if (len < 1 && arr2[x] != 0) len = 1;
        cout << std::setw(3) << x << " | ";
        for (int c = 0; c < len; ++c) {
            if ((int)x == j) cout << "\033[31m*\033[0m";
            else if ((int)x < j) cout << " ";
            else cout << "*";
        }
        if ((int)x == j) cout << "  <-- текущий";
        cout << "\n";
    }

    // 3. Результат
    cout << "\nРезультат (слияние):\n";
    for (int x = 0; x < k; ++x) {
        int len = (maxVal == 0) ? 0 : (result[x] * maxBarWidth / maxVal);
        if (len < 1 && result[x] != 0) len = 1;
        cout << std::setw(3) << x << " | ";
        for (int c = 0; c < len; ++c) cout << "\033[32m*\033[0m"; // Зеленый - добавлено
        cout << " " << result[x] << "\n";
    }
    cout << endl;
}

// ---------- Исходные функции ----------

int kol() {
    int n;
    cout << "Введите количество чисел массива 1:\n";
    cin >> n;
    if (n <= 0) {
        cout << "ошибка";
        return 0;
    }
    return n;
}

void vvod(int n, int arr1[]) {
    cout << "введите массив 1: \n";
    for (int i = 0; i < n; ++i) {
        cin >> arr1[i];
    }
}

// Сортировка пузырьком с визуализацией
void sort1(int n, int arr1[]) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            drawBars(arr1, n, j, j + 1, "Сортировка пузырьком: сравниваем");
            sleep_ms(1000);

            if (arr1[j] > arr1[j + 1]) {
                std::swap(arr1[j], arr1[j + 1]);
                drawBars(arr1, n, j, j + 1, "Сортировка пузырьком: меняем местами");
                sleep_ms(1000);
            }
        }
    }
    drawBars(arr1, n, -1, -1, "Сортировка пузырьком (готово)");
    sleep_ms(2000);
}

// Сортировка вставками с визуализацией
void Sort2(std::vector<int>& arr2) {
    for (size_t i = 1; i < arr2.size(); ++i) {
        int key = arr2[i];
        size_t j = i;
        drawBars(arr2, j, -1, "Сортировка вставками: берём элемент");
        sleep_ms(1000);

        while (j > 0 && arr2[j - 1] > key) {
            arr2[j] = arr2[j - 1];
            --j;
            drawBars(arr2, j, j + 1, "Сортировка вставками: сдвигаем");
            sleep_ms(1000);
        }
        arr2[j] = key;
        drawBars(arr2, j, -1, "Сортировка вставками: вставляем");
        sleep_ms(1000);
    }
    drawBars(arr2, -1, -1, "Сортировка вставками (готово)");
    sleep_ms(2000);

    cout << "Отсортированный массив 2: \n";
    for (int num : arr2) cout << num << " ";
    cout << "\n";
    sleep_ms(1000);
}

std::vector<int> InputArray2() {
    int n;
    cout << "Введите количество элементов массива 2:\n";
    cin >> n;
    std::vector<int> arr2(n);
    cout << "Введите элементы массива 2:\n";
    for (int i = 0; i < n; ++i) {
        cin >> arr2[i];
    }
    return arr2;
}

// ---------- main ----------

int main() {
    setlocale(LC_ALL, "Russian");

    int n = kol();
    int* arr1 = new int[n];
    vvod(n, arr1);
    sort1(n, arr1);

    cout << "Результат: ";
    for (int i = 0; i < n; ++i) cout << arr1[i] << " ";
    cout << "\n";
    sleep_ms(1500);

    std::vector<int> my_array = InputArray2();
    Sort2(my_array);

    std::vector<int> result(n + my_array.size());
    int i = 0, j = 0, k = 0;

    // Слияние с новой красивой визуализацией
    drawMergeVisual(arr1, n, i, my_array, j, result, k, "Начинаем слияние массивов");
    sleep_ms(1500);

    while (i < n && j < my_array.size()) {
        if (arr1[i] <= my_array[j]) {
            result[k] = arr1[i];
            k++; i++;
        }
        else {
            result[k] = my_array[j];
            k++; j++;
        }
        drawMergeVisual(arr1, n, i, my_array, j, result, k, "Слияние массивов");
        sleep_ms(1200);
    }
    while (i < n) {
        result[k] = arr1[i];
        k++; i++;
        drawMergeVisual(arr1, n, i, my_array, j, result, k, "Слияние массивов: добираем из 1-го");
        sleep_ms(1200);
    }
    while (j < my_array.size()) {
        result[k] = my_array[j];
        k++; j++;
        drawMergeVisual(arr1, n, i, my_array, j, result, k, "Слияние массивов: добираем из 2-го");
        sleep_ms(1200);
    }

    cout << "\nИтоговый массив: \n";
    for (int x = 0; x < result.size(); x++)
        cout << result[x] << " ";

    delete[] arr1;
    return 0;
}
