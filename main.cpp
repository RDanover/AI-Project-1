#include <stdlib.h> //used for abs function
#include <iostream> //used to get user input and output
#include <vector> 
#include <algorithm> //used for sort function

//Change lines 8 - 18 to alter the program to work for any size sliding block puzzle so long as the row size >1
//Begin puzzle specific section
const int puzzle_size = 9;
const int row_size = 3;

std::vector<int> goal_state{ 1, 2, 3, 4, 5, 6, 7, 8, 0 };
//uncomment puzzle to make it the default
std::vector<int> puzzle{ 1, 2, 3, 4, 5, 6, 7, 8, 0 };//Trivial
//std::vector<int> puzzle{ 1, 2, 3, 4, 5, 6, 7, 0, 8 };//Very easy
//std::vector<int> puzzle{ 1, 2, 0, 4, 5, 3, 7, 8, 6 };//Easy
//std::vector<int> puzzle{ 0, 1, 2, 4, 5, 3, 7, 8, 6 };//Doable
//std::vector<int> puzzle{ 8, 7, 1, 6, 0, 2, 5, 4, 3 };//Oh boy
//std::vector<int> puzzle{ 1, 2, 3, 4, 5, 6, 8, 7, 0 };//Impossible

//End puzzle specific section

//variables used for statistics
int max_node_count = 0;
int num_expanded_nodes = 0;

//stores all previously expanded states
std::vector< std::vector<int> > explored_nodes;

//This function is where the A* comparison takes place where the H(n)+G(n) of two different states are compared
bool compareVectors(const std::vector<int>& a, const std::vector<int>& b){
    return (a[puzzle_size] + a[puzzle_size+1])<(b[puzzle_size] + b[puzzle_size+1]);
}

/*
Description: helper function to print out a given state 
Input:  std::vector<int> p: state representation vector 
        int s: puzzle size
        int r: row size
Output: Prints puzzle to terminal in format:
        N N N
        N N N
        N N B
*/
void print_puzzle(std::vector<int> p, int s, int r){
    for(int i = 1; i<=s;i++){
        std::cout<<(p[i-1]);
        if(i%r==0){
            std::cout<<("\n");
        }
        else{
            std::cout<<(" ");
        }
    }
}

/*
Description: helper function to determine if a state has already been expanded by checking the explored nodes vector
Input:  std::vector<int> p: state representation vector assumes G(n) and H(n) are both 0
        int s: puzzle size
Output: True if state has been expanded before
        False if state has not been expanded before
*/
bool is_duplicate(std::vector<int> p, int s){
    int k = 0;
    for(int i = 0; i < explored_nodes.size();i++){
        k = 0;
        for(int j=0; j<s;j++){
            if(p[j]==explored_nodes.at(i)[j]){
                k++;
            }
        }
        if(k==s){
            return true;
        }
    }
    return false;
}

/*
Description: heuristic function that determines the euclidean distance sums of all given states
Input:  std::vector< std::vector<int> > p: vector containing many state representation vectors
        int s: puzzle size
        int r: row size
Output: Returns the original vector p with the heuristic value for each state updated to the correct value
*/
std::vector< std::vector<int> > euclidean_distance(std::vector< std::vector<int> > p, int s, int r){
    int j = 0;//represents where the value at i is actually supposed to be located
    int h = 0;//heuristic value
    int row_cost_i = 0;
    int row_cost_j = 0;
    //loops through list of states and calculates the heuristic value 
    for(int a = 0; a < p.size(); a++){
        //loops through each tile in the puzzle 
        for(int i = 0; i < s; i++){
            if(p.at(a)[i]==0){
                //special case blank space
                j = s-1;
            }
            else{
                j = p.at(a)[i]-1;
            }
            if(i!=j){
                h+=abs(j%r - i%r);//column cost 
                for(int k = 0; k < s;k++){//loop determines row for i and j by using ranges of each row 
                    if((i>=k*r)&&(i<(k+1)*r)){
                        row_cost_i = k;
                    }
                    if((j>=k*r)&&(j<(k+1)*r)){
                        row_cost_j = k;
                    }
                }
                h+=abs(row_cost_i - row_cost_j);//row cost
            }
        }
        p.at(a).at(s+1) = h;//set heuristic value to h
        //reset values before next iteration
        j = 0;
        h = 0;
        row_cost_i = 0;
        row_cost_j = 0;
    }
    return p;
}

