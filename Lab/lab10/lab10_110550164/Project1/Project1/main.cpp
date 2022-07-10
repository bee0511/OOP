#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void PrintArray(std::vector<int>& array) {
    for (int i = 0; i < array.size(); i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

void QuickSort(vector<int> &arr, int left, int right) {
    if (left < 0 || right >= arr.size() || right <= left) {
        return;
    }
    int i = left, j = right, standard = arr[left];

    while (i != j) {
        while (arr[j] >= standard && i < j) { j -= 1; }
        while (arr[i] <= standard && i < j) { i += 1; }
        if (i < j) {
            swap(arr[i], arr[j]);
        }
    }
    arr[left] = arr[i];
    arr[i] = standard;

    QuickSort(arr, left, i - 1);
    QuickSort(arr, i + 1, right);
}

void Heapify(vector<int>& arr, int n, int i) {//n是長度, i是root
    int left = 2 * i, right = 2 * i + 1, max = i;
    if (left < n && arr[left] > arr[i]) {
        max = left;
    }
    if (right < n && arr[right] > arr[max]) {
        max = right;
    }
    if (max != i) {
        swap(arr[i], arr[max]);
        Heapify(arr, n, max);
    }
}

void BuildMaxHeap(vector<int>& arr) {
    for (int i = arr.size() - 1; i >= 0; i--) {
        Heapify(arr, arr.size(), i);
    }
    //cout << "After BuildMaxHeap(): ";
    //PrintArray(arr);
}

void HeapSort(vector<int>& arr) {
    BuildMaxHeap(arr);
    for (int length = arr.size()- 1; length > 0; length--) {
        swap(arr[0], arr[length]);
        Heapify(arr, length, 0);//長度-1 因為最後一個是sort好的
    }
}

int main() {
    std::fstream file;
    file.open("input2.txt");

    int times = 0;
    file >> times;

    for (int t = 0; t < times; t++) {
        int size = 0;
        file >> size;

        std::vector<int> array1;
        std::vector<int> array2;

        for (int i = 0; i < size; i++) {
            int x;
            file >> x;
            array1.push_back(x);
            array2.push_back(x);
        }

        HeapSort(array1);
        cout << "Max Heap Sort : ";
        PrintArray(array1);

        QuickSort(array2, 0, array2.size() - 1);
        cout << "Quick Sort : ";
        PrintArray(array2);
        cout << endl;
    }
    system("pause");
    return 0;
}