## Selection of the k-th element of a list
This reporitory contains different implementations to select the k-th element of a list of integers:
* **Quick select** choosing a **deterministic pivot** (last element of the list)
* **Quick select** choosing a **random pivot**
* **Quick select** using the **Median of medians** algorithm to choose a pivot
* **Monte Carlo** algorithm 

To execute the code type the following in your command window:

```
# make
# ./main -opt-sample -opt-algorithm <number_elements> <k>
```
where 'opt-sample' refers to how the sample vector is going to be created:
* *-rep*: Creates a sample vector which can have repeated elements
* *-norep*: Creates a sample vector of distinct elements
On the other hand, '-opt-algorithm' can be any of the following:
* *-det*: Deterministic pivot for quickselect
* *-rand*: Random pivot for quickselect
* *-mom*: Median of medians pivot for quickselect
* *-monte*: Monte Carlo algorithm

This creates a sample list of n distinct elements and returns the k-th element 
