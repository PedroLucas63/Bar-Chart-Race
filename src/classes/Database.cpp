/**
 * @file Database.cpp
 * @author Pedro Lucas (pedrolucas.jsrn@gmail.com)
 * @brief
 * @version 1.0
 * @date 2023-10-02
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "Database.hpp"

Database::~Database() {
   bar_charts.clear();
}

string Database::getTitle() const {
   return title;
}
string Database::getScale() const {
   return scale;
}
string Database::getSource() const {
   return source;
}
map<string, short> Database::getCategories() const {
   return categories;
}
vector<shared_ptr<BarChart>> Database::getBarCharts() const {
   return bar_charts;
}

void Database::setTitle(string title_) {
   title = title_;
}
void Database::setScale(string scale_) {
   scale = scale_;
}
void Database::setSource(string source_) {
   source = source_;
}
bool Database::addCategory(string text, short color) {
   if (categories.find(text) == categories.end()) {
      categories[text] = color;
         if (categories.size() > NUMBER_OF_COLORS) {
      for (auto& category : categories) {
         category.second = fos::foreground::green;
      }
   }
   return true;
   }

   return false;
}

void Database::addBarChart(BarChart const* bar_chart) {
   if (bar_chart) {
      shared_ptr<BarChart> ptr { make_shared<BarChart>(*bar_chart) };
      bar_charts.push_back(ptr);
   }
}

void Database::draw(short fps, short bar_size, short _view_bars, short _ticks,
  short _terminal_size) const {
   for (shared_ptr<BarChart> bar_chart : bar_charts) {
      std::chrono::milliseconds time(1000 / fps);
      std::this_thread::sleep_for(time);

      string buffer { title };

      if (_terminal_size != 0) {
         buffer = columnWrap(buffer, _terminal_size);
         buffer = alignment(buffer, _terminal_size, center, " ");
      }

      cout << setStyle(buffer, blue, -1, bold) << "\n\n";

      bar_chart->draw(bar_size, _view_bars, _ticks, _terminal_size, categories);

      cout << setStyle(scale, yellow, -1, bold) << "\n\n";
      cout << setStyle(source, -1, -1, bold) << "\n";

      if (categories.size() <= NUMBER_OF_COLORS) {
      for (auto category : categories) {
         cout << setStyle("\u2588", category.second, -1, bold) << ": ";
         cout << setStyle(category.first, category.second, -1, bold) << " ";
      }
      }

      cout << "\n\n";
   }
}