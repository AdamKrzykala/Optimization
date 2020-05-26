QT  += core gui concurrent charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 sdk_no_version_check

#QMAKE_CXXFLAGS += -Wa,-mbig-obj

INCLUDEPATH += ../inc\

SOURCES += \
    ../src/Math_Parser.cpp \
    ../src/NSGA.cpp \
    ../src/allele.cpp \
    ../src/main.cpp \
    ../src/mainwindow.cpp \
    ../src/librarywindow.cpp \
    ../src/resultwindow.cpp

HEADERS += \
    ../inc/Math_Parser.hpp \
    ../inc/NSGA.hpp \
    ../inc/allele.hpp \
    ../inc/exprtk.hpp \
    ../inc/mainwindow.h \
    ../inc/librarywindow.h \
    ../inc/resultwindow.h

FORMS += \
    ../uic/mainwindow.ui \
    ../uic/resultwindow.ui

RESOURCES += \
    ../res/resources.qrc
