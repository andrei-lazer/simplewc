#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* WordState is An enum to keep track of the 'state' of the parser at chunk
 * boundaries. Files are read and parsed in chunks, so to avoid overcounting
 * words (if we're inside a word at a chunk boundary), the state is always
 * passed from chunk to chunk.
 */
enum WordState { OUT, IN };

// simple struct to keep counts all in one place
typedef struct {
  int lines;
  int words;
  int bytes;
} fileStats;

/* print_help: used to print the help message when invalid input or the "-h"
 * argument is provided.
 */
void print_help() {
  FILE *help_file;
  help_file = fopen("./help.txt", "r");

  char c;

  while ((c = getc(help_file)) != EOF) {
    putchar(c);
  }
  fclose(help_file);
}

/* simplewc_str: counts the lines, words and bytes in a string. Main workhorse.
 * param *str: pointer to the string in question
 *
 *
 * param *stats: pointer to a fileStats struct that will be updated, not
 * overwritten
 *
 * param state: WordState enum used to keep track of words at chunk
 * boundaries
 *
 *
 * returns: a WordState enum to pass to the next chunk
 */
enum WordState simplewc_str(const char *str, fileStats *stats, enum WordState state) {

  int len = strlen(str);

  int i;
  char c;

  for (i = 0; i < len; i++) {
    c = str[i];
    if (isspace(c)) {

      if (c == '\n') {
        stats->lines++;
      }

      state = OUT;

    } else if (state == OUT) {
      state = IN;
      stats->words++;
    }
    stats->bytes++;
  }
  return state;

}

void simplewc_file(const char *fileName, fileStats *stats) {
  const int chunksize = 64;
  char buffer[chunksize + 1]; // + 1 to have space for a \0 character at the end
  fileStats temp_fs = {0, 0, 0};
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
  enum WordState state = OUT;

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
  fileStats fs = {0, 0, 0};
  for (i = 0; i < filesCount; i++) {
    simplewc_file(fileNames[i], &fs);
  }
  if (filesCount > 1) {
    printf("%4d %4d %4d %s\n", fs.lines, fs.words, fs.bytes, "total");
  }
}

#endif // SIMPLEWC_H
