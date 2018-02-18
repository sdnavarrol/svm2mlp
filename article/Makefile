all: clean doc
	
clean:
	rm *.aux *.pdf
doc:
	latex bare_jrnl.tex
	bibtex bare_jrnl.aux
	pdflatex bare_jrnl.tex
	atril bare_jrnl.pdf