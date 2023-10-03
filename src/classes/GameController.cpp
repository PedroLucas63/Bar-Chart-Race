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
      case PROCESS_CONFIGS:
         processConfigs();
         break;
      case PROCESS_DATA:
         processData();
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
         if (aborted) {
            game_state = ENDING;
         } else {
            game_state = ANIMATION;
         }
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
         renderDrawing();
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
   cout << alignment(welcome, column_size, center, ' ') << "\n";
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

void GameController::renderDrawing() const {
   database.draw(program_config.frames_per_second,
     program_config.bars_size,
     program_config.number_of_bars,
     program_config.ticks,
     program_config.terminal_size);
}

void GameController::processConfigs() {
   try {
      FileIni file { program_config.config_file };
      map<string, string> global_configs { file["global"] };

      if (global_configs.empty()) {
         return;
      }

      if (global_configs.find("fps") != global_configs.end()) {
         processFPS(global_configs["fps"]);
      }

      if (global_configs.find("bars") != global_configs.end()) {
         processBars(global_configs["bars"]);
      }

      if (global_configs.find("bar_size") != global_configs.end()) {
         processBarSize(global_configs["bar_size"]);
      }

      if (global_configs.find("colors") != global_configs.end()) {
         processColors(global_configs["colors"]);
      }

      if (global_configs.find("columns") != global_configs.end()) {
         processColumns(global_configs["columns"]);
      }

      if (global_configs.find("ticks") != global_configs.end()) {
         processTicks(global_configs["ticks"]);
      }

      if (global_configs.find("terminal_size") != global_configs.end()) {
         processTerminalSize(global_configs["terminal_size"]);
      }
   } catch (std::runtime_error& e) {
      program_config.warnings.push_back(e.what());
   }
}

void GameController::processFPS(string buffer) {
   try {
      short fps_converted { static_cast<short>(stoi(buffer)) };

      if (fps_converted < MINIMUM_FPS || fps_converted > MAXIMUM_FPS) {
         ostringstream oss;
         oss << "The value of fps must be between [" << MINIMUM_FPS << ", "
             << MAXIMUM_FPS << "]. The default value will be set.";
         program_config.warnings.push_back(oss.str());
      } else {
         program_config.frames_per_second = fps_converted;
      }
   } catch (...) {
      string error { "The value of fps must be of type "
                     "integer. The default value will be set." };
      program_config.warnings.push_back(error);
   }
}

void GameController::processBars(string buffer) {
   try {
      short bars_converted { static_cast<short>(stoi(buffer)) };

      if (bars_converted < MINIMUM_BARS || bars_converted > MAXIMUM_BARS) {
         ostringstream oss;
         oss << "The value of bars must be between [" << MINIMUM_BARS << ", "
             << MAXIMUM_BARS << "]. The default value will be set.";
         program_config.warnings.push_back(oss.str());
      } else {
         program_config.number_of_bars = bars_converted;
      }
   } catch (...) {
      string error { "The value of bars must be of type "
                     "integer. The default value will be set." };
      program_config.warnings.push_back(error);
   }
}

void GameController::processBarSize(string buffer) {
   try {
      short bar_size_converted { static_cast<short>(stoi(buffer)) };

      if (bar_size_converted < MINIMUM_BARS_SIZE
        || bar_size_converted > MAXIMUM_BARS_SIZE) {
         ostringstream oss;
         oss << "The value of bars size must be between [" << MINIMUM_BARS_SIZE
             << ", " << MAXIMUM_BARS_SIZE
             << "]. The default value will be set.";
         program_config.warnings.push_back(oss.str());
      } else {
         program_config.bars_size = bar_size_converted;
      }
   } catch (...) {
      string error { "The value of bars size must be of type "
                     "integer. The default value will be set." };
      program_config.warnings.push_back(error);
   }
}

void GameController::processColors(string buffer) {
   if (buffer == "true") {
      program_config.colors = true;
   } else {
      program_config.colors = false;
   }
}

