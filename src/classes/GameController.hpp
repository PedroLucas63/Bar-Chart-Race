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

#include "fstring.hpp" /// aligment, center, repeat, setStyle, splitWithEmpty, trim, green
using fos::alignment;
using fos::center;
using fos::repeat;
using fos::setStyle;
using fos::splitWithEmpty;
using fos::trim;
using fos::foreground::green;

#include "Database.hpp"
#include "fileini.hpp"

#include <iostream> /// cerr, cin, cout
using std::cerr;
using std::cin;
using std::cout;

#include <vector> /// vector
using std::vector;

#include <string> /// getline, stof, stoi, stold, string
using std::getline;
using std::stof;
using std::stoi;
using std::stold;
using std::string;

#include <map> /// map
using std::map;

#include <sstream> /// ostringstream
using std::ostringstream;

#include <fstream> /// ifstream
using std::ifstream;

constexpr short MINIMUM_TICKS { 0 }; ///< Minimum number of ticks >//
constexpr short MINIMUM_TERMINAL_SIZE { 20 }; ///< Minimum terminal size >//
constexpr short MAXIMUM_TERMINAL_SIZE { 512 }; ///< Maximum terminal size >//
constexpr short HEADER_SIZE { 3 }; ///< Header size >//

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
}; ///< List of colors used in categories >//

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
      INFORMATIONS, ///< Informations about data
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
     instance; ///< Pointer to the singleton instance of GameController
   GameState game_state; ///< Current game state
   ProgramConfig program_config; ///< Program configuration
   Database database; ///< Database used by the game
   short max_number_of_bars { 0 }; ///< Maximum number of bars
   bool aborted { false }; ///< Flag indicating if the game was aborted

   /**
    * @brief Deleted copy constructor
    *
    * The copy constructor for GameController is explicitly deleted, preventing
    * the creation of new instances by copying from existing ones. This ensures
    * that GameController remains a singleton class with only one instance
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
    * GameController is allowed
    *
    * @param other The GameController object to assign from (not used).
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

   /**
    * @brief Render information
    */
   void renderInformations() const;

   /**
    * @brief Render warnings
    */
   void renderWarnings() const;

   /**
    * @brief Render the drawing
    */
   void renderDrawing() const;

   /**
    * @brief Process game configurations
    */
   void processConfigs();

   /**
    * @brief Process frames per second (FPS)
    * @param buffer The input buffer containing FPS data
    */
   void processFPS(string buffer);

   /**
    * @brief Process the maximum number of bars
    * @param buffer The input buffer containing the maximum number of bars data
    */
   void processBars(string buffer);

   /**
    * @brief Process the bar size
    * @param buffer The input buffer containing bar size data
    */
   void processBarSize(string buffer);

   /**
    * @brief Process colors configuration
    * @param buffer The input buffer containing colors data
    */
   void processColors(string buffer);

   /**
    * @brief Process columns configuration
    * @param buffer The input buffer containing columns data
    */
   void processColumns(string buffer);

   /**
    * @brief Process ticks configuration
    * @param buffer The input buffer containing ticks data
    */
   void processTicks(string buffer);

   /**
    * @brief Process terminal size configuration
    * @param buffer The input buffer containing terminal size data
    */
   void processTerminalSize(string buffer);

   /**
    * @brief Process game data
    */
   void processData();

   /**
    * @brief Check if a line contains a "quantify" command
    * @param line The line to check
    * @return true if the line contains a "quantify" command, false otherwise
    */
   bool isQuantify(string line);
};

#endif /// GAME_CONTROLLER_HPP_
