/**
 * @file fileini.hpp
 * @brief Definition of the FileIni class for handling .ini files and its methods.
 * @author Pedro Lucas (pedrolucas.jsrn@gmail.com)
 * @version 1.0
 * @date 2023-09-27
 * 
 * @copyright Copyright (c) 2023
 */

#ifndef FILEINI_HPP_
#define FILEINI_HPP_

#include <string> /// string
using std::string;
#include <fstream> /// ifstream
using std::ifstream;
#include <map> /// map
using std::map;
#include "fstring.hpp" /// trim
using fos::trim;

/**
 * @class FileIni
 * @brief Class for handling .ini files
 */
class FileIni {
public:
   /**
    * @brief Default constructor for the FileIni class
    */
   FileIni() { }

   /**
    * @brief Constructor that takes the location of the .ini file to load
    * @param local_file The path of the .ini file to load
    */
   FileIni(string local_file);

   /**
    * @brief Destructor for the FileIni class
    */
   ~FileIni() { }

   /**
    * @brief Overloaded subscript operator for accessing values by section
    * @param section The section to access the values
    * @return A map of section-key pairs
    */
   map<string, string> operator[](string section) const;

   /**
    * @brief Opens and loads the specified .ini file
    * @param local_file The path of the .ini file to open and load
    */
   void open(string local_file);

   /**
    * @brief Retrieves the configurations as a map of sections containing key-value pairs
    * @return A map of sections and their associated key-value pairs
    */
   map<string, map<string, string>> getConfigs() const;
private:
   map<string, map<string, string>> configs; ///< map of section-key-value >/
};

#endif /// FILEINI_HPP_