void GameController::processColumns(string buffer) {
   vector<string> columns { splitWithEmpty(buffer, ";") };

   if (columns.size() != 5) {
      bool error = false;
      for (short column { 0 }; column != 5; ++column) {
         try {
            program_config.select_columns[column] = stoi(columns[column]);

            if (column != 2 && program_config.select_columns[column] < 0) {
               string error { "Only the third option can be disabled. The "
                              "default value will be set." };
               program_config.warnings.push_back(error);
               error = true;
               break;
            }
         } catch (...) {
            string error { "The column index must be an integer. The "
                           "default value will be set." };
            program_config.warnings.push_back(error);
            error = true;
            break;
         }
      }

      if (error) {
         program_config.select_columns[0] = COLUMN_1;
         program_config.select_columns[1] = COLUMN_2;
         program_config.select_columns[2] = COLUMN_3;
         program_config.select_columns[3] = COLUMN_4;
         program_config.select_columns[4] = COLUMN_5;
      }
   }
}
void GameController::processTicks(string buffer) {
   try {
      short ticks_converted { static_cast<short>(stoi(buffer)) };

      if (ticks_converted < MINIMUM_TICKS) {
         ostringstream oss;
         oss << "The number of ticks cannot be less than " << MINIMUM_TICKS
             << ". The default value will be set.";
         program_config.warnings.push_back(oss.str());
      } else {
         program_config.bars_size = ticks_converted;
      }
   } catch (...) {
      string error { "The value of ticks must be of type "
                     "integer. The default value will be set." };
      program_config.warnings.push_back(error);
   }
}
void GameController::processTerminalSize(string buffer) {
   try {
      short terminal_size_converted { static_cast<short>(stoi(buffer)) };

      if (terminal_size_converted < MINIMUM_TERMINAL_SIZE
        || terminal_size_converted > MAXIMUM_TERMINAL_SIZE) {
         ostringstream oss;
         oss << "The value of terminal size must be between ["
             << MINIMUM_TERMINAL_SIZE << ", " << MAXIMUM_TERMINAL_SIZE
             << "]. The default value will be set.";
         program_config.warnings.push_back(oss.str());
      } else {
         program_config.terminal_size = terminal_size_converted;
      }
   } catch (...) {
      string error { "The value of terminal size must be of type "
                     "integer. The default value will be set." };
      program_config.warnings.push_back(error);
   }
}

void GameController::processData() {
   ifstream file { program_config.data_file };

   if (!file.is_open()) {
      program_config.warnings.push_back(
        "The data file does not exist or cannot be opened.\n Aborted!");
      aborted = true;
      return;
   }

   string buffer;

   for (short header { 0 }; header != HEADER_SIZE; ++header) {
      getline(file >> std::ws, buffer);

      if (header == 0) {
         database.setTitle(buffer);
      } else if (header == 1) {
         database.setScale(buffer);
      } else {
         database.setSource(buffer);
      }
   }

   int bar_chart_number { 0 };

   while (getline(file >> std::ws, buffer)) {
      int quantify { 0 };

      if (isQuantify(buffer)) {
         quantify = stoi(buffer);
      }

      BarChart* bar_chart = new BarChart();

      int bar_number { 0 };
      for (int line { 0 }; line != quantify; ++line) {
         getline(file >> std::ws, buffer);

         if (isQuantify(buffer)) {
            quantify = stoi(buffer);

            ostringstream oss;
            oss << "The Number Bar chart " << bar_chart_number
                << " has less data than specified.";
            program_config.warnings.push_back(oss.str());

            break;
         }

         vector<string> columns { splitWithEmpty(buffer, ",") };
         string other_info;

         if (bar_number == 0) {
            bar_chart->setTimeStamp(columns[program_config.select_columns[0]]);
         }

         if (program_config.select_columns[2] != -1) {
            other_info = columns[program_config.select_columns[2]];
         }

         double long value;

         try {
            value = stold(columns[program_config.select_columns[3]]);
         } catch (...) { value = 0; }

         Bar* bar = new Bar(columns[program_config.select_columns[1]],
           other_info,
           columns[program_config.select_columns[4]],
           value);

         database.addCategory(columns[program_config.select_columns[4]], green);

         bar_chart->addBar(bar);

         ++bar_number;
      }

      database.addBarChart(bar_chart);

      ++bar_chart_number;
   }
}

bool GameController::isQuantify(string line) {
   try {
      size_t pos;
      int buffer = std::stoi(line, &pos);

      if (pos == line.length()) {
         return true;
      } else {
         return false;
      }
   } catch (...) {
      return false;
   }
}
