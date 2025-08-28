#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>

// 绘制结果
void plot_results(const std::vector<double>& results) {
    // 将数据写入一个临时文件
    std::ofstream dataFile("integral_data.txt");
    if (!dataFile.is_open()) {
        std::cerr << "Error: Unable to open file for writing data." << std::endl;
        return;
    }
    for (size_t i = 0; i < results.size(); ++i) {
        dataFile << i  << " " << results[i] << std::endl;
    }
    dataFile.close();

    // 创建一个 gnuplot 脚本文件
    std::ofstream scriptFile("plot_script.gp");
    if (!scriptFile.is_open()) {
        std::cerr << "Error: Unable to open file for creating gnuplot script." << std::endl;
        return;
    }
    scriptFile << "set terminal pngcairo\n";
    scriptFile << "set output 'integral_plot.png'\n";
    scriptFile << "set title 'Metropolis Expectation Value'\n";
    scriptFile << "set xlabel 'Number of Steps'\n";
    scriptFile << "set ylabel 'E_p[x^2]'\n";
    scriptFile << "plot 'integral_data.txt' with lines title 'Metropolis Result'\n";
    scriptFile.close();

    // 调用 gnuplot
    std::cout << "Plotting results... A file named 'integral_plot.png' will be created." << std::endl;
    std::string command = "gnuplot plot_script.gp";
    system(command.c_str());
    
    // 清理临时文件（可选）
    system("rm integral_data.txt plot_script.gp");
}