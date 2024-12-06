// Advent of code 2024 Day-05 Part-01

// Guard Gallivant

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char **map = NULL;
enum compass { RIGHT, DOWN, LEFT, UP };
int direction;

// Turn right
void turn_right(int *direction) { *direction = (*direction + 1) % 4; }

// Check if the next step is an obstacle
bool is_obstacle(char **map, int *pos, int *direction) {
  switch (*direction) {
  case UP:
    if (map[pos[0] - 1][pos[1]] == '#') {
      return true;
    }
    break;
  case RIGHT:
    if (map[pos[0]][pos[1] + 1] == '#') {
      return true;
    }
    break;
  case DOWN:
    if (map[pos[0] + 1][pos[1]] == '#') {
      return true;
    }
    break;
  case LEFT:
    if (map[pos[0]][pos[1] - 1] == '#') {
      return true;
    }
    break;
  }
  return false;
}

// Mark the current location in map with an X
void mark_path(char ***map, int *pos) { (*map)[pos[0]][pos[1]] = 'X'; }

// Change the position based on the direction
void travel(int *pos, int direction) {
  if (direction == UP) {
    pos[0] -= 1;
  } else if (direction == DOWN) {
    pos[0] += 1;
  } else if (direction == LEFT) {
    pos[1] -= 1;
  } else if (direction == RIGHT) {
    pos[1] += 1;
  }
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

  int pos[2];
  unsigned long rows = 0;

  char *line = NULL;
  size_t n;

  // For each line in the file
  for (int i = 0; getline(&line, &n, f) != -1; i++) {
    // Allocate memory for new row
    rows++;
    map = (char **)realloc(map, (rows) * sizeof(char *));

    for (int j = 0; j < (strlen(line) - 1); j++) {

      // Extend memory for new character
      map[i] = (char *)realloc(map[i], (j + 1) * sizeof(char));
      map[i][j] = line[j];

      // Find the starting position
      if (line[j] == '^') {
        pos[0] = i;
        pos[1] = j;
        direction = UP;
      }
    }
  }

  free(line);

  // Loop until an out of bounds position (Guard left the map)
  while (pos[0] >= 0 && pos[0] < rows - 1 && pos[1] > 0 &&
         pos[1] <= strlen(map[pos[0]])) {

    if (is_obstacle(map, &pos[0], &direction)) {
      turn_right(&direction);

      // Clear the screen
      system("clear");
      // Print the map
      for (int i = 0; i < rows; i++) {
        for (int j = 0; j < strlen(map[i]); j++) {
          // Print the current position with the direction
          if (i == pos[0] && j == pos[1]) {

            switch (direction) {
            case LEFT:
              printf("<");
              break;
            case RIGHT:
              printf(">");
              break;
            case DOWN:
              printf("v");
              break;
            case UP:
              printf("^");
            }
          } else {
            printf("%c", map[i][j]);
          }
        }
        printf("\n");
      }
      usleep(100000);
    }

    travel(pos, direction);
    mark_path(&map, pos);
  }

  unsigned long count = 0;

  // Count the number of X
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < strlen(map[i]); j++) {
      if (map[i][j] == 'X') {
        count++;
      }
    }
  }

  printf("Number of steps: %lu\n", count);

  // printf("END\n");
  return EXIT_SUCCESS;
}
