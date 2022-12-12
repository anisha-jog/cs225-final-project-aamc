# CS 255 Final Project: Web Graphs & PageRank Results
## Goals
- Load a dataset of web graph edges from the Stanford Large Network Dataset Collection (web-Google) into a graph structure
- Perform a complete breadth-first traversal on our graph
- Run the PageRank algorithm on our graph and output a list of pages ordered by likelihood of being visited
- Examine the effects of changing the alpha parameter of the PageRank algorithm

Overall, we accomplished our goals, though our complexity is higher than expected.

## Our deliverables

- Our makefile runs as expected
- We properly read in our Google web graph and built an adjacency list & adjacency matrix based on it
- We have thoroughly tested our graph and algorithms for bugs and memory leaks
- We have completed the BFS & PageRank algorithms
- All outputs are printed to `/output/<name>.txt`

# Algorithms & Traversals

We have decomposed our project into a Graph class and an algos namespace, where our static functions algorithm functions are located.
Wherever possible, we have observed good programming habits; this may be through git, documentation, etc.

## Graph Class

Our graph class includes structs for vertices and edges and various data structures to store and manipulate data. We build an adjacency list for our BFS algorithm with a space complexity of O(V + E). In addition, we have a list of vertices and a map that connects IDs to their indices, both with O(V) space complexity. Our adjacency matrix was necessary for the PageRank algorithm and has a space complexity of O(V^2).<br>

The graph class contains functions for Rule of Three, constructors, and helper functions for accessing member variables. The constructors include a blank default constructor, a copy constructor, and a constructor that reads data from a file in the following format:<br>
|    |  |
| ----------- | ----------- |
| Vertex1      | Vertex2       |
| Vertex1   | Vertex3        |

We have test cases to test our rule of three functions and constructors for the correct edges and vertices, which include simple, connected, disconnected, and circular graphs. The test cases also cover the reading from file constructor to ensure that it reads properly.

## BFS

Our BFS traversal starts at a given vertex and travels to each connected vertex while using a queue to track visited vertices. Once it finds all of the vertices in the connected subgraph, it goes through all vertices to identify any components that are disconnected from the starting point's subgraph to completely cover the entire graph. This makes our traversal able to appropriately handle and continue to work in a disconnected graph. This algorithm is able to run on our entire dataset, though it may require a lower ID cap on a low-performance computer due to the non-availability of sufficient power or RAM.<br>

We have test cases to evaluate the BFS traversal on a variety of smaller graphs, including simple, connected, disconnected, and circular graphs. These tests check that the traversal visits these vertices in the right order. It also tests for different starting points and numbers of vertices.<br>

The complexity of our BFS algorithm is O(V^2 + E).

## PageRank
Our PageRank algorithm is implemented with an adjacency matrix and calculates a sorted vector of ranked pages at different iterations that works in connected and disconnected graphs. It uses the Markov Chain interpretation of the algorithm to apply a random factor to all vertices (i.e. the chance that a user will get bored and click on a random page, even if it is not linked by the current page). It calculates a vector of pages and their PageRank values to determine how likely they are to be visited after a certain number of iterations, sorted in descending order. Since this involves the creation of an adjacency matrix and multiplication of matrices, which is complex to perform in C++, this algorithm can handle up to 20000 vertices (ID cap of 50000) on a high-performance computer, though for faster runtime or a low-performance computer it is recommended to lower the ID cap to less than 20000 (3000 vertices), especially for multiple iterations.<br>

We have test cases to evaluate whether the PageRank list is correct. Some cases test that the rank of page IDs is correct, while others check that the PageRank value is correct based on manual calculation. The graphs for these tests include simple, complex, disconnected, and connected graphs.<br>

The complexity of our PageRank algorithm is O(V^3).

# Example results

