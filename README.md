## Selection of the k-th element of a list
This reporitory contains different implementations to select the k-th element of a list of integers:
* **Quick select** choosing a **deterministic pivot** (last element of the list)
* **Quick select** choosing a **random pivot**
* **Quick select** using the **Median of medians** algorithm to choose a pivot
* **Monte Carlo** algorithm 

To execute the code type the following in your command window:

```
# make
# ./main -opt <number_elements> <k>
```
where '-opt' can be any of the following:
* *-det*: Deterministic pivot
* *-rand*: Random pivot
* *-mom*: Median of medians pivot
* *-monte*: Monte Carlo algorithm

This creates a sample list of n distinct elements and returns the k-th element 
