#include <QPalette>
#include "qthelper.h"

QTHelper::QTHelper()
{

}

QTHelper::~QTHelper()
{
    arreterMusique();
}


void QTHelper::jouerMusique(QString path){
    arreterMusique();
    playlist_ = new QMediaPlaylist();
    playlist_->addMedia(QUrl(path));
    playlist_->setPlaybackMode(QMediaPlaylist::Loop);

    player_ = new QMediaPlayer();
    player_->setPlaylist(playlist_);
    player_->play();
}

void QTHelper::jouerSon(QString path){

    if(son_ == Q_NULLPTR){
        path_son_en_cours_ = path;
        son_ = new QSound(path);
        son_->play();
    } else {
        if(path_son_en_cours_ == path){
            if(son_->isFinished() == true){
                son_->play();
            }
        } else {
            delete son_;
            path_son_en_cours_ = path;
            son_ = new QSound(path);
            son_->play();
        }
    }
}

void QTHelper::arreterSon(){
    if(son_ != Q_NULLPTR){
        son_->stop();
        delete son_;
        son_ = Q_NULLPTR;
    }
}

void QTHelper::arreterMusique(){
    if(player_ != Q_NULLPTR){
        player_->stop();
        delete player_;
        player_ = Q_NULLPTR;
        if(playlist_ != Q_NULLPTR){
            delete playlist_;
            playlist_ = Q_NULLPTR;
        }
    }
}

void QTHelper::setImageDeFond(QWidget * widget, QString chemin){
    QPixmap image_de_fond(chemin);
    image_de_fond = image_de_fond.scaled(widget->size());

    QPalette palette;
    palette.setBrush(QPalette::Background, image_de_fond);
    widget->setPalette(palette);
}
