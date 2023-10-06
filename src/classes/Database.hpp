/**
 * @file Database.hpp
 * @author Pedro Lucas (pedrolucas.jsrn@gmail.com)
 * @brief Represents a database for storing and managing bar chart data.
 * @version 1.0
 * @date 2023-10-02
 *
 * The Database class provides functionality for storing information about bar
 * charts, including their titles, scales, sources, categories, and actual bar
 * chart data.
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef DATABASE_HPP_
#define DATABASE_HPP_

#include "BarChart.hpp"

#include <vector> /// vector
using std::vector;

#include <string> /// string
using std::string;

#include <memory> /// shared_ptr, make_shared
using std::make_shared;
using std::shared_ptr;

#include <map> /// map
using std::map;

#include <iostream> /// iostream
using std::cout;

#include <chrono>
#include <thread>

#include "fstring.hpp" /// alignment, columnWrap, setStyle, center, blue, yellow, bold
using fos::alignment;
using fos::columnWrap;
using fos::setStyle;
using fos::align::center;
using fos::foreground::blue;
using fos::foreground::yellow;
using fos::style::bold;

///< Definition of system constants >//
constexpr short NUMBER_OF_COLORS { 14 }; ///< Number of colors >//

/**
 * @class Database
 * @brief Represents a database for storing and managing bar chart data
 *
 * The Database class provides functionality for storing information about bar
 * charts, including their titles, scales, sources, categories, and actual bar
 * chart data.
 */
class Database {
   public:
   /**
    * @brief Default constructor for the Database class
    */
   Database() { }

   /**
    * @brief Constructor for the Database class
    * @param title_ Title of the database
    * @param scale_ Scale of the database
    * @param source_ Source of the database
    */
   Database(string title_, string scale_, string source_)
       : title(title_), scale(scale_), source(source_) { }

   /**
    * @brief Destructor for the Database class
    */
   ~Database();

   /**
    * @brief Get the title of the database
    * @return The title of the database
    */
   string getTitle() const;

   /**
    * @brief Get the scale of the database
    * @return The scale of the database
    */
   string getScale() const;

   /**
    * @brief Get the source of the database
    * @return The source of the database
    */
   string getSource() const;

   /**
    * @brief Get the categories stored in the database
    * @return A map of category names to colors
    */
   map<string, short> getCategories() const;

   /**
    * @brief Get the bar charts stored in the database
    * @return A vector of shared pointers to BarChart objects
    */
   vector<shared_ptr<BarChart>> getBarCharts() const;

   /**
    * @brief Set the title of the database
    * @param title_ The new title for the database
    */
   void setTitle(string title_);

   /**
    * @brief Set the scale of the database
    * @param scale_ The new scale for the database
    */
   void setScale(string scale_);

   /**
    * @brief Set the source of the database
    * @param source_ The new source for the database
    */
   void setSource(string source_);

   /**
    * @brief Add a category to the database
    * @param text The name of the category
    * @param color The color associated with the category
    * @return True if the category was added successfully, false otherwise
    */
   bool addCategory(string text, short color);

   /**
    * @brief Add a bar chart to the database
    * @param bar_chart A pointer to a BarChart object to add
    */
   void addBarChart(BarChart const* bar_chart);

   /**
    * @brief Draw the database's content with customizable parameters
    * @param fps Frames per second for the drawing
    * @param bar_size Size of the bars in the chart
    * @param _view_bars Number of bars to display (0 to show all)
    * @param _ticks Number of ticks to display (0 for none)
    * @param _terminal_size Terminal size for proper formatting (0 for default)
    */
   void draw(short fps, short bar_size, short _view_bars = 0, short _ticks = 0,
     short _terminal_size = 0) const;

   private:
   string title; ///< Title of the database

   string scale; ///< Scale of the database

   string source; ///< Source of the database

   map<string, short> categories; ///< Map of category names to colors

   vector<shared_ptr<BarChart>>
     bar_charts; ///< Vector of shared pointers to BarChart objects
};

#endif /// DATABASE_HPP_