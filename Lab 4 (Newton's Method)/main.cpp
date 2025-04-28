#include <iostream>

#include "newton_method.h"
// #include "newton_method_with_steepest_descent.h"
#include "../matrix_operations.h"

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
	auto initial_point = {-2.0, 3.0};

	test_name = "r11";
	std::cout << test_name << std::endl;
	auto min = newton_method<double>(test_func,initial_point, 1e-2);
	std::cout << std::setprecision(6) << "Minimum " << min.second << " at " << std::setprecision(4) << min.first << '\n' << '\n';

	// min = newton_method<double>(test_func,initial_point, 1e-5);
	// std::cout << std::setprecision(6) << "Minimum " << min.second << " at " << std::setprecision(4) << min.first << '\n' << '\n';


	min = newton_method<double>(test_func,initial_point, 1e-2, true);
	std::cout << std::setprecision(6) << "Minimum " << min.second << " at " << std::setprecision(4) << min.first << '\n' << '\n';

	// min = newton_method<double>(test_func,initial_point, 1e-5, true);
	// std::cout << std::setprecision(6) << "Minimum " << min.second << " at " << std::setprecision(4) << min.first << '\n' << '\n';

	return 0;
}