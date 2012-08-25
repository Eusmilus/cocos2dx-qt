#ifndef __CC_APPLICATION_QT_H__
#define __CC_APPLICATION_QT_H__

#include <QApplication>
#include "platform/CCCommon.h"
#include "platform/CCApplicationProtocol.h"

NS_CC_BEGIN

class CCRect;

class CC_DLL CCApplication : public CCApplicationProtocol, public QApplication
{
public:
    CCApplication(int argc, char *argv[]);
    virtual ~CCApplication();

    /**
    @brief    Run the message loop.
    */
    int run();

    /**
    @brief    Get current applicaiton instance.
    @return Current application instance pointer.
    */
    static CCApplication& sharedApplication();

    /* override functions */
    virtual void setAnimationInterval(double interval);
    virtual ccLanguageType getCurrentLanguage();

protected:
    long       m_nAnimationInterval;

    static CCApplication * sm_pSharedApplication;
};

NS_CC_END

#endif    // __CC_APPLICATION_WIN32_H__
