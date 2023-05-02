/*
 *@file:   captchabox.cpp
 *@author: 缪庆瑞
 *@date:   2016.12.10
 *@brief:  存放验证码的区域
 */
#include "captchabox.h"
#include "time.h"
#include <QtGlobal>
#include <QDebug>
#include <QLabel>

#define FONTSIZE 20    //La macro définit la taille de la police
//#define FONTFAMILY "宋体"
#define ROTATEANGLE 20  //L'angle de rotation maximal du code de vérification
#define SIZEINCREMENT 12//L'incrément de la taille du widget par rapport à la taille de l'espace réellement occupé par la police

CaptchaBox::CaptchaBox(QWidget *parent)
    : QWidget(parent)
{
    qsrand(time(0));//générer une graine de nombre aléatoire
    initCharset();
    initColorset();
    initDefaultFont();
    generateCaptcha();

    /*problème nouvellement découvert
    Problème d'arrière-plan : je souhaite voir la taille et la position du composant, et définir la couleur d'arrière-plan de la feuille de style, mais cela ne fonctionne pas. Découvrez les composants qui
    héritent directement de QWidget grâce aux tests
    Les feuilles de style peuvent être définies en tant que fenêtres de niveau supérieur, mais pas en tant que fenêtres enfants. Trouvé une solution par requête, document d'aide Qt style sheets reference
    QWidgetpaintEvent Il existe en partie une solution, en Ajouter quelques mots à la fonction de traitement des événements, mais je ne sais pas pourquoi, donc je ne l'étudierai pas pour le moment
    this->setStyleSheet("background-color: red;");*/
}

CaptchaBox::~CaptchaBox()
{

}
/*
 *@author:  缪庆瑞
 *@date:    2016.12.10
 *@brief:   初始化验证码的可用字符集
 */
