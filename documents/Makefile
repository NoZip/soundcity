
all: biblio.pdf etude.pdf cahier_besoins.pdf

biblio.pdf: biblio.tex
	pdflatex $<
	pdflatex $<
	bibtex $(basename $< .tex)
	pdflatex $<
	pdflatex $<

etude.pdf: etude.tex
	pdflatex $<
	pdflatex $<

cahier_besoins.pdf: cahier_besoins.tex
	pdflatex $<
	pdflatex $<
