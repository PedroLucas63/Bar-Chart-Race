/**
 * @file Bar.hpp
 * @author Pedro Lucas (pedrolucas.jsrn@gmail.com)
 * @brief Declaration of the Bar class for representing and rendering a bar in a
 * bar chart
 * @version 1.0
 * @date 2023-09-29
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef BAR_HPP_
#define BAR_HPP_

#include <string> /// string
using std::string;

#include "fstring.hpp" /// repeat, setStyle, green
using fos::repeat;
using fos::setStyle;

#include <iostream> /// cout
using std::cout;

#include <sstream> /// ostringstream
using std::ostringstream;

#include <iomanip>

///< Definition of system constants >//
constexpr short DEFAULT_BAR_COLOR {
   fos::foreground::green
}; ///< Default bar color

/**
 * @brief The Bar class represents an individual bar in a bar chart
 *
 * The Bar class provides methods to access and modify the bar's properties,
 * such as label, category, and value, as well as a method to render the bar
 * graphically. It leverages the "fstring" library for formatting and styling
 * text output.
 *
 */
class Bar {
   public:
   /**
    * @brief Default constructor for the Bar class
    */
   Bar() { }

   /**
    * @brief Parameterized constructor for the Bar class
    * @param label_ The label of the bar
    * @param other_related_info_ Additional information related to the bar
    * @param category_ The category to which the bar belongs
    * @param value_ The value associated with the bar
    */
   Bar(string label_, string other_related_info_, string category_,
     double long value_)
       : label(label_)
       , other_related_info(other_related_info_)
       , category(category_)
       , value(value_) { }

   /**
    * @brief Overload of the less than (<) operator for the Bar class
    *
    * This operator allows comparing two Bar objects and determining whether the
    * current object is less than the object passed as an argument.
    *
    * @param rhs The Bar object to compare with the current object
    * @return true if the current object is less than rhs, otherwise, false
    */
   bool operator<(Bar const& rhs);

   /**
    * @brief Overload of the greater than (>) operator for the Bar class
    *
    * This operator allows comparing two Bar objects and determining whether the
    * current object is greater than the object passed as an argument.
    *
    * @param rhs The Bar object to compare with the current object
    * @return true if the current object is greater than rhs, otherwise, false
    */
   bool operator>(Bar const& rhs);

   /**
    * @brief Get the label of the bar
    * @return The label of the bar as a string
    */
   string getLabel() const;

   /**
    * @brief Get additional information related to the bar
    * @return Additional information related to the bar as a string
    */
   string getOtherRelatedInfo() const;

   /**
    * @brief Get the category to which the bar belongs
    * @return The category of the bar as a string
    */
   string getCategory() const;

   /**
    * @brief Get the value associated with the bar
    * @return The value of the bar as a double
    */
   double long getValue() const;

   /**
    * @brief Set the label of the bar
    * @param label_ The label to set for the bar
    */
   void setLabel(string label_);

   /**
    * @brief Set additional information related to the bar
    * @param other_related_info_ The additional information to set for the bar
    */
   void setOtherRelatedInfo(string other_related_info_);

   /**
    * @brief Set the category to which the bar belongs
    * @param category_ The category to set for the bar
    */
   void setCategory(string category_);

   /**
    * @brief Set the value associated with the bar
    * @param value_ The value to set for the bar
    */
   void setValue(double long value_);

   /**
    * @brief Draw and render the bar graphically
    * @param bar_size The size of the bar
    * @param _base_value The base value to determine the bar's height (default:
    * 0)
    * @param _color The color to use for rendering the bar (default:
    * DEFAULT_BAR_COLOR)
    */
   void draw(short bar_size, double long _base_value = 0,
     short const _color = DEFAULT_BAR_COLOR) const;

   private:
   string label; ///< The label of the bar
   string other_related_info; ///< Additional information related to the bar
   string category; ///< The category to which the bar belongs
   double long value; ///< The value associated with the bar
};

#endif /// BAR_HPP_
