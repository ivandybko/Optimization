//
// Created by Ivan Dybko on 20.02.25.
//

#ifndef DICHOTOMY_METHOD_H
#define DICHOTOMY_METHOD_H
template <typename T>
std::pair<T,T> dichotomy_method(std::function<T(T)> f, T a, T b, T delta=5*1e-11, T tol = 1e-10, bool iterations=false)
{
	T interval = b-a; T x1, x2, f_1, f_2, iter=0;;
	while(interval > tol)
	{
		x1=(a+b)/2 - delta; x2=(a+b)/2 + delta;
		f_1=f(x1); f_2=f(x2);
		if(f_1 < f_2)
		{
			b=x2;
		}
		else
		{
			a=x1;
		}
		interval=b-a;
		iter++;
	}
	if (iterations)
	{
		std::cout << "Convergence after " << iter << " iterations" << std::endl;
	}
	return std::make_pair((a+b)/2,f((a+b)/2));
}
#endif //DICHOTOMY_METHOD_H
