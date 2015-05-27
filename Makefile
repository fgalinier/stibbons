NULL =

PREFIX = /usr/local
BINDIR = $(PREFIX)/bin
SHAREDIR = $(PREFIX)/share
APPSDIR = $(SHAREDIR)/applications
ICONSDIR = $(SHAREDIR)/icons
INSTALLEDICONDIR = $(ICONSDIR)/hicolor/scalable/apps

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

CLIINCDIRS = \
	-I$(QTINCDIR) \
	-I$(QTINCDIR)/QtCore \
	-I$(QTINCDIR)/QtGui \
	$(NULL)

CLILIBS = \
	-lQt5Core \
	-lQt5Gui \
	$(NULL)

CFLAGS = -fPIC -Wall -Wpedantic -std=c++11 -g -ljson_spirit

MODELSRC = \
	src/model/agent.cpp \
	src/model/breed.cpp \
	src/model/boolean.cpp \
	src/model/changeable.cpp \
	src/model/color.cpp \
	src/model/line.cpp \
	src/model/function.cpp \
	src/model/number.cpp \
	src/model/nil.cpp \
	src/model/point.cpp \
	src/model/size.cpp \
	src/model/standard-function.cpp \
	src/model/string.cpp \
	src/model/table.cpp \
	src/model/turtle.cpp \
	src/model/type.cpp \
	src/model/type-value.cpp \
	src/model/user-function.cpp \
	src/model/world.cpp \
	src/model/zone.cpp \
	$(NULL)

BISONSRC = \
	src/interpreter/parser.y+ \
	$(NULL)

BISONTMP = \
	src/interpreter/y.tab.c \
	$(NULL)

BISONHEADERS = \
	src/interpreter/stack.hh \
	src/interpreter/location.hh \
	src/interpreter/position.hh \
	src/interpreter/y.tab.h \
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
	src/interpreter/interpreter-exception.cpp \
	src/interpreter/interpreter-manager.cpp \
	src/interpreter/syntax-exception.cpp \
	src/interpreter/semantic-exception.cpp \
	src/interpreter/turtle-interpreter.cpp \
	src/interpreter/world-interpreter.cpp \
	$(NULL)

TESTSRC = \
	src/tests/test-agent.cpp \
	src/tests/test-breed.cpp \
	src/tests/test-color.cpp \
	src/tests/test-function.cpp \
	src/tests/test-point.cpp \
	src/tests/test-number.cpp \
	src/tests/test-table.cpp \
	src/tests/test-turtle.cpp \
	src/tests/test-value.cpp \
	src/tests/test-world.cpp \
	src/tests/tests.cpp \
	$(NULL)

QTSRC = \
	src/qt/application.cpp \
	src/qt/stibbons.cpp \
	src/qt/stibbons-editor.cpp \
	src/qt/stibbons-highlighter.cpp \
	src/qt/window.cpp \
	src/qt/world-view.cpp \
	$(NULL)

CLISRC = \
	src/cli/application.cpp \
	src/cli/stibbons-cli.cpp \
	$(NULL)

COMMONSRC = \
	src/qt/runner.cpp \
	src/qt/world-painter.cpp \
	$(NULL)

MOCHEADERS = \
	src/qt/window.h \
	src/qt/world-view.h \
	src/qt/stibbons-editor.h \
	$(NULL)

COMMONMOCHEADERS = \
	src/qt/runner.h \
	$(NULL)

CLIMOCHEADERS = \
	src/cli/application.h \
	$(NULL)

MOCSRC = $(MOCHEADERS:%.h=%.moc.cpp)

CLIMOCSRC = $(CLIMOCHEADERS:%.h=%.moc.cpp)

COMMONMOCSRC = $(COMMONMOCHEADERS:%.h=%.moc.cpp)

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

COMMONOBJECTS = $(COMMONSRC:%.cpp=%.o) $(COMMONMOCSRC:%.cpp=%.o)

CLIOBJECTS = $(CLISRC:%.cpp=%.o) $(CLIMOCSRC:%.cpp=%.o)

APP = stibbons

CLIAPP = stibbons-cli

TEST = test

# Variables pour la documentation

DOCDIR = doc
REPDIR = $(DOCDIR)/report
RAILDIR = $(REPDIR)/rail
PDFDIR = $(DOCDIR)

RAILBIN = $(RAILDIR)/rail

REPTEX = $(REPDIR)/report.tex
REPRAI = $(DOCDIR)/report

