#ifndef GOLDEN_SECTION_SEARCH_H
#define GOLDEN_SECTION_SEARCH_H

#include <cmath>
template <typename T>
std::pair<T,T> golden_section_search(std::function<T(T)> func, T left, T right, T tol, bool show_iterations=false)
{
	T ratio = (1 + std::sqrt(5)) / 2;
	T x_1 = right - ((right - left) / ratio);
	T x_2 = left + ((right - left) / ratio);
	T f_1 = func(x_1);
	T f_2 = func(x_2);
	T iteration_count = 1;
	while((right - left) > tol){
		if (f_1 < f_2){
			right=x_2;
			x_2 = x_1;
			f_2 = f_1;
			x_1 = left+right-x_2;
			f_1 = func(x_1);
		}
		else{
			left=x_1;
			x_1 = x_2;
			f_1 = f_2;
			x_2 = left+right-x_1;
			f_2 = func(x_2);
		}
		iteration_count++;
	}
	if (show_iterations){
		std::cout << "Convergence after " << iteration_count << " iterations " << 1+iteration_count << " function calculations" <<  std::endl;
	}
	return {(left + right) / 2,func((left + right) / 2)};
}
#endif //GOLDEN_SECTION_SEARCH_H
