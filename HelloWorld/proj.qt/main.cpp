#include "AppDelegate.h"


int main(int argc, char *argv[])
{
    // create the application instance
    AppDelegate app(argc, argv);

    int width = 480;
    int height = 320;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_QT)
    cocos2d::CCEGLView& eglView = cocos2d::CCEGLView::sharedOpenGLView();
    eglView.setViewName("Hello World with Qt");
    eglView.setFrameSize(width, height);
#endif

    return cocos2d::CCApplication::sharedApplication().run();
}
