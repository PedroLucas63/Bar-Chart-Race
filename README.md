# 📊 Bar Chart Race

[![🚀 Download Latest Release](https://img.shields.io/badge/Download-Latest%20Release-blue.svg)](https://github.com/PedroLucas63/bar-chart-race/releases/)

## 📖 Overview

The Bar Chart Race project is a 🌟 C++ program that takes a CSV data file and creates an exciting bar chart race animation over time. It's a powerful tool for visualizing data trends and changes, providing an engaging and dynamic way to explore your data.

## ✨ Features

- Create bar charts with bars of different colors based on categories 🎨.
- Customize which columns to use for data collection 📊.
- Configure animation settings using a configuration file ⚙️.
- Adjust animation speed, the number of bars, the number of ticks, and more 🕐.
- Robust error handling ensures the program runs even with poorly formatted data files, such as having fewer bars or columns than expected 🛠️.
- Requires only the first three lines of the data file to contain the title, time unit, and source, in that order 📝.

## 💡 Usage

```
bar-race [<options>] <input_data_file>
```

## ⚙️ Options

| Option | Description |
| ------ | ----------- |
| -b <num> | Maximum number of bars in a single chart. Valid range is [1, 15]. Default value is 5. |
| -f <num> | Animation speed in frames per second (fps). Valid range is [1, 24]. Default value is 24. |
| -c <local> | Location of the configuration file. |

## 🚀 Building the Project

To build the project, follow these steps:

```bash
cmake -S . -B build
cmake --build build
```

## 📄 License

This project is licensed under the MIT License 📜 - see the [LICENSE](LICENSE) file for details.

## 🤝 Contributions

Contributions are welcome! If you'd like to contribute to this project, please open an issue or submit a pull request 🙌.

## 📧 Contact

- Pedro Lucas 📧
- Email: pedrolucas.jsrn@gmail.com
