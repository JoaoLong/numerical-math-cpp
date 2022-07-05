# Numerical math methods
A set of C++ classes and programs to solve math problems numerically.
This is our repository of C++ programs to solve math problems numerically, which can be also applied to many physics problems. This work was developed by me and my group of friends in Computational Physics class.


**Software requirements:**
The libraries [Eigen](https://eigen.tuxfamily.org/) (used for storing matrices) and [CERN-ROOT](https://root.cern/) (used for graphing) are required to run the code.


**Folder structure:**
The structure of classes is a class per type of problem. Each class has a main file (an example: *class.cpp* has as main *tClass.cpp*) with a code example of a problem. The folder structure is understandable from the Makefile code, and consists of:

- *bin* - binary and executable files.
- *lib* - library of classes for faster compilation.
- *main* - main programs and files.
- *src* - classes and header files.


**Developed methods:**
The classes available for each type of problem are:

- Random number generator - *FCrand*.
- Matrix methods - *FCmatrixAlgo*.
- Systems of linear equations - *EqSolver*.
- Interpolation - *DataPoints*, *Interpolator*.
- Functions - *Functor*, *FunctorND*, *VectorField*.
- Derivatives and integrals - *IntegDeriv*, *IntegDerivND*, *IntegDerivVF*.
- Nonlinear equations and systems - *RootFinder*, *RootFinderND*.
- Graph fitting - *Fitter*, *MultiFitter*
- Ordinary differential equations - *Xvar*, *ODEpoint*, *ODEsolver*.
- Boundary value problems in ODEs - *BVPsolver*.
- Partial differential equations - *PDEpoint*.
- Infinite series, Taylor and Fourier series - *SeriesTransforms*. 


**In development:**
We tried to make the code as broad and widely applicable as possible. Nonetheless, there are still classes in development, such as methods for solving some partial differential equations, Fourier transforms, multidimensional fitting and integrals on manifolds and of vector fields.
