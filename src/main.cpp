/**
 * @file main.cpp
 * @author pedro Lucas (pedrolucas.jsrn@gmail.com)
 * @brief Entry point for the game application.
 * @version 1.0
 * @date 2023-09-29
 *
 * This file contains the main function, which serves as the entry point for the
 * game application. It creates an instance of the GameController class,
 * initializes it, and enters a loop where it processes events, updates the game
 * state, and renders the game until the game is over. Finally, it cleans up the
 * GameController instance before exiting the program.
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "Database.hpp"
#include "GameController.hpp" ///< Include the GameController class header
#include <stdlib.h> ///< Include the standard library for EXIT_SUCCESS

int main(int argc, char* argv[]) {
   GameController& app {
      GameController::getInstance()
   }; ///< Create a GameController instance

   // Initialize the GameController with command-line arguments
   app.initialize(argc, argv);

   Bar bar1_1 {"Pedro", "", "Masculino", 10};
   Bar bar1_2 {"Moisés", "", "Masculino", 20};
   Bar bar1_3 {"Ana", "", "Feminino", 15};
   Bar bar1_4 {"Renata", "", "Feminino", 40};

   BarChart bar_chart1 {"01-01-1999"};
   bar_chart1.addBar(&bar1_1);
   bar_chart1.addBar(&bar1_2);
   bar_chart1.addBar(&bar1_3);
   bar_chart1.addBar(&bar1_4);

   Bar bar2_1 {"Pedro", "", "Masculino", 50};
   Bar bar2_2 {"Moisés", "", "Masculino", 20};
   Bar bar2_3 {"Ana", "", "Feminino", 30};
   Bar bar2_4 {"Renata", "", "Feminino", 45};

   BarChart bar_chart2 {"01-01-2000"};
   bar_chart2.addBar(&bar2_1);
   bar_chart2.addBar(&bar2_2);
   bar_chart2.addBar(&bar2_3);
   bar_chart2.addBar(&bar2_4);

   Bar bar3_1 {"Pedro", "", "Masculino", 70};
   Bar bar3_2 {"Moisés", "", "Masculino", 110};
   Bar bar3_3 {"Ana", "", "Feminino", 220};
   Bar bar3_4 {"Renata", "", "Feminino", 10};
   Bar bar3_5 {"Ahtgk", "Klan autres", "Alien", 1};

   BarChart bar_chart3 {"01-01-2001"};
   bar_chart3.addBar(&bar3_1);
   bar_chart3.addBar(&bar3_2);
   bar_chart3.addBar(&bar3_3);
   bar_chart3.addBar(&bar3_4);
   bar_chart3.addBar(&bar3_5);

   Bar bar4_1 {"Pedro", "", "Masculino", 29356};
   Bar bar4_2 {"Moisés", "", "Masculino", 3232};
   Bar bar4_3 {"Ana", "", "Feminino", 32434};
   Bar bar4_4 {"Renata", "", "Feminino", 23644};
   Bar bar4_5 {"Ahtgk", "Klan autres", "Alien", 32244};
   Bar bar4_6 {"Jdoii", "Klan Uhinh", "Alien", 2245};

   BarChart bar_chart4 {"01-01-2002"};
   bar_chart4.addBar(&bar4_1);
   bar_chart4.addBar(&bar4_2);
   bar_chart4.addBar(&bar4_3);
   bar_chart4.addBar(&bar4_4);
   bar_chart4.addBar(&bar4_5);
   bar_chart4.addBar(&bar4_6);

   Database database { "Nomes de criancas no seculo XXI\nNovidades do oriente", "Milhoes", "Source: NASA"};
   database.addCategory("Masculino", fos::foreground::blue);
   database.addCategory("Feminino", fos::foreground::red);
   database.addBarChart(&bar_chart1);
   database.addBarChart(&bar_chart2);
   database.addCategory("Alien", fos::foreground::green);
   database.addBarChart(&bar_chart3);
   database.addBarChart(&bar_chart4);

   database.draw(1, 40, 6, 0, 80);

   // Main game loop.
   /*while (!app.gameOver()) {
      app.processEvent(); ///< Process game events
      app.update(); ///< Update the game state
      app.render(); ///< Render the game
      // The loop continues until the game is over
   }*/

   app.destruct(); ///< Clean up the GameController instance

   return EXIT_SUCCESS; ///< Return a successful exit status
}