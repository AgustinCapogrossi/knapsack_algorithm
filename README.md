# KNAPSACK ALGORITHM

## Flags

> -b: Enables the backtracking algorithm
> -d: Enables the dinamic programming algorithn
> -s: Shows the selected items when used alongside -d
> -w <arg>: forces the capacity of the bag to be *arg*
> -t: Enables verifications
> -f <files>: List of files for which you want to run the specified algorithms. If you don't include this flag you must enter the items with the following format: name:value:weight

## How to run (with examples)

```
$make
//Backtracking
$./knapsack -b -f input/example0.in 
//Dynamic
$./knapsack -d -f input/example0.in
//Dynamic showing the collection of items
$./knapsack -ds -f input/example0.in
//Backtracking and Dynamic
$./knapsack -bd -f input/example0.in
//Backtracking and Dynamic showing selection and verifying the obtained value
$./knapsack -bdst -f input/example*.in
```
