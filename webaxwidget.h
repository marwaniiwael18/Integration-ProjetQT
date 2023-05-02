#ifndef WEBAXWIDGET_H
#define WEBAXWIDGET_H

#include <ActiveQt/QAxWidget>
#include "windows.h"

class WebAxWidget : public QAxWidget
{
public:

    WebAxWidget(QWidget *parent = nullptr, Qt::WindowFlags f = 0)
        : QAxWidget(parent, f)
    {
    }
protected:
    bool translateKeyEvent(int message, int keycode) const Q_DECL_OVERRIDE
    {
        if (message >= WM_KEYFIRST && message <= WM_KEYLAST)
            return true;
        return QAxWidget::translateKeyEvent(message, keycode);
    }

};

#endif // WEBAXWIDGET_H
