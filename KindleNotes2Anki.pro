QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ClippingParser.cpp \
    DictionnaryWidget.cpp \
    KindleParser.cpp \
    NetworkManager.cpp \
    WordManager.cpp \
    main.cpp \
    MainWindow.cpp \
    models/BookModel.cpp

HEADERS += \
    ClippingParser.h \
    DictionnaryWidget.h \
    KindleParser.h \
    MainWindow.h \
    NetworkManager.h \
    WordManager.h \
    models/BookModel.h

FORMS += \
    DictionnaryWidget.ui \
    MainWindow.ui

TRANSLATIONS += \
    KindleNotes2Anki_en_150.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
