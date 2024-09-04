#include <iostream>
#include <fstream>
#include <time.h>
#include <random>
#include <algorithm>
#include <cstdlib>

void print_clock_freq(){
    std::ifstream cpuinfo("/proc/cpuinfo");
    std::string line;
    std::string frequency;

    while (std::getline(cpuinfo, line)) {
        if (line.find("cpu MHz") != std::string::npos) {
            frequency = line.substr(line.find(":") + 2);
            break;
        }
    }

    std::cout << frequency << "\n";
}

void matrix_multiply(float* A, float* B, float* C, int size) {
    for (int i = 0; i < size; i++) {
        print_clock_freq();
        for (int j = 0; j < size; j++) {
            float sum = 0.0;
            for (int k = 0; k < size; k++) {
                sum += A[i * size + k] * B[k * size + j];
            }
            C[i * size + j] = sum;
        }
    }
}

int main() {

    int SIZE = 128; // Size of the matrices
    for (int j=0; j<SIZE * SIZE; ++j){

	// Create input matrices
        float A[SIZE * SIZE];
        std::generate_n(A, SIZE * SIZE, [](){ return static_cast<float>(rand()) / RAND_MAX; });
        float B[SIZE * SIZE];
        std::generate_n(B, SIZE * SIZE, [](){ return static_cast<float>(rand()) / RAND_MAX; });
        float C[SIZE * SIZE] = {0};

	// Perform matrix multiplication without AVX instructions
        matrix_multiply(A, B, C, SIZE);
    }

    return 0;
}
