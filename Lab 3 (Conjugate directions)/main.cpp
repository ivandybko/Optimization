#include <iostream>

#include "conjugate_gradient.h"
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
	auto initial_point = {0.0, .0};

	std::cout <<"conjugate_gradient\n";
	auto min = conjugate_gradient<double>(test_func,initial_point, CGMethod::conjugate_gradient,false, 1e-2);
	std::cout << std::setprecision(6) << "Minimum " << min.second << " at " << std::setprecision(4) << min.first << '\n' << '\n';

	min = conjugate_gradient<double>(test_func,initial_point, CGMethod::conjugate_gradient, false,1e-5);
	std::cout << std::setprecision(6) << "Minimum " << min.second << " at " << std::setprecision(4) << min.first << '\n' << '\n';

	std::cout <<"fletcher_reeves\n";
	min = conjugate_gradient<double>(test_func,initial_point, CGMethod::fletcher_reeves,false, 1e-2);
	std::cout << std::setprecision(6) << "Minimum " << min.second << " at " << std::setprecision(4) << min.first << '\n' << '\n';

	min = conjugate_gradient<double>(test_func,initial_point, CGMethod::fletcher_reeves,false, 1e-5);
	std::cout << std::setprecision(6) << "Minimum " << min.second << " at " << std::setprecision(4) << min.first << '\n' << '\n';

	std::cout <<"polak_ribiere\n";
	min = conjugate_gradient<double>(test_func,initial_point, CGMethod::polak_ribiere, false,1e-2);
	std::cout << std::setprecision(6) << "Minimum " << min.second << " at " << std::setprecision(4) << min.first << '\n' << '\n';

	min = conjugate_gradient<double>(test_func,initial_point, CGMethod::polak_ribiere, false,1e-5);
	std::cout << std::setprecision(6) << "Minimum " << min.second << " at " << std::setprecision(4) << min.first << '\n' << '\n';

	return 0;
}
