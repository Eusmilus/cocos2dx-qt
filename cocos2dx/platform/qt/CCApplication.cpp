#include "CCApplication.h"
#include "CCEGLView.h"
#include "CCDirector.h"

NS_CC_BEGIN

// sharedApplication pointer
CCApplication * CCApplication::sm_pSharedApplication = 0;

CCApplication::CCApplication(int argc, char *argv[])
    : QApplication(argc, argv)
{
    m_nAnimationInterval = 0;
    CC_ASSERT(! sm_pSharedApplication);
    sm_pSharedApplication = this;
}

CCApplication::~CCApplication()
{
    CC_ASSERT(this == sm_pSharedApplication);
    sm_pSharedApplication = NULL;
}

int CCApplication::run()
{
    CCEGLView::sharedOpenGLView();

    if (! applicationDidFinishLaunching() )
    {
        return 0;
    }

    return cocos2d::CCApplication::sharedApplication().exec();
}

void CCApplication::setAnimationInterval(double)
{
}

//////////////////////////////////////////////////////////////////////////
// static member function
//////////////////////////////////////////////////////////////////////////
CCApplication& CCApplication::sharedApplication()
{
    CC_ASSERT(sm_pSharedApplication);
    return *sm_pSharedApplication;
}

ccLanguageType CCApplication::getCurrentLanguage()
{
    ccLanguageType ret = kLanguageEnglish;

    return ret;
}

NS_CC_END
