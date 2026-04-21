#include "include/tuihandler.h"
#include <ncurses.h>
#include <locale.h>

void tuimenu_start(void) {
    initscr();
    cbreak();
    setlocale(LC_ALL, "");

    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);

    bkgd(COLOR_PAIR(1));

    WINDOW* menu_win = newwin(30, 100, 1, 1);
    box(menu_win, 0, 0);

    mvwprintw(menu_win, 1, 1, "日本語表示テスト。");
    refresh();
    wrefresh(menu_win);

    getch();

    endwin();
}