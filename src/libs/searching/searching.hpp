/**
 * @file searching.hpp
 * @author Pedro Lucas (pedrolucas.jsrn@gmail.com)
 * @brief Contains utility functions for searching algorithms and custom
 * comparison functions.
 * @version 1.0
 * @date 2023-09-30
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef SEARCHING_HPP_
#define SEARCHING_HPP_

#include <functional> /// function, less
using std::function;
using std::less;

#include <iterator> /// distance, next, prev
using std::distance;
using std::next;
using std::prev;

namespace sch {
   /**
    * @brief Alias for a comparison function object used in searching
    * algorithms
    *
    * This alias defines a function type for comparing two elements of DataType.
    * It is used as a custom comparison function in search algorithms.
    *
    * @tparam DataType The data type to be compared
    */
   template <typename DataType>
   using Compare = function<bool(DataType const&, DataType const&)>;

   /**
    * @brief Find the upper bound of a value in a range using a custom
    * comparison function
    *
    * This function finds the upper bound of a value in a range defined by
    * [begin, end). It uses a custom comparison function to determine the bound.
    *
    * @tparam DataType The data type of elements in the range
    * @param value The value to find the upper bound for
    * @param begin The iterator to the beginning of the range
    * @param end The iterator to the end of the range
    * @param _comp A custom comparison function (default is less<>)
    * @return A pointer to the upper bound element within the range
    */
   template <typename DataType>
   DataType* upperBound(DataType value, DataType* begin, DataType* end,
     Compare<DataType> _comp = less<>()) {
      DataType* bound { end-- };

      while (begin <= end) {
         size_t dist { static_cast<size_t>(distance(begin, end)) };
         DataType* middle { next(begin, dist / 2) };

         if (_comp(value, *middle)) {
            bound = middle;
            end = prev(middle);
         } else {
            begin = next(middle);
         }
      }

      return bound;
   }
}

#endif /// SEARCHING_HPP_
