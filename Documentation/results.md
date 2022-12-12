Overall, we accomplished our goals.

# Our deliverables

- Our makefiles runs as expected
- We properly read in our Google web graph and built an adjacency list based on it
- We have thoroughly tested our graph and algorithms for bugs and memory leaks

# Algorithms & Traversals

- Our BFS traversal appopriately handles, and even continues to work in, a disconnected graph
- Our PageRank algorithm is implemented with an adjacency matrix and calculates a sorted vector of ranked pages at different iterations that works in connected and disconnected graphs.

We have decomposed our project into a Graph class, and an algos namespace, where our static functions algorithm functions are located.
Wherever possible, we have observed good programming habits; this may be through git, documentation, etc.

# Example results

![Connected Graph](../input/web-connected.jpeg)
![Disconnected Graph](../input/web-disconnected.jpeg)

```
BFS

Connected Graph:
0 -> 1 -> 2 -> 3 -> 4 -> 5 -> 6

Disconnected Graph:
1 -> 2 -> 3 -> 0 -> 4 -> 6 -> 5
```

```
PageRank

Connected Graph:

1 Iteration:
1	0.163095
5	0.163095
6	0.163095
2	0.163095
3	0.163095
4	0.163095
0	0.0214286


Disconnected Graph:

1 Iteration:
3	0.28027
4	0.177055
5	0.177055
6	0.177055
2	0.1068
0	0.0408819
1	0.0408819

10 Iterations:
6	0.238138
4	0.238138
5	0.238138
3	0.1177
2	0.0964458
0	0.0357207
1	0.0357207
```
