#include "labyrinthe3d.h"
#include "ui_labyrinthe3d.h"

Labyrinthe3D::Labyrinthe3D(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Labyrinthe3D)
{
    ui->setupUi(this);
}

Labyrinthe3D::~Labyrinthe3D()
{
    delete ui;
}

