// Advent of code 2024 Day-01 Part-02

// Historian Hysteria

// Similarity Score

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void split_number(int *num1, int *num2, char num[15]) {
  char firstc[6];
  char secondc[6];

  // Copy the first 5 characters
  strncpy(firstc, num, 5);
  firstc[5] = '\0';

  // Move the rest of the characters to the beginning of the array (remove
  // spaces)
  memmove(num, num + 8, strlen(num) - 8 + 1);

  // Copy the next 5 characters
  strncpy(secondc, num, 5);
  firstc[5] = '\0';

  *num1 = atoi(firstc);
  *num2 = atoi(secondc);
}

// Bubble sort
void sort_list(int *list, int length) {
  int temp;
  for (int i = 0; i < length; i++) {
    for (int j = i + 1; j < length; j++) {
      if (list[i] > list[j]) {
        temp = list[i];
        list[i] = list[j];
        list[j] = temp;
      }
    }
  }
}

int similarity_score(int num1, int *list2, int length) {
  int score = 0;

  for (int i = 0; i < length; i++) {
    if (num1 == list2[i]) {
      score += num1;
    }
  }

  return score;
}

int main(int argc, char *argv[]) {
  FILE *listf;

  // Check for input file
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <input file>\n", argv[0]);
    return EXIT_FAILURE;
  }

  // Open file
  if ((listf = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "Error: unable to open file %s\n", argv[1]);
    return EXIT_FAILURE;
  }

  // File length
  int lines = 0;

  while (!feof(listf)) {
    if (fgetc(listf) == '\n') {
      lines++;
    }
  }

  fseek(listf, 0, SEEK_SET);

  char line[15];
  int list1[lines];
  int list2[lines];

  for (int i = 0; i < lines; i++) {
    fgets(line, sizeof(line), listf);

    // Allocate memory for the numbers
    int *num1ptr = (int *)malloc(sizeof(int));
    int *num2ptr = (int *)malloc(sizeof(int));

    // Split the line into two numbers
    split_number(num1ptr, num2ptr, line);

    // assign the numbers to the lists
    list1[i] = *num1ptr;
    list2[i] = *num2ptr;

    // Free the memory
    free(num1ptr);
    free(num2ptr);
  }

  // Close file
  fclose(listf);

  // Sort the lists
  sort_list(list1, sizeof(list1) / sizeof(list1[0]));
  sort_list(list2, sizeof(list2) / sizeof(list2[0]));

  int score = 0;

  for (int i = 0; i < lines; i++) {
    score += similarity_score(list1[i], list2, lines);
  }

  printf("Similarity Score: %d\n", score);

  return EXIT_SUCCESS;
}
