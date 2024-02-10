# simplewc

Prints the number of lines, words, and bytes in a file. Simplified clone of the `wc` command line tool in UNIX using C.

A variety of testing methods have been implemented in C and Python.


## Requirements
Make and gcc to build everything.

For property-based testing, python with [Hypothesis](https://github.com/HypothesisWorks/hypothesis) and [pytest](https://github.com/pytest-dev/pytest).

`pip install hypothesis pytest`


## Installation
First, clone the repo:

`git clone https://github.com/andrei-lazer/simplewc.git`

Then, build:

`cd simplewc && make`


## Usage

`./simplewc FILE...`

Print total newline, word, and byte counts for all FILEs given.

A word is a non-zero-length sequence of characters delimited by a whitespace,
and a line is a sequence of zero or more non-newline characters plus a 
terminating newline character.

At least one FILE must be given as input

## Testing

Running `./simplewc --test` will run all the C unit tests, with output.

For more thorough property-based testing using the [Hypothesis](https://github.com/HypothesisWorks/hypothesis) module, run:

`pytests tests/proptesting/test.py`


## Fuzzing

Run 

`tests/fuzzing/build-afl.sh`

to build [AFL](https://github.com/google/AFL), a brute-force fuzzer driven by a genetic algorithm.

Then, run 

`tests/fuzzing/afl-testing.sh`

to start the fuzzer.
