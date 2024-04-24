//TBD: 
//      - implement heuristics

#include <iostream>
#include <vector>
#include <chrono>

//only need to change lines 9-19 to suit any sliding puzzle where row size > 1
const int puzzle_size = 9;
const int row_size = 3;

std::vector<int> goal_state{ 1, 2, 3, 4, 5, 6, 7, 8, 0 };
//uncomment puzzle to make it the default
//std::vector<int> puzzle{ 1, 2, 3, 4, 5, 6, 7, 8, 0 };//Trivial
//std::vector<int> puzzle{ 1, 2, 3, 4, 5, 6, 7, 0, 8 };//Very easy
//std::vector<int> puzzle{ 1, 2, 0, 4, 5, 3, 7, 8, 6 };//Easy
//std::vector<int> puzzle{ 0, 1, 2, 4, 5, 3, 7, 8, 6 };//Doable
//std::vector<int> puzzle{ 8, 7, 1, 6, 0, 2, 5, 4, 3 };//Oh boy
std::vector<int> puzzle{ 1, 2, 3, 4, 5, 6, 8, 7, 0 };//Impossible


int max_node_count = 0;
int num_expanded_nodes = 0;
int max_node_depth = 0;
std::vector< std::vector<int> > explored_nodes;

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
    std::cout<<("\n");
}

bool is_duplicate(std::vector<int> p, int s){
    p[s] = 0;
    for(int i = 0; i < explored_nodes.size();i++){
        if(p == explored_nodes[i]){
            return true;
        }
    }
    return false;
}

std::vector< std::vector<int> > uniform_cost_search(std::vector<int> p, int s, int r, std::vector<int> g){
    std::vector< std::vector<int> > ordered_moves;
    return ordered_moves;
}

std::vector< std::vector<int> > manhattan_distance(std::vector<int> p, int s, int r, std::vector<int> g){
    std::vector< std::vector<int> > ordered_moves;
    return ordered_moves;
}

std::vector< std::vector<int> > misplaced_tile(std::vector<int> p, int s, int r, std::vector<int> g){
    std::vector< std::vector<int> > ordered_moves;
    return ordered_moves;
}

std::vector< std::vector<int> > get_possible_moves (std::vector<int> p, int s, int r){
    std::vector< std::vector<int> > possible_moves;
    std::vector<int> temp_move{-1};
    int current_depth = p[s] + 1;

    p[s] = 0;
    if(current_depth > max_node_depth){
        max_node_depth = current_depth;
    }
    explored_nodes.push_back(p);

    //possible operators swap blank space with tile above, below, left, or right of it
    for(int i = 0;i<s;i++){
        if(p[i]==0){
            if(i<((r-1)*r)){
                //not in bottom row
                //swap down
                temp_move = p;
                temp_move[s] = current_depth;
                //i+r
                temp_move[i] = p[i+r];
                temp_move[i+r] = p[i];
                possible_moves.push_back(temp_move);
            }
            if(r<=i){
                //not in top row
                //swap up
                temp_move = p;
                temp_move[s] = current_depth;
                //i-r
                temp_move[i] = p[i-r];
                temp_move[i-r] = p[i];
                possible_moves.push_back(temp_move);
            }
            if(i%r<=(r-2)){
                //not in rightmost column
                //swap right
                temp_move = p;
                temp_move[s] = current_depth;
                //i+1
                temp_move[i] = p[i+1];
                temp_move[i+1] = p[i];
                possible_moves.push_back(temp_move);
            }
            if(i%r>0){
                //not in leftmost column
                //swap left
                temp_move = p;
                temp_move[s] = current_depth;
                //i-1
                temp_move[i] = p[i-1];
                temp_move[i-1] = p[i];
                possible_moves.push_back(temp_move);
            }
            return possible_moves;
        }
    }

    possible_moves.push_back(temp_move);
    return possible_moves;
}

std::vector<int> solve_puzzle(std::vector<int> p, int s, int r, std::vector<int> g){
    std::vector< std::vector<int> > queue;
    std::vector< std::vector<int> > possible_moves;
    std::vector<int> no_solution{ -1 };
    std::vector<int> current_node;
    int temp_depth = 0;

    //nodes = MAKE-QUEUE(MAKE_NODE(problem.INITIAL-STATE))
    queue.push_back(p);

    //loop do
    //if EMPTY(nodes) then return "failure"
    while (queue.size() != 0){
        //node = REMOVE-FRONT(nodes)
        current_node = queue.front();
        queue.erase(queue.begin());
        temp_depth = current_node[s];
        current_node[s] = 0;

        //if problem.GOAL-TEST(node.STATE) succeeds then return node
        if(current_node == g){
            current_node[s] = temp_depth;
            std::cout<<("Solution found!\n");
            print_puzzle(current_node, s, r);
            return current_node;
        }
        current_node[s] = temp_depth;

        if(!is_duplicate(current_node,s)){
            //nodes = QUEUEING-FUNCTION(nodes,EXPAND(node,problem.OPERATORS))
            std::cout<<("Expanding State: \n");
            print_puzzle(current_node, s, r);
            num_expanded_nodes++;
            possible_moves = get_possible_moves(current_node,s,r);
            for(int i = 0; i<possible_moves.size();i++){
                queue.push_back(possible_moves[i]);
            }
            if(queue.size()>max_node_count){
                max_node_count = queue.size();
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
    puzzle.push_back(0);//represents initial depth 
    goal_state.push_back(0);//set to zero to make comparisons easier 

    std::cout<<("Puzzle to be solved: \n");
    print_puzzle(puzzle,puzzle_size,row_size);


    //start timer
    std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();

    std::vector<int> goal_node = solve_puzzle(puzzle, puzzle_size, row_size, goal_state);
    
    //stop timer 
    std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();
    std::chrono::microseconds elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    //output stats
    std::cout << ("Elapsed time: ") << elapsed_time.count() <<(" micro seconds. \n\n");
    std::cout<<("To solve this problem the search algorithm expanded a total of ") << (num_expanded_nodes) << (" nodes. \n \n");
    std::cout<<("The maximum number of nodes in the queue at any one time was: ") << (max_node_count) << (".\n \n");
    if(goal_node[0]!= -1){
        std::cout<<("The depth of the goal node was: ") << (goal_node[puzzle_size]) << (".\n \n");
    }
    std::cout<<("The maximum depth reached was: ") << (max_node_depth) << (".\n \n");
    return 0;
}