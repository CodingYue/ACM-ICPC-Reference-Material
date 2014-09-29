@echo off
rem For windows users without MSYS or Cygwin.

cd utils
python gentex.py > code.tex && xelatex main.tex && xelatex main.tex
cd ..
move utils\main.pdf .
