#include "functions.h"
#include "tests/tests.h"


int main(int argc, const char *argv[]) {
  if (argc < 2 || strcmp(argv[1], "-h") == 0) {

    print_help();
    return (0);

  } else if (strcmp(argv[1], "--test") == 0) {

    run_str_tests(1);
    run_file_tests(1);

  } else {

    simplewc(argv + 1, argc - 1);
  }

  return (0);
}
