#include <iostream>

void print_puzzle(int p[], int s, int r){
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
    const int puzzle_size = 9;
    int row_size = 3;
    int puzzle[puzzle_size] = {1,2,3,4,5,6,7,0,8};
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