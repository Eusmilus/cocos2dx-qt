QT       += core gui opengl

TARGET = HelloWorld
TEMPLATE = app

win32 {
    LIBS += -L$(DESTDIR) -llibcocos2d -llibglew32
}

unix {
    LIBS += -L$(DESTDIR) -lcocos2d
}

CONFIG(debug, debug|release) {
    DESTDIR = ../../Debug.qt
}

CONFIG(release, debug|release) {
    DESTDIR = ../../Release.qt
}

DEFINES += _USRDLL
DEFINES += __QT__
DEFINES += CC_UNDER_QT


INCLUDEPATH += ../../cocos2dx/platform \
        ../../cocos2dx/include \
        ../../cocos2dx \
        ../../HelloWorld/Classes \
        ../../cocos2dx/platform/qt \
        ../../cocos2dx/kazmath/include \
        ../../cocos2dx/platform/third_party/win32/OGLES

HEADERS += \
    ../Classes/HelloWorldScene.h \
    ../Classes/AppDelegate.h

SOURCES += \
    ../Classes/HelloWorldScene.cpp \
    ../Classes/AppDelegate.cpp \
    main.cpp
