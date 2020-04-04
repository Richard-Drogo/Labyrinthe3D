#include <QDebug>

#include "chronometre.h"

Chronometre::Chronometre(QLabel * label_chronometre) : QObject()
{
    timer_ = new QTimer();
    timer_->setInterval(INTERVALLE);
    label_chronometre_ = label_chronometre;
    connect(timer_, SIGNAL(timeout()), this, SLOT(augmenter1Seconde()));
}

void Chronometre::augmenter1Seconde(){
    secondes_++;
    if(secondes_ == 60){
        secondes_ = 0;
        minutes_++;
        if(minutes_ == 60){
            minutes_ = 0;
            heures_++;
            if(heures_ == 24){
                heures_ = 0;
                jours_++;
            }
        }
    }

    label_chronometre_->setText(getTempsEcoule());
}

QString Chronometre::getTempsEcoule(){
    quint8 type_affichage = 0;
    // type_affichage = 1 => Secondes uniquement
    // type_affichage = 2 => Minutes
    // type_affichage = 3 => Heures
    // type_afficahge = 4 => Jours

    if(jours_ == 0){
        if(heures_ == 0){
            if(minutes_ == 0){
                type_affichage = 1;
            } else {
                type_affichage = 2;
            }
        } else {
            type_affichage = 3;
        }
    } else {
        type_affichage = 4;
    }

    switch (type_affichage){
    case 1:{
        return QString(QString::number(secondes_) + tr("s"));
    }break;

    case 2:{
        return QString(QString::number(minutes_) + tr("m") + QString::number(secondes_) + tr("s"));
    }break;

    case 3:{
        return QString(QString::number(heures_) + tr("h") + QString::number(minutes_) + tr("m") + QString::number(secondes_) + tr("s"));
    }break;

    case 4:{
        return QString(QString::number(jours_) + tr("j") + QString::number(heures_) + tr("h") + QString::number(minutes_) + tr("m") + QString::number(secondes_) + tr("s"));
    }break;

    default:{
        qDebug() << tr("Erreur dans le chronomètre ! Type d'afficahge inconnu ! : ") << type_affichage;
        return QString(tr("ERREUR!"));
    }break;
    }
}
