NULL =

SRC = \
	$(NULL)

BIN = \
	$(NULL)

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

all: doc

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
	rm -Rf $(BIN) $(PDFCLN)

.PHONY: all doc clean

