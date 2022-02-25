# numerical-math-cpp
A set of C++ classes and programs to solve math problems numerically.
This is my repository of C++ programs to solve math problems numerically, which can be also applied to many physics problems. Most of this work was developed in my Computational Physics class, along with my colleagues and friends, who developed the code with me (thanks Bruna, Gonçalo and Manuel). 

The structure of classes is a class per type of problem. Each class has a main file (example, class.cpp, main tClass.cpp) with a code example of a problem. The folder structure is understandable from the Makefile code, and consists of:

- Bin: binary and executable files, .o and .exe
- Lib: library of classes
- Main: main programs and files
- Src: classes and header files.

The classes available for each type of problem are:

- Random generator: FCrand;
- Matrix methods: FCmatrixAlgo;
- Systems of linear equations: EqSolver;
- Interpolation: DataPoints, Interpolator;
- Functions: Functor, FunctorND;
- Derivatives and integrals: IntegDeriv, IntegDerivND;
- Nonlinear equations and systems: RootFinder, RootFinderND;
- Vector fields: VectorField, IntegDerivVF;
- Ordinary differential equations: Xvar, ODEpoint, ODEsolver;
- Partial differential equations: PDEpoint;

There are still classes in development, such as methods for solving some partial differential equations, Taylor and Fourier series, Fourier transforms and integrals on manifolds and of vector fields. 
