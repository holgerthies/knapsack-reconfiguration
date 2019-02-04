# knapsack-reconfiguration
I wrote a small C++ program during the seminar to brute force the shortest path for cases with a small number of different weights.
The code is not very nice but maybe it will be useful for someone.
The script can be run from the terminal with the following parameters.
* `./knapsack -input` you can input the number of bins (different weights), the weights, initial and goal configuration and the interval and the program then searches and outputs a shortest valid path from the initial configuration to the goal.
It only works for at most 4-5 bins.
* `./knapsack -play` For the case of 4 bins you can give weights, initial condition and the interval and then play by yourself by making moves of the form `0 k` (take one element of weight weight[k] out) or `1 k` (put one element of weight weight[k] in)
* `./knapsack -rand` Randomly searches for a configuration that only has a long optimal path. You probably have to adapt the code to make this useful for you.
