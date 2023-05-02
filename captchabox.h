/*
 *@file:   captchabox.h
 *@author: 缪庆瑞
 *@date:   2016.12.10
 *@brief:  存放验证码的区域
 */
#ifndef CAPTCHABOX_H
#define CAPTCHABOX_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

class CaptchaBox : public QWidget
{
    Q_OBJECT

public:
    explicit CaptchaBox(QWidget *parent = 0);
    ~CaptchaBox();
    void generateCaptcha(int count=4);//Générer un code de vérification aléatoire, 4 chiffres par défaut

    bool checkCaptcha(QString text);//Vérifiez que le code de vérification saisi est correct

protected:
    virtual void paintEvent(QPaintEvent *event);//remplacer l'événement de dessin
    virtual void mousePressEvent(QMouseEvent *event);

private:
    void initCharset();//Initialiser le jeu de caractères
    void initColorset();//Initialiser le jeu de couleurs
    void initDefaultFont();//Initialiser la police

    void drawDisturb(QPainter &painter);//Dessiner des éléments interférents
    //Transformation morphologique
    void rotateAngle(QPainter &painter);//Angle de rotation
    void scaleSize(QPainter &painter);//taille du zoom
    void shearForm(QPainter &painter);//forme déformée

    void drawCaptcha(QPainter &painter);//dessiner un captcha

signals:

public slots:

private:
    int boxHeight;//La largeur et la hauteur du composant sont automatiquement déterminées par la police
    int boxWidth;

    QStringList charSetEn;//Jeu de caractères Captcha - chiffres, lettres
    //QStringList charSetCh;//Jeu de caractères Captcha - Caractères chinois
    QStringList captchaChars;//Un certain nombre de personnages générés aléatoirement

    QList<QColor> colorSet;//Jeu de couleurs Captcha
};

#endif // CAPTCHABOX_H