void CaptchaBox::initCharset()
{
    //Initialiser les caractères anglais (chiffres et lettres majuscules et minuscules)
    QString tempStringEn(tr("0123456789abcdefghijklmnopqrstuvwxyz"
                            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"));
    for(int i=0;i<tempStringEn.size();i++)
    {
        charSetEn.append(tempStringEn.mid(i,1));
    }
    //Initialiser le jeu de caractères chinois (prenez simplement quelques paroles)
    /*QString tmpStringCh(tr("昨夜同门云集推杯又换盏今朝茶凉酒寒豪言成笑谈半生累尽徒然碑文完美有谁看"
                      "隐居山水之间誓与浮名散湖畔青石板上一把油纸伞旅人停步折花淋湿了绸缎"
                      "满树玉瓣多傲然江南烟雨却痴缠花飞雨追一如尘缘理还乱落花雨你飘摇的美丽"
                      "花香氤把往日情勾起我愿意化浮萍躺湖心只陪你泛岁月的涟漪古木檀香小筑经文诵得缓"
                      "锦服华裳一炬粗袖如心宽林中抚琴曲委婉群山听懂我悲欢泪如雨落才知过往剪不断"
                      "落花雨你飘摇在天地晚风急吹皱芳华太无情我愿意化流沙躺湖堤只陪你恭候春夏的轮替"));
    for(int i =0;i<tmpStringCh.size();i++)
    {
        charSetCh.append(tmpStringCh.mid(i,1));
    }*/
}
/*
 *@author:  缪庆瑞
 *@date:    2016.12.10
 *@brief:   初始化验证码的可用颜色集
 */
void CaptchaBox::initColorset()
{
    //Utilisez la valeur d'énumération QT pour initialiser la collection de couleurs.
    //Choisissez une couleur plus foncée et la couleur claire n'est pas facile à reconnaître par l'œil humain.
    colorSet<<QColor(Qt::black)<<QColor(Qt::red)<<QColor(Qt::darkRed)<<QColor(Qt::darkGreen)
           <<QColor(Qt::blue)<<QColor(Qt::darkBlue)<<QColor(Qt::darkCyan)<<QColor(Qt::magenta)
          <<QColor(Qt::darkMagenta)<<QColor(Qt::darkYellow);
}
/*
 *@author:  缪庆瑞
 *@date:    2016.12.10
 *@brief:   初始化默认使用的字体
 */
void CaptchaBox::initDefaultFont()
{
    QFont defaultFont;//police par défaut
    //defaultFont.setFamily(tr(FONTFAMILY));
    defaultFont.setPointSize(FONTSIZE);
    defaultFont.setBold(true);//mettre la police en gras
    this->setFont(defaultFont);
}
/*
 *@author:  缪庆瑞
 *@date:    2016.12.10
 *@brief:   生成随机验证码
 *@param:   count：验证码的位数
 */
void CaptchaBox::generateCaptcha(int count)
{
    captchaChars.clear();
    if(qrand()%2)//Générer aléatoirement des séquences alphanumériques
    {
        int num = charSetEn.size();//Obtenir la taille du jeu de caractères
        for(int i=0;i<count;i++)
        {
            captchaChars.append(charSetEn.at(qrand()%num));
        }
    }
    /*else//Générer aléatoirement des séquences chinoises
    {
        int num = charSetCh.size();
        for(int i=0;i<count/2;i++)//中文个数是字母的一半
        {
            captchaChars.append(charSetCh.at(qrand()%num));
        }
    }*/
    /* 根据验证码的字符和所设字体，确定整个验证码区域的高度和宽度。
     * 整个区域的大小会略大于验证码字符实际的大小。
     * 注：因为字符的宽度除了与字体有关系外,可能还与字符本身有关系。为了避免不同的
     * 验证码产生不同的宽度导致整个部件大小变化，这里以一个固定的英文字符(W,基本上
     * 是所有英文字符中最宽的)求宽
     */
    boxHeight = this->fontMetrics().height()+SIZEINCREMENT;
    boxWidth = this->fontMetrics().width("W")*count+SIZEINCREMENT;
    this->setFixedSize(boxWidth,boxHeight);//définir la taille de la zone
}
/*
 *@author:  缪庆瑞
 *@date:    2016.12.11
 *@brief:   绘制干扰元素  可以以后针对性添加
 *@param:   painter:绘制的工具，是paintevent中的引用
 */
void CaptchaBox::drawDisturb(QPainter &painter)
{
    int num = colorSet.size();//obtenir un jeu de couleurs
    switch(qrand()%3)
    {
    case 0: //Quatre lignes d'interférence aléatoires horizontales
        painter.setPen(QPen(QBrush(QColor(colorSet.at(qrand()%num))),1));
        painter.drawLine(0,qrand()%boxHeight,boxWidth,qrand()%boxHeight);
        painter.drawLine(0,qrand()%boxHeight,boxWidth,qrand()%boxHeight);
        painter.drawLine(0,qrand()%boxHeight,boxWidth,qrand()%boxHeight);
        painter.drawLine(0,qrand()%boxHeight,boxWidth,qrand()%boxHeight);
        break;
    case 1: //dessiner des points de bruit
        for(int i=0;i<150;i++)
        {
            painter.setPen(QPen(QBrush(QColor(colorSet.at(qrand()%num))),1));
            painter.drawPoint(qrand()%boxWidth,qrand()%boxHeight);
        }
        break;
    case 2: //Lignes d'interférence horizontales et verticales
        painter.setPen(QPen(QBrush(QColor(colorSet.at(qrand()%num))),1));
        painter.drawLine(0,boxHeight/5,boxWidth,boxHeight/5);
        painter.drawLine(0,boxHeight/5*2,boxWidth,boxHeight/5*2);
        painter.drawLine(0,boxHeight/5*3,boxWidth,boxHeight/5*3);
        painter.drawLine(0,boxHeight/5*4,boxWidth,boxHeight/5*4);
        painter.drawLine(boxWidth/6,0,boxWidth/6,boxHeight);
        painter.drawLine(boxWidth/6*2,0,boxWidth/6*2,boxHeight);
        painter.drawLine(boxWidth/6*3,0,boxWidth/6*3,boxHeight);
        painter.drawLine(boxWidth/6*4,0,boxWidth/6*4,boxHeight);
        painter.drawLine(boxWidth/6*5,0,boxWidth/6*5,boxHeight);
        break;
    default :break;
    }
}
/*
 *@author:  缪庆瑞
 *@date:    2016.12.11
 *@brief:   随机旋转角度
 *@param:   painter:绘制的工具，是paintevent中的引用
 */
void CaptchaBox::rotateAngle(QPainter &painter)
{
    //Rotation aléatoire dans le sens des aiguilles d'une montre d'un angle aléatoire
    if(qrand()%2)
    {
        painter.rotate(qrand()%ROTATEANGLE);
    }
    //Rotation aléatoire dans le sens antihoraire par angle aléatoire
    else
    {
        painter.rotate(-qrand()%ROTATEANGLE);
    }
}
/*
 *@author:  缪庆瑞
 *@date:    2016.12.11
 *@brief:   随机放缩大小
 *@param:   painter:绘制的工具，是paintevent中的引用
 */
void CaptchaBox::scaleSize(QPainter &painter)
{
    //这里将放缩范围设置为0.9-1.1,scale
    double xSize = (qrand()%3+9)/10.0;
    double ySize = (qrand()%3+9)/10.0;
    painter.scale(xSize,ySize);
}
/*
 *@author:  缪庆瑞
 *@date:    2016.12.10
 *@brief:   随机扭曲字符
 *@param:   painter:绘制的工具，是paintevent中的引用
 */
void CaptchaBox::shearForm(QPainter &painter)
{
    //L'effet de distorsion est similaire à la combinaison
    //de rotation et de mise à l'échelle, qui reflète un effet tridimensionnel et peut être utilisé seul
    //范围-0.3-0.3
    double xShear = qrand()%4/10.0;
    double yShear = qrand()%4/10.0;
    if(qrand()%2)
    {
        xShear = -xShear;
    }
    if(qrand()%2)
    {
        yShear = -yShear;
    }
    painter.shear(xShear,yShear);
}
/*
 *@author:  缪庆瑞
 *@date:    2016.12.10
 *@brief:   绘制产生的随机验证码
 *@param:   painter:绘制的工具，是paintevent中的引用
 */
void CaptchaBox::drawCaptcha(QPainter &painter)
{
    drawDisturb(painter);//Dessinez d'abord les éléments distrayants

    int num = colorSet.size();//Obtenir la taille du jeu de couleurs
    //Selon la taille du composant de code de vérification,
    //l'espace occupé par chaque caractère est divisé de manière égale et la taille incrémentielle est allouée aux blancs gauche et droit du composant
    int charWidth = (boxWidth-SIZEINCREMENT)/captchaChars.size();
    for(int i=0;i<captchaChars.size();i++)
    {
        painter.setPen(QColor(colorSet.at(qrand()%num)));//Réglez le pinceau sur une couleur aléatoire
        //Enregistrez l'état du peintre actuel, principalement l'état du système de coordonnées,
        //car les opérations suivantes telles que la translation et la rotation seront utilisées pour changer le système de coordonnées
        painter.save();
        /* 因为rotate默认以坐标原点旋转，所以通过平移改变原点，以各文本原点旋转
         * 这里为了保证实际字符居中在各自的空间，需要求出字符左右留白的长度，同时将增量
         * 大小分给整个部件的左右留白
         */
        int charSpace = (charWidth-this->fontMetrics().width(captchaChars.at(i)))/2;
        charSpace += SIZEINCREMENT/2;
        painter.translate(i*charWidth+charSpace,0);
        if(qrand()%2)
        {
            //Déformation d'échelle par rotation
            rotateAngle(painter);
            scaleSize(painter);
        }
        else
        {
            shearForm(painter);//Déformer le texte directement
        }
        /* 前两个参数指定画文本的起始位置，以文本左下角为起始点
         * 平移变换起始点的横坐标实际是i*charWidth+charSpace
         */
        painter.drawText(0,boxHeight-SIZEINCREMENT,captchaChars.at(i));
        painter.restore();//restaurer l'état précédent
    }
}
/*
 *@author:  缪庆瑞
 *@date:    2016.12.11
 *@brief:   检验输入的验证码是否正确
 *@return:  bool类型
 */
bool CaptchaBox::checkCaptcha(QString text)
{
    QString captchaString = captchaChars.join("");
    //qDebug()<<captchaString;
    if(text.compare(captchaString,Qt::CaseInsensitive)==0)//Pas sensible à la casse
    {
        return true;
    }
    else
    {
        return false;
    }
}
/*
 *@author:  缪庆瑞
 *@date:    2016.12.10
 *@brief:   绘制整个验证码区域
 */
void CaptchaBox::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);//painter Héritera automatiquement de la police du périphérique de dessin (this)
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(Qt::white));
    QRect rect(QPoint(0,0),this->size());
    painter.drawRect(rect);//L'arrière-plan général du code de vérification est défini sur blanc

    drawCaptcha(painter);
    QWidget::paintEvent(event);
}
/*
 *@author:  缪庆瑞
 *@date:    2016.12.10
 *@brief:   重写鼠标事件，点击更换验证码
 */
void CaptchaBox::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        generateCaptcha();//générer un nouveau captcha
        update();//repeindre
    }
    QWidget::mousePressEvent(event);//Manipulez la pression de la souris avant d'effectuer le remplacement
}

