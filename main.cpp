#include <iostream>
#include <cmath>
#include <omp.h>
#include <windows.h>

int N = 100000000;
double pi = 0;
int blockSize = 8301260;

int main(int argc, char* argv[]) {
    if (argc == 1) {
        std::cout << "Usage: " << argv[0] << " <thread amount>" << std::endl;
        return 0;
    }

    omp_set_num_threads(atoi(argv[1]));
    auto start = GetCurrentTime();

#pragma omp parallel for schedule(dynamic, blockSize) reduction(+:pi) default(none) shared(blockSize, N)
    for (int i = 0; i < N; i++) {
        pi += (4.0 / (1.0 + pow((i + 0.5) / N, 2.0))) / N ;
    }

    auto end = GetCurrentTime();

    std::cout << "Time: " << end - start << "(ms) Result: " << pi << std::endl;
    return 0;
}
