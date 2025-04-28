#include <iostream>

#include "quasi_newton_methods.h"
// #include "newton_method_with_steepest_descent.h"
#include "../matrix_operations.h"

int main()
{
	std::function<double(const std::vector<double>&)> const func = [](const std::vector<double>& point) {
		double x = point[0];
		double y = point[1];
		return 5 * x * x - 4 * x * y + 8 * y * y + 8 * std::sqrt(7) * (2 * x + y) - 44;
	};

	std::function<double(const std::vector<double>&)> const func2 = [](const std::vector<double>& point) {
		double x = point[0];
		double y = point[1];
		return 5 * x * x + 4 * x * y + 2 * y * y + 4 * std::sqrt(5) * (x + y) + 51;
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
	std::cout << "DFP eps=1e-2" << std::endl;
	auto min =	quasi_newton_method<double>(test_func,initial_point, QNMethod::DFP, 1e-2);
	std::cout << std::setprecision(6) << "Minimum " << min.second << " at " << std::setprecision(4) << min.first << '\n' << '\n';

	std::cout << "DFP eps=1e-5" << std::endl;
	min = quasi_newton_method<double>(test_func,initial_point, QNMethod::DFP, 1e-5);
	std::cout << std::setprecision(6) << "Minimum " << min.second << " at " << std::setprecision(4) << min.first << '\n' << '\n';

	std::cout << "BFS eps=1e-2" << std::endl;
	min =	quasi_newton_method<double>(test_func,initial_point, QNMethod::BFS, 1e-2);
	std::cout << std::setprecision(6) << "Minimum " << min.second << " at " << std::setprecision(4) << min.first << '\n' << '\n';

	std::cout << "BFS eps=1e-5" << std::endl;
	min = quasi_newton_method<double>(test_func,initial_point, QNMethod::BFS, 1e-5);
	std::cout << std::setprecision(6) << "Minimum " << min.second << " at " << std::setprecision(4) << min.first << '\n' << '\n';

	std::cout << "POWWEL eps=1e-2" << std::endl;
	min =	quasi_newton_method<double>(test_func,initial_point, QNMethod::powells, 1e-2);
	std::cout << std::setprecision(6) << "Minimum " << min.second << " at " << std::setprecision(4) << min.first << '\n' << '\n';

	std::cout << "POWWEL eps=1e-5" << std::endl;

	min = quasi_newton_method<double>(test_func,initial_point, QNMethod::powells, 1e-5);
	std::cout << std::setprecision(6) << "Minimum " << min.second << " at " << std::setprecision(4) << min.first << '\n' << '\n';

	return 0;
}