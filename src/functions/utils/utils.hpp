/**
 * @file utils.example.hpp
 * @author Pedro Lucas (pedrolucas.jsrn@gmail.com)
 * @brief Header file containing utility structures and constants.
 * @version 1.0
 * @date 2023-09-26
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <vector> /// vector
using std::vector;

#include <string> /// string
using std::string;

/// Default frames per second
constexpr short DEFAULT_FRAMES_PER_SECOND { 24 };

/// Default number of bars
constexpr short DEFAULT_NUMBER_OF_BARS { 5 };

/// Default size of bars
constexpr short DEFAULT_SIZE_OF_BARS { 40 };

/// Default enable colors
constexpr bool DEFAULT_ENABLE_COLORS { true };

/// Default help menu
constexpr bool DEFAULT_HELP_MENU { false };

constexpr short COLUMNS { 5 };
constexpr short COLUMN_1 { 1 };
constexpr short COLUMN_2 { 2 };
constexpr short COLUMN_3 { 3 };
constexpr short COLUMN_4 { 4 };
constexpr short COLUMN_5 { 5 };

/**
 * @struct ProgramConfig
 * @brief Struct representing the program configs with file locals and values
 *
 */
struct ProgramConfig {
   short frames_per_second { DEFAULT_FRAMES_PER_SECOND }; ///< Frames per second
   short number_of_bars { DEFAULT_NUMBER_OF_BARS }; ///< Number of bars
   short bars_size { DEFAULT_SIZE_OF_BARS }; ///< Size of bars
   short select_columns[COLUMNS] {
      COLUMN_1, COLUMN_2, COLUMN_3, COLUMN_4, COLUMN_5
   }; ///< Select columns
   bool colors { DEFAULT_ENABLE_COLORS }; ///< Enable colors
   bool help_menu { DEFAULT_HELP_MENU }; ///< Help menu
   vector<string> warnings; ///< Warnings list
   string data_file; ///< Data file local
   string config_file; ///< Config file local
};

#endif /// UTILS_HPP_
