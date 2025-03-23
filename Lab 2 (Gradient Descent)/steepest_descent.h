//
// Created by Ivan Dybko on 27.02.25.
//

#ifndef STEEPEST_DESCENT_H
#define STEEPEST_DESCENT_H
#include <functional>
#include <vector>
#include <fstream>
#include "../matrix_operations.h"
#include "../Lab 1 (One-dimensional optimization)/golden_section_search.h"

int func_call_count{0};

template <typename T>
std::vector<T> gradient(const std::function<T(const std::vector<T> &)> &func, const std::vector<T> &point, T h = 1e-12){
	std::vector<T> grad(point.size());
	for (size_t i = 0; i < point.size(); ++i){
		std::vector<T> point_forward = point;
		std::vector<T> point_backward = point;
		point_forward[i] += h;
		point_backward[i] -= h;
		grad[i] = (func(point_forward) - func(point_backward)) / (2 * h);
		func_call_count+=2;
	}
	return grad;
}

template <typename T>
std::pair<std::vector<T>, T> steepest_descent(const std::function<T(const std::vector<T> &)> &func, std::vector<T> initial_point, T tolerance = 1e-6, int max_iter = 1000, bool show_iterations=false) {
	T alpha{1};
	func_call_count = 0;
	int iteration_count{0};
	int gradient_count{0};
	std::ofstream outFile("/Users/ivandybko/Projects/Optimization/Lab 2 (Gradient Descent)/data/func1/sd_0_0_2.txt");
	outFile << std::setprecision(16) <<  initial_point[0] << " " << initial_point[1] << " " << func(initial_point) << std::endl;
	for (int iter = 0; iter < max_iter; ++iter){
		auto grad = gradient(func, initial_point, tolerance);
		gradient_count++;
		T grad_norm = compute2Norm(grad);
		if (grad_norm < tolerance) {break;}
		auto alpha_function = [&grad, &initial_point, &func](const T alpha) {
			func_call_count++;
			return func(initial_point - alpha*grad);
		};
		alpha = golden_section_search<T>(alpha_function, -3, 3, 1e-10).first;
		for (size_t i = 0; i < initial_point.size(); ++i){
			// if (alpha < tolerance/10){alpha = tolerance/10;}
			initial_point[i] -= alpha * grad[i];
		}
		iteration_count++;
		outFile << std::setprecision(16) <<  initial_point[0] << " " << initial_point[1] << " " << func(initial_point) << std::endl;
	}
	func_call_count++;
	if (show_iterations){
		std::cout << "Convergence after " << iteration_count << " iterations, "  << func_call_count << " function and " << gradient_count << " gradient calculations"<<  std::endl;
	}
	outFile.close();
	return {initial_point, func(initial_point)};
}
#endif //STEEPEST_DESCENT_H
