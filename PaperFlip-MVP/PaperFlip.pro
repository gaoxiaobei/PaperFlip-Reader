QT += core gui widgets xml core5compat
QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PaperFlip
TEMPLATE = app

CONFIG += c++17
CONFIG += console

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    ReaderWidget.cpp \
    EPUBManager.cpp \
    Views/PreviewBar.cpp \
    epub_utils.cpp

HEADERS += \
    MainWindow.h \
    ReaderWidget.h \
    EPUBManager.h \
    Views/PreviewBar.h \
    epub_utils.h

# Windows specific
win32:CONFIG += release
win32:DEFINES += QT_NO_DEBUG

# --- QuaZip library (static build) ---
QUAZIP_DIR = $$PWD/libs/quazip-1.5
INCLUDEPATH += $$QUAZIP_DIR/quazip
DEFINES += QUAZIP_STATIC

# Use system ZLIB and link properly
LIBS += -lz

# Include required QuaZip sources without duplication
SOURCES += \
    $$QUAZIP_DIR/quazip/JlCompress.cpp \
    $$QUAZIP_DIR/quazip/quazip.cpp \
    $$QUAZIP_DIR/quazip/quazipfile.cpp \
    $$QUAZIP_DIR/quazip/quazipdir.cpp \
    $$QUAZIP_DIR/quazip/quazipfileinfo.cpp \
    $$QUAZIP_DIR/quazip/quazipnewinfo.cpp \
    $$QUAZIP_DIR/quazip/qioapi.cpp \
    $$QUAZIP_DIR/quazip/unzip.c \
    $$QUAZIP_DIR/quazip/zip.c

# Add QuaZip headers to ensure they are processed by moc if needed
HEADERS += \
    $$QUAZIP_DIR/quazip/quazip_global.h \
    $$QUAZIP_DIR/quazip/quazip.h \
    $$QUAZIP_DIR/quazip/quazipfile.h \
    $$QUAZIP_DIR/quazip/quazipfileinfo.h \
    $$QUAZIP_DIR/quazip/quazipnewinfo.h \
    $$QUAZIP_DIR/quazip/quazipdir.h \
    $$QUAZIP_DIR/quazip/JlCompress.h \
    $$QUAZIP_DIR/quazip/ioapi.h \
    $$QUAZIP_DIR/quazip/unzip.h \
    $$QUAZIP_DIR/quazip/zip.h


# Default rules for deployment
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
