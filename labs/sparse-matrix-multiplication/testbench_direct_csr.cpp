#include <iostream>
#include <cmath>

#define N 4

extern void csr_mm(const float x[N], float y[N]);

bool is_close(float a, float b, float tol = 1e-3f) {
    return std::fabs(a - b) < tol;
}

int main() {
    float x[N]        = {1, 2, 3, 4};
    float y[N]        = {0};
    float expected[N] = {7, 0, 22, 5};

    csr_mm(x, y);

    bool pass = true;
    for (int i = 0; i < N; ++i) {
        std::cout << "y[" << i << "]=" << y[i]
                  << " expected=" << expected[i] << std::endl;
        if (!is_close(y[i], expected[i])) pass = false;
    }
    std::cout << (pass ? "TEST PASSED\n" : "TEST FAILED\n");
    return pass ? 0 : 1;
}
