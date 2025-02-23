#include <iostream>
#include <cmath>
#include <functional>
#include <iomanip>

#include "dichotomy_method.h"
#include "golden_section_search.h"

int main()
{
	std::function<double(double)> test1 = [](double x) {
		return std::asin((25 * std::pow(x, 2) - 30 * x + 9) / 20) + std::cos((10 * std::pow(x, 3) + 185 * std::pow(x, 2) + 340 * x + 103) /
							  (50 * std::pow(x, 2) + 100 * x + 30)) + 0.5;
	};
	auto min_d_1 = dichotomy_method<double>(test1, 0.0, 1.0, 1e-3,1e-2, true);
	std::cout << "Dichotomy method: (x=" << min_d_1.first << ", f(x)=" << min_d_1.second << ")" <<  '\n';
	auto min_g_1 = golden_section_search<double>(test1, 0.0, 1.0,1e-2, true);
	std::cout << "Golden section search: (x=" << min_g_1.first << ", f(x)=" << min_g_1.second << ")" <<  '\n' <<  '\n';
	auto min_d_2 = dichotomy_method<double>(test1, 0.0, 1.0, 1e-9,1e-8, true);
	std::cout << "Dichotomy method: (x=" << std::setprecision(8) << min_d_2.first << ", f(x)=" << min_d_2.second << ")" <<  '\n';
	auto min_g_2 = golden_section_search<double>(test1, 0.0, 1.0,1e-8, true);
	std::cout << "Golden section search: (x=" << min_g_2.first << ", f(x)=" << min_g_2.second << ")" <<  '\n' <<  '\n';
	auto min_d_3 = dichotomy_method<double>(test1, 0.0, 1.0, 1e-18,1e-17, true);
	std::cout << "Dichotomy method: (x=" << min_d_3.first << ", f(x)=" << min_d_3.second << ")" <<  '\n';
	auto min_g_3 = golden_section_search<double>(test1, 0.0, 1.0,1e-17, true);
	std::cout << "Golden section search: (x=" << min_g_3.first << ", f(x)=" << min_g_3.second << ")" <<  '\n' <<  '\n';
	return 0;
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.