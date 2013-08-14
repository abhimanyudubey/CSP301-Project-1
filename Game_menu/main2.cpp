#include "game_menu.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Game_Menu w;
    w.show();
    
    return a.exec();
}
