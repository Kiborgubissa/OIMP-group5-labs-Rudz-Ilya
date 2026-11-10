#include <iostream>
#include <algorithm>
#include <vector>
#include <clocale>

//лаба совметсная сортировка

int kol() {
    int n;
    std::cout << "Введите количество чисел массива 1:\n";
    std::cin >> n;
    if (n <= 0) {
        std::cout << "ошибка";
        return 0;
    }
    return n;
}

void vvod(int n, int arr1[]) {
    std::cout << "введите массив 1: \n";
    for (int i = 0; i < n; ++i) {
        std::cin >> arr1[i];
    }

}

// Сортировка пузырьком

void sort1(int n, int arr1[]) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr1[j] > arr1[j + 1]) {
                std::swap(arr1[j], arr1[j + 1]);
            }
        }
    }

}

// Сортировка вставками

void Sort2(std::vector<int>& arr2) 
{
    for (size_t i = 1; i < arr2.size(); ++i) {
        int key = arr2[i];
        size_t j = i;
        while (j > 0 && arr2[j - 1] > key) {
            arr2[j] = arr2[j - 1];
            --j;
        }
        arr2[j] = key;
    }

    std::cout << "Отсортированный массив 2: \n";
    for (int num : arr2) {
        std::cout << num << " ";
    }
    std::cout << "\n";
}

std::vector<int> InputArray2() {
    int n;
    std::cout << "Введите количество элементов массива 2:\n";
    std::cin >> n;
    std::vector<int> arr2(n);
    std::cout << "Введите элементы массива 2:\n";
    for (int i = 0; i < n; ++i) {
        std::cin >> arr2[i];
    }
    return arr2;
}



int main()
{ 
    setlocale(LC_ALL, "Russian");

    int n = kol();
    int* arr1 = new int[n];
    vvod(n, arr1);
    sort1(n, arr1);

    std::cout << "Результат: ";
    for (int i = 0; i < n; ++i) {
        std::cout << arr1[i] << " ";
    }
    std::cout << "\n";


    std::vector<int> my_array = InputArray2();
    Sort2(my_array);


    std::vector<int> result(n+my_array.size());

    int i = 0, j = 0, k = 0;

    while (i < n && j < my_array.size())
    {
        if (arr1[i] <= my_array[j])
        {
            result[k] = arr1[i];
            k++; i++;
        }
        else
        {
            result[k] = my_array[j];
            k++; j++;
        }
            
    }
    while(i < n) result[k++] = arr1[i++];
    while(j < my_array.size()) result[k++] = my_array[j++];


    std::cout << "\nИтоговый массив: \n";
    for (int i = 0; i < result.size(); i++)
        std::cout << result[i] << " ";

    delete[] arr1;
    return 0;
}
