#include "include/tuihandler.h"
#include <ncurses.h>
#include <locale.h>

int selectmenu(WINDOW* menu_win);

void tuimenu_start(void) {
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    setlocale(LC_ALL, "");
    clear();

    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_WHITE, COLOR_CYAN);

    bkgd(COLOR_PAIR(1));

    WINDOW* menu_win = newwin(30, 100, 1, 1);
    box(menu_win, 0, 0);
    keypad(menu_win, TRUE);

    wattron(menu_win, COLOR_PAIR(2));
    wattron(menu_win, A_BOLD);
    mvwprintw(menu_win, 0, 2, " Motiana1 メインメニュー ");
    wattroff(menu_win, A_BOLD);
    wattroff(menu_win, COLOR_PAIR(2));

    refresh();
    wrefresh(menu_win);

    while(1) {
        if (selectmenu(menu_win) != 0) {
            break;
        }
        wrefresh(menu_win);
    }

    endwin();
}

int selectmenu(WINDOW* menu_win) {
    const char *choices[] = {"Option 1", "Option 2", "Option 3", "終了"};
    int n_choices = 4;
    static int highlight = 0;
    int choice = -1;
    int c;
    for(int i = 0; i < n_choices; i++) {
        if(i == highlight) {
            wattron(menu_win, A_REVERSE);
        }
        mvwprintw(menu_win, i + 2, 2, "%s", choices[i]);
        wattroff(menu_win, A_REVERSE);
    }
    wrefresh(menu_win);

    c = wgetch(menu_win);
    switch(c) {
        case KEY_UP:
            highlight = (highlight == 0) ? n_choices - 1 : highlight - 1;
            break;
        case KEY_DOWN:
            highlight = (highlight == n_choices - 1) ? 0 : highlight + 1;
            break;
        case 10:
            choice = highlight;
            break;
    }
    if(choice != -1) {
        return -1;
    }
    return 0;
}