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
  short bar_size, short _view_bars, map<string, short const> _colors) const {
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
}
