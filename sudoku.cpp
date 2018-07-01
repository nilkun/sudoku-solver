/*
**  SUDOKU SOLVER
**  by nilkun
*/

#include <set>
#include <iostream>

bool isAvailable(int matrix[][9], int number, int row, int column);
bool hasSolution(int matrix[][9], int row, int column);
void print(); // Prints the solution to the screen

// Enter puzzle to solve
int matrix[9][9] =  {   
                        { 0, 0, 0,     0, 0, 0,    0, 0, 0 },
                        { 0, 0, 0,     0, 0, 0,    0, 0, 0 },
                        { 0, 0, 0,     0, 0, 0,    0, 0, 0 },
                        
                        { 0, 0, 0,     0, 0, 0,    0, 0, 0 },
                        { 0, 0, 0,     0, 0, 0,    0, 0, 0 },
                        { 0, 0, 0,     0, 0, 0,    0, 0, 0 },

                        { 0, 0, 0,     0, 0, 0,    0, 0, 0 },
                        { 0, 0, 0,     0, 0, 0,    0, 0, 0 },
                        { 0, 0, 0,     0, 0, 8,    0, 0, 0 } 
                    };

int main() 
{
    hasSolution(matrix, 0, 0);
    print();
    return 1;
}

bool isAvailable(int matrix[][9], int number, int row, int column)
{
    for(int i = 0; i<9; i++)
    {
        // check if number exists in row or column
        if ((matrix[row][i]==number) || matrix[i][column]==number) return false;

    }
    // normalize to sector
    int row_sector = row / 3;
    int column_sector = column / 3;

    // Check the sector
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++) if(matrix[(row_sector*3) + i][(column_sector*3) + j] == number) return false;
    }
    return true;

}

bool hasSolution(int matrix[][9], int row, int column)
{
    if(row==9) return true; // end of recursion

    if(matrix[row][column]!=0) // if square already has number, then skip
    {
        if(column==8) 
        {
            if(hasSolution(matrix, row+1, 0)) return true;
        }
        else if(hasSolution(matrix, row, column+1)) return true;
    }
    // if square has no number, then recurse
    else
    {
        for(int i = 1; i<10; i++)
        {
            if(isAvailable(matrix, i, row, column))
            {
                matrix[row][column] = i;

                if(column==8) 
                {
                    if(hasSolution(matrix, row+1, 0)) return true;
                }
                else if(hasSolution(matrix, row, column+1)) return true;

                // reset if number is wrong    
                matrix[row][column] = 0;
            }
        }
    }
    return false;
}


// PRINTS OUT THE SOLUTION IN BEAUTIFUL ASCII
void print() 
{
    std::cout << "-----------------------------" << std::endl;
    for(int i=0; i<9; ++i) 
    {   
        std::cout << std::endl;
        for(int j=0; j<9; ++j)
        {
            std::cout << " ";

            if(matrix[i][j]==0) std::cout << " ";
            else std::cout << matrix[i][j]; 
            
            std::cout << " ";
            if(j == 2 || j==5) std::cout << "|";
        }
        std::cout << std::endl;
        if(i==2 || i==5) std::cout << "-----------------------------" << std::endl;        
    }
    std::cout << "-----------------------------" << std::endl;
}

