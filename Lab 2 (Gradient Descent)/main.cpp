#include <iomanip>
#include <iostream>

#include "gradient_descent_step_split.h"
#include "steepest_descent.h"
#include "../matrix_operations.h"
// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main()
{
	std::function<double(const std::vector<double>&)> const func = [](const std::vector<double>& point) {
		double x = point[0];
		double y = point[1];
		return 5 * x * x - 4 * x * y + 8 * y * y + 8 * std::sqrt(7) * (2 * x + y) - 44;
	};

	std::function<double(const std::vector<double>&)> const rosenbrock = [](const std::vector<double>& point) {
		double x = point[0];
		double y = point[1];
		double alpha = 11;
		return alpha * (x * x - y) * (x * x - y) + (x - 1) * (x - 1);
	};
	std::cout << "eps=1e-2\n";
	auto func_sd_0_0_2 = steepest_descent<double>(rosenbrock,{5.0, 5.0}, 1e-5, 1000, true);
	std::cout << std::setprecision(6) << "Minimum " << func_sd_0_0_2.second << " at " << std::setprecision(4) << func_sd_0_0_2.first << '\n' << '\n';
	auto func_gd_0_0_2 = gradient_descent_step_split<double>(func,{-12.0, 10.0}, 1e-5, 0.5, 0.1, 1000, true);
	std::cout << std::setprecision(6) << "Minimum " << func_gd_0_0_2.second << " at " << std::setprecision(4) << func_gd_0_0_2.first << '\n' << '\n';

	// std::cout << "eps=1e-5\n";
	// func_sd_0_0_2 = steepest_descent<double>(func,{0.0, 0.0}, 1e-5, 30000, true);
	// std::cout << std::setprecision(6) << "Minimum " << func_sd_0_0_2.second << " at " << std::setprecision(6) << func_sd_0_0_2.first << '\n' << '\n';
	// func_gd_0_0_2 = gradient_descent_step_split<double>(func,{-12.0, 4.0}, 1e-5, 0.5, 0.1, 20000, true);
	// std::cout << std::setprecision(6) << "Minimum " << func_gd_0_0_2.second << " at " << std::setprecision(6) << func_gd_0_0_2.first << '\n';
	//
	//

	// auto func_100_1000_2 = steepest_descent<double>(func,{100,100}, 1e-5, 1000, true);
	// std::cout << std::setprecision(6) << "Minimum " << func_100_1000_2.second << " at " << std::setprecision(6) << func_100_1000_2.first << '\n';
	// auto rosenbrock_0_0_2 = steepest_descent<double>(rosenbrock,{0,0}, 1e-5, 1000, true);
	// std::cout << std::setprecision(6) << "Minimum " << rosenbrock_0_0_2.second << " at " << std::setprecision(6) << rosenbrock_0_0_2.first << '\n';
	// auto rosenbrock_20_20_2 = steepest_descent<double>(rosenbrock,{1.1,1.1}, 1e-5, 1000, true);
	// std::cout << std::setprecision(6) << "Minimum " << rosenbrock_20_20_2.second << " at " << std::setprecision(6) << rosenbrock_20_20_2.first << '\n';
	// return 0;
}

