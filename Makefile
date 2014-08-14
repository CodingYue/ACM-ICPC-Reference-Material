all:
	find . -name .DS_Store -exec rm -f {} \;
	cd utils && python ./gentex.py > code.tex && xelatex main.tex && xelatex main.tex
	mv utils/main.pdf ./ && open main.pdf && cp main.pdf ~/Dropbox/acm-pdf
clean:
	cd utils; rm -f main.pdf main.aux main.log
