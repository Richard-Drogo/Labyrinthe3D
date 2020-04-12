#ifndef QTHELPER_H
#define QTHELPER_H

#include <QWidget>
#include <QString>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QSound>

/* Classe QTHelper
Rôle : Classe permettant de gérer la musique, les sons et les images de fond des widgets.
*/
class QTHelper
{
public:
    QTHelper();    
    ~QTHelper();

    // Début : Méthodes nécessitant une instanciation
    void jouerMusique(QString path);
    void arreterMusique();
    void jouerSon(QString path);
    void arreterSon();
    // Fin : Méthodes nécessitant une instanciation

    static void setImageDeFond(QWidget * widget, QString chemin); // Méthode statique pouvant s'utiliser sans instanciation


private:
    // Début : Attributs pour la gestion de la musique de fond
    QMediaPlaylist * playlist_ = Q_NULLPTR;
    QMediaPlayer * player_ = Q_NULLPTR;
    // Fin : Attributs pour la gestion de la musique de fond

    // Début : Attributs pour la gestion des sons
    QString path_son_en_cours_ = "";
    QSound * son_ = Q_NULLPTR;
    // Fin : Attributs pour la gestion des sons
};

#endif // QTHELPER_H
