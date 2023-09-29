/**
 * @file clioptions.cpp
 * @author Pedro Lucas (pedrolucas.jsrn@gmail.com)
 * @brief Implementation of the CLIOptions class for handling command-line
 * options.
 * @version 1.0
 * @date 2023-09-26
 *
 * This file contains the implementation of the CLIOptions class, which is
 * responsible for parsing and managing command-line options for the
 * application. It defines functions to retrieve and handle various command-line
 * configurations.
 *
 *
 * @copyright Copyright (c) 2023
 */

#include "clioptions.hpp"

CLIOptions* CLIOptions::instance = nullptr;

// Gets the single instance of CLIOptions
CLIOptions& CLIOptions::getInstance() {
   if (instance == nullptr) {
      instance = new CLIOptions;
   }

   return *instance;
}

// Destroys the instance of CLIOptions
void CLIOptions::destruct() {
   delete instance;
   instance = nullptr;
}

// Parses command-line arguments to obtain configurations
void CLIOptions::getConfigs(int arguments_count, char* arguments[]) {
   for (int index { FIRST_ARGUMENT_INDEX }; index < arguments_count; ++index) {
      Argument const* argument = verifyArgument(arguments[index]);

      if (argument->type == BASIC) {
         getBasicConfig(argument);
      } else if (argument->type == COMPOST || argument->type == COMPLEX) {
         if (index + 1 != arguments_count) {
            if (argument->type == COMPOST) {
               getCompostConfig(argument, arguments[++index]);

            } else {
               getComplexConfig(argument, arguments, ++index);
            }
         } else {
            ostringstream oss;
            oss << "The argument \"" << argument->code
                << "\" needs some complementary argument. The default will be "
                   "set.";
            program_configs.warnings.push_back(oss.str());
         }
      } else if (argument->type == NONE) {
         string unknown_argument { arguments[index] };

         if (unknown_argument[0] == '-') {
            ostringstream oss;
            oss << "Unknow option: \"" << unknown_argument << "\"";
            program_configs.warnings.push_back(oss.str());
            ++index;
         }

         index = getLostArguments(arguments_count, index, arguments);
      }
   }
}

// Retrieves program configurations
ProgramConfig CLIOptions::getProgramConfigs() const {
   return program_configs;
}

// Retrieves the execute option
bool CLIOptions::getExecute() const {
   return execute;
}

// Verifies the type of a command-line argument
Argument const* CLIOptions::verifyArgument(char* argument) const {
   for (Argument const& arg : arguments) {
      if (arg.code == argument) {
         return &arg;
      }
   }

   return &arguments[ARG_UNDEFINED];
};

// Handles basic configuration settings
void CLIOptions::getBasicConfig(Argument const* argument) {
   if (argument == &arguments[ARG_HELP]) {
      program_configs.help_menu = true;
   }
}

// Handles compound configuration settings
void CLIOptions::getCompostConfig(
  Argument const* argument, string complementary) {
   if (argument == &arguments[ARG_FPS]) {
      try {
         short fps { static_cast<short>(stoi(complementary)) };

         if (fps < MINIMUM_FPS || fps > MAXIMUM_FPS) {
            ostringstream oss;
            oss << "The value of \"" << argument->code << "\" must be between ["
                << MINIMUM_FPS << ", " << MAXIMUM_FPS
                << "]. The default value will be set.";
            program_configs.warnings.push_back(oss.str());
         } else {
            program_configs.frames_per_second = fps;
         }
      } catch (...) {
         ostringstream oss;
         oss << "The value of \"" << argument->code
             << "\" must be of type "
                "integer. The default value will be set.";
         program_configs.warnings.push_back(oss.str());
      }
   } else if (argument == &arguments[ARG_BARS]) {
      try {
         short bars { static_cast<short>(stoi(complementary)) };

         if (bars < MINIMUM_BARS || bars > MAXIMUM_BARS) {
            ostringstream oss;
            oss << "The value of \"" << argument->code << "\" must be between ["
                << MINIMUM_BARS << ", " << MAXIMUM_BARS
                << "]. The default value will be set.";
            program_configs.warnings.push_back(oss.str());
         } else {
            program_configs.number_of_bars = bars;
         }
      } catch (...) {
         ostringstream oss;
         oss << "The value of \"" << argument->code
             << "\" must be of type "
                "integer. The default value will be set.";
         program_configs.warnings.push_back(oss.str());
      }
   } else if (argument == &arguments[ARG_BARS_SIZE]) {
      try {
         short bars_size { static_cast<short>(stoi(complementary)) };

         if (bars_size < MINIMUM_BARS_SIZE || bars_size > MAXIMUM_BARS_SIZE) {
            ostringstream oss;
            oss << "The value of \"" << argument->code << "\" must be between ["
                << MINIMUM_BARS_SIZE << ", " << MAXIMUM_BARS_SIZE
                << "]. The default value will be set.";
            program_configs.warnings.push_back(oss.str());
         } else {
            program_configs.bars_size = bars_size;
         }
      } catch (...) {
         ostringstream oss;
         oss << "The value of \"" << argument->code
             << "\" must be of type "
                "integer. The default value will be set.";
         program_configs.warnings.push_back(oss.str());
      }
   } else if (argument == &arguments[ARG_FILE_CONFIG]) {
      complementary = trim(complementary);

      if (complementary.empty()) {
         ostringstream oss;
         oss << "The value of \"" << argument->code
             << "\" cannot be empty. Entry disregarded.";
         program_configs.warnings.push_back(oss.str());
      } else {
         program_configs.config_file = complementary;
      }
   }
}

// Handles complex configuration settings (currently commented out)
void CLIOptions::getComplexConfig(
  Argument const* argument, char* arguments_values[], int& index) { }

// Prints help information for command-line usage
void CLIOptions::printHelp() { }

// Retrieves lost command-line arguments
int CLIOptions::getLostArguments(
  int arguments_count, int last_index, char* arguments[]) {
   lost_arguments_size = arguments_count - last_index;
   lost_arguments = new string[lost_arguments_size];

   for (int l_index { 0 }; l_index < lost_arguments_size; ++l_index) {
      if (l_index == 0) {
         program_configs.data_file = trim(arguments[last_index++]);
      } else {
         lost_arguments[l_index] = arguments[last_index++];
      }
   }

   return last_index;
}

// Retrieves pending configurations from lost arguments or standard input
void CLIOptions::getPendingConfig() { }