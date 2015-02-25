NULL =

CC = g++
MOC = moc-qt5
RCC = rcc-qt5

INCDIR = /usr/include
QTINCDIR = $(INCDIR)/qt5

INCDIRS = \
	-I$(QTINCDIR) \
	-I$(QTINCDIR)/QtCore \
	-I$(QTINCDIR)/QtGui \
	-I$(QTINCDIR)/QtWidgets \
	$(NULL)

LIBS = \
	-lQt5Core \
	-lQt5Gui \
	-lQt5Widgets \
	$(NULL)

CFLAGS = -fPIC -Wall -Wpedantic

SRC = \
	$(NULL)

MOCHEADERS = \
	$(NULL)

MOCSRC = $(MOCHEADERS:%.h=%.moc.cpp)

QRCFILES = \
	$(NULL)

QRCSRC = $(QRCFILES:%.qrc=%.qrc.cpp)

OBJECTS = $(SRC:%.cpp=%.o) $(MOCSRC:%.cpp=%.o) $(QRCSRC:%.cpp=%.o)

BIN = stibbons

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

all: doc $(BIN)

# Compilation du logiciel

$(BIN): $(OBJECTS)
	$(CC) $(CFLAGS) $(INCDIRS) $(LIBS) $^ -o $@

%.moc.cpp: %.h
	$(MOC) $(INCDIRS) $< -o $@

%.qrc.cpp: %.qrc
	$(RCC) -name $(basename $(<F)) $< -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCDIRS) $(LIBS) $< -c -o $@

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
	rm -Rf $(BIN) $(OBJECTS) $(PDFCLN)

.PHONY: all doc clean

