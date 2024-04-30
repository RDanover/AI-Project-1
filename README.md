**Project Description:** </br></br>
This project uses A* search using Uniform Cost, Manhattan Distance, and Misplaced Tile heuristics to solve the 8 sliding block puzzle. This program can take in any 8 sliding block puzzle arrangement and will determine whether it is solvable. If the puzzle is solvable it will give the minimum number of moves needed for an optimal solution (the depth of the goal node). This program does not provide the steps to solve the problem. 

**Instructions for how to run:**
1. download main.cpp
2. In directory where main.cpp is run the command: g++ -std=c++11 main.cpp 
3. Then run the command: ./a.out
4. In the terminal, when prompted whether you would like to enter a puzzle to be solved enter "Y"
5. Enter the puzzle you would like solved</br>
   for example: let 0 represent the blank space in the puzzle to solve the puzzle:</br>
   0 1 2</br>
   4 5 3</br>
   7 8 6</br>
   enter: "0, 1, 2, 4, 5, 3, 7, 8, 6"</br>
6. Then enter the number next to the heuristic you would like to be used to solve the puzzle (1, 2, or 3). 

