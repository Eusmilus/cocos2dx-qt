#include "AppDelegate.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_QT)
#include <QHBoxLayout>
#include <QLabel>

#include "CCEGLView.h"
#include "CCGLWidget.h"
#include "widget.h"

static CCEGLView* s_pMainWindow = NULL;

static void mouseMove(QMouseEvent *event)
{
    s_pMainWindow->mouseMove(event);
}

static void mousePress(QMouseEvent *event)
{
    s_pMainWindow->mousePress(event);
}

static void mouseRelease(QMouseEvent *event)
{
    s_pMainWindow->mouseRelease(event);
}

#endif

int main(int argc, char *argv[])
{
    // create the application instance
    AppDelegate app(argc, argv);

    int width = 480;
    int height = 320;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_QT)
//    cocos2d::CCEGLView& eglView = cocos2d::CCEGLView::sharedOpenGLView();
//    eglView.setViewName("Hello World with Qt");
//    eglView.setFrameSize(width, height);

    // extract CCEGLView::setFrameSize here


    // 1. create main widget and layout
    Widget *widget = new Widget();
    widget->setWindowTitle("Hello world with Qt!");
    QHBoxLayout* layout = new QHBoxLayout(widget);

    widget->show();

    // 2. create glview for cocos2d-x
    s_pMainWindow = new cocos2d::CCEGLView();

    // 3. create glwidget for cocos2d-x
    // then ADD the glwidget to layout.
    // set glwidget information
    GLWidget* m_window = new GLWidget(width,height, CCDirector::sharedDirector());
    layout->addWidget(m_window); // !! Must here !! Below m_window init !

    m_window->setFixedSize(width, height);
    m_window->show();


    // 4. set glwidget as render widget
    s_pMainWindow->setWindow(m_window);


    // 5. OpenGL init (extract from CCEGLView::InitGL)
    // check ..
    GLenum GlewInitResult = glewInit();

    if (GLEW_OK != GlewInitResult)
    {
        fprintf(stderr,"ERROR: %s\n",glewGetErrorString(GlewInitResult));
        return false;
    }

    if (GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader)
    {
        CCLog("Ready for GLSL\n");
    }
    else
    {
        CCLog("Not totally ready :( \n");
    }

    if (glewIsSupported("GL_VERSION_2_0"))
    {
        CCLog("Ready for OpenGL 2.0\n");
    }
    else
    {
        CCLog("OpenGL 2.0 not supported\n");
    }

#endif

    return cocos2d::CCApplication::sharedApplication().run();
}
