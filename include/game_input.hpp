#ifndef GAME_INPUT_HPP_
#define GAME_INPUT_HPP_
#include "../include/button_driver.hpp"

 void savePlayerInput(button_handle* buttons[], int buttonCounter);
 extern char playerInput[60];
 extern int playerIndex;

#endif