//TBD: 
//      - implement get_possible_moves better
//      - implement heuristics


#include <iostream>
#include <vector>
#include <chrono>

const int puzzle_size = 9;
const int row_size = 3;
int max_node_count = 0;
int num_expanded_nodes = 0;
int max_node_depth = 0;

//last digit represents node depth 
const std::vector<int> goal_state{ 1, 2, 3, 4, 5, 6, 7, 8, 0, 0 };
std::vector<int> puzzle{ 1, 2, 3, 4, 5, 6, 7, 8, 0, 0 };//Trivial
//std::vector<int> puzzle{ 1, 2, 3, 4, 5, 6, 7, 0, 8, 0 };//Very easy
//std::vector<int> puzzle{ 1, 2, 0, 4, 5, 3, 7, 8, 6, 0 };//Easy
//std::vector<int> puzzle{ 0, 1, 2, 4, 5, 3, 7, 8, 6, 0 };//Doable
//std::vector<int> puzzle{ 8, 7, 1, 6, 0, 2, 5, 4, 3, 0 };//Oh boy
//std::vector<int> puzzle{ 1, 2, 3, 4, 5, 6, 8, 7, 0, 0 };//Impossible

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

bool is_duplicate(std::vector<int> p){
    p[puzzle_size] = 0;
    for(int i = 0; i < explored_nodes.size();i++){
        if(p == explored_nodes[i]){
            return true;
        }
    }
    return false;
}

std::vector< std::vector<int> > get_possible_moves (std::vector<int> p){
    std::vector< std::vector<int> > possible_moves;
    std::vector<int> temp_move;
    int current_depth = p[puzzle_size] + 1;
    p[puzzle_size] = 0;
    if(current_depth > max_node_depth){
        max_node_depth = current_depth;
    }
    explored_nodes.push_back(p);
    //get possible moves 
    //possible operators swap blank space with tile above, below, left, or right of it
    //hard coded solution fix to something better
    if(p[0] == 0){
        temp_move = p;
        temp_move[9] = current_depth;
        //swap right
        temp_move[0] = p[1]; 
        temp_move[1] = p[0];
        possible_moves.push_back(temp_move);
        temp_move = p;
        temp_move[9] = current_depth;
        //swap down
        temp_move[0] = p[3]; 
        temp_move[3] = p[0];
        possible_moves.push_back(temp_move);
    }
    else if(p[1] == 0){
        temp_move = p;
        temp_move[9] = current_depth;
        //swap left
        temp_move[1] = p[0];
        temp_move[0] = p[1];
        possible_moves.push_back(temp_move);
        temp_move = p;
        temp_move[9] = current_depth;
        //swap right
        temp_move[1] = p[2];
        temp_move[2] = p[1];
        possible_moves.push_back(temp_move);
        temp_move = p;
        temp_move[9] = current_depth;
        //swap down
        temp_move[1] = p[4];
        temp_move[4] = p[1];
        possible_moves.push_back(temp_move);
    }
    else if(p[2] == 0){
        temp_move = p;
        temp_move[9] = current_depth;
        //swap left
        temp_move[2] = p[1];
        temp_move[1] = p[2];
        possible_moves.push_back(temp_move);
        temp_move = p;
        temp_move[9] = current_depth;
        //swap down
        temp_move[2] = p[5];
        temp_move[5] = p[2];
        possible_moves.push_back(temp_move);
    }
    else if(p[3] == 0){
        temp_move = p;
        temp_move[9] = current_depth;
        //swap right
        temp_move[3] = p[4];
        temp_move[4] = p[3];
        possible_moves.push_back(temp_move);
        temp_move = p;
        temp_move[9] = current_depth;
        //swap up
        temp_move[3] = p[0];
        temp_move[0] = p[3];
        possible_moves.push_back(temp_move);
        temp_move = p;
        temp_move[9] = current_depth;
        //swap down
        temp_move[3] = p[6];
        temp_move[6] = p[3];
        possible_moves.push_back(temp_move);
    }
    else if(p[4] == 0){
        temp_move = p;
        temp_move[9] = current_depth;
        //swap left
        temp_move[4] = p[3];
        temp_move[3] = p[4];
        possible_moves.push_back(temp_move);
        temp_move = p;
        temp_move[9] = current_depth;
        //swap right
        temp_move[4] = p[5];
        temp_move[5] = p[4];
        possible_moves.push_back(temp_move);
        temp_move = p;
        temp_move[9] = current_depth;
        //swap up
        temp_move[4] = p[1];
        temp_move[1] = p[4];
        possible_moves.push_back(temp_move);
        temp_move = p;
        temp_move[9] = current_depth;
        //swap down
        temp_move[4] = p[7];
        temp_move[7] = p[4];
        possible_moves.push_back(temp_move);
    }
    else if(p[5] == 0){
        temp_move = p;
        temp_move[9] = current_depth;
        //swap left
        temp_move[5] = p[4];
        temp_move[4] = p[5];
        possible_moves.push_back(temp_move);
        temp_move = p;
        temp_move[9] = current_depth;
        //swap up
        temp_move[5] = p[2];
        temp_move[2] = p[5];
        possible_moves.push_back(temp_move);
        temp_move = p;
        temp_move[9] = current_depth;
        //swap down
        temp_move[5] = p[8];
        temp_move[8] = p[5];
        possible_moves.push_back(temp_move);
    }
    else if(p[6] == 0){
        temp_move = p;
        temp_move[9] = current_depth;
        //swap right
        temp_move[6] = p[7];
        temp_move[7] = p[6];
        possible_moves.push_back(temp_move);
        temp_move = p;
        temp_move[9] = current_depth;
        //swap up
        temp_move[6] = p[3];
        temp_move[3] = p[6];
        possible_moves.push_back(temp_move);
    }
    else if(p[7] == 0){
        temp_move = p;
        temp_move[9] = current_depth;
        //swap left
        temp_move[7] = p[6];
        temp_move[6] = p[7];
        possible_moves.push_back(temp_move);
        temp_move = p;
        temp_move[9] = current_depth;
        //swap right
        temp_move[7] = p[8];
        temp_move[8] = p[7];
        possible_moves.push_back(temp_move);
        temp_move = p;
        temp_move[9] = current_depth;
        //swap up
        temp_move[7] = p[4];
        temp_move[4] = p[7];
        possible_moves.push_back(temp_move);
    }
    else{//p[8] == 0
        temp_move = p;
        temp_move[9] = current_depth;
        //swap left
        temp_move[8] = p[7];
        temp_move[7] = p[8];
        possible_moves.push_back(temp_move);
        temp_move = p;
        temp_move[9] = current_depth;
        //swap up
        temp_move[8] = p[5];
        temp_move[5] = p[8];
        possible_moves.push_back(temp_move);
    }
    return possible_moves;
}

