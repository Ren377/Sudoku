/*
 *  sudoku.h
 *  Sudoku
 *  Created by Renren Deng
 *  Inspired by: http://web.eecs.utk.edu/courses/spring2012/cs140/Notes/Sudoku/index.html
 *  Renren Deng, NetID: renrend2
 */

#ifndef sudoku
#define sudoku

#include <vector>
#include <fstream>
using std::vector;
using namespace std;
class Sudoku
{
    // Private
    int puzzle[9][9];
    
    // Private member function that checks if the named row is valid
    bool row_valid(int row)
    {
        // code that checks if "row" is valid
        bool valid = true;
        
        for (int i = 0; i < 9-1; i++)
        {
            for (int j = i + 1; j < 9; j++)
            {
                if (puzzle[row][i] == puzzle[row][j] && puzzle[row][i] != 0 && puzzle[row][j] != 0)
                    valid = false;
            }
        }
        return valid;
    }
    
    // Private member function that checks if the named column is valid
    bool col_valid(int col)
    {
        // check validity of "col"
        bool valid = true;
        
        for (int i = 0; i < 9-1; i++)
        {
            for (int j = i + 1; j < 9; j ++)
            {
                if (puzzle[i][col] == puzzle[j][col] && puzzle[i][col] != 0 && puzzle[j][col] != 0)
                    valid = false;
            }
        }
        return valid;
    }
    
    // Private member function that checks if the named 3x3 block is valid
    bool block_valid(int row, int col)
    {
        // check 3 x 3 block validity
        bool valid = true;
        int n = row/3;
        int m = col/3;
        for(int i = n * 3; i < (n * 3 + 3); i++)
        {
            for(int j = m * 3; j < (m * 3 + 3); j++)
            {
                if(row != i || col != j)
                {
                    if(puzzle[row][col]==puzzle[i][j] && puzzle[i][j] != 0)
                        valid = false;
                }
            }
        }
        return valid;
    }
    
public:

    void read_puzzle(int argc, char * const argv[])
    {
        // write code that reads the input puzzle using the
        // guidelines of figure 23 of the bootcamp material
        
        int read_file;
        vector <int> P;
        
        ifstream input_file ("argc");
        
        if (input_file.is_open())
        {
            while (input_file >> read_file)
            {
                P.push_back(read_file);
            }
        }
        else
            cout << "Input_file_does_not_exist_in_PWD" <<endl;
        
        int p = 0;
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                puzzle[i][j] = P[p];
                p = p + 1;
            }
        }
    
        
    }
    
    // Public member function that prints the puzzle when called
    void print_puzzle()
    {
        std::cout << std::endl << "Board Position" << std::endl;
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                // check if we have a legitimate integer between 1 and 9
                if ((puzzle[i][j] >= 1) && (puzzle[i][j] <= 9))
                {
                    // printing initial value of the puzzle with some formatting
                    std::cout << puzzle[i][j] << " ";
                }
                else {
                    // printing initial value of the puzzle with some formatting
                    std::cout << "X ";
                }
            }
            std::cout << std::endl;
        }
    }
    
    // Public member function that (recursively) implements the brute-force
    // search for possible solutions to the incomplete Sudoku puzzle
    
    bool Solve(int row, int col)
    { // check and store empty spot
        
         // count solution numbers
        
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (puzzle[i][j] == 0)
                { // store the spot
                    row = i;
                    col = j;
                    goto stop1; // break out the loop when find an empty spot
                }
            }
        }
        
        //no more avalible spot
        static int solution = 1;
        cout << "Solution " << solution;
        print_puzzle();
        solution ++;
        return true;

        
    stop1:
        for (int k = 1; k < 10; k++)
        {
            puzzle[row][col] = k;
            if (row_valid(row) && col_valid(col) && block_valid(row,col))
            {
                Solve(row,col); // delete "return" keep finding more solution by trying other k.
                 /*return true;*/
            }
        }
        puzzle[row][col] = 0; // make it zero after all attempting k.
        return false;
    }
    
};

#endif

