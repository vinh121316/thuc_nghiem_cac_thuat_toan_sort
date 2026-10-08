#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include <algorithm>
#include <iomanip>


// --- MERGE SORT ---
void merge(std::vector<double>& a, int left, int mid, int right, std::vector<double>& temp) {
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) {
        if (a[i] <= a[j]) temp[k++] = a[i++];
        else temp[k++] = a[j++];
    }
    while (i <= mid) temp[k++] = a[i++];
    while (j <= right) temp[k++] = a[j++];
    for (i = left; i <= right; ++i) a[i] = temp[i];
}

void mergeSortHelper(std::vector<double>& a, int left, int right, std::vector<double>& temp) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSortHelper(a, left, mid, temp);
    mergeSortHelper(a, mid + 1, right, temp);
    merge(a, left, mid, right, temp);
}

void runMergeSort(std::vector<double>& a) {
    std::vector<double> temp(a.size());
    mergeSortHelper(a, 0, (int)a.size() - 1, temp);
}

// --- HEAP SORT ---
void heapify(std::vector<double>& a, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && a[left] > a[largest]) largest = left;
    if (right < n && a[right] > a[largest]) largest = right;

    if (largest != i) {
        std::swap(a[i], a[largest]);
        heapify(a, n, largest);
    }
}

void runHeapSort(std::vector<double>& a) {
    int n = a.size();
    for (int i = n / 2 - 1; i >= 0; --i)
        heapify(a, n, i);
    for (int i = n - 1; i > 0; --i) {
        std::swap(a[0], a[i]);
        heapify(a, i, 0);
    }
}

// --- QUICK SORT ---
void quickSortHelper(std::vector<double>& a, int low, int high) {
    if (low >= high) return;
    
    double pivot = a[low + (high - low) / 2];
    int i = low, j = high;

    while (i <= j) {
        while (a[i] < pivot) i++;
        while (a[j] > pivot) j--;
        if (i <= j) {
            std::swap(a[i], a[j]);
            i++;
            j--;
        }
    }

    if (low < j) quickSortHelper(a, low, j);
    if (i < high) quickSortHelper(a, i, high);
}

void runQuickSort(std::vector<double>& a) {
    quickSortHelper(a, 0, (int)a.size() - 1);
}


// Hàm đọc 1 triệu số từ file .txt vào vector
bool loadDataFromFile(const std::string& filename, std::vector<double>& arr) {
    std::ifstream in(filename);
    if (!in.is_open()) return false;

    int n;
    in >> n;
    arr.resize(n);
    for (int i = 0; i < n; ++i) {
        in >> arr[i];
    }
    in.close();
    return true;
}

template <typename Func>
double measureTime(Func sortFunc, std::vector<double> arr) {

    auto start = std::chrono::high_resolution_clock::now();
    sortFunc(arr);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration = end - start;
    return duration.count();
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "================================================================================\n";
    std::cout << "|   File    | QuickSort (ms) | HeapSort (ms) | MergeSort (ms) | std::sort (ms) |\n";
    std::cout << "================================================================================\n";

    for (int file_idx = 1; file_idx <= 10; ++file_idx) {
        std::string filename = "test_" + std::to_string(file_idx) + ".txt";
        std::vector<double> original_data;

        std::cout << "Dang doc " << filename << "..." << std::flush;
        if (!loadDataFromFile(filename, original_data)) {
            std::cerr << "\nKhong tim thay file " << filename << ". Vui long sinh file truoc!\n";
            continue;
        }

        double t_quick = measureTime(runQuickSort, original_data);
        double t_heap  = measureTime(runHeapSort, original_data);
        double t_merge = measureTime(runMergeSort, original_data);
        double t_std   = measureTime([](std::vector<double>& a) {
            std::sort(a.begin(), a.end());
        }, original_data);


        std::cout << "\r| " << std::setw(9) << filename 
                  << " | " << std::setw(14) << t_quick
                  << " | " << std::setw(13) << t_heap
                  << " | " << std::setw(14) << t_merge
                  << " | " << std::setw(14) << t_std << " |\n";
    }

    std::cout << "========================================================================\n";
    return 0;
}