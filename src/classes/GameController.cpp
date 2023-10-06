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
         break;
      case INFORMATIONS:
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
            game_state = INFORMATIONS;
         }
         break;
      case INFORMATIONS:
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
      case INFORMATIONS:
         renderInformations();
         break;
      case ANIMATION:
         renderDrawing();
         break;
      case ENDING:
         if (aborted) {
            renderWarnings();
         }
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
   cout << repeat("=", column_size) << "\n\n";

   ostringstream oss;
   oss << ">>> Preparing to read input file \"" << program_config.data_file
       << "\"...\n"
          ">>> Processing data, please wait.\n";
   cout << setStyle(oss.str(), green);
}

// Render a help message with available command-line options
void GameController::renderHelper() const {
   cout << "Usage: barchart [<options>] <input_data_file>\n"
           "  Bar Chart Race options:\n"
           "\t-b  <num> Max # of bars in a single char.\n"
           "\t\tValid range is [1,15]. Default value is 5.\n"
           "\t-f  <num> Animation speed in fps (frames per second).\n"
           "\t\tValid range is [1,24]. Default value is 24.\n"
           "\t-c  <local> Configuration file location.\n";

   cout << program_config.data_file << "\n";
}

// Render information about the game and data
void GameController::renderInformations() const {
   ostringstream oss;
   oss << ">>> Input file successfully read\n\n";
   oss << ">>> We have \"" << database.getBarCharts().size()
       << "\" graphs, with at most \"" << max_number_of_bars << "\" bars\n\n";
   oss << ">>> Animation speed is: " << program_config.frames_per_second
       << "\n";
   oss << ">>> Title: " << database.getTitle() << "\n";
   oss << ">>> Values is: " << database.getScale() << "\n";
   oss << ">>> Source: " << database.getSource() << "\n";
   oss << ">>> Number of categories found: " << database.getCategories().size()
       << "\n\n";

   cout << setStyle(oss.str(), green);

   renderWarnings();

   cout << setStyle(">>> Press enter to begin the animation\n", green);
}

// Render warnings if there are any
void GameController::renderWarnings() const {
   if (!program_config.warnings.empty()) {
      cout << setStyle(">>> Warnings:\n", yellow);
      for (string warning : program_config.warnings) {
         cout << setStyle("\t>>> " + warning + "\n", yellow);
      }
      cout << "\n";
   }
}

// Render the drawing using database information
void GameController::renderDrawing() const {
   database.draw(program_config.frames_per_second,
     program_config.bars_size,
     program_config.number_of_bars,
     program_config.ticks,
     program_config.terminal_size);
}

// Process configurations from the configuration file
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

// Process FPS configuration from the input buffer
void GameController::processFPS(string buffer) {
   try {
      short fps_converted { static_cast<short>(stoi(buffer)) };

      if (fps_converted < MINIMUM_FPS || fps_converted > MAXIMUM_FPS) {
         // Warn if FPS value is out of range
         program_config.warnings.push_back("The value of fps must be between ["
           + to_string(MINIMUM_FPS) + ", " + to_string(MAXIMUM_FPS)
           + "]. The default value will be set.");
      } else {
         program_config.frames_per_second = fps_converted;
      }
   } catch (...) {
      // Warn if FPS value is not an integer
      program_config.warnings.push_back(
        "The value of fps must be of type integer. The default value will be "
        "set.");
   }
}

// Process bars configuration from the input buffer
void GameController::processBars(string buffer) {
   try {
      short bars_converted { static_cast<short>(stoi(buffer)) };

      if (bars_converted < MINIMUM_BARS || bars_converted > MAXIMUM_BARS) {
         // Warn if the number of bars is out of range
         program_config.warnings.push_back("The value of bars must be between ["
           + to_string(MINIMUM_BARS) + ", " + to_string(MAXIMUM_BARS)
           + "]. The default value will be set.");
      } else {
         program_config.number_of_bars = bars_converted;
      }
   } catch (...) {
      // Warn if the number of bars is not an integer
      program_config.warnings.push_back(
        "The value of bars must be of type integer. The default value will be "
        "set.");
   }
}

