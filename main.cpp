/*TBD: 
- Bug fix heuristics
- Document functions
*/      

#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm> 

//only need to change lines 14-19 to suit any sliding puzzle where row size > 1
const int puzzle_size = 9;
const int row_size = 3;

std::vector<int> goal_state{ 1, 2, 3, 4, 5, 6, 7, 8, 0 };
//uncomment puzzle to make it the default
//std::vector<int> puzzle{ 1, 2, 3, 4, 5, 6, 7, 8, 0 };//Trivial
//std::vector<int> puzzle{ 1, 2, 3, 4, 5, 6, 7, 0, 8 };//Very easy
//std::vector<int> puzzle{ 1, 2, 0, 4, 5, 3, 7, 8, 6 };//Easy
std::vector<int> puzzle{ 0, 1, 2, 4, 5, 3, 7, 8, 6 };//Doable
//std::vector<int> puzzle{ 8, 7, 1, 6, 0, 2, 5, 4, 3 };//Oh boy
//std::vector<int> puzzle{ 1, 2, 3, 4, 5, 6, 8, 7, 0 };//Impossible


int max_node_count = 0;
int num_expanded_nodes = 0;
int max_node_depth = 0;
std::vector< std::vector<int> > explored_nodes;

bool compareVectors(const std::vector<int>& a, const std::vector<int>& b){
    return (a[puzzle_size] + a[puzzle_size+1])<(b[puzzle_size] + b[puzzle_size+1]);
}

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

void print_queue(std::vector< std::vector<int> > p, int s, int r){
    std::cout<<("Queue contains: \n");
    for(int i = 0; i<p.size();i++ ){
        print_puzzle(p.at(i), s+2, r);
    }
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

std::vector< std::vector<int> > uniform_cost_search(std::vector< std::vector<int> > p, int s, int r){
    //since depth = cost in this case and depth is already assigned we dont need to do anything to the list of moves
    return p;
}

std::vector< std::vector<int> > euclidean_distance(std::vector< std::vector<int> > p, int s, int r){
    int d = 2 * r - 2;//maximum distance
    int j = 0;
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
            if(i == j){
                break;
            }
            for(int k = 1; k <= d; k++){
                if((i==j+k)||(i==j-k)||(i==j-r-(k-1))||(i==j+r+(k-1))){
                    h += k;
                    break;
                }
            }
        }
        p.at(a).at(s+1) = h;//set heuristic value to h
        j = 0;
        h = 0;
    }
    return p;
}

std::vector< std::vector<int> > misplaced_tile(std::vector< std::vector<int> > p, int s, int r){
    int j = 0;
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

std::vector< std::vector<int> > get_possible_moves (std::vector<int> p, int s, int r){
    std::vector< std::vector<int> > possible_moves;
    std::vector<int> temp_move{-1};
    int current_depth = p[s] + 1;

    p[s] = 0;
    p[s+1] = 0;
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
        current_node[s] = temp_depth;
        current_node[s+1] = temp_h;

        //nodes = QUEUEING-FUNCTION(nodes,EXPAND(node,problem.OPERATORS))
        std::cout<<("The best state to expand with g(n) = ")<<current_node[s]<<(" and h(n) = ")<<current_node[s+1]<<("\n");
        print_puzzle(current_node, s, r);
        std::cout<<("Expanding this state: \n");
        num_expanded_nodes++;
        possible_moves = get_possible_moves(current_node,s,r);
        if(possible_moves.size()>0){
            //call given heuristic to add h values to moves in possible_moves
            if(h==1){
                possible_moves = uniform_cost_search(possible_moves, s, r);
            }
            else if(h==2){
                possible_moves = euclidean_distance(possible_moves, s,r);
            }
            else{
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

    std::cout<<("THIS PUZZLE HAS NO SOLUTION.\n");
    return no_solution;
}

int main (){
    int (*func)(std::vector< std::vector<int> > , int , int);//function pointer to represent heuristic function to be called
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

    //start timer
    std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();

    std::vector<int> goal_node = solve_puzzle(puzzle, puzzle_size, row_size, goal_state, h_input);
    
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