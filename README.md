# HOMFLY
A new algorithm is conceived to calculate the HOMFLY polynomials of even-crossing topological links. Here, based on the algorithm, a program is developed for calculating the HOMFLY polynomials of all of the even-crossing trigonal bipyramid links.

The source code, related data and results are stored in the `./special/2n-otbls/` directory. We provide two code version: C version (old) and Python version (new).

## 1 Usage

- C version

  The C code can be compiled directly with only the C standard library. For example, in Linux system, please implement the following command:

  ```bash
  $ cd ./special/2n-otbls/c/
  $ g++ homfly-of-2n-otbls.cpp -o homfly-of-2n-otbls
  ```

  Next we can calculate the HOMFLY polynomials with the input file provided:

  ```bash
  $ homfly-of-2n-otbls data/in.txt
  ```

  Of course, the expressions it outputs are messy, and it is a good idea to simplify them with the help of Mathematica. (The simplified neat result is stored in `./special/2n-otbls/c/results/104-homfly-polynomials-of-2n-otbls.nb` for reference.)

- Python version

  In this new version, we use the `SymPy` package for symbolic mathematics, with which we can carry out all kinds of symbolic manipulations just in Python code. Certainly, the installation of `SymPy` Python library is indispensable.

  ```bash
  $ pip install sympy
  ```

  The core of this program is included in the module `src/homfly.py`. And its instruction is fully shown in the notebook `homfly-for-even-cross-otbls.ipynb`, please refer to it for more information.

## 2 Citation

To be continued ...

