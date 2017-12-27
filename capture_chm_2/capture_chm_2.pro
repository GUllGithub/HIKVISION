SOURCES += \
    capture_chm.cpp \
    call_back.cpp

HEADERS += \
    PlayM4.h \
    HCNetSDK.h \
    call_back.h

INCLUDEPATH += /usr/local/include \
                /usr/local/include/opencv \
                /usr/local/include/opencv2

LIBS += /usr/local/lib/libopencv_highgui.so \
        /usr/local/lib/libopencv_core.so    \
        /usr/local/lib/libopencv_imgproc.so  \
        /usr/local/lib/libopencv_imgcodecs.so




win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/release/ -lSuperRender
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/debug/ -lSuperRender
else:unix: LIBS += -L$$PWD/../lib/ -lSuperRender

INCLUDEPATH += $$PWD/../
DEPENDPATH += $$PWD/../

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/release/ -lPlayCtrl
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/debug/ -lPlayCtrl
else:unix: LIBS += -L$$PWD/../lib/ -lPlayCtrl

INCLUDEPATH += $$PWD/../
DEPENDPATH += $$PWD/../

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/release/ -lhpr
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/debug/ -lhpr
else:unix: LIBS += -L$$PWD/../lib/ -lhpr

INCLUDEPATH += $$PWD/../
DEPENDPATH += $$PWD/../

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/release/ -lhcnetsdk
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/debug/ -lhcnetsdk
else:unix: LIBS += -L$$PWD/../lib/ -lhcnetsdk

INCLUDEPATH += $$PWD/../
DEPENDPATH += $$PWD/../

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/release/ -lHCCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/debug/ -lHCCore
else:unix: LIBS += -L$$PWD/../lib/ -lHCCore

INCLUDEPATH += $$PWD/../
DEPENDPATH += $$PWD/../

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/release/ -lAudioRender
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/debug/ -lAudioRender
else:unix: LIBS += -L$$PWD/../lib/ -lAudioRender

INCLUDEPATH += $$PWD/../
DEPENDPATH += $$PWD/../

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/HCNetSDKCom/release/ -lSystemTransform
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/HCNetSDKCom/debug/ -lSystemTransform
else:unix: LIBS += -L$$PWD/../lib/HCNetSDKCom/ -lSystemTransform

QT += widgets
