all: main.pdf

main.pdf: main.tex
	pdflatex $<
	pdflatex $<
	#bibtex main
	pdflatex $<
	pdflatex $<

clean:
	rm -f *.pdf
	rm -f *.aux
	rm -f *.log
	rm -f *.toc
	rm -f *.bbl
	rm -f *.blg
	rm -f *.lof