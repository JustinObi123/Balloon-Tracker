/*****************************************
** File:    proj1.cpp
** Project: CMSC 202 Project 1, Spring 2023
** Author:  Justin Obi
** Date:    2/18/23
** Section: 34
** E-mail:  wr64574@gl.umbc.edu 
**
** This file contains a tool that would allow us to guess where other large balloons might exist.
** There will be a large area that the balloon will exist,
** and the user will guess where the balloon is. If the balloon is not in that location, the application will identify which direction the balloon is.
** The user will continue guessing until the balloon is found.
**
**
***********************************************/

#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

const int GRID_WIDTH = 20; // Size of the array
const int GRID_HEIGHT = 20; // Size of the array
const char UNKNOWN_MARKER = '$'; // Symbol used to represent unguessed coordinate
const char KNOWN_MARKER = 'G';

// Function name: PrintMap
// Pre-condition: grid is an array with a given size is passed in
// Post-condition: grid gets printed out
void PrintMap (char grid[][GRID_HEIGHT]);

// Function name: resetMap
// Pre-condition: grid is an array with a given size is passed in
// Post-condition: grid fills up with UNKNOWN MARKER
void resetMap(char grid[][GRID_HEIGHT]);

// Function name: guessMap
// Pre-condition: guessx is the users guess in the x coordinate; guess y is the users guess in the y coordinate;
//  int h is the ballon's X coordinate; k is the balloons y coordinate; grid is the map
// Post-condition: grid assigns a 'G' on the coordinate of the users guess;
//  If the game is over this function will return a specific number depending if the user wants to play again
int guessMap(int guessx, int guessy, int h, int k, char grid[][GRID_HEIGHT]);

// Function name: balloonLocatex
// Pre-condition: 
// Post-condition: relocates balloon
int balloonLocatex();

// Function name: balloonLocatey
// Pre-condition: 
// Post-condition: relocates balloon
int balloonLocatey();

// Function name: checkDirection
// Pre-condition: x is the users guess in the x coordinate; y is th users guess in they y coordinate;
//  h is the balloon's x coordinate; k is the balloons y coordinate
// Post-condition: returns the direction of the balloon relative to the user's guess
void checkDirection(int x, int y, int h, int k);


int main() {
    char grid[GRID_HEIGHT][GRID_WIDTH]; // grid of the map
    int guessx = -1; 
    int guessy = -1;
    int userInput;
    int balloonx = balloonLocatex();
    int balloony = balloonLocatey();
    int isGameOver = 3;
    resetMap(grid);
    cout << "Welcome to the Surveillance Balloon Tracker" << endl;
    cout << "You are searching for the surveillance balloon" << endl;
    do
    {
        cout << "What would you like to do?: \n 1. Display Map \n 2. Guess Location of Balloon \n 3. Exit" << endl;
        cin >> userInput;
        switch (userInput)
        {
            case 1:
                PrintMap(grid);
                break;
            case 2:
                cout <<"Balloon Coordinate X: "<< balloonx << endl << "Balloon Coordinate Y: "<< balloony << endl;
                cout << "Where would you like to look for the balloon?" << endl;

                do{
                    cout << "Enter the X coordinate (0 - " << GRID_HEIGHT - 1 << "):" << " ";
                    cin >> guessx;
                } while (guessx > (GRID_HEIGHT - 1) || guessx < 0);

                do{
                    cout << "Enter the Y coordinate (0 - "<< GRID_HEIGHT - 1 << "):" << " ";
                    cin >> guessy;
                } while(guessy > (GRID_HEIGHT - 1) || guessy < 0);

                isGameOver = guessMap(guessx, guessy, balloonx, balloony, grid);

                if(isGameOver == 30)
                    return 0;
                else{
                    if(isGameOver == -40){
                        guessx = -1;
                        balloonx = balloonLocatex();
                        balloony = balloonLocatey();
                    }
                }
                break;
            case 3:
                return 0;
            default:
                cout << "Not an option" << endl;
        }
    } while (userInput != 3);
    return 0;
}
void checkDirection(int x, int y, int h, int k){
    cout << "You didn't find the balloon" << endl;
    if((y > k) || y < k)
        if(y < k)
            cout << "The balloon is south of your guess" << endl;
        else
            cout << "The balloon is north of your guess" << endl;
    else
        if(x < h)
            cout << "The balloon is east of your guess" << endl;
        else
            cout << "The balloon is west of your guess" << endl;

}
void PrintMap (char grid[][GRID_WIDTH]){
    cout << "   "<< "";
        for(int i = 0; i < GRID_HEIGHT; i++){
            if (i < 10)
                cout << " " << i << " ";
            else
                cout << "" << i << " ";
            }
    cout << endl;
        for(int i = 0; i < GRID_HEIGHT; i++){
            if (i < 10)
                cout << " "<< i << " ";
            else
                cout << i << " " ;
            for(int j = 0; j < GRID_WIDTH; j++){
                cout << " "<< grid[i][j]<< " ";
            }
            std::cout << std::endl;
        }    
}
void resetMap(char grid[][GRID_HEIGHT]){
    for(int i = 0; i < GRID_HEIGHT; i++)
        for(int j = 0; j < GRID_WIDTH; j++)
            grid[i][j] = UNKNOWN_MARKER;
}
int guessMap(int x, int y, int h, int k, char grid[][GRID_HEIGHT]){
    char input;
    if((x == h) && (y == k)){
        cout << "You found the Balloon!" << endl;
        do
        {
            cout << "Would you like to play again? y/n" << " ";
            cin >> input;
        }while(input!= 'y' && input!= 'n');

        if(input == 'y'){
            resetMap(grid);
        }
        else
            return 30;
    }   
    else{
        checkDirection(x, y, h, k);
        grid[y][x] = KNOWN_MARKER;
        return 2;
    }
    return -40;
}
int balloonLocatex(){
    int x;
    srand(time(NULL));
    x = (rand()% (GRID_HEIGHT));
    return x;
}
int balloonLocatey(){
    int y;
    y = (rand()% (GRID_HEIGHT));
    return y;
}