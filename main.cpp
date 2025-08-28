#include <iostream>
#include <vector>

// 声明simulate.cpp中的函数
std::vector<double> run_metropolis(int steps);
double run_normalization_monte_carlo(int steps);

// 声明plot.cpp中的函数
void plot_results(const std::vector<double>& results);

int main() {
    int steps = 10000000;
    
    std::cout << "Starting simulation with " << steps << " steps..." << std::endl;
    std::cout << "---------------------------------------" << std::endl;
    
    // 步骤1: 使用 Metropolis 算法计算期望值
    std::cout << "Step 1: Calculating the expectation value E_p[x^2] using Metropolis..." << std::endl;
    std::vector<double> metropolis_results = run_metropolis(steps);
    double metropolis_expectation = metropolis_results.back();
    std::cout << "Metropolis result (E_p[x^2]): " << metropolis_expectation << std::endl;

    std::cout << "---------------------------------------" << std::endl;

    // 步骤2: 使用标准蒙特卡洛计算归一化常数
    std::cout << "Step 2: Calculating the normalization constant using Monte Carlo..." << std::endl;
    double normalization_constant = run_normalization_monte_carlo(steps);
    std::cout << "Monte Carlo result for normalization constant: " << normalization_constant << std::endl;

    std::cout << "---------------------------------------" << std::endl;

    // 步骤3: 将两个结果相乘得到最终积分值
    double final_integral = metropolis_expectation * normalization_constant;
    std::cout << "Final Integral Value: " << final_integral << std::endl;
    std::cout << "---------------------------------------" << std::endl;

    // 绘制 Metropolis 算法的结果
    plot_results(metropolis_results);

    return 0;
}