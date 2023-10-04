/**
 * @file GameController.hpp
 * @author Pedro Lucas (pedrolucas.jsrn@gmail.com)
 * @brief Defines the GameController class, which manages the flow of a game
 * application.
 * @version 1.0
 * @date 2023-09-29
 *
 * This file contains the declaration of the GameController class, responsible
 * for controlling the various states and activities within a game application.
 * It utilizes the singleton pattern to ensure a single instance throughout
 * execution and interfaces with other supporting classes. The GameController
 * class handles initialization, event processing, updating, rendering, and
 * enforces proper encapsulation of game-related functionality.
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef GAME_CONTROLLER_HPP_
#define GAME_CONTROLLER_HPP_

#include "clioptions.hpp"
#include "utils.hpp"

#include "fstring.hpp" /// aligment, center, repeat, setStyle
using fos::trim;
using fos::alignment;
using fos::splitWithEmpty;
using fos::center;
using fos::foreground::green;
using fos::repeat;
using fos::setStyle;

#include "Database.hpp"

#include "fileini.hpp"

#include <iostream> /// cerr, cin, cout
using std::cerr;
using std::cin;
using std::cout;

#include <vector> /// vector
using std::vector;

#include <string> /// getline, string
using std::getline;
using std::stoi;
using std::stof;
using std::stold;
using std::string;

#include <map>
using std::map;

#include <sstream>
using std::ostringstream;

#include <fstream>
using std::ifstream;

constexpr short MINIMUM_TICKS { 0 };
constexpr short MINIMUM_TERMINAL_SIZE { 20 };
constexpr short MAXIMUM_TERMINAL_SIZE { 512 };

constexpr short HEADER_SIZE { 3 };

short const LIST_OF_COLORS[NUMBER_OF_COLORS] = {
   fos::foreground::red,
   fos::foreground::green,
   fos::foreground::yellow,
   fos::foreground::blue,
   fos::foreground::magenta,
   fos::foreground::cyan,
   fos::foreground::white,
   fos::foreground::bright_red,
   fos::foreground::bright_green,
   fos::foreground::bright_yellow,
   fos::foreground::bright_blue,
   fos::foreground::bright_magenta,
   fos::foreground::bright_cyan,
   fos::foreground::bright_white,
};

/**
 * @brief GameController class that controls the game flow
 */
class GameController {
   /**
    * @brief Enumeration representing different game states
    */
   enum GameState {
      STARTING, ///< Starting state
      WELCOME, ///< Welcome state
      HELPER, ///< Helper state
      PROCESS_CONFIGS, ///< Configuration processing state
      PROCESS_DATA, ///< Data processing state
      ANIMATION, ///< Animation state
      ENDING, ///< Ending state
   };

   public:
   /**
    * @brief Get the singleton instance of the GameController class
    * @return Reference to the singleton instance of GameController
    */
   static GameController& getInstance();

   /**
    * @brief Default constructor for GameController
    *
    * This constructor is explicitly defaulted, meaning it provides the default
    * behavior for constructing instances of the GameController class. It does
    * not perform any additional actions beyond default initialization.
    */
   GameController() = default;

   /**
    * @brief Default destructor for GameController
    *
    * This destructor is explicitly defaulted, indicating the default behavior
    * for destroying instances of the GameController class. It does not perform
    * any custom cleanup or resource release because the class does not manage
    * any dynamically allocated resources.
    */
   ~GameController() = default;

   /**
    * @brief Destroy the singleton instance of GameController
    */
   static void destruct();

   /**
    * @brief Initialize the game controller with command line arguments
    * @param arguments_count The number of command line arguments
    * @param arguments An array of strings containing the command line arguments
    */
   void initialize(int arguments_count, char* arguments[]);

   /**
    * @brief Check if the game is over
    * @return true if the game is over, false otherwise
    */
   bool gameOver() const;

   /**
    * @brief Process a game event
    */
   void processEvent();

   /**
    * @brief Update the game state
    */
   void update();

   /**
    * @brief Render the current game state
    */
   void render();

   private:
   static GameController*
     instance; ///< Pointer to singleton instance to GameController
   GameState game_state; ///< Current game state
   ProgramConfig program_config; ///< Program configuration
   Database database;
   bool aborted { false };

   /**
    * @brief Deleted copy constructor
    *
    * The copy constructor for GameController is explicitly deleted, preventing
    * the creation of new instances by copying from existing ones. This ensures
    * that GameController remains a singleton class with only one instance.
    *
    * @param other The GameController object to copy (not used)
    */
   GameController(GameController const&) = delete;

   /**
    * @brief Deleted copy assignment operator
    *
    * The copy assignment operator for GameController is explicitly deleted,
    * making it impossible to assign one GameController instance to another.
    * This enforces the singleton pattern, where only one instance of
    * GameController is allowed.
    *
    * @param other The GameController object to assign from (not used)
    * @return Reference to the current GameController instance
    */
   GameController operator=(GameController const&) = delete;

   /**
    * @brief Render the welcome message
    */
   void renderWelcome() const;

   /**
    * @brief Render the help message
    */
   void renderHelper() const;

   void renderDrawing() const;


   void processConfigs();

   void processFPS(string buffer);
   void processBars(string buffer);
   void processBarSize(string buffer);
   void processColors(string buffer);
   void processColumns(string buffer);
   void processTicks(string buffer);
   void processTerminalSize(string buffer);

   void processData();

   bool isQuantify(string line);
};

#endif /// GAME_CONTROLLER_HPP_
