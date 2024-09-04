CC = g++
CFLAGS = -std=c++17 -g -march=native

all: matmul_avx matmul_avx2 matmul_normal

matmul_avx: avx_matmul.cpp
	$(CC) $(CFLAGS) -mavx avx_matmul.cpp -o matmul_avx

matmul_avx2: avx2_matmul.cpp
	$(CC) $(CFLAGS) -mavx2 avx2_matmul.cpp -o matmul_avx2

matmul_normal: normal_matmul.cpp
	$(CC) $(CFLAGS) normal_matmul.cpp -o matmul_normal

clean:
	rm -f matmul_*
