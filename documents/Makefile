
all: biblio.pdf

%.pdf: %.dvi
	dvipdf $< $@

%.dvi: %.tex
	latex $<
	latex $<
	bibtex $(basename $< .tex)
	latex $<
	latex $<