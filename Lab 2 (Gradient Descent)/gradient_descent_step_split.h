#ifndef GRADIENT_DESCENT_STEP_SPLIT_H
#define GRADIENT_DESCENT_STEP_SPLIT_H
#include <functional>
#include <vector>
#include <fstream>
#include "../matrix_operations.h"
#include "steepest_descent.h"

template <typename T>
std::pair<std::vector<T>, T> gradient_descent_step_split(const std::function<T(const std::vector<T> &)> &func, std::vector<T> initial_point, T tolerance = 1e-6, T gamma = 0.5, T omega = 1, int max_iter = 1000, bool show_iterations=false) {
	T alpha{1};
	int iteration_count{0};
	int gradient_count{0};
	func_call_count = 0;
	std::ofstream outFile("/Users/ivandybko/Projects/Optimization/Lab 2 (Gradient Descent)/data/func1/gd_0_0_2.txt");
	outFile << std::setprecision(16) <<  initial_point[0] << " " << initial_point[1] << " " << func(initial_point) << std::endl;
	auto prev = initial_point;
	for (int iter = 0; iter < max_iter; ++iter){
		auto grad = gradient(func, initial_point, tolerance);
		gradient_count++;
		T grad_norm = compute2Norm(grad);
		func_call_count+=2;
		initial_point = initial_point - alpha * grad;
		iteration_count++;
		// if (func(initial_point) > func(prev) - omega * alpha * grad_norm * grad_norm) { alpha *= gamma; }
		while (func(initial_point) > func(prev) - omega * alpha * grad_norm * grad_norm)
		{
			initial_point = prev;
			alpha *= gamma;
			initial_point = initial_point - alpha * grad;
			func_call_count+=2;
		}
		outFile << std::setprecision(16) <<  initial_point[0] << " " << initial_point[1] << " " << func(initial_point) << std::endl;
		if (compute2Norm(initial_point - prev ) < tolerance){break;}
		prev = initial_point;
	}
	func_call_count++;
	if (show_iterations){
		std::cout << "Convergence after " << iteration_count << " iterations, "  << func_call_count << " function and " << gradient_count << " gradient calculations"<<  std::endl;
	}
	outFile.close();
	return {initial_point, func(initial_point)};
}
#endif //GRADIENT_DESCENT_STEP_SPLIT_H
