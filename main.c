/*
* CS 355 Final Project
* Luigi Game - Version 1
* Made by Jhaelin Thomas and Tim Gairing
* Main Functions: Manual movement, jumping, obstacles, stars, invincibility and castle ending
*/
#include <ncurses.h>
#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
// Main Function: Starts Game and Handles Movement
int main() { 

    int luigiX = 10; //Horizontal position
    int key;         // Stores Keyboard Input
    int maxY, maxX;  // Stores Terminal width
    
    initscr();        // Initializes the ncurses screen
    noecho();        // Prevents typed keys from appearing on the screen
    keypad(stdscr, True); // Enables special keyboard keys such as arrow keys
    
    printw("ITS a ME MAR- You mean Luigi."); 
    refresh();
    getch();

    While (1) {

        clear();
        getmaxyx(stdscr, maxY, maxX); //Gets current terminal height and width
        mvprintw(0, 0, "A: Left | D: Right | Q: Quit");    //Displays Movement Instructions
        mvprintw(5, luigiX, "L");    //Displays Luigi at his current horizontal position
        refresh();    //Updates screen display
        key = getch();
        if (key == 'a' || key == 'A'){
            if (luigiX > 0) {    // Makes sure Luigi does not move past the left boundary
                luigiX--;     // Moves Luigi one position to the left
            }
        }
        if (key == 'd' || key == 'D') {
            if (luigiX < maxX - 1) {    //Makes sure boundary was not crossed
                luigiX++;    // Moves Luigi one position to the right
            }
        }
    if (key == 'q' || key == 'Q') {
        break;    //Exits Game
        }
    }
        
    endwin();

    return 0;
}
