#ifndef CHRONOMETRE_H
#define CHRONOMETRE_H

#include <QTimer>
#include <QObject>
#include <QLabel>

class Chronometre : public QObject
{
    Q_OBJECT

public:
    Chronometre(QLabel * label_chronometre);
    void start() {timer_->start(INTERVALLE);};
    void stop() {timer_->stop();};
    QString getTempsEcoule();
    quint32 getTempsInt() {return (secondes_ + minutes_ * 60 + heures_ * 60 * 60 + jours_ * 24 * 60 * 60);};
private:
    QTimer * timer_ = Q_NULLPTR;
    QLabel * label_chronometre_ = Q_NULLPTR;

    quint8 secondes_ = 0;
    quint8 minutes_ = 0;
    quint8 heures_ = 0;
    quint16 jours_ = 0;

    const quint16 INTERVALLE = 1000;


private slots:
    void augmenter1Seconde();
};

#endif // CHRONOMETRE_H