[Connected Graph](https://github.com/anisha-jog/cs225-final-project-aamc/blob/19374e9994b45ee287df5bd00512b28b406895de/input/web-connected.jpeg)<br>
[Disconnected Graph](https://github.com/anisha-jog/cs225-final-project-aamc/blob/19374e9994b45ee287df5bd00512b28b406895de/input/web-disconnected.jpeg)<br>
[Small Graph](https://github.com/anisha-jog/cs225-final-project-aamc/blob/19374e9994b45ee287df5bd00512b28b406895de/input/web-small.PNG)<br>
[Complex Graph](https://github.com/anisha-jog/cs225-final-project-aamc/blob/19374e9994b45ee287df5bd00512b28b406895de/input/web-complex.PNG)<br>

```
BFS

Connected Graph:
0 -> 1 -> 2 -> 3 -> 4 -> 5 -> 6

Disconnected Graph:
1 -> 2 -> 3 -> 0 -> 4 -> 6 -> 5

Google Dataset (Cap of 10000, 835 vertices):
20 -> 7235 -> 54 -> 7969 -> 110 -> 6345 -> 111 -> 7314 -> 135 -> 3339 -> 145 -> 9652 -> 147 -> 3170 -> 157 -> 1673 -> 193 -> 3694 -> 208 -> 5654 -> 222 -> 8731 -> 242 -> 9141 -> 284 -> 9088 -> 285 -> 5756 -> 290 -> 9111 -> 300 -> 5534 -> 305 -> 4694 -> 372 -> 6555 -> 383 -> 3259 -> 422 -> 3410 -> 456 -> 3054 -> 504 -> 515 -> 9550 -> 517 -> 5314 -> 522 -> 5778 -> 539 -> 2531 -> 540 -> 3611 -> 554 -> 9678 -> 593 -> 2816 -> 600 -> 5524 -> 606 -> 1300 -> 616 -> 5651 -> 653 -> 3044 -> 679 -> 1479 -> 691 -> 6806 -> 8032 -> 697 -> 3905 -> 720 -> 2244 -> 726 -> 2920 -> 740 -> 2939 -> 756 -> 5236 -> 813 -> 8713 -> 827 -> 1985 -> 6264 -> 859 -> 2975 -> 872 -> 1532 -> 885 -> 9134 -> 932 -> 7912 -> 956 -> 3925 -> 973 -> 6115 -> 3613 -> 1025 -> 6988 -> 1035 -> 3472 -> 1041 -> 4015 -> 1049 -> 3496 -> 1051 -> 1304 -> 1054 -> 1087 -> 9542 -> 8040 -> 1122 -> 429 -> 1125 -> 1610 -> 1129 -> 2218 -> 1134 -> 5280 -> 1142 -> 3854 -> 1176 -> 8316 -> 1196 -> 6771 -> 1211 -> 7838 -> 1214 -> 9638 -> 1232 -> 1257 -> 2592 -> 1262 -> 1682 -> 1284 -> 6222 -> 1296 -> 2267 -> 1345 -> 5575 -> 1352 -> 1633 -> 1399 -> 9438 -> 1403 -> 1436 -> 409 -> 1473 -> 5347 -> 1509 -> 1401 -> 1513 -> 1406 -> 1535 -> 4990 -> 1546 -> 7796 -> 1549 -> 6111 -> 3395 -> 1624 -> 1636 -> 2048 -> 7896 -> 1650 -> 8979 -> 1661 -> 8669 -> 1669 -> 5108 -> 1695 -> 6530 -> 1705 -> 693 -> 1717 -> 1825 -> 1722 -> 8734 -> 1739 -> 6236 -> 1745 -> 1786 -> 4547 -> 1833 -> 1838 -> 8217 -> 1860 -> 5622 -> 1869 -> 5780 -> 1902 -> 9877 -> 1911 -> 1945 -> 9581 -> 1967 -> 4064 -> 1976 -> 2415 -> 2006 -> 3966 -> 2010 -> 9533 -> 2062 -> 7252 -> 206 -> 2127 -> 7010 -> 2135 -> 2146 -> 2028 -> 2185 -> 8899 -> 2210 -> 2217 -> 5432 -> 2255 -> 2264 -> 3378 -> 2283 -> 732 -> 2377 -> 9198 -> 2385 -> 4456 -> 2394 -> 2404 -> 2416 -> 1866 -> 2466 -> 2469 -> 9192 -> 2477 -> 7626 -> 2480 -> 3667 -> 2519 -> 7272 -> 2525 -> 2555 -> 8283 -> 2565 -> 2982 -> 2575 -> 7244 -> 2584 -> 8659 -> 2586 -> 6984 -> 2587 -> 9810 -> 2599 -> 2722 -> 2607 -> 4027 -> 2609 -> 2 -> 2628 -> 3401 -> 2636 -> 6571 -> 2706 -> 9303 -> 2714 -> 8631 -> 2791 -> 2796 -> 8549 -> 2810 -> 3284 -> 6517 -> 2827 -> 9706 -> 2842 -> 1684 -> 2844 -> 5776 -> 8670 -> 2852 -> 1536 -> 2893 -> 5500 -> 2999 -> 9605 -> 3004 -> 2596 -> 3035 -> 9310 -> 3039 -> 3373 -> 3049 -> 5547 -> 3060 -> 2402 -> 3064 -> 2486 -> 3071 -> 3822 -> 3101 -> 2964 -> 3105 -> 1236 -> 3128 -> 3160 -> 3140 -> 8385 -> 3151 -> 5624 -> 3174 -> 3179 -> 3190 -> 3241 -> 8922 -> 3245 -> 8329 -> 3251 -> 3276 -> 1298 -> 3283 -> 7382 -> 3296 -> 3299 -> 5132 -> 3315 -> 3518 -> 3338 -> 1737 -> 8853 -> 3343 -> 3366 -> 3692 -> 3368 -> 1723 -> 3369 -> 9893 -> 3384 -> 3386 -> 9804 -> 3406 -> 3532 -> 3407 -> 5355 -> 3421 -> 3437 -> 6574 -> 3468 -> 3471 -> 5623 -> 3537 -> 8082 -> 3560 -> 3579 -> 3580 -> 4548 -> 3614 -> 6559 -> 7334 -> 3653 -> 6939 -> 3654 -> 3683 -> 4000 -> 3685 -> 4657 -> 3686 -> 3726 -> 3765 -> 2107 -> 3781 -> 4466 -> 3791 -> 4627 -> 3795 -> 7533 -> 3814 -> 6573 -> 3818 -> 9572 -> 3819 -> 7539 -> 3827 -> 8766 -> 3858 -> 8879 -> 3861 -> 2527 -> 3883 -> 4635 -> 3897 -> 5625 -> 3898 -> 5409 -> 3908 -> 3483 -> 3943 -> 7004 -> 3977 -> 4667 -> 4001 -> 4042 -> 7550 -> 4073 -> 7531 -> 4107 -> 4118 -> 9787 -> 4127 -> 710 -> 4132 -> 9684 -> 4149 -> 8055 -> 4153 -> 7438 -> 4219 -> 8653 -> 2483 -> 4227 -> 4552 -> 4257 -> 5224 -> 4308 -> 4354 -> 8008 -> 4361 -> 8544 -> 4365 -> 5337 -> 4367 -> 280 -> 4396 -> 8275 -> 4463 -> 5763 -> 4476 -> 7917 -> 4516 -> 8676 -> 4518 -> 7747 -> 4541 -> 9080 -> 4557 -> 4571 -> 6693 -> 4581 -> 211 -> 4585 -> 4621 -> 4760 -> 4638 -> 7665 -> 4649 -> 2841 -> 4678 -> 5786 -> 4690 -> 4705 -> 7840 -> 4710 -> 9497 -> 4712 -> 4720 -> 8101 -> 4747 -> 7925 -> 4762 -> 4781 -> 4819 -> 4844 -> 4845 -> 2569 -> 4870 -> 4888 -> 8219 -> 4898 -> 7575 -> 4904 -> 3400 -> 4912 -> 4917 -> 3937 -> 4958 -> 4980 -> 278 -> 5006 -> 7038 -> 5019 -> 5054 -> 6047 -> 5079 -> 3805 -> 5099 -> 7906 -> 5110 -> 9129 -> 5111 -> 4333 -> 5124 -> 8994 -> 5133 -> 2874 -> 5158 -> 5241 -> 6557 -> 5249 -> 7117 -> 5313 -> 1155 -> 5316 -> 9553 -> 5350 -> 8148 -> 5354 -> 8317 -> 5358 -> 5363 -> 5381 -> 5715 -> 5386 -> 1285 -> 5426 -> 5441 -> 3497 -> 5444 -> 1068 -> 5452 -> 5676 -> 5453 -> 5489 -> 5532 -> 6100 -> 5539 -> 5546 -> 718 -> 5591 -> 5649 -> 8856 -> 5653 -> 5666 -> 5705 -> 5744 -> 5762 -> 8213 -> 5814 -> 5828 -> 9048 -> 5829 -> 5896 -> 4899 -> 5919 -> 3793 -> 5973 -> 7916 -> 5982 -> 4864 -> 5986 -> 520 -> 6042 -> 8545 -> 6082 -> 2825 -> 6087 -> 2591 -> 6099 -> 6101 -> 5918 -> 6158 -> 6208 -> 181 -> 6230 -> 407 -> 6242 -> 6245 -> 6127 -> 6290 -> 5005 -> 6368 -> 8249 -> 6386 -> 4702 -> 6403 -> 5930 -> 6414 -> 6428 -> 2161 -> 6431 -> 6465 -> 6492 -> 5461 -> 6500 -> 6545 -> 9662 -> 6566 -> 6615 -> 6956 -> 6620 -> 6658 -> 9205 -> 6667 -> 2719 -> 6670 -> 8983 -> 6694 -> 2912 -> 6715 -> 9246 -> 6723 -> 183 -> 6734 -> 943 -> 6775 -> 4481 -> 6792 -> 2142 -> 6810 -> 7240 -> 6818 -> 3388 -> 6838 -> 6840 -> 7476 -> 6916 -> 6922 -> 8881 -> 6935 -> 4312 -> 6942 -> 6962 -> 6885 -> 8019 -> 6968 -> 6969 -> 6109 -> 6987 -> 6989 -> 6991 -> 8196 -> 7002 -> 6550 -> 7018 -> 4131 -> 7033 -> 5603 -> 7042 -> 3423 -> 7049 -> 8743 -> 7094 -> 7107 -> 4863 -> 7113 -> 8726 -> 7138 -> 7159 -> 1826 -> 7179 -> 7221 -> 2488 -> 7229 -> 7230 -> 7288 -> 5766 -> 7343 -> 7358 -> 7366 -> 3919 -> 7431 -> 7456 -> 7457 -> 742 -> 7466 -> 7473 -> 8460 -> 7492 -> 5415 -> 7507 -> 7568 -> 1448 -> 7577 -> 3505 -> 7632 -> 2677 -> 3247 -> 8489 -> 7636 -> 8089 -> 7655 -> 7677 -> 7712 -> 8813 -> 7746 -> 7811 -> 7827 -> 7862 -> 7886 -> 9859 -> 7895 -> 5003 -> 7898 -> 7910 -> 109 -> 7911 -> 7970 -> 8005 -> 8022 -> 6349 -> 8102 -> 7684 -> 8142 -> 8476 -> 8145 -> 8402 -> 8284 -> 8287 -> 8304 -> 8344 -> 3679 -> 8378 -> 7402 -> 9233 -> 8399 -> 8442 -> 2778 -> 8744 -> 8466 -> 9608 -> 8475 -> 5042 -> 8498 -> 8637 -> 1279 -> 8638 -> 113 -> 8658 -> 8665 -> 3397 -> 8753 -> 3206 -> 8818 -> 9482 -> 8820 -> 9390 -> 8842 -> 2249 -> 8850 -> 8852 -> 9956 -> 8905 -> 9151 -> 8969 -> 71 -> 612 -> 1500 -> 9015 -> 9020 -> 6443 -> 9032 -> 4230 -> 9054 -> 9394 -> 9110 -> 9115 -> 9339 -> 9132 -> 5889 -> 9219 -> 9225 -> 7699 -> 9227 -> 9235 -> 9240 -> 9264 -> 3570 -> 9278 -> 9279 -> 9299 -> 2601 -> 9326 -> 514 -> 9331 -> 9333 -> 9334 -> 9346 -> 9347 -> 9352 -> 293 -> 9410 -> 9419 -> 9426 -> 7217 -> 9431 -> 9428 -> 9456 -> 9460 -> 9488 -> 9509 -> 9512 -> 6848 -> 9518 -> 7295 -> 9529 -> 1451 -> 9535 -> 9549 -> 5981 -> 9561 -> 5119 -> 9590 -> 9592 -> 4773 -> 9594 -> 5270 -> 9630 -> 1787 -> 9646 -> 9676 -> 9695 -> 9738 -> 2314 -> 9749 -> 7309 -> 9789 -> 9886 -> 5121 -> 9897 -> 9930 -> 9931 -> 9937 -> 9566 -> 9973 -> 5201 -> 9988 -> 7074
```

```
PageRank (Format: Page ID, PageRank number)

Connected Graph:

1 Iteration, alpha = 0.85:
1	0.163095
5	0.163095
6	0.163095
2	0.163095
3	0.163095
4	0.163095
0	0.0214286


Disconnected Graph:

1 Iteration, alpha = 0.85:
3	0.28027
4	0.177055
5	0.177055
6	0.177055
2	0.1068
0	0.0408819
1	0.0408819

10 Iterations, alpha - 0.85:
6	0.238138
4	0.238138
5	0.238138
3	0.1177
2	0.0964458
0	0.0357207
1	0.0357207

Google Dataset (835 vertices, 5 iterations), first 10 pages:

alpha = 0.85:
7314	0.0109186
6236	0.0104514
1739	0.00969656
6111	0.00924539
3395	0.00849052
827	0.00673895
1049	0.00673895
3496	0.0061728
8316	0.00585306
6115	0.00543855

alpha = 0.5:
7314	0.0125868
8316	0.00690245
6236	0.00460163
6111	0.00419561
1739	0.0035189
9533	0.00345123
3170	0.00324821
5314	0.00324821
8979	0.00324821
4635	0.00324821

alpha = 0.25:
7314	0.00827035
8316	0.00476171
6236	0.00274007
9533	0.00263147
6111	0.002573
3170	0.00250617
5314	0.00250617
8979	0.00250617
4635	0.00250617
4547	0.00225555
```

# Conclusion & Reflection

We found our PageRank results to be very interesting, as while the PageRank values turned out to be extremely small, it still established a clear list with pages that have more incoming edges towards the top while those with less were towards the bottom. We also learned that pages with the most incoming edges were not necessarily in the first entries, as random clicks to different websites affected how likely it was to be visited. This meant that the alpha value could affect how the pages were ordered, as shown above; while the top page remained the same, the positions of many of the subsequent pages shifted around, and all of the PageRank values were significantly smaller without the alpha boost.<br>

We could also see that the number of iterations changed the values and order of our pages. This makes sense, since matrix multiplication would alter these values over more iterations; however, after a certain number of iterations, the vector would converge, meaning there was a little to no change between each iteration.<br>

Given more time, we would like to change our implementation to use a sparse adjacency matrix. Unfortunately, an adjacency matrix with thousands of nodes makes it extremely complex to run and is often too much for a standard computer. Performing complex matrix multiplication also takes a very heavy toll on a computer. Using a sparse adjacency matrix not only reduces the space complexity of our structure, but it also reduces both the time to create the matrix and the time to multiply it with itself in the PageRank algorithm.<br>

We would also like to implement Tarjan's algorithm for strongly connected components. This was one of our original goals, but due to the changes in our team and the lack of time, we reduced the scope of our project. In the future, we would like to use this algorithm to see groups of connected pages in our dataset.
