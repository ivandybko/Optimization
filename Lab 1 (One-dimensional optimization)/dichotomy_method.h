//
// Created by Ivan Dybko on 20.02.25.
//

#ifndef DICHOTOMY_METHOD_H
#define DICHOTOMY_METHOD_H
#include <fstream>
template <typename T>
std::pair<T,T> dichotomy_method(std::function<T(T)> func, T left, T right, T delta, T tol, bool show_iterations = false)
{
	T x1, x2, f_1, f_2, iter=0;;
	while((b-a) > tol)
	{
		x1=(a+b)/2 - delta; x2=(a+b)/2 + delta;
		f_1=f(x1); f_2=f(x2);
		if(f_1 < f_2)
		{
			b=x2;
	T x_1{0};
	T x_2{0};
	T f_1{0};
	T f_2{0};
	T iteration_count{0};
	while((right - left) > tol){
		x_1 = (left + right) / 2 - delta;
		x_2 = (left + right) / 2 + delta;
		f_1 = func(x_1);
		f_2 = func(x_2);
		if(f_1 < f_2){
			right=x_2;
		}
		else{
			left=x_1;
		}
		iteration_count++;
		outFile << left << " " << right << std::endl;
	}
	if (show_iterations){
		std::cout << "Convergence after " << iteration_count << " iterations and " << 2*iteration_count << " function calculations" <<  std::endl;
	}
	return std::make_pair((a+b)/2,f((a+b)/2));
	return {(left + right) / 2,func((left + right) / 2)};
}
#endif //DICHOTOMY_METHOD_H
