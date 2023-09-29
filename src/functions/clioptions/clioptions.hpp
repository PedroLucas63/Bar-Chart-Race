/**
 * @file clioptions.hpp
 * @author Pedro Lucas (pedrolucas.jsrn@gmail.com)
 * @brief Defines the CLIOptions class for handling command-line options.
 * @version 1.0
 * @date 2023-09-26
 *
 * This file contains the definition of the CLIOptions class, which is
 * responsible for parsing and managing command-line options for the
 * application.
 *
 * @copyright Copyright (c) 2023
 */

#ifndef CLI_OPTIONS_HPP_
#define CLI_OPTIONS_HPP_

#include "utils.hpp"

#include "fstring.hpp" /// trim
using fos::trim;

#include <string> /// string, stoi
using std::string;
using std::stoi;

#include <sstream> /// ostringstream
using std::ostringstream;

///< Definition of system constants >//
constexpr short FIRST_ARGUMENT_INDEX {
   1
}; ///< Index of the first command-line argument

constexpr short MINIMUM_FPS { 1 }; ///< Defining a minimum fps accepted

constexpr short MAXIMUM_FPS { 24 }; ///< Defining a maximum fps accepted

constexpr short MINIMUM_BARS { 1 }; ///< Defining a minimum bars accepted

constexpr short MAXIMUM_BARS { 15 }; ///< Defining a maximum bars accepted

constexpr short MINIMUM_BARS_SIZE { 20 }; ///< Defining a minimum bars size accepted

constexpr short MAXIMUM_BARS_SIZE { 100 }; ///< Defining a maximum bars size accepted

/**
 * @brief Enumeration of argument types
 */
enum ArgumentType {
   BASIC, ///< Basic argument type
   COMPOST, ///< Compost argument type
   COMPLEX, ///< Complex argument type
   NONE, ///< No argument type
};

/**
 * @brief Structure representing a command-line argument
 */
struct Argument {
   ArgumentType type; ///< The type of the argument
   string code; ///< The code for the argument
   bool obligatory; ///< The obligation of the argument
};

/**
 * @brief List of command-line arguments
 */
Argument const arguments[] = { { BASIC, "-h", false }, /// Helper argument
   { COMPOST, "-f", false }, /// Fps config
   { COMPOST, "-b", false }, /// Bars config
   { COMPOST, "-s", false }, /// Bars size config
   { COMPOST, "-c", false }, /// File config
   { NONE, std::string() } }; /// This is an empty argument

/**
 * @brief Enumeration of argument types used in the application.
 */
enum ArgumentsEnumeration {
   ARG_HELP, /// Helper
   ARG_FPS, /// FPS
   ARG_BARS, /// Bars
   ARG_BARS_SIZE, /// Bars size
   ARG_FILE_CONFIG, /// File config
   ARG_UNDEFINED, /// Undefined
};

/**
 * @brief CLI Options class for handling command-line options
 */
class CLIOptions {
   public:
   /**
    * @brief Get the single instance of CLIOptions
    *
    * @return Pointer to the instance
    */
   static CLIOptions& getInstance();

   /**
    * @brief Default copy constructor for CLIOptions (disabled)
    */
   CLIOptions(CLIOptions const&) = delete;

   /**
    * @brief Default copy assignment operator for CLIOptions (disabled)
    */
   CLIOptions operator=(CLIOptions const&) = delete;

   /**
    * @brief Destruct the instance of CLIOptions
    */
   static void destruct();

   /**
    * @brief Set the configurations for billboards and creatures from
    * command-line arguments
    *
    * @param arguments_count The number of command-line arguments
    * @param arguments The command-line arguments
    */
   void getConfigs(int arguments_count, char* arguments[]);

   /**
    * @brief Get the program configurations
    *
    * @return Program configurations
    */
   ProgramConfig getProgramConfigs() const;

   /**
    * @brief Get the execute option
    *
    * @return The execute option
    */
   bool getExecute() const;

   /**
    * @brief Get the pending configuration
    */
   void getPendingConfig();

   private:
   static CLIOptions*
     instance; ///< Pointer to the single instance of CLIOptions

   ProgramConfig program_configs; ///< Configuration settings for program
   bool execute {
      true
   }; ///< Flag indicating if execution is enabled (default: true)
   string* lost_arguments; ///< Pointer to an array of lost arguments
   int lost_arguments_size; ///< The size of the lost arguments array

   /**
    * @brief Private constructor for creating a new CLIOptions object
    */
   CLIOptions() = default;

   /**
    * @brief Private destructor for destroying the CLIOptions object
    */
   ~CLIOptions() = default;

   /**
    * @brief Verifies the type of a command-line argument
    *
    * @param argument The command-line argument to be verified
    * @return Pointer to the Argument structure representing the argument type
    */
   Argument const* verifyArgument(char* argument) const;

   /**
    * @brief Gets basic configuration settings based on a command-line argument
    *
    * @param argument The command-line argument specifying the configuration
    * type.
    */
   void getBasicConfig(Argument const* argument);

   /**
    * @brief Gets compost configuration settings based on a command-line
    * argument and complementary data
    *
    * @param argument The command-line argument specifying the configuration
    * type.
    * @param complementary Additional data required for configuration
    */
   void getCompostConfig(Argument const* argument, string complementary);

   /**
    * @brief Retrieves lost command-line arguments from a list
    *
    * @param arguments_count The total number of command-line arguments
    * @param last_index The last index processed when searching for lost
    * arguments
    * @param arguments The array of command-line arguments
    */
   int getLostArguments(int arguments_count, int last_index, char* arguments[]);

   /**
    * @brief Gets complex configuration settings based on a command-line
    * argument and additional arguments
    *
    * @param argument The command-line argument specifying the configuration
    * type
    * @param arguments Additional command-line arguments required for
    * configuration
    * @param index The index of the current argument being processed
    */
   void getComplexConfig(
     Argument const* argument, char* arguments_values[], int& index);

   /**
    * @brief Prints help information for command-line usage
    */
   void printHelp();
};

#endif // CLI_OPTIONS_HPP_