#include "CCGLWidget.h"
#include <QtCore/QTimer>

GLWidget::GLWidget(int width, int height, CCDirector* director, QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
    , mouseMoveFunc(NULL)
    , mousePressFunc(NULL)
    , mouseReleaseFunc(NULL)
    , m_director(director)
{
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
    m_timer->start(1000 / 60);

    resize(width, height);
}

void GLWidget::setMouseMoveFunc(PTRFUN func)
{
    mouseMoveFunc = func;
}

void GLWidget::setMousePressFunc(PTRFUN func)
{
    mousePressFunc = func;
}

void GLWidget::setMouseReleaseFunc(PTRFUN func)
{
    mouseReleaseFunc = func;
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (mouseMoveFunc)
        mouseMoveFunc(event);

    QGLWidget::mouseMoveEvent(event);
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    if (mousePressFunc)
        mousePressFunc(event);

    QGLWidget::mousePressEvent(event);
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (mouseReleaseFunc)
        mouseReleaseFunc(event);

    QGLWidget::mouseReleaseEvent(event);
}

void GLWidget::update()
{
    glewInit();
    makeCurrent();

    if (m_director)
        m_director->mainLoop();

    doneCurrent();

    int newInterval = m_director->getAnimationInterval() * 1000;
    if (m_timer->interval() != newInterval) {
        m_timer->start(newInterval);
    }
}
