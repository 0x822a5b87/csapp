# 告别动态规划，连刷 40 道题，我总结了这些套路，看不懂你打我 

[Dynamic_programming](https://en.wikipedia.org/wiki/Dynamic_programming)

1. dynamic programming refers to simplifying a complicated problem by breaking it down into simpler sub-problems in a recursive manner. 
2. If sub-problems can be nested recursively inside larger problems, so that dynamic programming methods are applicable, then there is a relation between the value of the larger problem and the values of the sub-problems.

## Computer programming

There are two key attributes that a problem must have in order for dynamic programming to be applicable: [optimal substructure](https://en.wikipedia.org/wiki/Optimal_substructure) and [overlapping sub-problems](https://en.wikipedia.org/wiki/Overlapping_subproblemsl). **If a problem can be solved by combining optimal solutions to non-overlapping sub-problems, the strategy is called "[divide and conquer](https://en.wikipedia.org/wiki/Divide-and-conquer_algorithm)" instead**. This is why merge sort and quick sort are not classified as dynamic programming problems.

## 概述

1. 动态规划( **Dynamic Programming** )，通过 **将原问题分解为相对简单的子问题的方式来求解**。 
2. 通常许多子问题非常相似，所以为了优化动态规划的速度，我们需要试图为每个子问题只求值一次：一旦给定某个子问题的解，我们就可以将它存储起来，以便一下次解决同一个子问题时直接查表；
3. 动态规划只能应用于有 **最优子结构** 的

## 动态规划的三个步骤


