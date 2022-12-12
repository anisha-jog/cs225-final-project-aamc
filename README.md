# cs225-final-project-aamc

## Build and Run

To build the files, use the command:
```
   mkdir build
   cd build
   cmake ..
   make
```
    
After building the main executable from the main command, there are 2 main commands that can be run:
```
   ./test
   ./main
```
   
Running main will step through building our graph, running the BFS algorithm, and running the PageRank algorithm, the results of which will be written to files in the output folder. Follow the prompts given in the terminal to enter files for input/output. Comments are available in the file to explain which parameters to change for what purpose, if desired. Running test will run all of our test cases for our graph, BFS algorithm, and PageRank algorithm.

## Folder Hierarchy

`Documentation` - project documentation for non-code material such as our proposal, written report, and presentation video.<br>
`entry` - contains main.cpp.<br>
`input` - contains all of the input files we use. Each file contains a set of graph edges; the first number is the source vertex, and the second number is the destination vertex.<br>
`lib` - dummy folder for libraries. Currently, we are not using any external libraries.<br>
`output` - contains output files to write algorithm results to.<br>
`src` - contains our project implementation, including the graph class, graph functions, and our algorithms.<br>
`tests` - contains tests.cpp.
