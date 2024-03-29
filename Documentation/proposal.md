# Leading Question

How are websites ranked in a search engine? What factors affect this ranking and can we understand how website ranking changes if we tweak these factors? 

For the PageRank Algorithm, how different are the top sites for different values of alpha? How different are the PageRanks of these top sites? For Tarjan’s algorithm, how are websites clustered? Can we identify and define patterns between them? Do strongly connected websites have high PageRank values?

Specifically, we want to analyze the web graph of Google.

# Dataset Acquisition and Processing

We will be using data from Stanford Large Network Dataset Collection: http://snap.stanford.edu/data/web-Google.html

1. Data format: Our dataset consists of text files found in the Stanford Large Dataset Collection. One of the datasets we will use is the web graph of Google found in the Dataset Collection. This file is 73,614 KB large, and we will use the entire dataset in order to have a cohesive dataset. However, given the extensive number of nodes totaling 875713, if the runtime proves to be unreasonably excessive, we will first filter the nodes while ensuring the data remains comprehensive. 

2. Data Correction: When building our graph from this data, we will make sure to check for any errors or missing data that could cause issues. Our first check is to ensure that all the connections we have represented are present in the dataset, so that we can sufficiently match webpages to our node IDs. Since there is no specific range to adhere to, we should not run into too many complications, but should we need to filter the data to get a smaller dataset, we may also include a check to remove a few hundred of the later nodes, or nodes with less connections than average. If we happen to have any repeat edges, they will be ignored. Any vertices that do not have out-edges can cause problems with our traversal; to avoid this, we may add self-loops to simplify our algorithm.

3. Data Storage: Our data is in the form of a graph with the nodes specified in a text file. We will keep this graph formatting, and in the case of needing to filter out data, we will recreate this format with the filtered data set in a new file. Our data will be stored as an adjacency list while the program runs.The target space complexity is O(V+E). [Note: The space complexity for an adjacency matrix is O(V2), but we do not anticipate creating a matrix for our implementation.]

## Graph Algorithms<br>
- PageRank Algorithm - The PageRank algorithm is used by Google Search to rank websites in their search engine results.
- BFS - Depth First Traversal can also be used for crawlers, but the advantage with Breadth First Traversal is, depth or levels of the built tree can be limited. 
- Tarjan’s Strongly Connected Components Algorithm - Find clusters of connected websites.

1. Function Inputs: The Pagerank function will receive the Google web graphs text file and a number alpha as inputs. The alpha will correspond to the alpha used for PageRank. The text file will encode a graph. 
The BFS algorithm will receive an adjacency list representation of the graphs. We may also want to pass in the number of vertices our graph contains.
Tarjan’s Algorithm will receive an adjacency list representation of the graphs.

2. Function Outputs: Our code will compute the PageRank vector (a length-n vector corresponding to the stationary distribution of a random walk on the input graph). We should also be able to compute the shortest paths from the source to all vertices in the given graph and a vector containing the BFS traversal for the entire graph.
Tarjan’s algorithm will compute a vector containing each strongly connected component as a vector. Essentially, it will output a vector of vectors containing vertices.

3. Function Efficiency: The time and memory complexity of the algorithms:
Pagerank: Target time complexity of the PageRank algorithm is O(n+m). For each vertex v, we will store a list of vertices that have an edge to v as a 1D array of linked lists. Space complexity is O(V2), where V represents the vertices of the graph.
 BFS: Target time complexity is O(V+E) where V is the number of nodes and E is the number of edges. Space complexity will be O(V), where V represents the vertices of the graph.
Tarjan’s Strongly Connected Components Algorithm: Time complexity of this algorithm is O(V+E), where V is the number of nodes and E is the number of edges. Space complexity is O(V), where V represents the vertices of the graph.

# Timeline

## Week 1 (10/28/22 - 11/4/22)
- Writing our proposal
- Researching algorithms we will need
- Understanding our dataset
- Designing the layout of our project

## Week 2 (11/4/22 - 11/11/22)
- Data loading & preprocessing:
  - Importing data from file (small test dataset)
  - Creating the node class/framework
  - Constructing a graph/adjacency list from data
- Researching algorithms in preparation for next week
- Breadth First Traversal functions

## Week 3 (11/11/22 - 11/18/22)
- Implementing Tarjan’s Algorithm to find shortest path
- Start working on PageRank algorithm if not already started
- Import larger datasets in tests

## Week 4 (11/18/22 - 11/25/22) - Fall Break
- Team members will put in some hours of work if they are able, but are not expected to
- If possible, try importing the entire dataset for testing

## Week 5 (11/25/22 - 12/2/22)
- Continue working on PageRank algorithm
- Write test cases for all our functions
- Clean up terminal output for easy-to-use interface

## Week 6 (12/2/22 - 12/8/22) - Final Deliverables
- Understand how different are the top sites for different values of alpha? How different are the PageRanks of these top sites?
- Code and documentation clean-up
- Create video walkthrough of our project
- Create any other final deliverables required
