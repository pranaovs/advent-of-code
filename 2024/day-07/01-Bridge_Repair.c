// Advent of code 2024 Day-07 Part-01

// Bridge Repair

#include <stdbool.h>
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

  char *line = NULL;
  size_t n;

  // For each line in the file
  for (int i = 0; getline(&line, &n, f) != -1; i++) {

    // Skip empty lines
    if (strcmp(line, "\n\0") == 0) {
      continue;
    }

    int pos = strchr(line, ':') - line; // Calculate index of the colon
    char sans[pos];                     // Create an string for the number
    strncpy(sans, line, pos); // Copy the string before the colon into string
    sans[pos] = '\0';         // Null-Terminate the string
    int ans = atoi(sans);     // Convert the string to an integer
    for (int j = pos + 2; j < (strlen(line) - 1); j++) {
    }

  }

  // printf("END\n");
  return EXIT_SUCCESS;
}
