
QT       += core gui opengl

TEMPLATE = lib

include(actions.pri)
include(base_nodes.pri)
include(cocoa.pri)
include(effects.pri)
include(extensions.pri)
include(kazmath.pri)
include(keypad_dispatcher.pri)
include(label_nodes.pri)
include(layers_scenes_transitions_nodes.pri)
include(menu_nodes.pri)
include(misc_nodes.pri)
include(particle_nodes.pri)
include(platform.pri)
include(script_support.pri)
include(shaders.pri)
include(sprite_nodes.pri)
include(support.pri)
include(text_input_node.pri)
include(textures.pri)
include(tileMap_parallax_nodes.pri)
include(touch_dispatcher.pri)

win32 {
    TARGET = libcocos2d

    # You may need to change this include directory
    DEFINES += WIN32
    DEFINES += _WINDOWS
    INCLUDEPATH += \
            ../platform/third_party/win32/iconv \
            ../platform/third_party/win32/zlib \
            ../platform/third_party/win32/libtiff \
            ../platform/third_party/win32/libjpeg \
            ../platform/third_party/win32/libpng \
            ../platform/third_party/win32/pthread \
            ../platform/third_party/win32/libxml2 \
            ../platform/third_party/win32/OGLES

    LIBS += -lShell32 -lAdvapi32
    LIBS += -L../platform/third_party/win32/libraries -llibglew32
    LIBS += -L../platform/third_party/win32/libraries -llibxml2
    LIBS += -L../platform/third_party/win32/libraries -llibpng
    LIBS += -L../platform/third_party/win32/libraries -llibzlib
    LIBS += -L../platform/third_party/win32/libraries -llibjpeg
    LIBS += -L../platform/third_party/win32/libraries -llibiconv
    LIBS += -L../platform/third_party/win32/libraries -lpthreadVCE2
    LIBS += -L../platform/third_party/win32/libraries -llibtiff

    QMAKE_LFLAGS_DEBUG =  /DEBUG /NODEFAULTLIB:libcmt.lib
    QMAKE_LFLAGS_RELEASE = /INCREMENTAL:NO /NODEFAULTLIB:libcmt.lib
}

unix {
    TARGET = cocos2d

    INCLUDEPATH += /usr/local/include \
            /usr/include/libxml2 \
            ../../cocos2dx

    LIBS += -L/usr/local/lib/ -lpng
    LIBS += -L/usr/local/lib/ -ljpeg
    LIBS += -L/usr/local/lib/ -lxml2
    LIBS += -L/usr/local/lib/ -lGLEW
    LIBS += -L/usr/local/lib/ -lz
    LIBS += -L/usr/local/lib/ -lcurl
}

DEFINES += _USRDLL
DEFINES += __QT__
DEFINES += CC_UNDER_QT

INCLUDEPATH += ../platform \
        ../platform/qt \
        ../include \
        ../kazmath/include \
        ..

CONFIG(debug, debug|release) {
    OBJECTS_DIR = debug/
    DESTDIR = ../../Debug.qt
}

CONFIG(release, debug|release) {
    OBJECTS_DIR = release/
    DESTDIR = ../../Release.qt
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

HEADERS += \
    ../include/cocos2dExt.h \
    ../include/cocos2d.h \
    ../include/ccTypes.h \
    ../include/CCProtocols.h \
    ../include/ccMacros.h \
    ../include/CCEventType.h \
    ../include/ccConfig.h \
    ../CCScheduler.h \
    ../CCDrawingPrimitives.h \
    ../CCDirector.h \
    ../CCConfiguration.h \
    ../CCCamera.h

SOURCES += \
    ../CCCamera.cpp \
    ../CCConfiguration.cpp \
    ../CCDirector.cpp \
    ../CCDrawingPrimitives.cpp \
    ../CCScheduler.cpp \
    ../cocos2d.cpp