/*
Description: heuristic function that determines the sums of misplaced of all given states
Input:  std::vector< std::vector<int> > p: vector containing many state representation vectors
        int s: puzzle size
        int r: row size
Output: Returns the original vector p with the heuristic value for each state updated to the correct value
*/
std::vector< std::vector<int> > misplaced_tile(std::vector< std::vector<int> > p, int s, int r){
    int j = 0;//represents where the value at i is actually supposed to be located
    int h = 0;
    for(int a = 0; a < p.size(); a++){
        for(int i = 0; i < s; i++){
            if(p.at(a)[i]==0){
                //special case blank space
                j = s-1;
            }
            else{
                j = p.at(a)[i]-1;
            }

            if(i != j){
                h++;
            }
        }
        p.at(a).at(s+1) = h;//set heuristic value to h
        j = 0;
        h = 0;
    }
    return p;
}

/*
Description: helper function that determines the returns a vector containing all the unique valid states that can be reached from the input state
Input:  std::vector<int> p: state representation vector
        int s: puzzle size
        int r: row size
Output: std::vector< std::vector<int> > possible_moves: vector containing all the unique valid states that can be reached from the input state
        Returns an empty vector if no unique valid states can be reached
*/
std::vector< std::vector<int> > get_possible_moves (std::vector<int> p, int s, int r){
    std::vector< std::vector<int> > possible_moves;
    std::vector<int> temp_move{-1};
    int current_depth = p[s] + 1;

    p[s] = 0;//ensure depth is zero
    p[s+1] = 0;//ensure heuristic is zero
    explored_nodes.push_back(p);

    //possible operators swap blank space with tile above, below, left, or right of it
    for(int i = 0;i<s;i++){
        if(p[i]==0){
            if(i<((r-1)*r)){
                //not in bottom row
                //swap down
                temp_move = p;

                //i+r
                temp_move[i] = p[i+r];
                temp_move[i+r] = p[i];

                if(!is_duplicate(temp_move,s)){
                    temp_move[s] = current_depth;
                    possible_moves.push_back(temp_move);
                }
            }
            if(r<=i){
                //not in top row
                //swap up
                temp_move = p;

                //i-r
                temp_move[i] = p[i-r];
                temp_move[i-r] = p[i];

                if(!is_duplicate(temp_move,s)){
                    temp_move[s] = current_depth;
                    possible_moves.push_back(temp_move);
                }
            }
            if(i%r<=(r-2)){
                //not in rightmost column
                //swap right
                temp_move = p;

                //i+1
                temp_move[i] = p[i+1];
                temp_move[i+1] = p[i];

                if(!is_duplicate(temp_move,s)){
                    temp_move[s] = current_depth;
                    possible_moves.push_back(temp_move);
                }
            }
            if(i%r>0){
                //not in leftmost column
                //swap left
                temp_move = p;
                
                //i-1
                temp_move[i] = p[i-1];
                temp_move[i-1] = p[i];

                if(!is_duplicate(temp_move,s)){
                    temp_move[s] = current_depth;
                    possible_moves.push_back(temp_move);
                }
            }
            return possible_moves;
        }
    }
    return possible_moves;
}

