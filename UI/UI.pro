QT       += core gui
QT       += serialport      #加入串口模块
QT       += printsupport    #加入画图模块

DEFINES += QT_NO_WARNING_OUTPUT
DEFINES += QT_NO_DEBUG_OUTPUT
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#配置PRECOMPILED_HEADER，添加预编译头文件(PCH,PreCompiled Headers)支持
#CONFIG+=precompile_header
#PRECOMPILED_HEADER=stable.h

CONFIG += c++17


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    SerialConf.cpp \
    datashowui.cpp \
    extend/frmdevice.cpp \
    extend/panelwidget.cpp \
    freamui.cpp \
    main.cpp \
    qagreement.cpp \
    sendui.cpp \
    userconfui.cpp \
    waveformui.cpp \
    widget.cpp

HEADERS += \
    SerialConf.h \
    datashowui.h \
    extend/frmdevice.h \
    extend/panelwidget.h \
    freamui.h \
    qagreement.h \
    sendui.h \
    userconfui.h \
    waveformui.h \
    widget.h

FORMS += \
    SerialConf.ui \
    datashowui.ui \
    extend/frmdevice.ui \
    freamui.ui \
    sendui.ui \
    userconfui.ui \
    waveformui.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    main.qrc

LIBS += -L$$PWD/lib/ -lqcustomplotd2