std::vector<int> solve_puzzle(std::vector<int> p ){
    std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
    std::vector<int> no_solution{ -1 };
    std::vector< std::vector<int> > queue;
    std::vector< std::vector<int> > possible_moves;
    explored_nodes.clear();
    queue.push_back(p);
    std::vector<int> current_node;
    int temp_depth = 0;
    while (queue.size() != 0){
        current_node = queue.front();
        queue.erase(queue.begin());
        temp_depth = current_node[puzzle_size];
        current_node[puzzle_size] = 0;
        if(current_node == goal_state){
            current_node[puzzle_size] = temp_depth;
            std::cout<<("Solution found!\n");
            print_puzzle(current_node, puzzle_size, row_size);
            std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();
            std::chrono::microseconds elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
            std::cout << "Elapsed time: " << elapsed_time.count() << " micro seconds" << std::endl;
            
            return current_node;
        }
        current_node[puzzle_size] = temp_depth;
        if(!is_duplicate(current_node)){
            std::cout<<("Expanding State: \n");
            print_puzzle(current_node, puzzle_size, row_size);
            num_expanded_nodes++;
            possible_moves = get_possible_moves(current_node);
            for(int i = 0; i<possible_moves.size();i++){
                queue.push_back(possible_moves[i]);
            }
            if(queue.size()>max_node_count){
                max_node_count = queue.size();
            }
        }
    }
    std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();
    std::chrono::microseconds elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Elapsed time: " << elapsed_time.count()/1000000 << " seconds" << std::endl;
    
    std::cout<<("THIS PUZZLE HAS NO SOLUTION.\n");
    return no_solution;
}

int main (){
    char input = ' ';
    std::cout<<("Would you like to enter a puzzle to be solved? Y or N?\n");
    std::cin>>(input);
    if(input=='Y'){
        std::cout<<("Please enter the puzzle you would like solved using 0 to represent the blank space\n");
        int input = 0;
        puzzle.clear();
        for(int i = 0;i<puzzle_size;i++){
            std::cin>>(input);
            puzzle.push_back(input);
        }
        puzzle.push_back(0);
    }
    std::cout<<("Puzzle to be solved: \n");
    print_puzzle(puzzle,puzzle_size,row_size);
    std::vector<int> goal_node = solve_puzzle(puzzle);
    //output stats
    std::cout<<("To solve this problem the search algorithm expanded a total of ");
    std::cout<<(num_expanded_nodes);
    std::cout<<(" nodes. \n \n");
    std::cout<<("The maximum number of nodes in the queue at any one time was: ");
    std::cout<<(max_node_count);
    std::cout<<(".\n \n");
    if(goal_node[0]!= -1){
        std::cout<<("The depth of the goal node was: ");
        std::cout<<(goal_node[puzzle_size]);
        std::cout<<(".\n \n");
    }
    std::cout<<("The maximum depth reached was: ");
    std::cout<<(max_node_depth);
    std::cout<<(".\n \n");
    return 0;
}