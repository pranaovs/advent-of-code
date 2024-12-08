// Advent of code 2024 Day-XX Part-0X

// Template for AOC

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

  // printf("\nSTART\n");

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

  char **table = NULL;
  int rows = 0;

  char *line = NULL;
  size_t n;

  // For each line in the file
  for (int i = 0; getline(&line, &n, f) != -1; i++) {

    // Skip empty lines
    if (strcmp(line, "\n\0") == 0) {
      continue;
    }

    // Allocate memory for new row
    rows++;
    table = (char **)realloc(table, (rows) * sizeof(char *));

    for (int j = 0; j < (strlen(line) - 1); j++) {

      // Extend memory for new character
      table[i] = (char *)realloc(table[i], (j + 1) * sizeof(char));
      table[i][j] = line[j];
    }
  }
  free(line);

  // Print the table
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < strlen(table[i]); j++) {
      printf("%c", table[i][j]);
    }
    printf("\n");
  }

  // printf("END\n");
  return EXIT_SUCCESS;
}
