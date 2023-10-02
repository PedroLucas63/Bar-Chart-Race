
/**
 * @file BarChart.hpp
 * @author Pedro Lucas (pedrolucas.jsrn@gmail.com)
 * @brief Defines the BarChart class, which represents a bar chart with
 * associated data.
 * @version 1.0
 * @date 2023-09-30
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef BAR_CHART_HPP_
#define BAR_CHART_HPP_

#include "Bar.hpp"

#include "searching.hpp" /// upperBound
using sch::upperBound;

#include "fstring.hpp" /// setStyle, blue, bold
using fos::setStyle;
using fos::repeat;
using fos::foreground::blue;
using fos::style::bold;

#include <string> /// string
using std::string;

#include <vector> /// vector
using std::vector;

#include <memory> /// shared_ptr, make_shared
using std::make_shared;
using std::shared_ptr;

#include <iterator> /// next, distance
using std::distance;
using std::next;

#include <map> /// map
using std::map;

#include <iostream> /// cout
using std::cout;

#include <math.h>
using std::floor;
using std::ceil;

/**
 * @brief The BarChart class represents a bar chart with associated data
 */
class BarChart {
   public:
   /**
    * @brief Default constructor for the BarChart class
    */
   BarChart() { }

   /**
    * @brief Constructor for the BarChart class with a specified time stamp
    *
    * @param time_stamp_ The time stamp associated with the BarChart
    */
   BarChart(string time_stamp_) : time_stamp(time_stamp_) {};

   /**
    * @brief Destructor for the BarChart class
    */
   ~BarChart();

   /**
    * @brief Get the time stamp associated with the BarChart
    *
    * @return The time stamp as a string
    */
   string getTimeStamp() const;

   /**
    * @brief Get a vector of shared pointers to the Bar objects in the BarChart
    *
    * @return A vector of shared pointers to Bar objects
    */
   vector<shared_ptr<Bar>> getBars() const;

   /**
    * @brief Set the time stamp associated with the BarChart
    *
    * @param time_stamp_ The new time stamp as a string
    */
   void setTimeStamp(string time_stamp_);

   /**
    * @brief Add a new Bar object to the BarChart
    *
    * @param bar A pointer to the Bar object to be added
    */
   void addBar(Bar const* bar);

   /**
    * @brief Draw the BarChart with specified parameters
    *
    * @param bar_size The size of each bar
    * @param _view_bars The number of bars to display
    * @param _colors A map of colors for different categories
    */
   void draw(short bar_size, short _view_bars = 0, short _ticks = 0,
     map<string, short> _colors = {}) const;

   private:
   string time_stamp; ///< The time stamp associated with the BarChart
   vector<shared_ptr<Bar>> bars; ///< A vector of shared pointers to Bar objects
};

#endif /// BAR_CHART_HPP_