#include <iostream>
#include <cmath>
#include <functional>
#include "dichotomy_method.h"
#include "golden_section_search.h"
// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main()
{
	std::function<double(double)> test1 = [](double x) {
		double R1 = std::asin((35 * std::pow(x, 2) - 30 * x + 9) / 20);
		double R2 = std::cos((10 * std::pow(x, 3) + 185 * std::pow(x, 2) + 340 * x + 103) /
							  (50 * std::pow(x, 2) + 100 * x + 30));
		return R1 + R2 + 0.5;
	};
	auto min = dichotomy_method<double>(test1, 0.0, 1.0, 1e-7,1e-6, true);
	std::cout << "Dichotomy method: (x=" << min.first << ", f(x)=" << min.second << ")" <<  std::endl;
	return 0;
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.