/*
Description: helper function that determines the returns a vector containing all the unique valid states that can be reached from the input state
Input:  std::vector<int> p: initial state representation vector
        int s: puzzle size
        int r: row size
        std::vector<int> g: goal state representation vector
        int h: heuristic chosen by user
Output: std::vector<int> current_node: will return the goal state once it has been reached
        std::vector<int> no_solution: if there is no possible solution to the puzzle a vector with a single value -1 will be returned
*/
std::vector<int> solve_puzzle(std::vector<int> p, int s, int r, std::vector<int> g, int h){
    std::vector< std::vector<int> > queue;
    std::vector< std::vector<int> > possible_moves;
    std::vector<int> no_solution{ -1 };
    std::vector<int> current_node;
    int temp_depth = 0;
    int temp_h = 0;

    //nodes = MAKE-QUEUE(MAKE_NODE(problem.INITIAL-STATE))
    queue.push_back(p);

    //loop do
    //if EMPTY(nodes) then return "failure"
    while (queue.size() != 0){
        //node = REMOVE-FRONT(nodes)
        current_node = queue.front();
        queue.erase(queue.begin());
        temp_depth = current_node[s];
        temp_h = current_node[s+1];
        current_node[s] = 0;
        current_node[s+1] = 0;
        //if problem.GOAL-TEST(node.STATE) succeeds then return node
        
        if(current_node == g){
            current_node[s] = temp_depth;
            std::cout<<("Solution found!\n");
            print_puzzle(current_node, s, r);
            return current_node;
        }
        if(!is_duplicate(current_node,s)){
            current_node[s] = temp_depth;
            current_node[s+1] = temp_h;
            
            //nodes = QUEUEING-FUNCTION(nodes,EXPAND(node,problem.OPERATORS))
            std::cout<<("The best state to expand with g(n) = ")<<current_node[s]<<(" and h(n) = ")<<current_node[s+1]<<("\n");
            print_puzzle(current_node, s, r);
            std::cout<<("Expanding this state.\n\n");
            num_expanded_nodes++;

            possible_moves = get_possible_moves(current_node,s,r);

            if(possible_moves.size()>0){
                //call given heuristic to add h values to moves in possible_moves
                if(h==2){
                    possible_moves = euclidean_distance(possible_moves, s,r);
                }
                else if(h==3){
                    possible_moves = misplaced_tile(possible_moves, s,r);
                }

                for(int i = 0; i<possible_moves.size();i++){
                    queue.push_back(possible_moves[i]);
                }
                std::sort(queue.begin(),queue.end(), compareVectors);
                if(queue.size()>max_node_count){
                    max_node_count = queue.size();
                }
            }
        }
    }

    std::cout<<("THIS PUZZLE HAS NO SOLUTION.\n");
    return no_solution;
}

int main (){
    char input = ' ';
    std::cout<<("Would you like to enter a puzzle to be solved? Y or N? \n");
    std::cin>>(input);

    //get user puzzle
    if(input=='Y'){
        std::cout<<("Please enter the puzzle you would like solved using 0 to represent the blank space: \n");
        int input = 0;
        puzzle.clear();
        for(int i = 0;i<puzzle_size;i++){
            std::cin>>(input);
            puzzle.push_back(input);
        }
    }

    std::cout<<("Puzzle to be solved: \n");
    print_puzzle(puzzle,puzzle_size,row_size);

    puzzle.push_back(0);//represents initial depth 
    puzzle.push_back(0);//represents initial h value
    goal_state.push_back(0);//set to zero to make comparisons easier 
    goal_state.push_back(0);//set to zero to make comparisons easier

    int h_input = 0;
    std::cout<<("1. Uniform Cost Search \n2. Euclidean Distance \n3. Misplaced Tile \n Please enter the number of the heuristic would you like to use:\n ");
    std::cin>>(h_input);

    std::vector<int> goal_node = solve_puzzle(puzzle, puzzle_size, row_size, goal_state, h_input);
    
    //output stats
    std::cout <<"\nHeuristic used: ";
    if(h_input==1){
        std::cout <<"Uniform Cost\n\n";
    }
    else if(h_input==2){
        std::cout <<"Euclidean Distance\n\n";
    }
    else if(h_input==3){
        std::cout <<"Misplaced Tile\n\n";
    }
    std::cout<<("To solve this problem the search algorithm expanded a total of ") << (num_expanded_nodes) << (" nodes. \n \n");
    std::cout<<("The maximum number of nodes in the queue at any one time was: ") << (max_node_count) << (".\n \n");
    if(goal_node[0]!= -1){//if puzzle was solved display depth of goal node
        std::cout<<("The depth of the goal node was: ") << (goal_node[puzzle_size]) << (".\n \n");
    }
    return 0;
}