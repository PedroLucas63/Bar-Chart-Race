/**
 * @file fstring.cpp
 * @author Pedro Lucas (pedrolucas.jsrn@gmail.com)
 * @brief Implementation of Text Formatting Functions
 * @version 1.1
 * @date 2023-09-26
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "fstring.hpp"
#include <iostream>

namespace fos {
   // Removes target characters from the left of the string
   std::string leftTrim(std::string const& str, std::string _target) {
      std::string trimmed { str };

      trimmed.erase(0, trimmed.find_first_not_of(_target));

      return trimmed;
   }

   // Removes target characters from the right of the string
   std::string rightTrim(std::string const& str, std::string _target) {
      std::string trimmed { str };

      trimmed.erase(trimmed.find_last_not_of(_target) + 1);

      return trimmed;
   }

   // Removes target characters from both ends of the string
   std::string trim(std::string const& str, std::string _target) {
      std::string trimmed { str };
      trimmed = leftTrim(trimmed);
      trimmed = rightTrim(trimmed);

      return trimmed;
   }

   // Replaces the first occurrence of the target with the replacement string
   std::string replaceFirst(
     std::string const& str, std::string target, std::string _replace) {
      std::string replaced { str };
      size_t search = replaced.find(target);

      if (search != std::string::npos) {
         replaced.replace(search, target.length(), _replace);
      }

      return replaced;
   }

   // Replaces all occurrences of the target with the replacement string
   std::string replace(
     std::string const& str, std::string target, std::string _replace) {
      std::string replaced { replaceFirst(str, target, _replace) };
      std::string buffer;

      while (replaced != buffer) {
         buffer = replaced;
         replaced = replaceFirst(replaced, target, _replace);
      }

      return replaced;
   }

   // Retrieves a substring from a string
   std::string subString(std::string const& str, size_t end, size_t _init) {
      std::ostringstream sub_string;

      for (size_t index { _init }; index < end; ++index) {
         sub_string << str[index];
      }

      return sub_string.str();
   }

   // Splits a string based on a delimiter and stores substrings in a vector
   std::vector<std::string> split(
     std::string const& str, std::string _delimiter) {
      std::string divided { str };
      std::vector<std::string> split_tokens;

      while (divided.find_first_not_of(_delimiter) != std::string::npos) {
         divided.erase(0, divided.find_first_not_of(_delimiter));

         if (divided.find_first_of(_delimiter) != std::string::npos) {
            split_tokens.push_back(
              subString(divided, divided.find_first_of(_delimiter)));
            divided.erase(0, divided.find_first_of(_delimiter));
         } else {
            split_tokens.push_back(subString(divided, divided.length()));
            divided.clear();
         }
      }

      return split_tokens;
   }

   // Divides text into words while retaining additional line breaks
   std::vector<std::string> splitParagraphs(std::string const& str) {
      std::string divided { str };
      std::vector<std::string> split_tokens;
      bool last_text { false };

      while (divided.find_first_not_of("\n") != std::string::npos) {
         size_t break_position { divided.find_first_of("\n") };
         size_t text_position { divided.find_first_not_of("\n") };

         if (break_position < text_position && last_text) {
            split_tokens.push_back("\n");
            last_text = false;
            divided.erase(0, break_position + 1);
         } else if (break_position > text_position
           && break_position != std::string::npos) {
            split_tokens.push_back(subString(divided, break_position));
            divided.erase(0, break_position + 1);
            last_text = true;
         } else if (break_position == std::string::npos) {
            split_tokens.push_back(subString(divided, divided.length()));
            divided.clear();
         } else {
            divided.erase(0, break_position + 1);
         }
      }

      return split_tokens;
   }

   // Repeats an element a specified number of times
   template <typename T>
   std::string repeat(T element, size_t times, bool _max_width) {
      std::ostringstream repeated;

      for (size_t index { 0 }; index < times; ++index) {
         repeated << element;
      }

      std::string repeated_str { repeated.str() };

      if (_max_width) {
         repeated_str.resize(times);
      }

      return repeated_str;
   }

   template std::string repeat<char>(
     char element, size_t times, bool _max_width);
   template std::string repeat<char const*>(
     char const* element, size_t times, bool _max_width);
   template std::string repeat<std::string>(
     std::string element, size_t times, bool _max_width);
   template std::string repeat<int>(int element, size_t times, bool _max_width);
   template std::string repeat<float>(
     float element, size_t times, bool _max_width);
   template std::string repeat<double>(
     double element, size_t times, bool _max_width);

   // Wraps text to a specified width, with a specified delimiter
   std::string columnWrap(std::string& str, size_t size, std::string _delimiter,
     std::string _new_delimiter) {
      std::ostringstream text;
      std::string line;
      std::vector<std::string> phrases { splitParagraphs(str) };

      for (std::string& phrase : phrases) {
         std::string trimmed { trim(phrase) };
         std::vector<std::string> words { split(trimmed, _delimiter) };

         if (words.empty()) {
            text << '\n';
         }

         for (std::string& word : words) {
            if ((line + word).length() >= size) {
               text << line << '\n';

               while (word.length() >= size) {
                  text << subString(word, size) << '\n';
                  word.erase(0, size);
               }

               line.clear();
            }

            line += word;
            line += &word != &words.back() ? _new_delimiter : "";
         }

         if (!line.empty()) {
            text << line << '\n';
            line.clear();
         }
      }

      return text.str();
   }

   // Justifies text within a specified width and alignment
   template <typename T>
   std::string alignment(std::string& str, size_t size, align _align,
     T _element, bool _dynamic_size, bool _right_space) {
      std::ostringstream justified;
      std::vector<std::string> phrases { splitParagraphs(str) };

      std::string longest_line { trim(findLongestLine(str)) };
      size_t max_size { longest_line.length() };

      if (!_dynamic_size && max_size > size) {
         throw std::invalid_argument(
           "Some lines have a width greater than the defined width.");
      } else if (_dynamic_size && max_size < size) {
         size = max_size;
      }

      for (std::string& phrase : phrases) {
         std::string trimmed { fos::trim(phrase) };
         size_t free_space { size - trimmed.length() };
         bool is_even { free_space % 2 == 0 };

         if (_align == align::left) {
            justified << trimmed;
         } else if (_align == align::center) {
            justified << repeat(_element, free_space / 2, true) << trimmed;
            free_space /= 2;
         } else if (_align == align::right) {
            justified << repeat(_element, free_space, true) << trimmed;
         } else if (_align == align::justify) {
            std::vector<std::string> words { fos::split(trimmed, " ") };

            if (words.size() == 0) {
               justified << fos::repeat(_element, free_space, true);
            } else if (words.size() == 1) {
               justified << words.front()
                         << fos::repeat(_element, free_space, true);
            } else {
               size_t spaces { words.size() + free_space - 1 };
               size_t spaces_per_word { spaces / (words.size() - 1) };
               size_t spaces_truncated { spaces % (words.size() - 1) };

               for (std::string& word : words) {
                  if (&word == &words.back()) {
                     break;
                  }

                  justified << word
                            << fos::repeat(_element, spaces_per_word, true);

                  if (spaces_truncated != 0) {
                     justified << repeat(_element, 1, true);
                     --spaces_truncated;
                  }
               }

               justified << words.back();
            }
         }

         if (_right_space && _align == align::left && !trimmed.empty()) {
            justified << repeat(_element, free_space, true);
         } else if (_right_space && _align == align::center) {
            free_space += !is_even ? 1 : 0;
            justified << repeat(_element, free_space, true);
         }

         justified << '\n';
      }

      return justified.str();
   }

   template std::string alignment<char>(std::string& str, size_t size,
     align _align, char _element = ' ', bool _dynamic_size, bool _right_space);
   template std::string alignment<char const*>(std::string& str, size_t size,
     align _align, char const* _element = " ", bool _dynamic_size,
     bool _right_space);
   template std::string alignment<std::string>(std::string& str, size_t size,
     align _align, std::string _element = " ", bool _dynamic_size,
     bool _right_space);
   template std::string alignment<int>(std::string& str, size_t size,
     align _align, int _element = 0, bool _dynamic_size, bool _right_space);
   template std::string alignment<float>(std::string& str, size_t size,
     align _align, float _element = 0, bool _dynamic_size, bool _right_space);
   template std::string alignment<double>(std::string& str, size_t size,
     align _align, double _element = 0, bool _dynamic_size, bool _right_space);

   // Concatenates a collection of strings with a specified separator
   template <typename T>
   std::string concat(T* init, T* end, std::string _separator) {
      std::ostringstream concatenated;

      while (init != end) {
         concatenated << *init++;

         if (init != end) {
            concatenated << _separator;
         }
      }

      return concatenated.str();
   }

   template std::string concat<char>(
     char* init, char* end, std::string _separator);
   template std::string concat<std::string>(
     std::string* init, std::string* end, std::string _separator);
   template std::string concat<int>(
     int* init, int* end, std::string _separator);
   template std::string concat<float>(
     float* init, float* end, std::string _separator);
   template std::string concat<double>(
     double* init, double* end, std::string _separator);

   // Reverses the characters in a string
   std::string reverse(std::string const& str) {
      std::ostringstream reversed;

      for (size_t index { str.length() }; index != 0; --index) {
         reversed << str[index - 1];
      }

      return reversed.str();
   }

   // Counts the number of lines in a string
   size_t countLines(std::string const& str) {
      return (split(str, "\n")).size();
   }

   // Applies text styling to a string.
   std::string setStyle(std::string const& str, short const _color,
     short const _background, short const _style) {
      std::ostringstream text;
      std::ostringstream styled_escape;

      if (_style != style::none) {
         styled_escape << "\33[" << _style << 'm';
      }
      if (_color != foreground::none) {
         styled_escape << "\33[" << _color << 'm';
      }
      if (_background != background::none) {
         styled_escape << "\33[" << _background << 'm';
      }

      std::ostringstream regular_escape;
      regular_escape << "\33[" << style::regular << 'm';

      text << styled_escape.str() << str << regular_escape.str();

      return text.str();
   }

   // Finds the longest line of text
   std::string findLongestLine(std::string const& str) {
      std::vector<std::string> lines { splitParagraphs(str) };
      std::string max_line { lines.front() };
      std::string max_line_trimmed { trim(max_line) };

      for (std::string line : lines) {
         std::string trimmed { trim(line) };
         if (max_line.size() < line.size()) {
            max_line = line;
            max_line_trimmed = trim(line);
         } else if (max_line.size() == line.size()
           && trimmed.size() > max_line_trimmed.size()) {
            max_line = line;
            max_line_trimmed = trim(line);
         }
      }

      return max_line;
   }

   // Makes each line of a string the same length
   template <typename T>
   std::string completeLines(
     std::string const& str, size_t _size, T _complete) {
      if (_size == 0) {
         _size = findLongestLine(str).size();
      }

      std::vector<std::string> lines { splitParagraphs(str) };

      for (std::string& line : lines) {
         line += repeat(_complete, _size - line.size(), true);
      }

      return concat(&lines.front(), &(lines.back()) + 1, "\n");
   }

   template std::string completeLines<char>(
     std::string const& str, size_t _size, char _complete = ' ');
   template std::string completeLines<char const*>(
     std::string const& str, size_t _size, char const* _complete = " ");
   template std::string completeLines<std::string>(
     std::string const& str, size_t _size, std::string _complete = " ");
   template std::string completeLines<int>(
     std::string const& str, size_t _size, int _complete);
   template std::string completeLines<float>(
     std::string const& str, size_t _size, float _complete);
   template std::string completeLines<double>(
     std::string const& str, size_t _size, double _complete);

   // Inverts characters in a given string according to specific rules
   std::string invertCharacters(std::string const& str) {
      std::string new_string;

      for (size_t index { 0 }; index < str.length(); ++index) {
         if (str[index] == '(') {
            new_string.push_back(')');
         } else if (str[index] == ')') {
            new_string.push_back('(');
         } else if (str[index] == '[') {
            new_string.push_back(']');
         } else if (str[index] == ']') {
            new_string.push_back('[');
         } else if (str[index] == '{') {
            new_string.push_back('}');
         } else if (str[index] == '}') {
            new_string.push_back('{');
         } else if (str[index] == '\\') {
            new_string.push_back('/');
         } else if (str[index] == '/') {
            new_string.push_back('\\');
         } else if (str[index] == '<') {
            new_string.push_back('>');
         } else if (str[index] == '>') {
            new_string.push_back('<');
         } else {
            new_string.push_back(str[index]);
         }
      }

      return new_string;
   }

} // namespace fos
