//
// Created by Ivan Dybko on 04.05.25.
//

#ifndef DIRECT_SEARCH_METHODS_H
#define DIRECT_SEARCH_METHODS_H

#include <iomanip>
#include <functional>
#include <fstream>
#include <cmath>
#include <cassert>
#include <map>

#include "../matrix_operations.h"
#include "../Lab 1 (One-dimensional optimization)/golden_section_search.h"

std::string test_name;

template <typename T>
std::pair<std::vector<T>, T> cyclic_coordinate_descent(
    const std::function<T(const std::vector<T>&)> &func,
    std::vector<T> initial_point,
    T tolerance = 1e-6){
    int func_call_count = 0;
    std::ofstream outFile;
    std::string method;
        method = "_CCD";
    if (tolerance < 1e-4) {
        outFile.open("/Users/ivandybko/Projects/Optimization/Lab 6 (Direct search methods)/data/" +
                     test_name + "_" + std::to_string(static_cast<int>(initial_point[0])) + "_" +
                     std::to_string(static_cast<int>(initial_point[1])) + "_5" + method + ".txt");
    } else {
        outFile.open("/Users/ivandybko/Projects/Optimization/Lab 6 (Direct search methods)/data/" +
                     test_name + "_" + std::to_string(static_cast<int>(initial_point[0])) + "_" +
                     std::to_string(static_cast<int>(initial_point[1])) + "_2" + method + ".txt");
    }

    int iteration_count{0};
    T kappa{1};
    T left = -10.0;
    T right = -left;

    std::vector<T> prev_point(initial_point.size(), INFINITY);
    std::vector<T> alpha(initial_point.size(), 0);

    outFile << std::setprecision(16) << initial_point[0] << " " << initial_point[1] << " " << func(initial_point) << std::endl;

    while (compute2Norm(prev_point - initial_point) > tolerance)
    {
        std::fill(alpha.begin(), alpha.end(), 0);
        std::function<T(T)> phi;
        T gamma{0};
        for (size_t i = 0; i < initial_point.size(); i++) {
            // if (method_type == Method::CCD) {
            int current_index = i;
            phi = [=, &initial_point, &func, &alpha, &func_call_count](T kappa) -> T {
                std::vector<T> temp = initial_point + alpha;
                temp[current_index] += kappa;
                func_call_count++;
                return func(temp);
            };
            // }

            alpha[i] = golden_section_search<T>(phi, left, right, 1e-6, false).first;
            outFile << std::setprecision(16) << initial_point[0] + alpha[0] << " " << initial_point[1] + alpha[1] << " " << func(initial_point) << std::endl;
        }

        prev_point = initial_point;
        initial_point = initial_point + alpha;
        iteration_count++;
        outFile << std::setprecision(16) << initial_point[0] << " " << initial_point[1] << " " << func(initial_point) << std::endl;
    }

    func_call_count++;
    std::cout << iteration_count << " & " << func_call_count << " & ("
              << std::setprecision(-log10(tolerance)) << initial_point[0] << ", "
              << std::round(initial_point[1] / tolerance) * tolerance << ") & "
              << std::round(func(initial_point) / tolerance) * tolerance << std::endl;

    outFile.close();
    return { initial_point, func(initial_point) };
}

template <typename T>
std::pair<std::vector<T>, T> RM(
    const std::function<T(const std::vector<T>&)> &func,
    std::vector<T> initial_point,
    T tolerance = 1e-6)
{
    int func_call_count = 0;
    std::ofstream outFile;
    std::string method;
    method = "_RM";


    if (tolerance < 1e-4) {
        outFile.open("/Users/ivandybko/Projects/Optimization/Lab 6 (Direct search methods)/data/" +
                     test_name + "_" + std::to_string(static_cast<int>(initial_point[0])) + "_" +
                     std::to_string(static_cast<int>(initial_point[1])) + "_5" + method + ".txt");
    } else {
        outFile.open("/Users/ivandybko/Projects/Optimization/Lab 6 (Direct search methods)/data/" +
                     test_name + "_" + std::to_string(static_cast<int>(initial_point[0])) + "_" +
                     std::to_string(static_cast<int>(initial_point[1])) + "_2" + method + ".txt");
    }

    int iteration_count{0};
    T kappa{1};
    T left = -10.0;
    T right = -left;

    std::vector<T> prev_point(initial_point.size(), INFINITY);
    std::vector<T> alpha(initial_point.size(), 0);

    std::vector<T> b(initial_point.size(), 0.5);
    T gamma_HJ = 0.5;

    std::vector<std::vector<T>> U;
    U.resize(initial_point.size(), std::vector<T>(initial_point.size(), 0));
    for (size_t i = 0; i < initial_point.size(); ++i) {
        U[i][i] = 1;
    }


    outFile << std::setprecision(16) << initial_point[0] << " " << initial_point[1] << " " << func(initial_point) << std::endl;

    T gamma{0};
    std::vector<T> x_k = initial_point;
    std::vector<std::vector<T>> p_k = U;
    bool converged = false;
    while (!converged)
    {
        std::vector<T> x_j_k = x_k;
        std::vector<T> alpha_k(p_k.size(), 0);
        for (size_t j = 0; j < p_k.size(); ++j) {
            auto psi = [&](T x) {
                std::vector<T> direction = p_k[j];
                std::vector<T> temp = x_j_k + (direction * x);
                func_call_count++;
                return func(temp);
            };

            T x_j = golden_section_search<T>(psi, left, right, tolerance/10.0, false).first;
            alpha_k[j] = x_j;
            x_j_k = x_j_k + (p_k[j] * x_j);

            outFile << std::setprecision(16) << x_j_k[0] << " " << x_j_k[1] << " " << func(x_j_k) << std::endl;
        }
        if (compute2Norm(x_j_k - x_k) < tolerance) {
            converged = true;
            initial_point = x_j_k;
            break;
        }
        std::vector<std::vector<T>> a_k(p_k.size());
        std::vector<std::vector<T>> p_k1(p_k.size());

        for (size_t j = 0; j < p_k.size(); ++j) {
            if (std::abs(alpha_k[j]) < tolerance) {
                a_k[j] = p_k[j];
            } else {
                a_k[j] = std::vector<T>(p_k[0].size(), 0);
                for (size_t i = j; i < p_k.size(); ++i) {
                    a_k[j] = a_k[j] + (p_k[i] * alpha_k[i]);
                }
            }
        }
        for (size_t j = 0; j < p_k.size(); ++j) {
            std::vector<T> b_j = a_k[j];
            if (j > 0) {
                for (size_t i = 0; i < j; ++i) {
                    T dot_product = b_j * p_k1[i];
                    b_j = b_j - (p_k1[i] * dot_product);
                }
            }
            T norm = compute2Norm(b_j);
            if (norm < tolerance) {
                p_k1[j] = p_k[j];
            } else {
                p_k1[j] = b_j * (1.0 / norm);
            }
        }

        p_k = p_k1;
        x_k = x_j_k;
        iteration_count++;
    }

    func_call_count++;
    std::cout << iteration_count << " & " << func_call_count << " & ("
              << std::setprecision(-log10(tolerance)) << initial_point[0] << ", "
              << std::round(initial_point[1] / tolerance) * tolerance << ") & "
              << std::round(func(initial_point) / tolerance) * tolerance << std::endl;

    outFile.close();
    return { initial_point, func(initial_point) };
}
#endif // DIRECT_SEARCH_METHODS_H
