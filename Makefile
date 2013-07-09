#############################################################################
# Makefile for building: bwarg
# Generated by qmake (2.01a) (Qt 4.8.4) on: mar. juil. 9 01:40:11 2013
# Project:  Bwarg.pro
# Template: app
# Command: /usr/bin/qmake -o Makefile Bwarg.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I. -I.
LINK          = g++
LFLAGS        = -Wl,-O1
LIBS          = $(SUBLIBS)  -L/usr/lib64/qt4 -ltag -lQtGui -L/usr/lib64 -L/usr/lib64/qt4 -L/usr/X11R6/lib -lQtCore -lgthread-2.0 -lrt -lglib-2.0 -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = main.cpp \
		mainwindow.cpp \
		config.cpp \
		qid3.cpp \
		qstringtools.cpp \
		joblist.cpp \
		qiconizer.cpp \
		thumbsdbviewer.cpp \
		qcrc32.cpp \
		helpui.cpp moc_mainwindow.cpp \
		moc_config.cpp \
		moc_qid3.cpp \
		moc_qstringtools.cpp \
		moc_joblist.cpp \
		moc_qiconizer.cpp \
		moc_thumbsdbviewer.cpp \
		moc_qcrc32.cpp \
		moc_helpui.cpp
OBJECTS       = main.o \
		mainwindow.o \
		config.o \
		qid3.o \
		qstringtools.o \
		joblist.o \
		qiconizer.o \
		thumbsdbviewer.o \
		qcrc32.o \
		helpui.o \
		moc_mainwindow.o \
		moc_config.o \
		moc_qid3.o \
		moc_qstringtools.o \
		moc_joblist.o \
		moc_qiconizer.o \
		moc_thumbsdbviewer.o \
		moc_qcrc32.o \
		moc_helpui.o
DIST          = /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		Bwarg.pro
QMAKE_TARGET  = bwarg
DESTDIR       = 
TARGET        = bwarg

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET): ui_mainwindow.h ui_config.h ui_joblist.h ui_thumbsdbviewer.h ui_helpui.h $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: Bwarg.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib64/qt4/libQtGui.prl \
		/usr/lib64/qt4/libQtCore.prl
	$(QMAKE) -o Makefile Bwarg.pro
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/common/gcc-base.conf:
/usr/share/qt4/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt4/mkspecs/common/g++-base.conf:
/usr/share/qt4/mkspecs/common/g++-unix.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib64/qt4/libQtGui.prl:
/usr/lib64/qt4/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -o Makefile Bwarg.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/bwarg1.0.0 || $(MKDIR) .tmp/bwarg1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/bwarg1.0.0/ && $(COPY_FILE) --parents mainwindow.h config.h qexifimageheader.h qid3.h qstringtools.h joblist.h main.h qiconizer.h thumbsdbviewer.h qcrc32.h helpui.h .tmp/bwarg1.0.0/ && $(COPY_FILE) --parents main.cpp mainwindow.cpp config.cpp qid3.cpp qstringtools.cpp joblist.cpp qiconizer.cpp thumbsdbviewer.cpp qcrc32.cpp helpui.cpp .tmp/bwarg1.0.0/ && $(COPY_FILE) --parents mainwindow.ui config.ui joblist.ui thumbsdbviewer.ui helpui.ui .tmp/bwarg1.0.0/ && $(COPY_FILE) --parents lang_fr.ts lang_us.ts .tmp/bwarg1.0.0/ && (cd `dirname .tmp/bwarg1.0.0` && $(TAR) bwarg1.0.0.tar bwarg1.0.0 && $(COMPRESS) bwarg1.0.0.tar) && $(MOVE) `dirname .tmp/bwarg1.0.0`/bwarg1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/bwarg1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_mainwindow.cpp moc_config.cpp moc_qid3.cpp moc_qstringtools.cpp moc_joblist.cpp moc_qiconizer.cpp moc_thumbsdbviewer.cpp moc_qcrc32.cpp moc_helpui.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_mainwindow.cpp moc_config.cpp moc_qid3.cpp moc_qstringtools.cpp moc_joblist.cpp moc_qiconizer.cpp moc_thumbsdbviewer.cpp moc_qcrc32.cpp moc_helpui.cpp
moc_mainwindow.cpp: qexifimageheader.h \
		mainwindow.h
	/usr/bin/moc $(DEFINES) $(INCPATH) mainwindow.h -o moc_mainwindow.cpp

moc_config.cpp: config.h
	/usr/bin/moc $(DEFINES) $(INCPATH) config.h -o moc_config.cpp

moc_qid3.cpp: qid3.h
	/usr/bin/moc $(DEFINES) $(INCPATH) qid3.h -o moc_qid3.cpp

