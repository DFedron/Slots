//
//  main.cpp
//  Slots
//  This slots mini game need to install the ncurses library
//  Created by huidong wang on 10/21/22.
//

#include <iostream>
#include <ncurses.h>
#include <string>
#include <cstring>
#include <ctime>
#include <random>
using namespace std;
void start();
void game ();
int main(int argc, const char * argv[]) {
    
    initscr();
    noecho();
    keypad(stdscr, true);
    nodelay(stdscr, true);
    curs_set(0);

    start();
    
    getch();
    
    endwin();
    return 0;
}


void start() {
  string option[2] = {"Spin", "Exit"};
  int hightlight = 0;
  int choice;
  int init = 0;
  while (true) {
    WINDOW *mainMenu = newwin(4, 20, 15, (COLS-20)/2);
    box(mainMenu, 0, 0);
    refresh();
    
    keypad(mainMenu, true);
      
      
    for (int i = 0; i < 2; ++i) {
      if (i == hightlight)
        wattron(mainMenu, A_REVERSE);
      mvwprintw(mainMenu, i + 1, (20 - 4) / 2, option[i].c_str());
      wattroff(mainMenu, A_REVERSE);
    }
    wrefresh(mainMenu);
      
    string slots[3] = {"9   J   A   Q   10", "A   10   J   K   9", "J   K   A   10   Q"};
      string test[3] = {" ", " " , " "};
    WINDOW * gameWin = newwin(12, 40, 0, (COLS-40)/2);
    box(gameWin, 0, 0);
    
    
    if(init == 0){
        for (int i = 1; i <= 3; ++i) {
            mvwprintw(gameWin, i + i * 2, (40 - 17) / 2, slots[i-1].c_str());
        }
        refresh();
        wrefresh(gameWin);
        init = 1;
    }

    
    choice = wgetch(mainMenu);
    switch (choice) {
    case 10:
//      return hightlight;
      if(hightlight == 1){
          return;
      }
      else if(hightlight == 0){
          
          int min = 10000, max = 99999;
          random_device seed;
          ranlux48 engine(seed());
          uniform_int_distribution<> distrib(min, max);
          string Item[6] = {"9   ", "10  ", "J   ", "Q   ", "K   ", "A   "};
          string resultOnScree[3];
          for(int i = 0; i < 3; ++i){
              int random = distrib(engine);
              string tempString;
              for(int j = 0; j < 5; ++j){
                  int num = random % 10;
                  if(num >= 6)
                      num %= 6;
                  tempString = Item[num] + tempString;
                  random /= 10;
              }
              resultOnScree[i] = tempString;
          }
          
          WINDOW *answerWin = newwin(12, 40, LINES - 15, (COLS-40)/2);
          for (int i = 1; i <= 3; ++i) {
              mvwprintw(answerWin, i * 2 + i, (40 - 17) / 2, resultOnScree[i-1].c_str());
          }
          refresh();
          wrefresh(answerWin);
          
          
          clock_t timeStart = clock();
          while(true){
              if ((clock() - timeStart) / CLOCKS_PER_SEC >= 2){
                  for (int i = 1; i <= 3; ++i) {
                      if(i == 2)
                          wattron(gameWin, A_REVERSE);
                      mvwprintw(gameWin, i * 2 + i, (40 - 17) / 2, resultOnScree[i-1].c_str());
                      wattroff(gameWin, A_REVERSE);
                  }
                  refresh();
                  wrefresh(gameWin);
                  
                  break;
              } // time in seconds
              for (int i = 1; i <= 3; ++i) {
                            mvwprintw(gameWin, i + i * 2, (40 - 17) / 2, slots[(1+i)%3].c_str());
                        }
//                        wtimeout(gameWin, 3000);
                        refresh();
                        wrefresh(gameWin);
                        for (int i = 1; i <= 3; ++i) {
                            mvwprintw(gameWin, i * 2 + i, (40 - 17) / 2, slots[i-1].c_str());
                        }
                        refresh();
                        wrefresh(gameWin);
              
          }
          
          
      }
      break;
    case KEY_UP:
      --hightlight;
      if (hightlight < 0)
        hightlight = 0;
      break;
    case KEY_DOWN:
      ++hightlight;
      if (hightlight > 1)
        hightlight = 1;
      break;
    default:
      break;
    }

  }


}

