
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

#include "fstring.hpp" /// alignment, columnWrap, repeat, setStyle, center, blue, yellow, bold
using fos::alignment;
using fos::columnWrap;
using fos::repeat;
using fos::setStyle;
using fos::align::center;
using fos::foreground::blue;
using fos::foreground::yellow;
using fos::style::bold;

#include <string> /// string, to_string
using std::string;
using std::to_string;

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

#include <math.h> /// ceil, floor, round
using std::ceil;
using std::floor;
using std::round;

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
     short _terminal_size = 0, map<string, short> _colors = {}) const;

   private:
   string time_stamp; ///< The time stamp associated with the BarChart
   vector<shared_ptr<Bar>> bars; ///< A vector of shared pointers to Bar objects

   /**
    * @brief Draw a horizontal bar below the chart with ticks representing
    * intervals
    *
    * This function draws a horizontal bar below the chart with ticks that
    * represent intervals between the largest and smallest elements in the
    * chart. It allows you to customize the size of the bar, the number of
    * displayed ticks, and the terminal size for proper formatting
    *
    * @param bar_size Size of the horizontal bar
    * @param _view_bars Number of bars to display (0 to show all)
    * @param _ticks Number of ticks to display on the horizontal bar (0 for
    * none)
    * @param _terminal_size Terminal size for proper formatting (0 for default
    * value)
    *
    * @note Ensure that chart data is available before calling this function
    */
   void drawAxisX(short bar_size, short _view_bars = 0, short _ticks = 0,
     short _terminal_size = 0) const;
};

#endif /// BAR_CHART_HPP_