// Process bar size configuration from the input buffer
void GameController::processBarSize(string buffer) {
   try {
      short bar_size_converted { static_cast<short>(stoi(buffer)) };

      if (bar_size_converted < MINIMUM_BARS_SIZE
        || bar_size_converted > MAXIMUM_BARS_SIZE) {
         // Warn if bar size is out of range
         program_config.warnings.push_back(
           "The value of bars size must be between ["
           + to_string(MINIMUM_BARS_SIZE) + ", " + to_string(MAXIMUM_BARS_SIZE)
           + "]. The default value will be set.");
      } else {
         program_config.bars_size = bar_size_converted;
      }
   } catch (...) {
      // Warn if bar size is not an integer
      program_config.warnings.push_back(
        "The value of bars size must be of type integer. The default value "
        "will be set.");
   }
}

// Process colors configuration from the input buffer
void GameController::processColors(string buffer) {
   if (buffer == "true") {
      program_config.colors = true;
   } else {
      program_config.colors = false;
   }
}

// Process columns configuration from the input buffer
void GameController::processColumns(string buffer) {
   vector<string> columns { splitWithEmpty(buffer, ";") };

   if (columns.size() == 5) {
      bool error = false;
      for (short column { 0 }; column != 5; ++column) {
         try {
            program_config.select_columns[column] = stoi(columns[column]);

            if (column != 2 && program_config.select_columns[column] < 0) {
               // Warn if an invalid column value is found
               program_config.warnings.push_back(
                 "Only the third option can be disabled. The default value "
                 "will be set.");
               error = true;
               break;
            }
         } catch (...) {
            // Warn if a column index is not an integer
            program_config.warnings.push_back(
              "The column index must be an integer. The default value will be "
              "set.");
            error = true;
            break;
         }
      }

      if (error) {
         // Reset to default values if there was an error
         program_config.select_columns[0] = COLUMN_1;
         program_config.select_columns[1] = COLUMN_2;
         program_config.select_columns[2] = COLUMN_3;
         program_config.select_columns[3] = COLUMN_4;
         program_config.select_columns[4] = COLUMN_5;
      }
   }
}

// Process ticks configuration from the input buffer
void GameController::processTicks(string buffer) {
   try {
      short ticks_converted { static_cast<short>(stoi(buffer)) };

      if (ticks_converted < MINIMUM_TICKS) {
         // Warn if the number of ticks is less than the minimum allowed
         program_config.warnings.push_back(
           "The number of ticks cannot be less than " + to_string(MINIMUM_TICKS)
           + ". The default value will be set.");
      } else {
         program_config.ticks = ticks_converted;
      }
   } catch (...) {
      // Warn if the ticks value is not an integer
      program_config.warnings.push_back(
        "The value of ticks must be of type integer. The default value will be "
        "set.");
   }
}

