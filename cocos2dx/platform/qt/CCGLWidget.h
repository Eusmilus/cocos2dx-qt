#ifndef  _GL_WIDGET_H_
#define  _GL_WIDGET_H_

#include "CCDirector.h"
#include "CCCommon.h"
#undef CursorShape
#include <QtOpenGL/QGLWidget>

USING_NS_CC;

class QTimer;
class CC_DLL GLWidget : public QGLWidget
{
    Q_OBJECT

    typedef void(*PTRFUN)(QMouseEvent *event);

public:
    GLWidget(){}
    GLWidget(int width, int height, CCDirector* director = NULL, QWidget *parent = 0);

    void setMouseMoveFunc(PTRFUN func);
    void setMousePressFunc(PTRFUN func);
    void setMouseReleaseFunc(PTRFUN func);


protected:
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

public slots:
    void update();

private:
    PTRFUN mouseMoveFunc;
    PTRFUN mousePressFunc;
    PTRFUN mouseReleaseFunc;

    CCDirector* m_director;
    QTimer      *m_timer;
};

#endif // _GL_WIDGET_H_
