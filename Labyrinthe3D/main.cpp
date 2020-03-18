#include "labyrinthe3d.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Labyrinthe3D menu_principal;
    menu_principal.show();
    return a.exec();
}
