/*
* CS 355 Final Project
* Luigi Game - Version 1
* Made by Jhaelin Thomas and Tim Gairing
* Main Functions: Manual movement, jumping, obstacles, stars, invincibility and castle ending
*/
#define _POSIX_C_SOURCE 199309L
#include <ncurses.h>
#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
// Function: Gets current time in milliseconds.
long long getTimeMs() {
    struct timespec ts; // Stores current time
    clock_gettime(CLOCK_MONOTONIC, &ts);    // Gets elapsed time
    return(long long)ts.tv_sec * 1000 + ts.tv_nsec / 1000000; // Converts time to milliseconds
}
// Function: Loads the saved coin total from a file.
int loadCoins() {
    FILE *file = fopen("coins.txt", "r"); // Opens the coin file for reading
    int coins = 0; // Sets the default coin total to zero
    if (file != NULL) { // Checks whether the file exists
        fscanf(file, "%d", &coins); // Reads the saved coin total
        fclose(file); // Closes the file
    }
    return coins; // Returns the saved coin total
}
// Function: Saves the current coin total to a file.
void saveCoins(int coins) {
    FILE *file = fopen("coins.txt", "w"); // Opens the coin file for writing
    if (file != NULL) { // Checks whether the file opened successfully
        fprintf(file, "%d", coins); // Writes the current coin total
        fclose(file); // Closes the file
    }
}
// Main Function: Starts Game and Handles Movement
int main() { 

    int luigiX = 10;    // Stores Horizontal position
    int luigiY =5;      // Stores Vertical Position
    int groundY = 5;    // Stores Ground Position
    int key;         // Stores Keyboard Input
    int menuChoice; // Stores the main menu selection
    int maxY, maxX;  // Stores Terminal height and width
    int boxX = 20;   // Stores the reward box horizontal position
    int boxY = 4;    // Stores the reward box vertical position
    int coins = loadCoins();   // Loads the player's saved coin total
    bool boxOpened = false; // Tracks whether the reward box has been opened
    bool starPower = false; // Tracks whether Luigi received star power
    long long starStart = 0; // Stores when star power began
    bool jumping = false;   // Tracks wether Luigi is jumping
    long long jumpStart = 0;  // Stores when Luigi began jumping
    long long currentTime;  // Stores current time

    srand(time(NULL)); // Seeds the random number generator

    initscr();        // Initializes the ncurses screen
    noecho();        // Prevents typed keys from appearing on the screen
    keypad(stdscr, TRUE); // Enables special keyboard keys such as arrow keys
    timeout(10000);    // Waits up to 10 seconds for keyboard input

while (1) {     // Main Menu
    clear();    // Clears the screen

    mvprintw(2, 10, "LUIGI GAME");    // Displays game title
    mvprintw(4, 10, "Coins: %d", coins);    // Displays saved coins
    mvprintw(6, 10, "1. Play");    // Play option
    mvprintw(7, 10, "2. Coin Store");    // Coin Store option
    mvprintw(8, 10, "3. Quit");    // Quit option
    mvprintw(10, 10, "Select an option:");    // Prompts user

    refresh();    // Updates screen
    menuChoice = getch();    // Gets menu selection
    if (menuChoice == '3') {
        break;  // Quit the game
    }
    // Coin Store placeholder
    if (menuChoice == '2') {
        clear();    // Clears screen
        mvprintw(5, 10, "COIN STORE");    // Displays store title
        mvprintw(7, 10, "Store coming soon!");    // Placeholder message
        mvprintw(9, 10, "Press any key to return.");    // Return instructions
        refresh();    // Updates screen
        getch();    // Waits for user input
    }
    // Starts the game
    if (menuChoice == '1') {

        // Reset game variables
        luigiX = 10;
        luigiY = groundY;
        jumping = false;
        boxOpened = false;
        starPower = false;
        starStart = 0;
        printw("ITS a ME MAR- You mean Luigi.\n" "(PRESS ANY KEY TO CONTINUE)"); 
        printw("Coins Held: %d\n", coins); // Displays the saved coin total
        refresh();
        getch();

    while (1) {

        currentTime = getTimeMs(); // Gets current real time
        if (jumping && currentTime - jumpStart >= 1000){
            jumping = false;    // Ends Luigi's jump
            luigiY = groundY;   // Returns Luigi to the ground
        }
        
        if (starPower && currentTime - starStart >= 5000) {
            starPower = false; // Ends star power after five seconds
        }

        clear();
        getmaxyx(stdscr, maxY, maxX); // Gets current terminal height and width
        mvprintw(0, 0, "A: Left | D: Right | SPACE: Jump | Q: Menu");    // Displays Movement Instructions
        mvprintw(1, 0, "Coins: %d", coins); // Displays the player's coin total
        if (boxOpened == false && boxX < maxX && boxY < maxY) {
            mvprintw(boxY, boxX, "[?]"); // Displays the unopened reward box
        }

        if (boxOpened == true && boxX < maxX && boxY < maxY) {
            mvprintw(boxY, boxX, "[ ]"); // Displays the opened reward box
        }

        if (starPower) {
            mvprintw(2, 0, "STAR POWER ACTIVE!"); // Displays active star power
        }
        mvprintw(luigiY, luigiX, "L");    // Displays Luigi at his current horizontal position
        refresh();    // Updates screen display
        key = getch();  // Reads keyboard input
        if (key == 'a' || key == 'A'){
            if (luigiX > 0) {    // Makes sure Luigi does not move past the left boundary
                luigiX--;     // Moves Luigi one position to the left
            }
        }
        if (key == 'd' || key == 'D') {
            if (luigiX < maxX - 1) {    // Makes sure boundary was not crossed
                luigiX++;    // Moves Luigi one position to the right
            }
        }
        if (key == ' ' && jumping == false) {
            jumping = true; // Starts Luigi's Jump
            jumpStart = getTimeMs();    // Records the time the jump began
            luigiY = groundY - 1;   // Moves Luigi up 1 row
        }
         if (boxOpened == false && jumping == true && luigiX == boxX && luigiY == boxY) {
            boxOpened = true; // Opens the reward box
            if (rand() % 2 == 0) {
                coins += 10; // Awards ten gold coins
                saveCoins(coins); // Saves the updated coin total
                mvprintw(3, 0, "You received 10 gold coins!"); // Displays the coin reward
            }
            else {
                starPower = true; // Activates star power
                starStart = getTimeMs(); // Records when star power began
                mvprintw(3, 0, "You received Star Power!"); // Displays the star reward
            }
            refresh(); // Updates the screen with the reward message
        }
        if (key == 'q' || key == 'Q') {
        break;    // Exits Game
                }
            }
        }
    }
          
    endwin();

    return 0;
}
