//TBD: 
//      - implement get_possible_moves better
//      - allow user to enter puzzle
//      - implement heuristics


#include <iostream>
#include <vector>

const int puzzle_size = 9;
const int row_size = 3;
int max_node_count = 0;
int num_expanded_nodes = 0;
//last digit represents node depth 
const std::vector<int> goal_state{ 1, 2, 3, 4, 5, 6, 7, 8, 0, 0 };
std::vector<int> puzzle{ 1, 2, 3, 4, 5, 6, 7, 0, 8, 0 };

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

std::vector< std::vector<int> > get_possible_moves (std::vector<int> p){
    std::vector< std::vector<int> > possible_moves;
    std::vector<int> temp_move;
    int current_depth = p[puzzle_size] + 1;
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
    std::vector< std::vector<int> > queue;
    std::vector< std::vector<int> > possible_moves;
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
            return current_node;
        }
        current_node[puzzle_size] = temp_depth;
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
    std::cout<<("This puzzle has no solution.\n");
    std::vector<int> no_solution{ -1 };
    return no_solution;
}

int main (){
    char input = ' ';
    std::cout<<("Would you like to enter a puzzle to be solved? Y or N?\n");
    std::cin>>(input);
    if(input=='Y'){
        std::cout<<("Please enter the puzzle you would like solved using 0 to represent the blank space\n");
        //get user input and store in puzzle
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
    return 0;
}