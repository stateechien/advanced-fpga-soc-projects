#include "cordic_2.h"
#include <iostream>
#include <cmath>
#include <cstdlib>

struct Rmse {
    int num_sq;
    double sum_sq;  // 使用 double 提高精度
    double error;

    Rmse() : num_sq(0), sum_sq(0), error(0) {}

    double add_value(double d_n) {  // 使用 double
        num_sq++;
        sum_sq += (d_n * d_n);
        error = sqrt(sum_sq / num_sq);
        return error;
    }
};

Rmse rmse_sin, rmse_cos;

void run_test(THETA_TYPE theta, COS_SIN_TYPE golden_sin, COS_SIN_TYPE golden_cos) {
    COS_SIN_TYPE s, c;
    cordic(theta, s, c);

    // 轉換 ap_fixed 為 double 來比較
    double sin_error = static_cast<double>(s) - static_cast<double>(golden_sin);
    double cos_error = static_cast<double>(c) - static_cast<double>(golden_cos);

    // 使用 printf 來確保格式與圖片一致
    printf("Test: theta=%.3f golden_sin=%.6f golden_cos=%.6f your_sin=%.6f your_cos=%.6f\n",
           static_cast<double>(theta),
           static_cast<double>(golden_sin),
           static_cast<double>(golden_cos),
           static_cast<double>(s),
           static_cast<double>(c));

        rmse_sin.add_value(sin_error);
        rmse_cos.add_value(cos_error);

//    std::cout << "Test: theta=" << theta
//              << " golden_sin=" << golden_sin
//              << " golden_cos=" << golden_cos
//              << " your_sin=" << s
//              << " your_cos=" << c
//              << std::endl;
//    //使用 double 進行計算並在最後轉換
//    rmse_sin.add_value(static_cast<double>(s) - static_cast<double>(golden_sin));
//    rmse_cos.add_value(static_cast<double>(c) - static_cast<double>(golden_cos));
}

int main() {
//    std::cout << "--- Testing CORDIC Algorithm ---\n";
	printf("--- Testing CORDIC Algorithm ---\n");

    double test_angles_degrees[] = {0.000, 0.262, 0.524, 0.785, 1.047, 1.571, -0.785};
//    int num_tests = sizeof(test_angles_degrees) / sizeof(THETA_TYPE);
    int num_tests = sizeof(test_angles_degrees) / sizeof(test_angles_degrees[0]);

    for (int i = 0; i < num_tests; i++) {
        // 使用 THETA_TYPE
        THETA_TYPE theta = test_angles_degrees[i];    // 直接進行轉換

//        COS_SIN_TYPE golden_sin = sin(static_cast<double>(theta));  // 先轉為 double
//        COS_SIN_TYPE golden_cos = cos(static_cast<double>(theta));
        // 先使用 double 計算正確值，再轉換為 ap_fixed 來比較
        double theta_double = static_cast<double>(theta);
        double golden_sin = sin(theta_double);
        double golden_cos = cos(theta_double);

        run_test(theta, static_cast<COS_SIN_TYPE>(golden_sin), static_cast<COS_SIN_TYPE>(golden_cos));
;
    }

//    std::cout << "RMSE(Sin): " << rmse_sin.error << "\n";
//    std::cout << "RMSE(Cos): " << rmse_cos.error << "\n";
    printf("RMSE(Sin): %.6f\n", rmse_sin.error);
    printf("RMSE(Cos): %.6f\n", rmse_cos.error);

    return (rmse_sin.error < 0.1 && rmse_cos.error < 0.1) ? 0 : 1;
}
