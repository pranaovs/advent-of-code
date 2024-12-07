// Advent of code 2024 Day-04 Part-02

// Ceres Search

#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 2048

int main(int argc, char *argv[]) {

  FILE *f;

  // Check for input file
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <input file>\n", argv[0]);
    return EXIT_FAILURE;
  }

  // Open file
  if ((f = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "Error: unable to open file %s\n", argv[1]);
    return EXIT_FAILURE;
  }

  // File length
  int lines = 0;
  char c;
  char line[MAX_LINE_LENGTH];

  char crossword[MAX_LINE_LENGTH][MAX_LINE_LENGTH];

  // while (!feof(f)) {
  //   while ((c = fgetc(f) != '\n')) {
  //     printf("%c", c);
  //   }
  //   printf("\n");
  // }

  // Iterate through each line of the file
  int i = 0;
  while (fgets(line, sizeof(line), f)) {
    // Iterate through each character of the line
    int j = 0;
    while (line[j] != '\0' && line[j] != '\n') {
      crossword[i][j] = line[j];
      j++;
    }
    i++;
  }

  // Go the beginning of the file
  // fseek(listf, 0, SEEK_SET);

  int matches = 0;

  for (int i = 0; i < MAX_LINE_LENGTH; i++) {
    if (crossword[i][0] == '\0') {
      break;
    }
    for (int j = 0; j < MAX_LINE_LENGTH; j++) {
      if (crossword[i][j] == '\0') {
        break;
      }

      if (crossword[i][j] == 'A') {
        if (crossword[i - 1][j - 1] == 'M' && crossword[i - 1][j + 1] == 'S' &&
            crossword[i + 1][j - 1] == 'M' && crossword[i + 1][j + 1] == 'S') {
          matches++;
        }
        if (crossword[i - 1][j - 1] == 'S' && crossword[i - 1][j + 1] == 'M' &&
            crossword[i + 1][j - 1] == 'S' && crossword[i + 1][j + 1] == 'M') {
          matches++;
        }
        if (crossword[i - 1][j - 1] == 'S' && crossword[i - 1][j + 1] == 'S' &&
            crossword[i + 1][j - 1] == 'M' && crossword[i + 1][j + 1] == 'M') {
          matches++;
        }
        if (crossword[i - 1][j - 1] == 'M' && crossword[i - 1][j + 1] == 'M' &&
            crossword[i + 1][j - 1] == 'S' && crossword[i + 1][j + 1] == 'S') {
          matches++;
        }
      }
    }
  }

  // Close file
  fclose(f);

  printf("Matches: %d\n", matches);

  return EXIT_SUCCESS;
}
