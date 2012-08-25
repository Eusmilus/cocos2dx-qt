/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "CCEGLView.h"
#include "cocoa/CCSet.h"
#include "ccMacros.h"
#include "CCDirector.h"
#include "touch_dispatcher/CCTouch.h"
#include "touch_dispatcher/CCTouchDispatcher.h"
#include "text_input_node/CCIMEDispatcher.h"
#include "keypad_dispatcher/CCKeypadDispatcher.h"
#include "CCApplication.h"
#include "CCGLWidget.h"

NS_CC_BEGIN




//////////////////////////////////////////////////////////////////////////
// impliment CCEGLView
//////////////////////////////////////////////////////////////////////////
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


CCEGLView::CCEGLView()
    : m_bCaptured(false)
    , m_bOrientationReverted(false)
    , m_bOrientationInitVertical(false)
    , bIsInit(false)
//    , m_eInitOrientation(CCDeviceOrientationPortrait)
    , m_fScreenScaleFactor(1.0f)
    , m_window(NULL)
    , m_bIsSubWindow(false)
{
    m_pTouch = new CCTouch;
    m_pSet = new CCSet;
    m_sSizeInPoint.width = m_sSizeInPoint.height = 0;
}

CCEGLView::~CCEGLView()
{

}

bool CCEGLView::initGL()
{
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
    return true;
}

void CCEGLView::destroyGL()
{
//    if (m_hDC != NULL && m_hRC != NULL)
//    {
//        // deselect rendering context and delete it
//        wglMakeCurrent(m_hDC, NULL);
//        wglDeleteContext(m_hRC);
//    }
}

bool CCEGLView::isOpenGLReady()
{
    return bIsInit;
}

void CCEGLView::end()
{
    CC_SAFE_DELETE(m_pSet);
    CC_SAFE_DELETE(m_pTouch);
    CC_SAFE_DELETE(m_pDelegate);

    s_pMainWindow = NULL;

    // delete the opengl window only when it is created by CCEGLView::Create()
    if (! m_bIsSubWindow)
        CC_SAFE_DELETE(m_window);

    delete this;
}

void CCEGLView::swapBuffers()
{
    if (bIsInit)
    {
        m_window->swapBuffers();
    }
}


void CCEGLView::setIMEKeyboardState(bool /*bOpen*/)
{

}

void CCEGLView::mouseMove(QMouseEvent *event)
{
    if (! m_pDelegate || ! m_pTouch)
        return;

    if (! m_bCaptured)
        return;

    m_pTouch->setTouchInfo(0, (float)(event->x()) / m_fScreenScaleFactor,
        (float)(event->y()) / m_fScreenScaleFactor);
    m_pDelegate->touchesMoved(m_pSet, NULL);
}

void CCEGLView::mousePress(QMouseEvent *event)
{
    if (! m_pDelegate || ! m_pTouch)
        return;

    if (event->button() != Qt::LeftButton)
        return;

    m_bCaptured = true;

    m_pTouch->setTouchInfo(0, (float)(event->x()) / m_fScreenScaleFactor,
        (float)(event->y()) / m_fScreenScaleFactor);
    m_pSet->addObject(m_pTouch);
    m_pDelegate->touchesBegan(m_pSet, NULL);
}

void CCEGLView::mouseRelease(QMouseEvent *event)
{
    if (! m_pDelegate || ! m_pTouch)
        return;

    if (event->button() != Qt::LeftButton)
        return;

    m_bCaptured = false;

    m_pTouch->setTouchInfo(0, (float)(event->x()) / m_fScreenScaleFactor,
        (float)(event->y()) / m_fScreenScaleFactor);
    m_pDelegate->touchesEnded(m_pSet, NULL);
    m_pSet->removeObject(m_pTouch);
}

void CCEGLView::setWindow(GLWidget *window)
{
    if (NULL == window)
        return ;

    CC_SAFE_DELETE(m_window);
    m_window = window;

    int width = m_window->width();
    int height = m_window->height();

    m_window->setMouseMoveFunc(&cocos2d::mouseMove);
    m_window->setMousePressFunc(&cocos2d::mousePress);
    m_window->setMouseReleaseFunc(&cocos2d::mouseRelease);

    m_window->setWindowFlags(m_window->windowFlags()& ~Qt::WindowMaximizeButtonHint);
    m_window->setFixedSize(width, height);
//    m_window->show();

    s_pMainWindow = this;

    m_bIsSubWindow = true;

    bIsInit = true;

    resize(width, height);

    CCEGLViewProtocol::setFrameSize(width, height);
}

bool CCEGLView::Create(int width, int height)
{
    bool bRet(false);
    do {
        m_window = new GLWidget(width,height, CCDirector::sharedDirector()/*,  widget*/ );


        m_window->setMouseMoveFunc(&cocos2d::mouseMove);
        m_window->setMousePressFunc(&cocos2d::mousePress);
        m_window->setMouseReleaseFunc(&cocos2d::mouseRelease);

        m_window->setWindowFlags(m_window->windowFlags()& ~Qt::WindowMaximizeButtonHint);
        m_window->setFixedSize(width, height);
        m_window->show();

        m_bIsSubWindow = true;

        bIsInit = true;

        resize(width, height);

        initGL();

        bRet = true;
    } while(0);

    return bRet;
}

void CCEGLView::resize(int width, int height)
{
#if 1
    m_sSizeInPoint.width = width;
    m_sSizeInPoint.height = height;

    // update win size
    CCEGLViewProtocol::setFrameSize(width, height);

#else
    if (! m_hWnd)
    {
        return;
    }

    RECT rcClient;
    GetClientRect(m_hWnd, &rcClient);
    if (rcClient.right - rcClient.left == width &&
        rcClient.bottom - rcClient.top == height)
    {
        return;
    }
    // calculate new window width and height
    rcClient.right = rcClient.left + width;
    rcClient.bottom = rcClient.top + height;
    AdjustWindowRectEx(&rcClient, GetWindowLong(m_hWnd, GWL_STYLE), false, GetWindowLong(m_hWnd, GWL_EXSTYLE));

    // change width and height
    SetWindowPos(m_hWnd, 0, 0, 0, rcClient.right - rcClient.left, 
        rcClient.bottom - rcClient.top, SWP_NOCOPYBITS | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
#endif
}

void CCEGLView::setFrameSize(float width, float height)
{
    Create(width, height);
    CCEGLViewProtocol::setFrameSize(width, height);
}

bool CCEGLView::canSetContentScaleFactor()
{
    return true;
}

void CCEGLView::setContentScaleFactor(float contentScaleFactor)
{
#if 1
    Q_UNUSED(contentScaleFactor);
    CCLog("could not set contentScaleFactor after initialized");

#else
    CCEGLViewProtocol::setContentScaleFactor(contentScaleFactor);
    resize((int)(m_sSizeInPixel.width * contentScaleFactor), (int)(m_sSizeInPixel.height * contentScaleFactor));
    centerWindow();
#endif
}

CCEGLView& CCEGLView::sharedOpenGLView()
{
    if (s_pMainWindow == NULL)
    {
        s_pMainWindow = new CCEGLView();
    }
    return *s_pMainWindow;
}

NS_CC_END
