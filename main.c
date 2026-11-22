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

int main() { 

    initscr();
    
    printw("ITS a ME MAR- You mean Luigi."); 

    refresh();
    getch();
    
    endwin();

    return 0;
}
