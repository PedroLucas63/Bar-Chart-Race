/**
 * @file main.cpp
 * @author pedro Lucas (pedrolucas.jsrn@gmail.com)
 * @brief Entry point for the game application.
 * @version 1.0
 * @date 2023-09-29
 *
 * This file contains the main function, which serves as the entry point for the
 * game application. It creates an instance of the GameController class,
 * initializes it, and enters a loop where it processes events, updates the game
 * state, and renders the game until the game is over. Finally, it cleans up the
 * GameController instance before exiting the program.
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "GameController.hpp" ///< Include the GameController class header
#include <stdlib.h> ///< Include the standard library for EXIT_SUCCESS

int main(int argc, char* argv[]) {
   GameController& app {
      GameController::getInstance()
   }; ///< Create a GameController instance

   // Initialize the GameController with command-line arguments
   app.initialize(argc, argv);

   // Main game loop.
   while (!app.gameOver()) {
      app.processEvent(); ///< Process game events
      app.update(); ///< Update the game state
      app.render(); ///< Render the game
      // The loop continues until the game is over
   }

   app.destruct(); ///< Clean up the GameController instance

   return EXIT_SUCCESS; ///< Return a successful exit status
}