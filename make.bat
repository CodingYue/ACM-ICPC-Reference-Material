rem For windows users without MSYS or Cygwin.
@echo off

cd utils
python gentex.py > code.tex && xelatex main.tex && xelatex main.tex
cd ..
move utils\main.pdf .