// Process terminal size configuration from the input buffer
void GameController::processTerminalSize(string buffer) {
   try {
      short terminal_size_converted { static_cast<short>(stoi(buffer)) };

      if (terminal_size_converted < MINIMUM_TERMINAL_SIZE
        || terminal_size_converted > MAXIMUM_TERMINAL_SIZE) {
         // Warn if the terminal size is out of range
         program_config.warnings.push_back(
           "The value of terminal size must be between ["
           + to_string(MINIMUM_TERMINAL_SIZE) + ", "
           + to_string(MAXIMUM_TERMINAL_SIZE)
           + "]. The default value will be set.");
      } else {
         program_config.terminal_size = terminal_size_converted;
      }
   } catch (...) {
      // Warn if the terminal size is not an integer
      program_config.warnings.push_back(
        "The value of terminal size must be of type integer. The default value "
        "will be set.");
   }
}
// Open and process data from the input file
void GameController::processData() {
   ifstream file { program_config.data_file };

   if (!file.is_open()) {
      // Warn if the data file cannot be opened
      program_config.warnings.push_back(
        "The data file does not exist or cannot be opened.\n Aborted!");
      aborted = true;
      return;
   }

   string buffer;

   for (short header { 0 }; header != HEADER_SIZE; ++header) {
      getline(file >> std::ws, buffer);

      if (header == 0) {
         // Set the title of the database from the first line
         database.setTitle(buffer);
      } else if (header == 1) {
         // Set the scale of the database from the second line
         database.setScale(buffer);
      } else {
         // Set the source of the database from the third line
         database.setSource(buffer);
      }
   }

   int bar_chart_number { 0 };
   int categories { 0 };
   bool line_error { false };
   int quantify_buffer { 0 };

   while (getline(file >> std::ws, buffer)) {
      int quantify { 0 };
      string buffer_line;

      if (isQuantify(buffer)) {
         quantify = stoi(buffer);
      } else if (line_error) {
         quantify = quantify_buffer;
         line_error = false;
         buffer_line = buffer;
      }

      BarChart* bar_chart = new BarChart();

      int bar_number { 0 };
      for (int line { 0 }; line != quantify; ++line) {
         if (buffer_line.empty()) {
            getline(file >> std::ws, buffer);
         } else {
            buffer = buffer_line;
            buffer_line.clear();
         }

         if (isQuantify(buffer)) {
            quantify_buffer = stoi(buffer);
            line_error = true;

            ostringstream oss;
            oss << "The Number Bar chart " << bar_chart_number
                << " has less data than specified.";
            program_config.warnings.push_back(oss.str());
            break;
         }

         vector<string> columns { splitWithEmpty(buffer, ",") };
         string other_info;

         bool restart_for { false };

         for (short index { 0 }; index < COLUMNS; ++index) {
            if (program_config.select_columns[index] != -1
              && program_config.select_columns[index] > columns.size()) {
               // Warn if a bar has fewer columns than specified
               ostringstream oss;
               oss << "One of the bars in the " << bar_chart_number
                   << " bar chart has fewer columns than specified";
               program_config.warnings.push_back(oss.str());
               restart_for = true;
               break;
            }
         }

         if (restart_for) {
            continue;
         }

         if (bar_number == 0) {
            // Set the time stamp of the bar chart from the first column
            bar_chart->setTimeStamp(columns[program_config.select_columns[0]]);
         }

         if (program_config.select_columns[2] != -1) {
            other_info = columns[program_config.select_columns[2]];
         }

         double long value;

         try {
            value = stold(columns[program_config.select_columns[3]]);
         } catch (...) { value = 0; }

         // Create and add a bar to the current bar chart
         Bar* bar = new Bar(columns[program_config.select_columns[1]],
           other_info,
           columns[program_config.select_columns[4]],
           value);

         short color { green };
         if (program_config.colors) {
            // Set color based on configuration
            color = LIST_OF_COLORS[categories % NUMBER_OF_COLORS];
         }

         if (database.addCategory(
               columns[program_config.select_columns[4]], color)) {
            // Add category to the database and track the number of categories
            ++categories;
         }

         bar_chart->addBar(bar);

         ++bar_number;
      }

      if (max_number_of_bars < bar_number) {
         // Update the maximum number of bars encountered
         max_number_of_bars = bar_number;
      }

      // Add the completed bar chart to the database
      database.addBarChart(bar_chart);

      ++bar_chart_number;
   }
}

// Check if a given string can be converted to an integer, indicating a quantity
bool GameController::isQuantify(string line) {
   try {
      size_t pos;
      int buffer = std::stoi(line, &pos);

      // If the conversion position matches the trimmed line length, it's a
      // quantity
      if (pos == trim(line).length()) {
         return true;
      } else {
         return false;
      }
   } catch (...) { return false; }
}
