# Optimization Methods: Lab Work 1–8

This repository contains implementations of various optimization methods that were studied and applied in Laboratory Works 1–8.

Two objective functions were considered in Laboratory Works 2–7:

The first function is a **quadratic** function defined as:
```math
		f(x) = 5x^2 - 4xy + 8y^2 + 8\sqrt{7} (2x + y) - 44.
```

The second function is the **Rosenbrock** function defined as:
```math
		f(x) = \alpha (x^2 - y)^2 + (x - 1)^2, \quad \text{with} \; \alpha=2 \;  \text{or} \; \alpha=11.
```
* The optimization algorithms were tested starting from the following initial points:

  * For the quadratic function: (0, 0) and (-12, 4)
  * For the Rosenbrock function: (0, 0) and (-2, 3)

* For each experiment provided in the report:

  * Contour plots (level curves) with the trajectories of the optimization methods were included.
  * Detailed tables were presented, including:
    * The number of iterations
    * The number of function evaluations
    * The number of gradient and Hessian evaluations (where applicable)

The following optimization techniques were implemented and thoroughly tested:

* **Lab 1: One-Dimensional Optimization**
  * [Dichotomy Method](https://github.com/ivandybko/Optimization/blob/56910373e45850ef48abb62a948191190fdff57f/Lab%201%20(One-dimensional%20optimization)/dichotomy_method.h)
  * [Golden Section Search](https://github.com/ivandybko/Optimization/blob/56910373e45850ef48abb62a948191190fdff57f/Lab%201%20(One-dimensional%20optimization)/golden_section_search.h)

* **Lab 2: Gradient Descent**
  * [Gradient Descent with Fixed Step Size](https://github.com/ivandybko/Optimization/blob/56910373e45850ef48abb62a948191190fdff57f/Lab%202%20(Gradient%20Descent)/gradient_descent_step_split.h)
  * [Gradient Descent with Step Size Selection via Line Search](https://github.com/ivandybko/Optimization/blob/56910373e45850ef48abb62a948191190fdff57f/Lab%202%20(Gradient%20Descent)/steepest_descent.h)

* **Lab 3: Conjugate Directions**
  * [Method of Conjugate Directions, Fletcher-Reeves and Polak-Ribiere](https://github.com/ivandybko/Optimization/blob/56910373e45850ef48abb62a948191190fdff57f/Lab%203%20(Conjugate%20directions)/conjugate_gradient.h)

* **Lab 4: Newton’s Method**
  * [Newton's Method, Newton’s Method with Line Search](https://github.com/ivandybko/Optimization/blob/56910373e45850ef48abb62a948191190fdff57f/Lab%204%20(Newton's%20Method)/newton_method.h)

* **Lab 5: Quasi-Newton Methods**
  * [Davidon-Fletcher-Powell (DFP) Method, Broyden-Fletcher-Shanno (BFS) Method, Powell's Method](https://github.com/ivandybko/Optimization/blob/56910373e45850ef48abb62a948191190fdff57f/Lab%205%20(Quasi-Newton%20methods)/quasi_newton_methods.h)

* **Lab 6: Direct Search Methods**
  * Method of cyclic coordinate descent
  * Hooke-Jeeves method
  * Rosenbrock method

* **Lab 7: Simplex Method**
  * Regular Simplex Method
  * Nelder-Mead Simplex Method
    
* **Lab 8: Nonlinear Programming Problem**
  * Interior Penalty Method 
  * Exterior Penalty Method
