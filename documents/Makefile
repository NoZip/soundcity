
all: biblio.pdf etude.pdf

%.pdf: %.dvi
	dvipdf $< $@

biblio.dvi: biblio.tex
	latex $<
	latex $<
	bibtex $(basename $< .tex)
	latex $<
	latex $<

etude.dvi: etude.tex
	latex $< 