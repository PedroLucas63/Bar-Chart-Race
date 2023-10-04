/**
 * @file Database.hpp
 * @author Pedro Lucas (pedrolucas.jsrn@gmail.com)
 * @brief 
 * @version 1.0
 * @date 2023-10-02
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

#include "fstring.hpp" /// setStyle, blue, yellow, bold
using fos::setStyle;
using fos::columnWrap;
using fos::alignment;
using fos::foreground::blue;
using fos::foreground::yellow;
using fos::align::center;
using fos::style::bold;

constexpr short NUMBER_OF_COLORS { 14 };

class Database {
   public:

   Database(){}
   Database(string title_, string scale_, string source_) : title(title_), scale(scale_), source(source_) {}
   ~Database();

   string getTitle() const;
   string getScale() const;
   string getSource() const;
   map<string, short> getCategories() const;
   vector<shared_ptr<BarChart>> getBarCharts() const;

   void setTitle(string title_);
   void setScale(string scale_);
   void setSource(string source_);
   bool addCategory(string text, short color);
   void addBarChart(BarChart const* bar_chart);

   void draw(short fps, short bar_size, short _view_bars = 0, short _ticks = 0, short _terminal_size = 0) const;

   private:
   string title;
   string scale;
   string source;
   map<string, short> categories;
   vector<shared_ptr<BarChart>> bar_charts;
};

#endif /// DATABASE_HPP_