# testing simplewc and comparing it to wc

import string
import subprocess as sbp
from os import remove

from hypothesis import example, given
from hypothesis import strategies as st

import pytest

def normalize_wc_stdout(wc_process: sbp.CompletedProcess):
    """used to normalize the output from wc and ./simplewc, since
    they don't format strings the same exact way. returns an array of arrays:
    [[lines, words, bytes, file_name], ...] for each line (including the 'total' line.)
    """
    line_arr = wc_process.stdout.split(b"\n")
    output = []

    for l in line_arr:
        output.append(l.split())
    return output


def file_setup(file_name, text):
    with open(file_name, "w") as f:
        f.write(text)


def normal_wc(args):
    return normalize_wc_stdout(sbp.run(["wc"] + args, capture_output=True))


def normal_simplewc(args):
    return normalize_wc_stdout(sbp.run(["./simplewc"] + args, capture_output=True))


alphabet = list(string.printable)


class Tests:

    @given(text=st.text(alphabet))
    @example(text=("a" * 100))
    @example(text="\t" * 100 + "\r" * 100)
    def test_single_file(self, text):
        file_setup("test.txt", text)

        assert normal_wc(["test.txt"]) == normal_simplewc(["test.txt"])

        # teardown
        remove("test.txt")




    @given(st.lists(st.text(alphabet), min_size=1, max_size=100))
    # @example(["fsdaasfasfa", "a"*1000])
    # @example([""] * 1000)
    def test_multi_file(self, texts):
        # texts is an array, where texts[i] is the text to be put in the file "test{i}.txt"
        file_names = []
        for i, s in enumerate(texts):
            name = f"test_{i}.txt"
            file_setup(name, s)
            file_names.append(name)


        assert(normal_wc(file_names) == normal_simplewc(file_names))

        for name in file_names:
            remove(name)
