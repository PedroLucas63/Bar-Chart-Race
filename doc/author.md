# Introduction

<!-- TODO -->
The Bar Chart Race project is a 🌟 C++ program that takes a CSV data file and creates an exciting bar chart race animation over time. It's a powerful tool for visualizing data trends and changes, providing an engaging and dynamic way to explore your data.

# Author(s)

<!-- TODO -->
Pedro Lucas Medeiros do Nascimento,
pedrolucas.jsrn@gmail.com

# Problems found or limitations

No problems.

# Grading

<!-- TODO -->
Preencha os itens que você implementou, indicando qual a nota esperada para cada item.


Item     | Valor máximo   | Valor esperado
-------- | :-----: | :-----:
Read, validate, and process command line arguments | 5 | 5
Program runs with default values, if no options are provided | 5 | 5
Read the input data file and store the information in memory    | 10 | 10
Display a summary of the data read from the input file _before_ the animation starts | 5 | 5
Display a summary of the running options (set by the user or default values) _before_ the animation starts | 5 | 5
The project contains at least two classes | 10 | 10
Create individual bar charts containing all data items for a single date | 10 | 10
Run the bar chart animation at the correct speed | 10  | 10
The bar chart anatomy is complete and correct | 30 | 30
Program handles errors properly | 10 | 10

Teste a configuração de colunas via config.example.ini com o arquivo data/covid19_full.csv

Nota: Se funcionar foi eu quem fiz, se não funcionar não foi eu (testado apenas com duas variações de colunas).

# Compiling and Running

```bash
cmake -S . -B build
cmake --build build
```
