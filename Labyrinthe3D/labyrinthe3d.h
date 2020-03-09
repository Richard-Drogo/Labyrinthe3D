#ifndef LABYRINTHE3D_H
#define LABYRINTHE3D_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Labyrinthe3D; }
QT_END_NAMESPACE

class Labyrinthe3D : public QMainWindow
{
    Q_OBJECT

public:
    Labyrinthe3D(QWidget *parent = nullptr);
    ~Labyrinthe3D();

private:
    Ui::Labyrinthe3D *ui;
};
#endif // LABYRINTHE3D_H
