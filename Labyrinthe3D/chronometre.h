#ifndef CHRONOMETRE_H
#define CHRONOMETRE_H

#include <QTimer>
#include <QObject>
#include <QLabel>

/* Classe Chronometre
Rôle : Cette classe est le modèle de chronomètre utilisé dans le Labyrinthe.
*/
class Chronometre : public QObject
{
    Q_OBJECT

public:
    /* Chronometre(QLabel * label_chronometre)
    Rôle : Constructeur de la classe Chronomètre (Modèle)
    Entrée : QLabel *, pointeur vers le QLabel ou sera affiché le temps écoulé.
    */
    Chronometre(QLabel * label_chronometre);

    // Début : Méthodes publiques
    void start() {timer_->start(INTERVALLE);};
    void stop() {timer_->stop();};
    /* QString getTempsEcoule()
    Rôle : Permet de retourner le temps écoulé sous forme de QString pour l'afficher dans le QLabel des Records notamment.
    Sortie : Une QString représentant le temps écoulé sous la forme suivante : jour, heures, minutes, secondes.
    */
    QString getTempsEcoule();
    /* quint32 getTempsInt()
    Rôle : Retourne le temps écoulé en seconde sous forme d'un quint32. Pour être comparé avec le record précédent.
    Sorti : quint32, le temps écoulé en secondes.
    */
    quint32 getTempsInt() {return (secondes_ + minutes_ * 60 + heures_ * 60 * 60 + jours_ * 24 * 60 * 60);};
    // Fin : Méthodes publiques

private:
    QLabel * label_chronometre_ = Q_NULLPTR; // Pointeur vers le QLabel ou sera affiché le temps. (Celui du labyrinthe)

    // Début : Attributs de la gestion du temps
    QTimer * timer_ = Q_NULLPTR;
    quint8 secondes_ = 0;
    quint8 minutes_ = 0;
    quint8 heures_ = 0;
    quint16 jours_ = 0;
    const quint16 INTERVALLE = 1000; // Le timer déclenche le signal "timeout()" toutes les INTERVALLE ms.
    // Début : Attributs de la gestion du temps

private slots:
    /*
    Rôle : Slot activé par le signal "timeout()" du timer cette fonction permet d'incrémenter le temps écoulé.
    */
    void augmenter1Seconde();
};

#endif // CHRONOMETRE_H
