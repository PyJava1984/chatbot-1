#-------------------------------------------------
#
# Project created by QtCreator 2012-09-06T12:57:20
#
#-------------------------------------------------

QT       += testlib xml gui

TARGET = statsManagerTest
CONFIG   += console
CONFIG   -= app_bundle

PROJECT_PATH = $$PWD

TEMPLATE = app

INCLUDEPATH += ../../chatbot/ ../../third-party

HEADERS += \
    ../../chatbot/common/settings.h \
    ../../chatbot/stats/statsmanager.h \
    ../../chatbot/stats/statshelper.h \
    ../../chatbot/stats/historystatshelper.h \
    ../../chatbot/stats/rulestatshelper.h \

SOURCES += \
    ../../chatbot/stats/statsmanager.cpp \
    ../../chatbot/stats/securestatsfile.cpp \
    ../../chatbot/stats/historystatshelper.cpp \
    ../../chatbot/crypto/cipher.cpp \
    ../../chatbot/crypto/keymanagerfactory.cpp \
    ../../chatbot/common/settings.cpp \
    ../../chatbot/common/conversation.cpp \
    ../../chatbot/common/conversationreader.cpp \
    ../../chatbot/common/logger.cpp \
    ../../chatbot/common/csvrow.cpp \
    ../../chatbot/common/csvdocument.cpp \
    ../../chatbot/common/random.cpp \
    ../../chatbot/nlp-engine/defaultsanitizer.cpp \
    ../../chatbot/nlp-engine/parser.cpp \
    ../../chatbot/nlp-engine/varstack.cpp \
    ../../chatbot/nlp-engine/globaltools.cpp \
    ../../chatbot/back-end/rule.cpp \
    statsmanagertest.cpp


OTHER_FILES += data/*.txt

DEFINES += SRCDIR=\\\"$$PWD/\\\"


############################################
# Copy other files
win32:copyfiles.commands = copy /y $$PROJECT_PATH/data/*.txt .
else:copyfiles.commands = cp -f $$PROJECT_PATH/data/*.txt .

QMAKE_EXTRA_TARGETS += copyfiles
POST_TARGETDEPS += copyfiles
############################################


