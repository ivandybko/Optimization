
#ifndef QUASI_NEWTON_METHODS_H
#define QUASI_NEWTON_METHODS_H
#include <iomanip>
#include <functional>
#include <fstream>
#include "../Lab 4 (Newton's Method)/Gauss.h"
#include "../Lab 4 (Newton's Method)/newton_method.h"
#include "../matrix_operations.h"
#include "../Lab 1 (One-dimensional optimization)/golden_section_search.h"
#include "../Lab 2 (Gradient Descent)/steepest_descent.h"

// std::string test_name;

enum class QNMethod { DFP, BFS, powells };
template <typename T>
std::pair<std::vector<T>, T> quasi_newton_method(
    const std::function<T(const std::vector<T>&)> &func,
    std::vector<T> initial_point, QNMethod method_type,
    T tolerance = 1e-6, bool steepest_descent = false)
{
    std::ofstream outFile;
    std::string method;
    if (method_type == QNMethod::DFP) {
        method = "_DFP";
    }
    else if (method_type == QNMethod::BFS) {
        method = "_BFS";
    }
    else if (method_type == QNMethod::powells) {
        method = "_POWELL";
    }

    if (tolerance < 1e-4) {
        outFile.open("/Users/ivandybko/Projects/Optimization/Lab 5 (Quasi-Newton methods)/data/"+test_name+"_"+std::to_string(static_cast<int>(initial_point[0]))+"_"+std::to_string(static_cast<int>(initial_point[1]))+"_5"+method+".txt");
    }
    else {
        outFile.open("/Users/ivandybko/Projects/Optimization/Lab 5 (Quasi-Newton methods)/data/"+test_name+"_"+std::to_string(static_cast<int>(initial_point[0]))+"_"+std::to_string(static_cast<int>(initial_point[1]))+"_2"+method+".txt");
    }

    T epsilon = 1e-8;
    int iteration_count{0};
    int gradient_count{0};
    func_call_count = 0;

    outFile << std::setprecision(16) << initial_point[0] << " " << initial_point[1] << " " << func(initial_point) << std::endl;

    std::vector<std::vector<T>> A = identityMatrix<T>(initial_point.size());
    auto grad = gradient(func, initial_point, epsilon);
    gradient_count++;
    for (int i = 0; i < grad.size(); i++)
    {
        grad[i] = - grad[i];
    }
    T kappa{1};
    T left = 0.0;
    T right = 17.0;

    std::vector<T> prev_point;
    std::vector<T> prev_grad;

    while (compute2Norm(grad) > tolerance) {
        // std::cout << compute2Norm(grad) << std::endl;
        std::vector<T> delta = A * grad;
        auto phi = [=, &initial_point, &delta, &func](T kappa) -> T {
            std::vector<T> temp = initial_point + delta * kappa;
            func_call_count++;
            return func(temp);
        };

        kappa = golden_section_search<T>(phi, left, right, tolerance/10.0, false).first;

        prev_point = initial_point;
        prev_grad = grad;

        initial_point = initial_point + kappa * delta;
        grad = gradient(func, initial_point, epsilon);
        gradient_count++;
        for (int i = 0; i < grad.size(); i++)
        {
            grad[i] = - grad[i];
        }
        std::vector<T> delta_x = initial_point - prev_point;
        std::vector<T> delta_grad = grad-prev_grad;

        if (method_type == QNMethod::DFP) {
            auto term1 = (delta_x ^ delta_x) / (delta_grad * delta_x);
            auto temp = A * delta_grad;
            auto term2 = (temp ^ temp ) / (temp * delta_grad );
            A = A - term1 - term2;
        }

        else if (method_type == QNMethod::BFS) {
            T denominator = delta_grad * delta_x;
            if (std::abs(denominator) > epsilon) {
                std::vector<T> r_k = (A * delta_grad) * (1.0/((A * delta_grad) * delta_grad)) - delta_x * (1.0 / (delta_grad * delta_x));
                auto term1 = (delta_x ^ delta_x) / (delta_grad * delta_x);
                auto temp = A * delta_grad;
                auto term2 = (temp ^ temp ) / (temp * delta_grad );
                auto term3 = (temp * delta_grad ) * r_k ^ r_k;
                A = A - term1 - term2 + term3;
            }
        }
        else if (method_type == QNMethod::powells) {
            std::vector<T> delta_tilde = delta_x + A * delta_grad;
            auto term = (delta_tilde ^ delta_tilde) / (delta_grad * delta_tilde);
            A = A - term;
        }
        while (!steepest_descent and A[0][0]*A[1][1] - A[0][1]*A[1][0] <= 0)
        {
            for (int i = 0; i < grad.size(); i++)
            {
                A[i][i] += 2;
            }
        };
        iteration_count++;
        outFile << std::setprecision(16) << initial_point[0] << " " << initial_point[1] << " " << func(initial_point) << std::endl;
    }

    func_call_count++;
    std::cout << iteration_count << " & " << func_call_count << " & " << gradient_count << " & ("
              << std::setprecision(-log10(tolerance)) << initial_point[0] << ", "
              << std::round(initial_point[1]/tolerance)*tolerance << ") & "
              << std::round(func(initial_point)/tolerance)*tolerance << std::endl;

    outFile.close();
    return { initial_point, func(initial_point) };
}
#endif //QUASI_NEWTON_METHODS_H
