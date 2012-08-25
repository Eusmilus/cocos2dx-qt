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

#ifndef __CC_EGLVIEW_QT_H__
#define __CC_EGLVIEW_QT_H__

#include <QMouseEvent>

#include "CCGL.h"
#include "platform/CCCommon.h"
#include "cocoa/CCGeometry.h"
#include "platform/CCEGLViewProtocol.h"

class GLWidget;
class QWidget;

NS_CC_BEGIN

class CCEGL;
class CCTouch;

class CC_DLL CCEGLView : public CCEGLViewProtocol
{
public:
    CCEGLView();
    virtual ~CCEGLView();

    /* override functions */
    virtual bool isOpenGLReady();
    virtual void end();
    virtual void swapBuffers();
    virtual bool canSetContentScaleFactor();
    virtual void setContentScaleFactor(float contentScaleFactor);
    virtual void setFrameSize(float width, float height);
    virtual void setIMEKeyboardState(bool bOpen);

    /* qt */
    void mouseMove(QMouseEvent *event);
    void mousePress(QMouseEvent *event);
    void mouseRelease(QMouseEvent *event);
    void setWindow(GLWidget *window);

private:
    virtual bool Create(int iWidth, int iHeight);
    bool initGL();
    void destroyGL();
public:

    void resize(int width, int height);

    // static function
    /**
    @brief    get the shared main open gl window
    */
    static CCEGLView& sharedOpenGLView();

protected:

private:
    bool m_bCaptured;
    bool m_bOrientationReverted;
    bool m_bOrientationInitVertical;
    CCSet * m_pSet;
    CCTouch * m_pTouch;

    //store current mouse point for moving, valid if and only if the mouse pressed
    CCPoint m_mousePoint;

    CCSize m_sSizeInPoint;
    CCRect m_rcViewPort;

    bool bIsInit;
//    int m_eInitOrientation;
    float m_fScreenScaleFactor;

    GLWidget* m_window;
    bool m_bIsSubWindow;
};

NS_CC_END

#endif    // end of __CC_EGLVIEW_WIN32_H__
