// Advent of code 2024 Day-05 Part-01

// Print Queue

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 128

// Function to get position of an integer in a queue
int get_pos(int *queue, int queue_count, int value) {
  int pos = -1;
  for (int i = 0; i < queue_count; i++) {
    if (queue[i] == value) {
      pos = i;
      break;
    }
  }
  return pos;
}

// Function to validate a queue against rules
bool validate_queue(int *queue, int queue_count, int **rules, int rules_count) {
  bool valid = true;

  // for (int i = 0; i < queue_count; i++) {
  //   printf("Position of 5 in queue is %d\n", get_pos(queue, queue_count,
  //   75));
  // }

  // For each rule
  for (int i = 0; i < rules_count; i++) {
    // Get position of first and second integer of rule in queue
    int pos0 = get_pos(queue, queue_count, rules[i][0]);
    int pos1 = get_pos(queue, queue_count, rules[i][1]);
    // If both integers are present in queue and are not in order, break
    if (pos0 != -1 && pos1 != -1) {
      if (pos0 > pos1) {
        valid = false;
        break;
      }
    }
  }

  return valid;
}

int main(int argc, char *argv[]) {

  printf("\nSTART\n");

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

  enum state { RULES, QUEUE };
  int program_state = RULES;

  int **rules = NULL;
  int rules_count = 0;

  int mid_count = 0;

  // For each line in the file
  char line[MAX_LINE_LENGTH];
  for (int line_no = 0; fgets(line, sizeof(line), f); line_no++) {

    if (program_state == RULES) {
      // printf("Processing RULES at line %d\n", line_no + 1);

      // If line is empty, switch to processing QUEUE
      if (strcmp(line, "\n") == 0) {
        // printf("Switching to QUEUE at line %d\n", line_no + 1);
        program_state = QUEUE;
      }

      // If line is not empty, parse rules
      else {

        // Allocate memory for new rule
        rules = (int **)realloc(rules, (rules_count + 1) * sizeof(int *));

        // Allocate memory for two integers
        rules[rules_count] = (int *)malloc(2 * sizeof(int));

        // Parse integers from line and store in newly allocated rules array
        sscanf(line, "%d|%d", &rules[rules_count][0], &rules[rules_count][1]);
        rules_count++;
      }

    } else if (strcmp(line, "\n\0") == 0) {
      // printf("Ignoring empty line %d\n", line_no + 1);
      continue;
    } else if (program_state == QUEUE) {
      // printf("Processing QUEUE at line %d\n", line_no + 1);

      int *queue = NULL;
      int queue_count = 0;
      int last_comma = -1;

      // For each character in line
      for (int i = 0; i < strlen(line); i++) {

        if (line[i] == ',' || line[i] == '\0' || line[i] == '\n') {
          // Reallocate (increase) memory for new queue int
          queue = (int *)realloc(queue, (queue_count + 1) * sizeof(int));

          char temp[i - last_comma];
          // Copy integer from line to temp
          strncpy(temp, &line[last_comma + 1], i - last_comma - 1);

          // Null terminate temp
          temp[i - last_comma - 1] = '\0';

          // Convert temp to integer and store in queue array
          queue[queue_count] = atoi(temp);

          queue_count++;
          last_comma = i;
        }
      }
      bool ans = validate_queue(queue, queue_count, rules, rules_count);
      if (ans) {
        printf("valid queue: ");
        for (int i = 0; i < queue_count; i++) {
          printf("%d ", queue[i]);
        }
        printf("\n");
        printf("Queue length: %d\n", queue_count);
        mid_count += queue[(queue_count) / 2];
      }
    }
  }

  printf("Valid queues: %d\n", mid_count);
  printf("END\n");
  return EXIT_SUCCESS;
}
