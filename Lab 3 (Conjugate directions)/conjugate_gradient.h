//
// Created by Ivan Dybko on 23.03.25.
//
#include <iostream>
#include <vector>
#include <cmath>
#include <functional>
#include "../Lab 1 (One-dimensional optimization)/golden_section_search.h"
#include "../Lab 2 (Gradient Descent)/steepest_descent.h"
#include "../matrix_operations.h"
#ifndef CONJUGATE_GRADIENT_H
#define CONJUGATE_GRADIENT_H

enum class CGMethod { conjugate_gradient, fletcher_reeves, polak_ribiere };

template <typename T>
std::pair<std::vector<T>, T> conjugate_gradient(
    const std::function<T(const std::vector<T>&)> &func,
    std::vector<T> initial_point, CGMethod method_type,bool restart,
    T tolerance = 1e-6)
{
    std::ofstream outFile;
    if (method_type == CGMethod::conjugate_gradient)
    {
        if (tolerance < 1e-4)
        {
            outFile.open("/Users/ivandybko/Projects/Optimization/Lab 3 (Conjugate directions)/data/cg5.txt");
        }
        else
        {
            outFile.open("/Users/ivandybko/Projects/Optimization/Lab 3 (Conjugate directions)/data/cg2.txt");
        }
    }
    if (method_type == CGMethod::fletcher_reeves)
    {
        if (tolerance < 1e-4)
        {
            outFile.open("/Users/ivandybko/Projects/Optimization/Lab 3 (Conjugate directions)/data/fr5.txt");
        }
        else
        {
            outFile.open("/Users/ivandybko/Projects/Optimization/Lab 3 (Conjugate directions)/data/fr2.txt");
        }
    }
    if (method_type == CGMethod::polak_ribiere)
    {
        if (tolerance < 1e-4)
        {
            outFile.open("/Users/ivandybko/Projects/Optimization/Lab 3 (Conjugate directions)/data/pr5.txt");
        }
        else
        {
            outFile.open("/Users/ivandybko/Projects/Optimization/Lab 3 (Conjugate directions)/data/pr2.txt");
        }
    }
    outFile << std::setprecision(16) <<  initial_point[0] << " " << initial_point[1] << " " << func(initial_point) << std::endl;
    T alpha{1.0};
    func_call_count = 0;
    int iteration_count = 0;
    int gradient_count = 0;

    T epsilon = 1e-8;
    std::vector<T> x = initial_point;
    std::vector<T> grad = gradient(func, x, epsilon);
    for (int i = 0; i < grad.size(); i++)
    {
        grad[i] = - grad[i];
    }
    gradient_count++;

    std::vector<T> d = grad;
    // for (size_t i = 0; i < grad.size(); i++) {
    //     d[i] = -grad[i];
    // }
    T gamma{};
    T right_max = 0;
    while (compute2Norm(grad) > tolerance) {
        // for (int i = 0; i < grad.size(); i++)
        // {
        //     grad[i] = - grad[i];
        // }
        auto phi = [=, &x, &d, &func](T alpha) -> T {
            std::vector<T> temp(x.size());
            for (size_t i = 0; i < x.size(); i++) {
                temp[i] = x[i] + alpha * d[i];
            }
            func_call_count++;
            return func(temp);
        };

        T left = 0.0;
        T right = 0.22;
        // right = 0.1;
        // while (phi(right) < phi(0)) right *= 1.001;  // Ищем подходящую верхнюю границу
        // if (right > right_max) right_max = right;


        auto search_result = golden_section_search<T>(phi, left, right, epsilon, false);
        alpha = search_result.first;


        std::vector<T> x_new(x.size());
        for (size_t i = 0; i < x.size(); i++) {
            x_new[i] = x[i] + alpha * d[i];
        }
        iteration_count++;

        std::vector<T> grad_new = gradient(func, x_new, epsilon);
        for (int i = 0; i < grad.size(); i++)
        {
            grad_new[i] = - grad_new[i];
        }
        gradient_count++;;
        if (method_type == CGMethod::fletcher_reeves)
        {
            gamma = (grad_new * grad_new) / (grad * grad);
        }
        else if (method_type == CGMethod::polak_ribiere)
        {
            std::vector<T> diff(grad.size());
            diff = grad_new - grad;
            gamma = (grad_new * diff) / (grad * grad);
        }
        else if (method_type == CGMethod::conjugate_gradient) {
            // T numerator = grad_new * grad_new;
            // T denominator = grad * d;
            //
            // if (denominator == 0) {
            //     gamma = 0;
            //
            // } else {
            gamma = (grad_new * grad_new) / (grad * d);
            // }
        }
        if (gamma < 0.01){std::cout << gamma << std::endl;}
        if (restart and iteration_count % 4 == 0){
            for (size_t i = 0; i < grad.size(); i++){
                d[i] = grad_new[i];
            }
        }
        else {
                // std::vector<T> d_new(grad.size());
            for (size_t i = 0; i < grad.size(); i++){
                d[i] = grad_new[i] + gamma * d[i];
            }
        }

        x = x_new;
        grad = grad_new;
        outFile << std::setprecision(16) <<  x[0] << " " << x[1] << " " << func(x ) << std::endl;
    }
    func_call_count++;
    std::cout << "Max step " << right_max << std::endl;
    // std::cout << "Convergence after " << iteration_count << " iterations, "  << func_call_count << " function and " << gradient_count << " gradient calculations"<<  std::endl;
    std::cout  << iteration_count << " & "  << func_call_count << " & " << gradient_count << std::endl;
    outFile.close();
    return { x, func(x) };
}

#endif //CONJUGATE_GRADIENT_H
