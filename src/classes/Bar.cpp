/**
 * @file Bar.cpp
 * @author Pedro Lucas (pedrolucas.jsrn@gmail.com)
 * @brief Declaration of the Bar class for representing and rendering a bar in a
 * bar chart.
 * @version 1.0
 * @date 2023-09-29
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "Bar.hpp"

// Overload of the less than (<) operator for the Bar class
bool Bar::operator<(Bar const& rhs) {
   return value < rhs.getValue();
}

// Overload of the greater than (>) operator for the Bar class
bool Bar::operator>(Bar const& rhs) {
   return value > rhs.getValue();
}

// Get the label of the bar
string Bar::getLabel() const {
   return label;
}

// Get additional information related to the bar
string Bar::getOtherRelatedInfo() const {
   return other_related_info;
}

// Get the category to which the bar belongs
string Bar::getCategory() const {
   return category;
}

// Get the value associated with the bar
double long Bar::getValue() const {
   return value;
}

// Set the label of the bar
void Bar::setLabel(string label_) {
   label = label_;
}

// Set additional information related to the bar
void Bar::setOtherRelatedInfo(string other_related_info_) {
   other_related_info = other_related_info_;
}

// Set the category to which the bar belongs
void Bar::setCategory(string category_) {
   category = category_;
}

// Set the value associated with the bar
void Bar::setValue(double long value_) {
   value = value_;
}

// Draw and render the bar graphically
void Bar::draw(short bar_size, double long _base_value, short const _color) const {
   short size;
   if (_base_value == 0) {
      size = bar_size;
   } else {
      size = (value * bar_size) / _base_value;
   }

   ostringstream oss;
   oss << setStyle(repeat("\u2588", size), _color) << " "
       << setStyle(label, _color) << " ";
   if (!other_related_info.empty()) {
      string buffer { "(" + other_related_info + ")" };
      oss << setStyle(buffer, _color) << " ";
   }
   
   oss << std::fixed << std::setprecision(2);
   oss << "[" << std::fixed << value << "]";

   cout << oss.str() << "\n";
}
