#ifndef TESTS_H
#define TESTS_H
#include <assert.h>
#include <stdio.h>

// testing the simplewc_str function

void str_test_bytes() {
  fileStats fs = {0, 0, 0};
  char s[] = "abcdefghijklmnopqrstuvwxyz";
  simplewc_str(s, &fs, 0);
  assert(fs.bytes == 26);
}

void str_test_words() {
  fileStats fs = {0, 0, 0};
  char s[] = "Here are many words about some things that people talk about.";
  simplewc_str(s, &fs, 0);
  assert(fs.words == 11);
}

void str_test_lines() {
  fileStats fs = {0, 0, 0};
  char s[] = "Wow!\nSo\nMany\nLines!\n";
  simplewc_str(s, &fs, 0);
  assert(fs.lines == 4);
}

void str_test_empty() {
  fileStats fs = {0, 0, 0};
  char s[] = "";
  simplewc_str(s, &fs, 0);
  assert(fs.bytes == 0);
  assert(fs.words == 0);
  assert(fs.lines == 0);
}

void str_test_multiple_spaces() {
  fileStats fs = {0, 0, 0};
  char s[] = "So         many       spaces";
  simplewc_str(s, &fs, 0);
  assert(fs.bytes == 28);
  assert(fs.words == 3);
  assert(fs.lines == 1);
}

void str_test_multiple_lines() {
  fileStats fs = {0, 0, 0};
  char s[] = "many\n\n\n\n\n new \n\n\n\n\n\n lineeeeee \n\n\n\n\n eeeeeees";
  simplewc_str(s, &fs, 0);
  assert(fs.bytes == 36);
  assert(fs.words == 4);
  assert(fs.lines == 17);
}

void run_str_tests(const int verbose) {
  if (verbose > 0) {
    printf("Running string tests...\n");
  }

  str_test_bytes();
  str_test_words();
  str_test_lines();
  str_test_empty();

  if (verbose > 0) {
    printf("Tests passed!\n");
  }
}

// testing simplewc_file

void file_test_bytes() {
  // setup
  char test_string[] = "abcdefghijklmnopqrstuvwxyz";
  FILE *ftest;
  ftest = fopen("test.txt", "w");
  fputs(test_string, ftest);

  fclose(ftest);

  fileStats fs = {0, 0, 0};
  simplewc_file("test.txt", &fs);

  // assert
  assert(fs.bytes == 26);

  // teardown
  remove("test.txt");
}

void run_file_tests(const int verbose) {
  if (verbose > 0) {
    printf("Running file tests...\n");
  }

  file_test_bytes();

  if (verbose > 0) {
    printf("Tests passed!\n");
  }
}


#endif // TESTS_H
