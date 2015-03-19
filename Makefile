NULL =

CC = g++
MOC = moc-qt5
RCC = rcc-qt5

INCDIR = /usr/include
QTINCDIR = $(INCDIR)/qt5

TESTINCDIRS = `pkg-config --cflags cppunit`

TESTLIBS = `pkg-config --libs cppunit`

QTINCDIRS = \
	-I$(QTINCDIR) \
	-I$(QTINCDIR)/QtCore \
	-I$(QTINCDIR)/QtGui \
	-I$(QTINCDIR)/QtWidgets \
	$(NULL)

QTLIBS = \
	-lQt5Core \
	-lQt5Gui \
	-lQt5Widgets \
	$(NULL)

CFLAGS = -fPIC -Wall -Wpedantic -std=c++11

MODELSRC = \
	src/model/changeable.cpp \
	src/model/color.cpp \
	src/model/line.cpp \
	src/model/point.cpp \
	src/model/turtle.cpp \
	src/model/world.cpp \
	src/model/zone.cpp \
	$(NULL)

BISONSRC = \
	src/interpreter/parser.y+ \
	$(NULL)

BISONTMP = \
	src/interpreter/y.tab.c \
	$(NULL)

FLEXSRC = \
	src/interpreter/lexer.l+ \
	$(NULL)

FLEXTMP = \
	src/interpreter/lex.yy.c \
	$(NULL)

INTERPETERSRC = \
	src/interpreter/interpreter.cpp \
	src/interpreter/tree.cpp \
	$(NULL)

TESTSRC = \
	src/tests/test-color.cpp \
	src/tests/test-point.cpp \
	src/tests/test-number.cpp \
	src/tests/test-turtle.cpp \
	src/tests/test-value.cpp \
	src/tests/tests.cpp \
	$(NULL)

QTSRC = \
	src/qt/application.cpp \
	src/qt/stibbons.cpp \
	src/qt/window.cpp \
	src/qt/world-view.cpp \
	$(NULL)

MOCHEADERS = \
	src/qt/window.h \
	src/qt/world-view.h \
	$(NULL)

MOCSRC = $(MOCHEADERS:%.h=%.moc.cpp)

QRCFILES = \
	data/stibbons.qrc \
	$(NULL)

QRCSRC = $(QRCFILES:%.qrc=%.qrc.cpp)

MODELOBJECTS = $(MODELSRC:%.cpp=%.o)

BISONOBJECTS = $(BISONTMP:%.c=%.o)

FLEXOBJECTS = $(FLEXTMP:%.c=%.o)

INTERPRETEROBJECTS = $(INTERPETERSRC:%.cpp=%.o)

TESTOBJECTS = $(TESTSRC:%.cpp=%.o)

QTOBJECTS = $(QTSRC:%.cpp=%.o) $(MOCSRC:%.cpp=%.o) $(QRCSRC:%.cpp=%.o)

APP = stibbons

TEST = test

# Variables pour la documentation

DOCDIR = doc
REPDIR = $(DOCDIR)/report
PDFDIR = $(DOCDIR)

REPDEPS = \
	$(REPDIR)/*.tex \
	$(NULL)

PDF = \
	$(PDFDIR)/report.pdf \
	$(NULL)

PDFCLN = \
	$(PDF) \
	$(PDF:%.pdf=%.aux) \
	$(PDF:%.pdf=%.log) \
	$(PDF:%.pdf=%.toc) \
	$(NULL)

# Tout compiler

all: doc $(APP) $(TEST)

# Compilation du logiciel

$(APP): $(MODELOBJECTS) $(QTOBJECTS) $(BISONOBJECTS) $(FLEXOBJECTS) $(INTERPRETEROBJECTS)
	$(CC) $^ -o $@ $(CFLAGS) $(QTINCDIRS) $(QTLIBS)

$(TEST): $(MODELOBJECTS) $(TESTOBJECTS)
	$(CC) $^ -o $@ $(CFLAGS) $(TESTINCDIRS) $(TESTLIBS)

$(BISONTMP): $(BISONSRC)
	bison -ydt -b $(<D)/y $<

$(FLEXTMP): $(FLEXSRC)
	flex -o $@ $<

%.moc.cpp: %.h
	$(MOC) $(QTINCDIRS) $< -o $@

%.qrc.cpp: %.qrc
	$(RCC) -name $(basename $(<F)) $< -o $@

$(MODELOBJECTS): %.o: %.cpp
	$(CC) $< -c -o $@ $(CFLAGS)

$(BISONOBJECTS): %.o: %.c
	$(CC) $< -c -o $@ $(CFLAGS)

$(FLEXOBJECTS): %.o: %.c
	$(CC) $< -c -o $@ $(CFLAGS)

$(INTERPRETEROBJECTS): %.o: %.cpp
	$(CC) $< -c -o $@ $(CFLAGS)

$(TESTOBJECTS): %.o: %.cpp
	$(CC) $< -c -o $@ $(CFLAGS) $(TESTINCDIRS) $(TESTLIBS)

$(QTOBJECTS): %.o: %.cpp
	$(CC) $< -c -o $@ $(CFLAGS) $(QTINCDIRS) $(QTLIBS)

# Compilation de la documentation

doc: $(PDF)

$(PDFDIR)/%.pdf: $(REPDIR)/%.tex
	# Compile pour générer la TOC
	pdflatex -output-directory $(@D) $^
	# Compile avec la TOC
	pdflatex -output-directory $(@D) $^

$(REPDIR)/report.tex: $(REPDEPS)
	touch $@

clean:
	rm -Rf $(APP) $(TEST) \
	$(MODELOBJECTS) \
	$(BISONOBJECTS) \
	$(FLEXOBJECTS) \
	$(INTERPRETEROBJECTS) \
	$(TESTOBJECTS) \
	$(QTOBJECTS) \
	$(PDFCLN)\
	$(NULL)

.PHONY: all doc clean

