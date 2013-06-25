#-------------------------------------------------
#
# Project created by QtCreator 2013-03-26T12:58:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bwarg
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
	config.cpp \
	qexifimageheader.cpp \
	qid3.cpp \
	qstringtools.cpp \
	joblist.cpp \
	qiconizer.cpp \
	thumbsdbviewer.cpp \
    qcrc32.cpp

HEADERS  += mainwindow.h \
	config.h \
	qexifimageheader.h \
	qid3.h \
	qstringtools.h \
	joblist.h \
	main.h \
	qiconizer.h \
	thumbsdbviewer.h \
    qcrc32.h

FORMS    += mainwindow.ui \
	config.ui \
	joblist.ui \
	thumbsdbviewer.ui

LIBS += -ltag
