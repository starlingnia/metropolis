#include <iostream>
#include <vector>
#include <cmath>
#include <random>

// 定义目标分布的非归一化函数：p(x) 正比于 exp(-x^2)
double target_distribution(double x) {
    return std::exp(-x * x);
}

// 使用 Metropolis 算法进行采样并计算期望值 E_p[x^2]
// 这里 p(x) ∝ exp(-x^2)
static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_real_distribution<> dis(0.0, 1.0);

std::vector<double> run_metropolis(int steps) {
    std::vector<double> results;
    results.reserve(steps);

    double current_x = dis(gen); // 在 [0, 1] 范围内随机初始化一个起点
    double integral_sum = 0.0;
    
    for (int i = 0; i < steps; ++i) {
        // 生成一个随机的提议状态 (proposal)
        double proposed_x = dis(gen);

        // 计算接受率 alpha = p(proposed_x) / p(current_x)
        double alpha = target_distribution(proposed_x) / target_distribution(current_x);
        
        // 接受或拒绝提议状态
        if (dis(gen) < alpha) {
            current_x = proposed_x;
        }
        
        // 累加函数 g(x) = x^2 的值
        integral_sum += current_x * current_x;
        
        // 记录当前步的平均值
        results.push_back(integral_sum / (i + 1.0));
    }
    return results;
}

// 使用标准蒙特卡洛积分计算归一化常数：int_0^1 exp(-x^2) dx
double run_normalization_monte_carlo(int steps) {
    double integral_sum = 0.0;
    
    for (int i = 0; i < steps; ++i) {
        // 在 [0, 1] 区间内均匀地生成随机数
        double random_x = dis(gen);
        
        // 累加函数值 exp(-x^2)
        integral_sum += target_distribution(random_x);
    }

    // 返回平均值
    return integral_sum / steps;
}