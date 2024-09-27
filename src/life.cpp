#include <iostream>
#include "grid.h"
#include "lifeutil.h"
#include <string>
#include<fstream>
using namespace std;

/* Reads in a file from input and returns an empty Grid structure
 */
Grid<char> readAFileAndGenerateGrid();

/* Displays a text and reads an input a / t / q
 * Returns the inputted char
 */
char getCommand();

/* Calculate next generation of bacteria
 * Creates temporary (new) grid, adds all changes to that grid,
 * then writes the new grid to the old grid
 * Also outputs the updated grid
 */
void tick(Grid<char> &grid);

/* Plays 20 generations forward and waits 1 second between each new generation
 * before outputting
 */
void animate(Grid<char> &grid);

/* Returns the amount of neighbours for a given x, y coordinate in the grid
 */
int getNeighbours(const Grid<char> &grid, int x, int y);

/* Will be called if the current cell being analyzed has 0-1 or 4+ neighbours
 * NOTE: Since both 0-1 and 4+ rules are the same (always set cell to empty), we can call the same function
 */
void zeroOneFourMoreNeighbours( Grid<char> &newGrid, int x, int y);

/* Will be called if the current cell being analyzed has 2 neighbours
 * Applies the appropriate rule
 */
void twoNeighbours( Grid<char> &newGrid, int x, int y, char currentCell);

/* Will be called if the current cell being analyzed has 3 neighbours
 * Applies the appropriate rule
 */
void threeNeighbours( Grid<char> &newGrid, int x, int y);

/* Oututs a string on the format provided by Grid.toString()
 */
void printGrid(const Grid<char> &grid);


int main() {

    // Create main grid
    Grid<char> grid = readAFileAndGenerateGrid();

    while (true) {

        char input = getCommand();

        if (input == 't') {
            tick(grid);
        } else if (input == 'a') {
            animate(grid);
        } else if (input == 'q') {
            cout << "Have a nice life!" << endl;
            break;
        }
    }

    return 0;
}

Grid<char> readAFileAndGenerateGrid(){

    // Get a file name from input
    string file_name;
    cout << "give a file name: ";
    getline(cin, file_name);

    // Open file
    ifstream fin(file_name.c_str());

    // Read line by line
    string line;
    string rows;
    string columns;
    string board;

    // The first two lines are always the rows and columns
    // Read those and store in variables
    getline(fin, rows);
    getline(fin, columns);

    // Convert rows/columns from string to int type
    int gridRows = stoi(rows);
    int gridCols = stoi(columns);

    // Read each line of the rest of the file
    while(getline(fin, line)){

        // If a line begins with #, it is a comment. Ignore it
        if ( line[0] == '#') {
            continue;
        }
        board += line;
    }
    // Create a grid object
    Grid<char> matrix(gridRows, gridCols);
    int i = 0;

    // For every cell in the grid, add the corresponding
    // item we got from the input file
    for (int x = 0; x < gridRows; x++) {
        for(int y = 0; y < gridCols; y++){
            matrix.set(x,y,board[i]);
            i++;
        }
    }

    // Output the base file
    printGrid(matrix);

    return matrix;
}

char getCommand(){
    char command;
    cout << "a)nimate, t)ick, q)uit? ";
    cin >> command;
    return command;
}

void tick(Grid<char> &grid){
    // Create a temporaly grid
    Grid<char> tempGrid(grid.numRows(), grid.numCols());

    // MAIN IDEA: Iterate through each cell and calculate if the current cell should
    // or should not have a bacteria. Write the result to the temp grid.
    for(int x = 0; x < grid.numRows(); x++){
        for(int y = 0; y < grid.numCols(); y++){

            int numNeighbours = getNeighbours(grid,x,y);

            if (numNeighbours == 0 || numNeighbours == 1 || numNeighbours >=4) {
                zeroOneFourMoreNeighbours(tempGrid, x, y);

            } else if (numNeighbours == 2) {
                char currentCell = grid.get(x, y);
                twoNeighbours(tempGrid, x, y, currentCell);

            } else if (numNeighbours == 3) {
                threeNeighbours(tempGrid, x, y);
            }
        }
    }

    // Write tempGrid to grid
    grid = tempGrid;

    // Output the new grid
    printGrid(grid);

}

void animate(Grid<char> &grid) {

    // Call tick 20 times and wait 1 second
    for (int i = 0; i < 20; i++) {
        tick(grid);
        pause(1000);
        cout << endl;
    }

}

int getNeighbours(const Grid<char> &grid, int x, int y){
    int numNeighbours = 0;

    // Check for each cell around the current one.
    // Add 1 to variable if there is a bacteria there
    if(grid.inBounds(x+1, y)){
        char cell = grid.get(x+1,y);
        if (cell == 'X')
            numNeighbours++;
    }

    if(grid.inBounds(x+1, y+1)){
        char cell = grid.get(x+1,y+1);
        if (cell == 'X')
            numNeighbours++;
    }

    if(grid.inBounds(x, y+1)){
        char cell = grid.get(x,y+1);
        if (cell == 'X')
            numNeighbours++;
    }

    if(grid.inBounds(x, y-1)){
        char cell = grid.get(x,y-1);
        if (cell == 'X')
            numNeighbours++;
    }

    if(grid.inBounds(x-1, y-1)){
        char cell = grid.get(x-1,y-1);
        if (cell == 'X')
            numNeighbours++;
    }

    if(grid.inBounds(x-1, y)){
        char cell = grid.get(x-1,y);
        if (cell == 'X')
            numNeighbours++;
    }

    if(grid.inBounds(x-1, y+1)){
        char cell = grid.get(x-1,y+1);
        if (cell == 'X')
            numNeighbours++;
    }

    if(grid.inBounds(x+1, y-1)){
        char cell = grid.get(x+1,y-1);
        if (cell == 'X')
            numNeighbours++;
    }

    return numNeighbours;
}


void zeroOneFourMoreNeighbours(Grid<char> &newGrid, int x, int y){
    newGrid.set(x,y,'-');
}

void twoNeighbours( Grid<char> &newGrid, int x, int y, char currentCell){
    newGrid.set(x, y, currentCell);
}

void threeNeighbours( Grid<char> &newGrid, int x, int y){
    newGrid.set(x, y, 'X');
}

void printGrid(const Grid<char> &grid) {

    string finalString;

    // Go through each cell in the grid and add
    // it to a string builder
    for (int x = 0; x < grid.numRows(); x++) {
        for (int y = 0; y < grid.numCols(); y++) {
            finalString += grid.get(x, y);
        }

        finalString += "\n";
    }

    cout << finalString;
}
