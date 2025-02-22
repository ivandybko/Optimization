#ifndef GOLDEN_SECTION_SEARCH_H
#define GOLDEN_SECTION_SEARCH_H
template <typename T>
std::pair<T,T> golden_secion_search(std::function<T(T)> f, T a, T b, T tol = 1e-10, bool iterations=false)
{
	T ratio=(1+std::sqrt(5))/2, x1 = b-(b-a)/ratio, x2=a+(b-a)/ratio, f_1=f(x1), f_2=f(x2), iter=1;;
	while((b-a) > tol)
	{
		if (f_1 < f_2)
		{
			b=x2;
			x2 = x1;
			f_2 = f_1;
			x1=a+b-x2;
			f_1=f(x1);
		}
		else
		{
			a=x1;
			x1 = x2;
			f_1 = f_2;
			x2=a+b-x1;
			f_2=f(x2);
		}
		iter++;
	}
	if (iterations)
	{
		std::cout << "Convergence after " << iter << " iterations " << 1+iter << " function calculations" <<  std::endl;
	}
	return std::make_pair((a+b)/2,f((a+b)/2));
}
#endif //GOLDEN_SECTION_SEARCH_H
