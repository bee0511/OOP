#include <iostream>
#include <vector>
using namespace std;

#define Max 1000

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
/*int Partition(int *arr, int front, int end){
    int pivot = arr[end];
    int i = front -1;
    for (int j = front; j < end; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    i++;
    swap(&arr[i], &arr[end]);
    return i;
}
void QuickSort(int *arr, int front, int end){
    if (front < end) {
        int pivot = Partition(arr, front, end);
        QuickSort(arr, front, pivot - 1);
        QuickSort(arr, pivot + 1, end);
    }
}*/

void QuickSort(int *arr, int left, int right, int size){
    if(left < 0 || right > size || right <= left ){
        return;
    }
    //cout << "sizeof(arr)/sizeof(int): " << sizeof(arr)/sizeof(int*) << endl;
    int i = left, j = right, standard = arr[left];

    while(i != j){
        while(arr[j] >= standard && i < j){ j -= 1;}
        while(arr[i] <= standard && i < j){ i += 1;}
        if(i < j){
            int temp = arr[j];
            arr[j] = arr[i];
            arr[i] = temp;
        }
    }
    arr[left] = arr[i];
    arr[i] = standard;

    QuickSort(arr, left, i-1, size);
    QuickSort(arr, i+1, right, size);
}

void InsertionSort(int *arr, int size){
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        while (key < arr[j] && j >= 0) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

void SelectionSort(int *arr, int size){
    for(int i = 0 ; i < size - 1; i++){
        int min_index = i;
        for(int j = i + 1 ; j < size ; j++){
            if(arr[min_index] > arr[j])
                min_index = j;
        }
        int temp = arr[min_index];
        arr[min_index] = arr[i];
        arr[i] = temp;
    }
}

int BinarySearch(int *arr, int size, int key){
    int L = 0, R = size - 1, mid, ret = -1; //ret stands for return value.
    while(L <= R){
        mid = L + (R - L) / 2;
        if(arr[mid] < key)
            L = mid + 1;
        else if (arr[mid] > key)
            R = mid - 1;
        else{
            ret = mid;
            break;
        }
    }
    return ret;
}

void Merge(std::vector<int> &Array, int front, int mid, int end){

    // 利用 std::vector 的constructor, 
    // 把array[front]~array[mid]放進 LeftSub[]
    // 把array[mid+1]~array[end]放進 RightSub[]
    std::vector<int> LeftSub(Array.begin()+front, Array.begin()+mid+1),
                     RightSub(Array.begin()+mid+1, Array.begin()+end+1);

    LeftSub.insert(LeftSub.end(), Max);      // 在LeftSub[]尾端加入值為 Max 的元素
    RightSub.insert(RightSub.end(), Max);    // 在RightSub[]尾端加入值為 Max 的元素

    int idxLeft = 0, idxRight = 0;

    for (int i = front; i <= end; i++) {

        if (LeftSub[idxLeft] <= RightSub[idxRight] ) {
            Array[i] = LeftSub[idxLeft];
            idxLeft++;
        }
        else{
            Array[i] = RightSub[idxRight];
            idxRight++;
        }
    }
}

void MergeSort(std::vector<int> &array, int front, int end){
                                         // front與end為矩陣範圍
    if (front < end) {                   // 表示目前的矩陣範圍是有效的
        int mid = (front+end)/2;         // mid即是將矩陣對半分的index
        MergeSort(array, front, mid);    // 繼續divide矩陣的前半段subarray
        MergeSort(array, mid+1, end);    // 繼續divide矩陣的後半段subarray
        Merge(array, front, mid, end);   // 將兩個subarray做比較, 並合併出排序後的矩陣
    }
}

void PrintArray(std::vector<int> &array){
    for (int i = 0; i < array.size(); i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}



void PrintArray(int *arr, int size){
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}
int main(){
    int a[] = {3,1,2,4,9,7,6,8,5};
    std::vector<int> array(a, a+sizeof(a)/sizeof(int));
    MergeSort(array, 0, 8);
    //PrintArray(array);
    int size = sizeof(a)/sizeof(int);
    //cout << "sizeof(a)/sizeof(int): " << sizeof(a)/sizeof(int) << endl;
    //SelectionSort( a, size);
    //InsertionSort(a, size);
    //int index, find = 1;
    //index = BinarySearch(a, size, find);
    //cout << find << " is at " << index << endl;
    QuickSort(a, 0, 8, size);
    PrintArray(a, size);
    return 0;
}