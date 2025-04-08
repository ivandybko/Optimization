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
	auto test_func = rosenbrock;
	auto initial_point = {0.0, 0.0};
	std::cout << "SD\n";
	auto func_sd_0_0_2 = steepest_descent<double>(test_func,initial_point, 1e-2, 10000, true);
	std::cout << std::setprecision(6) << "Minimum " << func_sd_0_0_2.second << " at " << std::setprecision(6) << func_sd_0_0_2.first << '\n' << '\n';
	func_sd_0_0_2 = steepest_descent<double>(test_func,initial_point, 1e-5, 30000, true);
	std::cout << std::setprecision(6) << "Minimum " << func_sd_0_0_2.second << " at " << std::setprecision(6) << func_sd_0_0_2.first << '\n' << '\n';

	std::cout << "GD\n";
	auto func_gd_0_0_2 = gradient_descent_step_split<double>(test_func,initial_point, 1e-2, 0.5, 0.1, 10000, true);
	std::cout << std::setprecision(6) << "Minimum " << func_gd_0_0_2.second << " at " << std::setprecision(4) << func_gd_0_0_2.first << '\n' << '\n';
	func_gd_0_0_2 = gradient_descent_step_split<double>(test_func,initial_point, 1e-5, 0.5, 0.1,20000, true);
	std::cout << std::setprecision(6) << "Minimum " << func_gd_0_0_2.second << " at " << std::setprecision(6) << func_gd_0_0_2.first << '\n';
	return 0;
}

