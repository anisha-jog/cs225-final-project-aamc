Overall, we accomplished our goals.

# Our deliverables

- Our makefiles runs as expected
- We properly read in our Google web graph and built an adjacency list based on it
- We have thoroughly tested our graph and algorithms for bugs and memory leaks

# Algorithms & Traversals

- Our BFS traversal appopriately handles, and even continues to work in, a disconnected graph
- Our PageRank algorithm is implemented ...

We have decomposed our project into a Graph class, and an algos namespace, where our static functions algorithm functions are located.
Wherever possible, we have observed good programming habits; this may be through git, documentation, etc.

# Example results

```
BFS

![Connected Graph](input/web-connected.jpeg)
0 -> 1 -> 2 -> 3 -> 4 -> 5 -> 6

![Disconnected Graph](input/web-disconnected.jpeg)
1 -> 2 -> 3 -> 0 -> 4 -> 6 -> 5
```

```
PageRank

![Connected Graph](input/web-connected.jpeg)
0	0.0214286
1	0.163095
2	0.163095
3	0.163095
4	0.163095
5	0.163095
6	0.163095

![Disconnected Graph](input/web-disconnected.jpeg)

```