# GAME OF LIFE

## About
My first c++ project!

This is a command line version of the game of life coined by John Conway.
The game of life is about bacteria either appearing, living or dying according to a set of rules.

Here are the rules:
1. Any live cell with fewer than two live neighbours dies, as if by underpopulation.
2. Any live cell with two or three live neighbours lives on to the next generation.
3. Any live cell with more than three live neighbours dies, as if by overpopulation.
4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

## Usage
This project was made in Qt Creator and was only tested on Qt Creator.
To run the program optimally, use Qt.

The program will first ask the user for an input file. There are many to choose from, but inputting "simple.txt" will show a basic demonstration.
See the /res/ folder for all available files to choose from.

Then the user can tick the game one step forward, animate 20 ticks ahead, or quit.
