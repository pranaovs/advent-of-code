// Advent of code 2024 Day-08 Part-01

// Resonant Collinearity

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double distance(char antenna, int startx, int starty, char **map, int rows) {

  for (int i = startx; i < rows; i++) {
    // Start loop from starty only if outer loop is startx
    for (int j = (i == startx ? starty : 0); j < strlen(map[i]); j++) {
      if (map[i][j] == antenna) {
        return sqrt(pow(i - startx, 2) + pow(j - starty, 2));
      }
    }
  }
  return 0;
}

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

  char **map = NULL;
  char **antinodes = NULL;
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
    map = (char **)realloc(map, (rows) * sizeof(char *));
    antinodes = (char **)realloc(antinodes, (rows) * sizeof(char *));

    for (int j = 0; j < (strlen(line) - 1); j++) {

      // Extend memory for new character
      map[i] = (char *)realloc(map[i], (j + 1) * sizeof(char));
      map[i][j] = line[j];

      // Put empty value in antinodes
      antinodes[i] = (char *)realloc(antinodes[i], (j + 1) * sizeof(char));
      antinodes[i][j] = '.';
    }
  }
  free(line);

  // For each point in the empty map
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < strlen(antinodes[i]); j++) {
      // printf("Row %d, Col %d\n", i, j);
      // For each point on the antenna map
      for (int m = 0; m < rows; m++) {
        for (int n = 0; n < strlen(map[i]); n++) {
          // printf("Antenna Row %d, Col %d\n", m, n);
          // If the point is an antenna
          if (map[m][n] != '.') {
            char antenna = map[m][n];

            // Distance between empty place and first antenna
            long double dist1 = sqrt(pow(i - m, 2) + pow(j - n, 2));
            long double dist2;

            for (int p = m; p < rows; p++) {
              // start loop from starty only if outer loop is startx
              for (int q = (p == m ? (n + 1) : 0); q < strlen(map[p]); q++) {
                if (map[p][q] == antenna) {
                  // Distance between empty place and second antenna
                  dist2 = sqrt(pow(i - p, 2) + pow(j - q, 2));

                  if (((2 * dist1) == dist2) || ((2 * dist2) == dist1)) {

                    antinodes[i][j] = 'X';
                    // printf("Antinode found at %d, %d\n", p, q);
                    // goto found; // Skip the rest of the loop
                  }
                }
              }
            }
          }
        }
      }
    found:
    }
  }

  // Print the map

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < strlen(antinodes[i]); j++) {
      printf("%c", antinodes[i][j]);
    }
    printf("\n");
  };

  // Count the number of antinodes
  unsigned int count = 0;

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < strlen(antinodes[i]); j++) {
      if (antinodes[i][j] == 'X') {
        count++;
      }
    }
  }

  printf("Antinodes: %d\n", count);

  // printf("END\n");
  return EXIT_SUCCESS;
}
