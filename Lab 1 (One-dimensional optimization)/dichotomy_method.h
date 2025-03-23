//
// Created by Ivan Dybko on 20.02.25.
//

#ifndef DICHOTOMY_METHOD_H
#define DICHOTOMY_METHOD_H
#include <fstream>
template <typename T>
std::pair<T,T> dichotomy_method(std::function<T(T)> func, T left, T right, T delta, T tol, bool show_iterations = false)
{
	std::ofstream outFile("/Users/ivandybko/Projects/Optimization/Lab 1 (One-dimensional optimization)/data/dichotomy_method_17.txt");
	T x_1{0};
	T x_2{0};
	T f_1{0};
	T f_2{0};
	T iteration_count{0};
	T func_call_count{0};
	outFile << std::setprecision(20) << left << " " << right << '\n';
	while((right - left) > tol){
		x_1 = (left + right) / 2 - delta;
		x_2 = (left + right) / 2 + delta;
		f_1 = func(x_1);
		func_call_count++;
		f_2 = func(x_2);
		func_call_count++;
		if(f_1 < f_2){
			right=x_2;
		}
		else{
			left=x_1;
		}
		// {
		// 	throw std::invalid_argument("The delta was selected incorrectly");
		// }
		iteration_count++;
		outFile << std::setprecision(20) << x_1 << " " << x_2 << '\n';
	}
	if (show_iterations){
		std::cout << "Convergence after " << iteration_count << " iterations and " << func_call_count << " function calculations" <<  std::endl;
	}
	outFile.close();
	return {(left + right) / 2,func((left + right) / 2)};
}
#endif //DICHOTOMY_METHOD_H
