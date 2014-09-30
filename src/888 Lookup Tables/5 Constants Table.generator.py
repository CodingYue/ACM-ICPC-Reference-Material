#!/usr/bin/python
# coding=utf-8

# ----------------------- HELPERS ---------------------------
def zipper(lst, start=1): return dict(zip(range(len(lst)),lst))
def crange(l,r,step=1): return range(l,r+1,step)
def cxrange(l,r,step=1): return xrange(l,r+1,step)
# -----------------------------------------------------------

# ----------------------- TABULAR ---------------------------
'''
name: Column name.
list: The number sequence, it could be a function (named or lambda) with single parameter `n`, or a list (0-based index), or a dict (like {2:10, 3: 20, 10: 233}).
limit: A function with single parameter `n`, return True if n should be included.
limit_result: Similar to `limit` but works on `f(n)` instead of `n`.
'''

import math, sys
from fractions import gcd
def binom(n,k):
	return math.factorial(n) / math.factorial(k) / math.factorial(n-k)

C_TABLE_1 = {
	"n_list": crange(2,12) + crange(15,30,5) + [40, 50, 70] ,
	"sequences":[
	{
		"name": r"$ \log _ {10} n $",
		"list": lambda n: '%.2f' % math.log10(n),
		"limit": lambda n: n <= 10
	},
	{
		"name": r"$ n! $",
		"list": math.factorial,
		"limit_result": lambda x: len(str(x)) < 10
	},
	{
		"name": r"$\binom{n}{n/2}$",
		"list": lambda n: binom(n,n//2),
		"limit_result": lambda x: len(str(x)) < 10
	},
	{
		"name": r"$LCM(1 \ldots n)$",
		"list": lambda n: reduce(lambda a,b: a/gcd(a,b)*b, cxrange(1,n), 1),
		"limit_result": lambda x: len(str(x)) < 10
	},
	{
		"name": r"$P_n$",
		"list": [1, 1, 2, 3, 5, 7, 11, 15, 22, 30, 42, 56, 77, 101, 135, 176, 231, 297, 385, 490, 627, 792, 1002, 1255, 1575, 1958, 2436, 3010, 3718, 4565, 5604, 6842, 8349, 10143, 12310, 14883, 17977, 21637, 26015, 31185, 37338, 44583, 53174, 63261, 75175, 89134, 105558, 124754, 147273, 173525]
	},
	{
		"name": r"$B_n$",
		"list": [1, 1, 2, 5, 15, 52, 203, 877, 4140, 21147, 115975, 678570, 4213597, 27644437, 190899322, 1382958545]
	},]
}

def minRep(n):
	f = [0] * (n+1)
	f[1] = 1
	for i in xrange(2,n+1):
		f[i] = i ** n
		for j in xrange(1,i): f[i] -= f[j] * binom(i,j)
	ans = 0
	for i in xrange(1,n+1): ans += f[i] / math.factorial(i)
	return ans

C_TABLE_2 = {
	"n_list": crange(1,20), 
	"sequences":[
	{
		"name": r"最小表示",
		"list": minRep,
		"limit_result": lambda x: len(str(x)) < 10
	},
	]
}

C_TABLE = [C_TABLE_1,C_TABLE_2,]
# -----------------------------------------------------------

def generate_table(tab):
	column_cnt = len(tab["sequences"]) + 1
	print r'\begin{tabular}{ | ' + ('r | ' * column_cnt) + '}'
	print r'\hline'

	# title
	print ' & '.join(["$n$"] + [item["name"] for item in tab["sequences"]]), r'\\ \hline'

	# items
	for n in tab["n_list"]:
		arr = [n]
		for item in tab["sequences"]:
			if item.has_key("limit") and not item["limit"](n):
				arr.append(None)
				continue

			result = None
			try:
				conv = item["list"]
				if callable(conv):
					result = conv(n)
				else:
					result = conv[n]
				if item.has_key("limit_result") and not item["limit_result"](result):
					result = None
			except Exception as e:
				if e.message != 'list index out of range':
					print >>sys.stderr, 'Warning: Generation of %d-th item of %s failed with %s.' % (n, item["name"], e.message)

			arr.append(result)
		print ' & '.join(map(lambda x: '' if x is None else str(x), arr)), r'\\ \hline'


	print r'\end{tabular}'
	print ''

for tab in C_TABLE:
	generate_table(tab)