REPDEPS = \
	$(REPDIR)/analyse-code.tex \
	$(REPDIR)/analyseurLexical.tex \
	$(REPDIR)/analyseurSemantique.tex \
	$(REPDIR)/analyseurs.tex \
	$(REPDIR)/analyseurSyntaxique.tex \
	$(REPDIR)/applications.tex \
	$(REPDIR)/conclusion.tex \
	$(REPDIR)/cpp11.tex \
	$(REPDIR)/gestion-projet.tex \
	$(REPDIR)/git.tex \
	$(REPDIR)/intro.tex \
	$(REPDIR)/latex.tex \
	$(REPDIR)/logo.tex \
	$(REPDIR)/methode.tex \
	$(REPDIR)/modele.tex \
	$(REPDIR)/netlogo.tex \
	$(REPDIR)/qt.tex \
	$(REPDIR)/refman.tex \
	$(REPDIR)/reunion1.tex \
	$(REPDIR)/reunion2.tex \
	$(REPDIR)/reunion3.tex \
	$(REPDIR)/reunion4.tex \
	$(REPDIR)/reunion5.tex \
	$(REPDIR)/reunion6.tex \
	$(REPDIR)/reunion7.tex \
	$(REPDIR)/standard.tex \
	$(REPDIR)/starlogo.tex \
	$(REPDIR)/syntaxe.tex \
	$(REPDIR)/tests-unitaires.tex \
	$(REPDIR)/tutoriel.tex \
	$(NULL)

REPPDF = $(PDFDIR)/report.pdf

REPPDFCLN = \
	$(REPPDF) \
	$(PDFDIR)/report.aux \
	$(PDFDIR)/report.brf \
	$(PDFDIR)/report.idx \
	$(PDFDIR)/report.lof \
	$(PDFDIR)/report.log \
	$(PDFDIR)/report.lol \
	$(PDFDIR)/report.lot \
	$(PDFDIR)/report.out \
	$(PDFDIR)/report.rai \
	$(PDFDIR)/report.rao \
	$(PDFDIR)/report.toc \
	$(REPDIR)/report.aux \
	$(REPDIR)/report.bbl \
	$(REPDIR)/report.blg \
	$(REPDIR)/report.idx \
	$(REPDIR)/report.lof \
	$(REPDIR)/report.log \
	$(REPDIR)/report.lol \
	$(REPDIR)/report.lot \
	$(REPDIR)/report.out \
	$(REPDIR)/report.rai \
	$(REPDIR)/report.toc \
	$(NULL)

# Variables pour le rapport de gestion de projet

PRODIR = $(DOCDIR)/gestionProjet

PROTEX = $(PRODIR)/reportProjet.tex

