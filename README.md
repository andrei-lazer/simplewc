# simplewc

Prints the number of lines, words, and bytes in a file. Simplified clone of the `wc` command line tool in UNIX using C.

Unit and fuzzy tests implemented in C and Python.

## Installation
First, clone the repo:
`git clone https://github.com/andrei-lazer/simplewc.git`

Then, build:
`cd simplewc && make`

## Usage

`wc FILE...`

Print total newline, word, and byte counts for all FILEs given.

A word is a non-zero-length sequence of characters delimited by a whitespace,
and a line is a sequence of zero or more non-<newline> characters plus a 
terminating <newline> character.

At least one FILE must be given as input



