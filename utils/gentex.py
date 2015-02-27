#!/usr/bin/python
import re, os, sys, hashlib, subprocess

# Improved Windows Support.

line_count = 1

def digest_line(s):
	return hashlib.md5(re.sub(r'\s|//.*', '', s)).hexdigest()[-4:]

langs = {"c": "C", "cpp": "C++", "py": "Python", "pl": "Perl",
		 "sh": "sh", "java": "Java"}

def lang(ext):
	if not ext: return "{}"
	ext = ext.lower()
	return langs[ext] if ext in langs else "{}"

def gen_section(name, dirname):
	global line_count
	sect = []
	#sect.append("\\section{%s}" % name)
	sect.append("\\section{%s}" % name.encode('utf-8'))

	files = []
	for src in os.listdir(u"./%s/" % dirname):
		fp = open(u"./%s/%s" % (dirname, src), "r") # read the file
		code = fp.read().strip()
		fp.close()

		match = re.search(r'^((\d+) )?(.*?)(\.([^.]*))?$', src)
		index = int(match.group(2)) if match.group(1) else 99999
		title = match.group(3)
		extension = match.group(5)
		orig_name = u"./%s/%s" % (dirname, src)

		files.append( (index, title, extension, code, orig_name) )
		
	for (index, title, extension, code, orig_name) in sorted(files):
		#sect.append("\\subsection{%s}" % title)
		if extension.lower() == 'bak':
			continue
		isGenerator = False
		title = title.replace('_','\\_')
		if title.endswith('.generator'):
			title = title[:-len('.generator')]
			isGenerator = True
		sect.append("\\subsection{%s}" % title.encode('utf-8'))

		#for line in code.split("\n"):
		#	sect.append("\\createlinenumber{%d}{%s}" % (line_count, digest_line(line)))
		#	line_count += 1

		if extension.lower() == 'tex':
			sect.append(code)
		elif isGenerator:
			code = subprocess.Popen(['python', orig_name], stdout=subprocess.PIPE).communicate()[0]
			sect.append(code)
		else:
			code = code.strip()
			if code.find('<TeX>') == 0:
				pos = code.find('</TeX>')
				if pos == -1:
					print '<TeX> tag mismatch in %s' % title
					sys.exit(1)
				pretex = code[5:pos]
				code = code[pos+6:].strip()
				sect.append(pretex)

			sect.append("\\begin{lstlisting}[language=%s]" % lang(extension))
			sect.append(code)
			sect.append("\\end{lstlisting}")
	
	return "\n".join(sect)

doc = []
os.chdir(u"../src/")
for section in os.listdir(u"."):
	match = re.search(r'^(\d+) (.*)$', section)
	(index, name) = (int(match.group(1)), match.group(2)) if match else (99999, section)
	doc.append((index, name, section))

print "\n\n".join([gen_section(item[1], item[2]) for item in sorted(doc)])
