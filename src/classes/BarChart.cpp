/**
 * @file BarChart.cpp
 * @author Pedro Lucas (pedrolucas.jsrn@gmail.com)
 * @brief Implements the member functions of the BarChart class for creating and
 * managing bar charts.
 * @version 1.0
 * @date 2023-09-30
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "BarChart.hpp"

// Destructor for the BarChart class
BarChart::~BarChart() {
   bars.clear();
}

// Getter for the 'time_stamp' attribute
string BarChart::getTimeStamp() const {
   return time_stamp;
}

// Getter for the 'bars' attribute
vector<shared_ptr<Bar>> BarChart::getBars() const {
   return bars;
}

// Setter for the 'time_stamp' attribute
void BarChart::setTimeStamp(string time_stamp_) {
   time_stamp = time_stamp_;
}

// Add a Bar to the 'bars' vector
void BarChart::addBar(Bar const* bar) {
   shared_ptr<Bar> ptr { make_shared<Bar>(*bar) };

   if (bars.empty() && bar) {
      bars.push_back(ptr);
   } else if (bar) {
      shared_ptr<Bar>* local = upperBound<shared_ptr<Bar>>(ptr,
        &(*bars.begin()),
        &(*bars.end()),
        [](shared_ptr<Bar> const& first, shared_ptr<Bar> const& second)
          -> bool { return *(first.get()) > *(second.get()); });

      bars.insert(bars.begin() + distance(&bars.front(), local), ptr);
   }
}

// Draw the BarChart with specified parameters
void BarChart::draw(
  short bar_size, short _view_bars, short _ticks, map<string, short> _colors) const {
   string buffer { "Time stamp: " + time_stamp };

   cout << setStyle(buffer, blue, -1, bold) << "\n\n";

   double max_bar_value { bars.front() ? bars.front().get()->getValue() : 0 };
   _view_bars = _view_bars == 0 ? bars.size() : _view_bars;
   short color { DEFAULT_BAR_COLOR };

   for (short view_bar { 0 }; view_bar != _view_bars; ++view_bar) {
      if (view_bar < bars.size()) {
         Bar* bar { bars[view_bar].get() };

         if (_colors.find(bar->getCategory()) != _colors.end()) {
            color = _colors[bar->getCategory()];
         }

         bar->draw(bar_size, max_bar_value, color);
      } else {
         cout << "\n";
      }

      cout << "\n";
   }

   _ticks = _ticks == 0 ? bars.size() : _ticks;

   double minimum_value { bars.size() > _view_bars ? bars[_view_bars - 1]->getValue() : bars.back()->getValue()};
   minimum_value = static_cast<int>(floor(minimum_value / 100) * 100);
   double maximum_value { bars.front()->getValue() };
   maximum_value  = static_cast<int>(ceil(maximum_value / 100) * 100);

   double divided_distance { (maximum_value - minimum_value) / _ticks};
   int ticks_distance { static_cast<int>(divided_distance * bar_size / maximum_value) };

   short pos_ticks[_ticks];
   pos_ticks[0] = minimum_value * bar_size / maximum_value;

   for (short index { 1 }; index != _ticks - 1; ++index) {
      pos_ticks[index] = pos_ticks[index - 1] + ticks_distance;
   }

   pos_ticks[_ticks - 1] = bar_size;

   string x_axis { repeat("-", bar_size * 2)};
   string numbers { repeat(" ", bar_size * 2)};
   x_axis[0] = '+';
   numbers[0] = 0;

   int value { static_cast<int>(minimum_value) };
   for (short index { 0 }; index != _ticks; ++index) {
      x_axis[pos_ticks[index]] = '+';
      string value_string { std::to_string(value) };
      numbers.replace(pos_ticks[index], 1, value_string);
      value += divided_distance;
   }

   x_axis += '>';

   cout << x_axis << "\n";
   cout << numbers << "\n";
}
