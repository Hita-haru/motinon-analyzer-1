#include "include/tuihandler.h"
#include <iostream>
#include <locale.h>

int main() {
    setlocale(LC_ALL, ""); //日本語表示
    std::cout << "Starting main finction...." << std::endl;
    tuimenu_start();
    return 0;
}
