#include <iostream>
#include <fstream>
#include <time.h>
#include <random>
#include <algorithm>
#include <cstdlib>
#include <immintrin.h> // Include the AVX and AVX2 headers

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

// Matrix multiplication using AVX instructions
void matrix_multiply_avx(float* A, float* B, float* C, int size) {
    for (int i = 0; i < size; i++) {
            print_clock_freq();
        for (int j = 0; j < size; j += 8) {
            __m256 a = _mm256_loadu_ps(&A[i * size]);
            __m256 b = _mm256_loadu_ps(&B[j]);
            __m256 c = _mm256_loadu_ps(&C[i * size + j]);
            c = _mm256_fmadd_ps(a, b, c);
            _mm256_storeu_ps(&C[i * size + j], c);
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

	// Perform matrix multiplication using AVX instructions
        matrix_multiply_avx(A, B, C, SIZE);
    }

    return 0;
}