PRODEPS = \
	$(PRODIR)/*.tex \
	$(NULL)

PROPDF = $(PDFDIR)/reportProjet.pdf

PROPDFCLN = \
	$(PROPDF) \
	$(PDFDIR)/reportProjet.aux \
	$(PDFDIR)/reportProjet.log \
	$(PDFDIR)/reportProjet.toc \
	$(NULL)

# Variables pour la présentation

KEYDIR = $(DOCDIR)/Presentation

KEYTEX = $(KEYDIR)/presentation.tex
KEYRAI = $(DOCDIR)/presentation

KEYDEPS = \
	$(KEYDIR)/*.tex \
	$(NULL)

KEYPDF = $(PDFDIR)/presentation.pdf

KEYPDFCLN = \
	$(KEYPDF) \
	$(PDFDIR)/presentation.aux \
	$(PDFDIR)/presentation.log \
	$(PDFDIR)/presentation.nav \
	$(PDFDIR)/presentation.out \
	$(PDFDIR)/presentation.snm \
	$(PDFDIR)/presentation.toc \
	$(NULL)

# Tout compiler

all: doc $(APP) $(CLIAPP) $(TEST)

# Compilation du logiciel

$(APP): $(MODELOBJECTS) $(BISONOBJECTS) $(FLEXOBJECTS) $(INTERPRETEROBJECTS) $(QTOBJECTS) $(COMMONOBJECTS)
	$(CC) $^ -o $@ $(CFLAGS) $(QTINCDIRS) $(QTLIBS)

$(CLIAPP): $(MODELOBJECTS) $(BISONOBJECTS) $(FLEXOBJECTS) $(INTERPRETEROBJECTS) $(CLIOBJECTS) $(COMMONOBJECTS)
	$(CC) $^ -o $@ $(CFLAGS) $(CLIINCDIRS) $(QTLIBS)

$(TEST): $(MODELOBJECTS) $(BISONOBJECTS) $(FLEXOBJECTS) $(INTERPRETEROBJECTS) $(TESTOBJECTS)
	$(CC) $^ -o $@ $(CFLAGS) $(TESTINCDIRS) $(TESTLIBS)

$(BISONTMP): $(BISONSRC)
	bison -ydt -b $(<D)/y $<

$(FLEXTMP): $(FLEXSRC)
	flex -o $@ $<

$(MOCSRC): %.moc.cpp: %.h
	$(MOC) $(QTINCDIRS) $< -o $@
	
$(COMMONMOCSRC): %.moc.cpp: %.h
	$(MOC) $(QTINCDIRS) $< -o $@

%.qrc.cpp: %.qrc
	$(RCC) -name $(basename $(<F)) $< -o $@

$(CLIMOCSRC): %.moc.cpp: %.h
	$(MOC) $(CLIINCDIRS) $< -o $@

$(MODELOBJECTS): %.o: %.cpp $(BISONTMP) $(BISONHEADERS)
	$(CC) $< -c -o $@ $(CFLAGS)

$(BISONOBJECTS): %.o: %.c
	$(CC) $< -c -o $@ $(CFLAGS)

$(FLEXOBJECTS): %.o: %.c
	$(CC) $< -c -o $@ $(CFLAGS)

$(INTERPRETEROBJECTS): %.o: %.cpp $(BISONTMP) $(BISONHEADERS)
	$(CC) $< -c -o $@ $(CFLAGS)

$(TESTOBJECTS): %.o: %.cpp
	$(CC) $< -c -o $@ $(CFLAGS) $(TESTINCDIRS) $(TESTLIBS)

$(QTOBJECTS): %.o: %.cpp
	$(CC) $< -c -o $@ $(CFLAGS) $(QTINCDIRS) $(QTLIBS)
	
$(COMMONOBJECTS): %.o: %.cpp
	$(CC) $< -c -o $@ $(CFLAGS) $(QTINCDIRS) $(QTLIBS)

$(CLIOBJECTS): %.o: %.cpp
	$(CC) $< -c -o $@ $(CFLAGS) $(CLIINCDIRS) $(CLILIBS)

doc: refman report project keynote

# Compilation de Rail

$(RAILBIN): $(RAILDIR)/Makefile
	make -C $(<D) -f $(<F)

# Compilation du manuel de référence

refman: doc/refman

doc/refman:
	doxygen Doxyfile

# Compilation de la documentation

report: $(REPPDF)

$(REPPDF): $(PDFDIR)/%.pdf: $(REPDIR)/%.tex $(RAILBIN) bibtex
	# Compile pour générer la TOC
	TEXINPUTS=.//:$$TEXINPUTS pdflatex -output-directory $(@D) $<
	# Compile les diagrammes de syntaxe
	if [ -a $(REPRAI).rai ] ; \
	then \
		$(RAILBIN) $(REPRAI) ; \
	fi;
	# Compile avec la TOC
	TEXINPUTS=.//:$$TEXINPUTS pdflatex -output-directory $(@D) $<

bibtex: $(REPDIR)/report.aux
	bibtex $<

$(REPDIR)/report.aux: $(REPDIR)/report.tex 
	TEXINPUTS=.//:$$TEXINPUTS pdflatex -output-directory $(@D) $<

$(REPDIR)/report.tex: $(REPDEPS)
	touch $@

$(REPDIR)/refman.tex: refman
	grep "^\\\\input{\|^\\\\chapter{" doc/refman/latex/refman.tex | sed 's/\\input{/\\input{doc\/refman\/latex\//' > $@

# Compilation du rapport de gestion de projet

project: $(PROPDF)

$(PROPDF): $(PDFDIR)/%.pdf: $(PRODIR)/%.tex
	TEXINPUTS=.//:$$TEXINPUTS pdflatex -output-directory $(@D) $<
	TEXINPUTS=.//:$$TEXINPUTS pdflatex -output-directory $(@D) $<

# Compilation de la présentation

keynote: $(KEYPDF)

$(KEYPDF): $(PDFDIR)/%.pdf: $(KEYDIR)/%.tex $(RAILBIN)
	# Compile pour générer la TOC
	TEXINPUTS=.//:$$TEXINPUTS pdflatex -output-directory $(@D) $<
	# Compile les diagrammes de syntaxe
	if [ -a $(KEYRAI).rai ] ; \
	then \
		$(RAILBIN) $(REPRAI) ; \
	fi;
	# Compile avec la TOC
	TEXINPUTS=.//:$$TEXINPUTS pdflatex -output-directory $(@D) $<

# Installation

install: install-stibbons install-stibbons-cli

install-stibbons:
	# Install the program
	install -D $(APP) $(BINDIR)
	# Install the icon
	install -D data/images/stibbons.svg $(INSTALLEDICONDIR)/stibbons.svg
	# Install the desktop entry
	install -D data/stibbons.desktop $(APPSDIR)/stibbons.desktop

install-stibbons-cli:
	install -D $(CLIAPP) $(BINDIR)

# Nettoyage

clean:
	rm -Rf $(APP) $(TEST) \
	$(MODELOBJECTS) \
	$(BISONTMP) \
	$(BISONHEADERS) \
	$(BISONOBJECTS) \
	$(FLEXTMP) \
	$(FLEXOBJECTS) \
	$(INTERPRETEROBJECTS) \
	$(TESTOBJECTS) \
	$(MOCSRC) \
	$(COMMONMOCSRC) \
	$(QRCSRC) \
	$(QTOBJECTS) \
	$(COMMONOBJECTS) \
	$(CLIMOCSRC) \
	$(CLIOBJECTS) \
	$(REPPDFCLN) \
	$(PROPDFCLN) \
	$(KEYPDFCLN) \
	doc/refman \
	$(REPDIR)/refman.tex \
	$(NULL) \
	sauvegarde.json
	make clean -C $(RAILDIR) -f Makefile

.PHONY: all doc refman report project keynote install install-stibbons install-stibbons-cli clean

