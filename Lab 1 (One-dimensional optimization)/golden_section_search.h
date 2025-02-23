#ifndef GOLDEN_SECTION_SEARCH_H
#define GOLDEN_SECTION_SEARCH_H

#include <cmath>
template <typename T>
std::pair<T,T> golden_section_search(std::function<T(T)> func, T left, T right, T tol, bool show_iterations=false)
{
	T ratio=(1+std::sqrt(5))/2, x1 = b-(b-a)/ratio, x2=a+(b-a)/ratio, f_1=f(x1), f_2=f(x2), iter=1;;
	while((b-a) > tol)
	{
		if (f_1 < f_2)
		{
			b=x2;
			x2 = x1;
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
		outFile << left << " " << right << std::endl;
	}
	if (show_iterations){
		std::cout << "Convergence after " << iteration_count << " iterations " << 1+iteration_count << " function calculations" <<  std::endl;
	}
	return std::make_pair((a+b)/2,f((a+b)/2));
}
#endif //GOLDEN_SECTION_SEARCH_H
