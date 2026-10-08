#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <fstream>
#include <string>

const int N = 1000000;

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::random_device rd;
    std::mt19937_64 gen(rd());
    
    std::uniform_real_distribution<double> dis(-1000000.0, 1000000.0);

    std::vector<double> arr(N);

    for (int file_idx = 1; file_idx <= 10; ++file_idx) {
        for (int i = 0; i < N; ++i) {
            arr[i] = dis(gen);
        }

        if (file_idx == 1) {
            std::sort(arr.begin(), arr.end());
        } else if (file_idx == 2) {
            std::sort(arr.begin(), arr.end(), std::greater<double>());
        }

        std::string filename = "test_" + std::to_string(file_idx) + ".txt";
        std::ofstream out(filename);
        if (!out.is_open()) {
            std::cerr << "Lỗi mở file: " << filename << '\n';
            continue;
        }

        out << N << '\n';
        for (int i = 0; i < N; ++i) {
            out << arr[i] << '\n';
        }
        out.close();

        std::cout << "Tao thanh cong: " << filename << '\n';
    }

    return 0;
}