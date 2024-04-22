//TBD: 
//      - implement get_possible_moves
//      - allow user to enter puzzle
//      - implement heuristics


#include <iostream>
#include <vector>

const int puzzle_size = 9;
const int row_size = 3;
const std::vector<int> goal_state = {1,2,3,4,5,6,7,8,0};
std::vector<int> puzzle = {1,2,3,4,5,6,7,0,8};

std::vector<std::vector<int>> get_possible_moves (std::vector<int> p){
    std::vector<std::vector<int>> possible_moves;
    //get possible moves 
    return possible_moves;
}

void solve_puzzle(std::vector<int> p ){
    std::vector<std::vector<int>> queue;
    queue.push_back(p);
    std::vector<int> current_node;
    while (queue.size() != 0){
        current_node = queue.front();
        queue.erase(queue.begin());
        print_puzzle(current_node, puzzle_size, row_size);
        if(current_node == goal_state){
            std::cout<<("Solution found!\n");
            return;
        }
        std::cout<<("Expanding State: \n");
        std::vector<std::vector<int>> possible_moves = get_possible_moves(current_node);
        for(int i = 0; i<possible_moves.size();i++){
            queue.push_back(possible_moves[i]);
        }
    }
    std::cout<<("This puzzle has no solution.\n");
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
}

int main (){
    char input = ' ';
    std::cout<<("Would you like to enter a puzzle to be solved? Y or N?\n");
    std::cin>>(input);
    if(input=='Y'){
        std::cout<<("Please enter the puzzle you would like solved using 0 to represent the blank space\n");
        //get user input and store in puzzle
    }
    print_puzzle(puzzle,puzzle_size,row_size);
    return 0;
}