moc_qstringtools.cpp: qstringtools.h
	/usr/bin/moc $(DEFINES) $(INCPATH) qstringtools.h -o moc_qstringtools.cpp

moc_joblist.cpp: mainwindow.h \
		qexifimageheader.h \
		joblist.h
	/usr/bin/moc $(DEFINES) $(INCPATH) joblist.h -o moc_joblist.cpp

moc_qiconizer.cpp: qiconizer.h
	/usr/bin/moc $(DEFINES) $(INCPATH) qiconizer.h -o moc_qiconizer.cpp

moc_thumbsdbviewer.cpp: thumbsdbviewer.h
	/usr/bin/moc $(DEFINES) $(INCPATH) thumbsdbviewer.h -o moc_thumbsdbviewer.cpp

moc_qcrc32.cpp: qcrc32.h
	/usr/bin/moc $(DEFINES) $(INCPATH) qcrc32.h -o moc_qcrc32.cpp

moc_helpui.cpp: mainwindow.h \
		qexifimageheader.h \
		helpui.h
	/usr/bin/moc $(DEFINES) $(INCPATH) helpui.h -o moc_helpui.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_mainwindow.h ui_config.h ui_joblist.h ui_thumbsdbviewer.h ui_helpui.h
compiler_uic_clean:
	-$(DEL_FILE) ui_mainwindow.h ui_config.h ui_joblist.h ui_thumbsdbviewer.h ui_helpui.h
ui_mainwindow.h: mainwindow.ui
	/usr/bin/uic mainwindow.ui -o ui_mainwindow.h

ui_config.h: config.ui
	/usr/bin/uic config.ui -o ui_config.h

ui_joblist.h: joblist.ui
	/usr/bin/uic joblist.ui -o ui_joblist.h

ui_thumbsdbviewer.h: thumbsdbviewer.ui
	/usr/bin/uic thumbsdbviewer.ui -o ui_thumbsdbviewer.h

ui_helpui.h: helpui.ui
	/usr/bin/uic helpui.ui -o ui_helpui.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_uic_clean 

####### Compile

main.o: main.cpp mainwindow.h \
		qexifimageheader.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

mainwindow.o: mainwindow.cpp qexifimageheader.h \
		qexifimageheader.cpp \
		mainwindow.h \
		ui_mainwindow.h \
		config.h \
		joblist.h \
		qid3.h \
		qstringtools.h \
		qiconizer.h \
		qcrc32.h \
		thumbsdbviewer.h \
		helpui.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mainwindow.o mainwindow.cpp

config.o: config.cpp config.h \
		ui_config.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o config.o config.cpp

qid3.o: qid3.cpp qid3.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qid3.o qid3.cpp

qstringtools.o: qstringtools.cpp qstringtools.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qstringtools.o qstringtools.cpp

joblist.o: joblist.cpp joblist.h \
		mainwindow.h \
		qexifimageheader.h \
		ui_joblist.h \
		qstringtools.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o joblist.o joblist.cpp

qiconizer.o: qiconizer.cpp qiconizer.h \
		qexifimageheader.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qiconizer.o qiconizer.cpp

thumbsdbviewer.o: thumbsdbviewer.cpp thumbsdbviewer.h \
		ui_thumbsdbviewer.h \
		qiconizer.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o thumbsdbviewer.o thumbsdbviewer.cpp

qcrc32.o: qcrc32.cpp qcrc32.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qcrc32.o qcrc32.cpp

helpui.o: helpui.cpp helpui.h \
		mainwindow.h \
		qexifimageheader.h \
		ui_helpui.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o helpui.o helpui.cpp

moc_mainwindow.o: moc_mainwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mainwindow.o moc_mainwindow.cpp

moc_config.o: moc_config.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_config.o moc_config.cpp

moc_qid3.o: moc_qid3.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_qid3.o moc_qid3.cpp

moc_qstringtools.o: moc_qstringtools.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_qstringtools.o moc_qstringtools.cpp

moc_joblist.o: moc_joblist.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_joblist.o moc_joblist.cpp

moc_qiconizer.o: moc_qiconizer.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_qiconizer.o moc_qiconizer.cpp

moc_thumbsdbviewer.o: moc_thumbsdbviewer.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_thumbsdbviewer.o moc_thumbsdbviewer.cpp

moc_qcrc32.o: moc_qcrc32.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_qcrc32.o moc_qcrc32.cpp

moc_helpui.o: moc_helpui.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_helpui.o moc_helpui.cpp

####### Install

install: all
	mkdir -p /usr/share/bwarg/
	cp lang_*.qm /usr/share/bwarg/
	cp bwarg /usr/bin

uninstall:
	rm -r /usr/share/bwarg
	rm /usr/bin/bwarg

FORCE:

