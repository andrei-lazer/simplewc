#ifndef SIMPLEWC_H
#define SIMPLEWC_H

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct fileStats {
  int lines;
  int words;
  int bytes;
};

void print_help() {
  FILE *help_file;
  help_file = fopen("./help.txt", "r");

  int c;

  while ((c = getc(help_file)) != EOF) {
    putchar(c);
  }
  fclose(help_file);
}

int simplewc_str(const char *str, struct fileStats *stats, int state) {
  int len = strlen(str);

  // `state` defines whether in a word or in whitespace.
  // 0 = whitespace, 1 = word
  //
  // state is passed as an argument to keep track of whether the parser is in a
  // word or not at the chunk boundary.

  int i;
  char c;

  for (i = 0; i < len; i++) {
    c = str[i];
    if (isspace(c)) {
      state = 0;

      if (c == '\n') {stats->lines++;}

    } else if (state == 0) {
      state = 1;
      stats->words++;
    }
    stats->bytes++;
  }
  return state;
}

void simplewc_file(const char *fileName, struct fileStats *stats) {
  const int chunksize = 64;
  char buffer[chunksize + 1]; // + 1 so that I can add a \0 character at the end
  struct fileStats temp_fs = {0, 0, 0};
  /* temp_fs is used to track the stats for this file only, while also updating
   * stats. It's the easiest way I found to print out the values for each file
   * given AND keep track of the total at the end.*/

  FILE *f;
  f = fopen(fileName, "rb");
  if (f == NULL) {
    printf("simplewc: %s: no such file or directory.\n", fileName);
    return;
  }

  size_t bytesRead = 1;
  int state = 0;

  while (bytesRead > 0) {
    bytesRead = fread(buffer, sizeof(char), chunksize, f);
    buffer[bytesRead] = '\0';
    simplewc_str(buffer, stats, state);
    state = simplewc_str(buffer, &temp_fs, state);
  }

  fclose(f);

  printf("%4d %4d %4d %s\n", temp_fs.lines, temp_fs.words, temp_fs.bytes,
         fileName);
}

void simplewc(const char **fileNames, int filesCount) {
  int i;
  struct fileStats fs = {0, 0, 0};
  for (i = 0; i < filesCount; i++) {
    simplewc_file(fileNames[i], &fs);
  }
  if (filesCount > 1) {
    printf("%4d %4d %4d %s\n", fs.lines, fs.words, fs.bytes, "total");
  }
}

#endif // SIMPLEWC_H
