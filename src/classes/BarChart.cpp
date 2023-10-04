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
void BarChart::draw(short bar_size, short _view_bars, short _ticks,
  short _terminal_size, map<string, short> _colors) const {
   string buffer { "Time stamp: " + time_stamp };

   if (_terminal_size != 0) {
      buffer = columnWrap(buffer, _terminal_size);
      buffer = alignment(buffer, _terminal_size, center, " ");
   }

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

   drawAxisX(bar_size, _view_bars, _ticks, _terminal_size);
}

void BarChart::drawAxisX(
  short bar_size, short _view_bars, short _ticks, short _terminal_size) const {

   string axis_x;

   if (_terminal_size != 0) {
      axis_x = repeat('-', _terminal_size - 1);
   } else {
      axis_x = repeat('-', bar_size * 2 - 1);
   }

   axis_x += '>';

   string axis_x_numbers { repeat(' ', bar_size * 2 - 1) };

   if (_ticks == 0 && _view_bars > bars.size()) {
      _ticks = bars.size();
   } else if (_ticks == 0) {
      _ticks = _view_bars;
   } else if (_ticks > bars.size()) {
      _ticks = bars.size();
   }

   short last_bar;

   if (_ticks < _view_bars && _view_bars < bars.size()) {
      last_bar = _view_bars - 1;
   } else if (_ticks < _view_bars) {
      last_bar = bars.size() - 1;
   } else {
      last_bar = _ticks - 1;
   }

   double maximum_value { ceil(bars.front()->getValue() / 100) * 100 };
   double minimum_value { floor(bars[last_bar]->getValue() / 100) * 100 };
   double divided { floor((maximum_value - minimum_value) / _ticks) };

   double values[_ticks + 1];
   values[0] = 0;

   double value { minimum_value };

   for (short index { 1 }; index != _ticks; ++index) {
      values[index] = value;
      value += divided;
   }

   values[_ticks] = maximum_value;

   for (short tick { 0 }; tick != _ticks + 1; ++tick) {
      short position { static_cast<short>(
        values[tick] * bar_size / values[_ticks]) };

      axis_x[position] = '+';

      string value_str = to_string(static_cast<int>(values[tick]));
      axis_x_numbers.replace(position, value_str.size(), value_str);
   }

   cout << axis_x << "\n";
   cout << setStyle(axis_x_numbers, yellow, -1, bold) << "\n";
}