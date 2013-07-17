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
    qcrc32.cpp \
    helpui.cpp

HEADERS  += mainwindow.h \
	config.h \
	qexifimageheader.h \
	qid3.h \
	qstringtools.h \
	joblist.h \
	main.h \
	qiconizer.h \
	thumbsdbviewer.h \
    qcrc32.h \
    helpui.h

FORMS    += mainwindow.ui \
	config.ui \
	joblist.ui \
	thumbsdbviewer.ui \
    helpui.ui

LIBS += -ltag

RESOURCES +=

TRANSLATIONS=lang_fr.ts lang_us.ts



bwarg.files = bwarg
bwarg.path = /usr/bin/
trad.files = lang_*.qm
trad.path = /usr/share/bwarg/
desktop.files = bwarg.desktop
desktop.path = /usr/share/applications/

INSTALLS += bwarg trad desktop
