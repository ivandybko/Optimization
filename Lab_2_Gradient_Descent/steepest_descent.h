//
// Created by Ivan Dybko on 27.02.25.
//

#ifndef STEEPEST_DESCENT_H
#define STEEPEST_DESCENT_H
#include <functional>
#include <vector>
#include "../matrix_operations.h"
#include "../Lab 1 (One-dimensional optimization)/golden_section_search.h"


template <typename T>
std::vector<T> gradient(const std::function<T(const std::vector<T> &)> &func, const std::vector<T> &point, T h = 1e-6){
	std::vector<T> grad(point.size());
	for (size_t i = 0; i < point.size(); ++i){
		std::vector<T> point_forward = point;
		std::vector<T> point_backward = point;
		point_forward[i] += h;
		point_backward[i] -= h;
		grad[i] = (func(point_forward) - func(point_backward)) / (2 * h);
	}
	return grad;
}

template <typename T>
std::pair<std::vector<T>, T> steepest_descent(const std::function<T(const std::vector<T> &)> &func, std::vector<T> initial_point, T tolerance = 1e-6, int max_iter = 1000, bool show_iterations=false) {
	T alpha;
	T iteration_count{0};
	for (int iter = 0; iter < max_iter; ++iter){
		auto grad = gradient(func, initial_point, tolerance);
		T grad_norm = compute2Norm(grad);
		if (grad_norm < tolerance) {break;}
		for (size_t i = 0; i < initial_point.size(); ++i){
			auto alpha_function = [&grad, &initial_point, &func](const T alpha) {
				return func(initial_point - alpha*grad);
			};
			alpha = golden_section_search<T>(alpha_function, -1, 1, tolerance).first;
			initial_point[i] -= alpha * grad[i];
		}
		iteration_count++;
	}
	if (show_iterations){
		std::cout << "Convergence after " << iteration_count << " iterations."<<  std::endl;
	}
	return {initial_point, func(initial_point)};
}
#endif //STEEPEST_DESCENT_H
