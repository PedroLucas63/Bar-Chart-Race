/**
 * @file fileini.cpp
 * @brief Implementation of the FileIni class for handling .ini files and its
 * methods.
 * @author Pedro Lucas (pedrolucas.jsrn@gmail.com)
 * @version 1.0
 * @date 2023-09-27
 *
 * @copyright Copyright (c) 2023
 */

#include "fileini.hpp"

/// Constructor that takes the location of the .ini file to load
FileIni::FileIni(string local_file) {
   open(local_file);
}

/// Overloaded subscript operator for accessing values by section
map<string, string> FileIni::operator[](string section) const {
   try {
      return configs.at(section);
   } catch (...) { return {}; }
}

/// Opens and loads the specified .ini file
void FileIni::open(string local_file) {
   ifstream file(local_file);

   if (!file.is_open()) {
      throw std::runtime_error(
        "The .ini file does not exist or cannot be opened.");
   }

   string line;
   string last_section { "global" };
   while (std::getline(file, line)) {
      string key;
      string value;
      string section;
      bool catch_section { false };
      bool get_key { false };
      bool get_value { false };
      bool get_quotes { false };

      // The following loop parses each line of the .ini file
      for (char c : line) {
         if ((c == ';' || c == '#') && !get_quotes) {
            break;
         } else if (c == '[' && !get_quotes) {
            catch_section = true;
         } else if (c == ']' && !get_quotes) {
            last_section = section;
            catch_section = false;
         } else if (c == '\"' && catch_section && !get_quotes) {
            get_quotes = true;
         } else if (c == '\"' && catch_section && get_quotes) {
            get_quotes = false;
         } else if (catch_section) {
            section += c;
         } else if (c == '\"' && !get_key && !get_quotes) {
            get_quotes = true;
         } else if (c == '\"' && !get_key && get_quotes) {
            get_quotes = false;
         } else if (c == '=' && !get_key && get_quotes) {
            key += c;
         } else if (c == '=' && !get_key) {
            get_key = true;
         } else if (!get_key) {
            key += c;
         } else if (c == '\"' && get_key && !get_quotes) {
            get_quotes = true;
         } else if (c == '\"' && get_key && get_quotes) {
            get_quotes = false;
         } else if (!get_value) {
            value += c;
         }
      }
      section = trim(section);
      key = trim(key);
      value = trim(value);

      if (!last_section.empty() && !key.empty() && !value.empty()) {
         configs[last_section][key] = value;
      }
   }
}

/// Retrieves the configurations as a map of sections containing key-value pairs
map<string, map<string, string>> FileIni::getConfigs() const {
   return configs;
}