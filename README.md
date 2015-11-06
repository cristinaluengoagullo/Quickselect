## Selection of the k-th element of a list
This repository is created for an assignment on the course "Randomized Algorithms".  It contains different implementations on algorithms to select the k-th element of a list of integers:
* **Quick select** choosing a **deterministic pivot** (last element of the list)
* **Quick select** choosing a **random pivot**
* **Quick select** using the **Median of medians** algorithm to choose a pivot
* **Monte Carlo** algorithm 

To execute the code type the following in your command window:

```
# make
# ./main -opt-sample -opt-algorithm <number_elements> [<k>]
```
where '*-opt-sample*' refers to how the sample vector is going to be created:
* *-rep*: Creates a sample vector which can have repeated elements
* *-norep*: Creates a sample vector of distinct elements

On the other hand, '*-opt-algorithm*' can be any of the following:
* *-det*: Deterministic pivot for quickselect
* *-rand*: Random pivot for quickselect
* *-mom*: Median of medians pivot for quickselect
* *-monte*: Monte Carlo algorithm

The 'k' is optional only if you specify the **Monte Carlo** algorithm, since it uses different algorithms to compute either the median of the list or the k-th element. Hence, if parameter k is not specified, it computes the median of the list.

This commands execute a C++ program which creates a sample list of n distinct elements and returns the k-th element. 

Furthermore, in order to reproduce the experiments performed in the assignment, type the following in your command window:

```
# make -f MakefileTests
# ./main [-wc] <number_elements>
```
where '*-wc*' refers to executing experiments for the worst case scenario. 

Further information on the assignment and the experiments carried out can be found in the file **report.pdf**
