#ifndef NEWTON_METHOD_H
#define NEWTON_METHOD_H
#include <iomanip>
#include <functional>
#include <fstream>
#include "Gauss.h"
#include "../matrix_operations.h"
#include "../Lab 1 (One-dimensional optimization)/golden_section_search.h"
#include "../Lab 2 (Gradient Descent)/steepest_descent.h"
#include "/Users/ivandybko/Projects/Numerical_methods/Linear algebra/Lab4 (Solving the eigenvalue problem)/src/FrancisKublanovskayaQR.h"
// #include "main.cpp"
std::string test_name;
template <typename T>
std::vector<std::vector<T>> hessian(const std::function<T(const std::vector<T>&)>& func,
                 const std::vector<T>& x,
                 T eps = 1e-6)
{
    size_t n = x.size();
    std::vector<std::vector<T>> H(n, std::vector<T>(n));

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            // Численное вычисление второй производной
            std::vector<T> x_plus_eps_i = x;
            x_plus_eps_i[i] += eps;

            std::vector<T> x_plus_eps_j = x;
            x_plus_eps_j[j] += eps;

            std::vector<T> x_plus_eps_ij = x;
            x_plus_eps_ij[i] += eps;
            x_plus_eps_ij[j] += eps;

            H[i][j] = (func(x_plus_eps_ij) - func(x_plus_eps_i) -
                      func(x_plus_eps_j) + func(x)) / (eps * eps);
            func_call_count+=4;
        }
    }
    return H;
}

template <typename T>
std::pair<std::vector<T>, T> newton_method(
    const std::function<T(const std::vector<T>&)> &func,
    std::vector<T> initial_point,
    T tolerance = 1e-6, bool steepest_descent = false)
{
    std::ofstream outFile;
    std::string method;
    if (steepest_descent)
    {
        method = "_steepest_descent";
    }
    if (tolerance < 1e-4)
    {
        outFile.open("/Users/ivandybko/Projects/Optimization/Lab 4 (Newton's Method)/data/"+test_name+"_"+std::to_string(static_cast<int>(initial_point[0]))+"_"+std::to_string(static_cast<int>(initial_point[1]))+"_5"+method+".txt");
    }
    else
    {
        outFile.open("/Users/ivandybko/Projects/Optimization/Lab 4 (Newton's Method)/data/"+test_name+"_"+std::to_string(static_cast<int>(initial_point[0]))+"_"+std::to_string(static_cast<int>(initial_point[1]))+"_2"+method+".txt");
    }
    T epsilon = 1e-6;
    int iteration_count{0}; int gradient_count{0};
    func_call_count = 0;
    outFile << std::setprecision(16) <<  initial_point[0] << " " << initial_point[1] << " " << func(initial_point) << std::endl;
    auto H = hessian(func, initial_point, epsilon);
    auto grad = gradient(func, initial_point, epsilon);
    while (!steepest_descent and H[0][0]*H[1][1] - H[0][1]*H[1][0] <= 0)
    {
        for (int i = 0; i < grad.size(); i++)
        {
            H[i][i] += 4;
        }
    };
    gradient_count++;
    T kappa{1};
    T left = 0.0;
    T right = 10.0;
    while (compute2Norm(grad) > tolerance) {
        for (int i = 0; i < grad.size(); i++)
        {
            grad[i] = - grad[i];
        }
        auto delta = Gauss<T>(std::pair<std::vector<std::vector<T>>, std::vector<T>>(H , grad));
        if (steepest_descent)
        {
            auto phi = [=, &initial_point, &grad, &func](T kappa) -> T {
                std::vector<T> temp(initial_point.size());
                for (size_t i = 0; i < initial_point.size(); i++) {
                    temp[i] = initial_point[i] + kappa * delta[i];
                }
                func_call_count++;
                return func(temp);
            };
            kappa = golden_section_search<T>(phi, left, right, tolerance/10, false).first;
        }
        initial_point = initial_point + kappa * delta;
        H = hessian(func, initial_point, epsilon);
        while (!steepest_descent and H[0][0]*H[1][1] - H[0][1]*H[1][0] <= 0)
        {
            for (int i = 0; i < grad.size(); i++)
            {
                H[i][i] += 4;
            }
        };
        grad = gradient(func, initial_point, epsilon);
        gradient_count++;
        iteration_count++;
        outFile << std::setprecision(16) <<  initial_point[0] << " " << initial_point[1] << " " << func(initial_point) << std::endl;
    }
    func_call_count++;
    std::cout  << iteration_count << " & "  << func_call_count << " & " << gradient_count <<  " & (" << std::setprecision(-log10(tolerance)) << initial_point[0] << ", " << std::round(initial_point[1]/tolerance)*tolerance << ") & " <<  std::round(func(initial_point)/tolerance)*tolerance << std::endl;
    outFile.close();
    return { initial_point, func(initial_point) };
}
#endif //NEWTON_METHOD_H
