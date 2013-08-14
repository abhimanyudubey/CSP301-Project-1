#include "game_menu.h"
#include "ui_game_menu.h"

Game_Menu::Game_Menu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Game_Menu)
{
    ui->setupUi(this);
}

Game_Menu::~Game_Menu()
{
    delete ui;
}
