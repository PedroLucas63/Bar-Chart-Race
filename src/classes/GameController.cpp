/**
 * @file GameController.cpp
 * @author Pedro Lucas (pedrolucas.jsrn@gmail.com)
 * @brief Declaration of the GameController class responsible for managing a
 * game application's flow.
 * @version 1.0
 * @date 2023-09-29
 *
 *
 * This file contains the declaration of the GameController class, which serves
 * as the central controller for a game application. It implements the singleton
 * pattern to ensure a single instance throughout the program's execution.
 * GameController handles initialization, event processing, state updates, and
 * rendering of the game. It also interfaces with other classes for command-line
 * options and program configuration.
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "GameController.hpp"

// Initialize the static instance pointer to nullptr
GameController* GameController::instance = nullptr;

// Get the singleton instance of GameController
GameController& GameController::getInstance() {
   if (instance == nullptr) {
      instance = new GameController;
   }

   return *instance;
}

// Destructor for GameController, destroys the singleton instance
void GameController::destruct() {
   delete instance;
   instance = nullptr;
}

// Initialize the GameController with command-line arguments
void GameController::initialize(int arguments_count, char* arguments[]) {
   // Obtain CLIOptions instance and configure it
   CLIOptions& cli { CLIOptions::getInstance() };
   cli.getConfigs(arguments_count, arguments);

   // Retrieve program configuration and clean up CLIOptions
   program_config = cli.getProgramConfigs();
   cli.destruct();

   // Set the initial game state to STARTING
   game_state = STARTING;
}

// Check if the game is over (END state)
bool GameController::gameOver() const {
   return game_state == ENDING;
}

// Process game events based on the current game state
void GameController::processEvent() {
   string buffer;
   switch (game_state) {
      case PROCESS_DATA:
         getline(cin, buffer);
         break;
      default:
         break;
   }
}

// Update the game state based on the current state and program configuration
void GameController::update() {
   switch (game_state) {
      case STARTING:
         if (program_config.help_menu || program_config.data_file.empty()) {
            game_state = HELPER;
         } else {
            game_state = WELCOME;
         }
         break;
      case WELCOME:
         if (program_config.config_file.empty()) {
            game_state = PROCESS_DATA;
         } else {
            game_state = PROCESS_CONFIGS;
         }
         break;
      case HELPER:
         game_state = ENDING;
         break;
      case PROCESS_CONFIGS:
         game_state = PROCESS_DATA;
         break;
      case PROCESS_DATA:
         game_state = ANIMATION;
         break;
      case ANIMATION:
         game_state = ENDING;
         break;
      default:
         break;
   }
}

// Render the game based on the current game state
void GameController::render() {
   switch (game_state) {
      case WELCOME:
         renderWelcome();
         break;
      case HELPER:
         renderHelper();
         break;
      case PROCESS_CONFIGS:
         break;
      case PROCESS_DATA:
         break;
      case ANIMATION:
         break;
      default:
         break;
   }
}

// Render a welcome message with formatting
void GameController::renderWelcome() const {
   short const column_size = 50;
   string welcome { "Welcome to the Bar Chart Race v1.0\n"
                    "Copyright (C) 2023, Pedro Lucas" };

   cout << repeat("=", column_size) << "\n";
   cout << alignment(welcome, column_size, center, ' ');
   cout << repeat("=", column_size) << "\n";
}

// Render a help message with available command-line options
void GameController::renderHelper() const {
   cout << "Usage: barchart [<options>] <input_data_file>\n"
           "  Bar Chart Race options:\n"
           "\t-b  <num> Max # of bars in a single char.\n"
           "\t\tValid range is [1,15]. Default value is 5.\n"
           "\t-f  <num> Animation speed in fps (frames per second).\n"
           "\t\tValid range is [1,24]. Default value is 24.\n";
   "\t-c  <local> Configuration file location.\n";

   cout << program_config.data_file << "\n";
}
