NULL =

SRC = \
	$(NULL)

BIN = \
	$(NULL)

DOCDIR = doc
PDFDIR = $(DOCDIR)

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

doc: $(PDF)

$(PDFDIR)/%.pdf: $(DOCDIR)/report/%.tex
	pdflatex -output-directory $(@D) $^

clean:
	rm -Rf $(BIN) $(PDFCLN)

.PHONY: all doc clean

