// Advent of code 2024 Day-02 Part-01

// Nosed Reports

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 100

void strcsub(char *dest, char *src, int start, int end) {
  int length = end - start + 1;
  strncpy(dest, src + start, length);
  dest[length] = '\0';
}

void split_number(char *num, int **nums, int *numc) {

  // Count the number of characters in the string
  int strcount = 0;
  for (int i = 0; i < MAX_LINE; i++) {
    if (num[i] == '\0') {
      break;
    } else {
      strcount++;
    }
  }

  int numcount = 1;
  for (int i = 0; i < strcount; i++) {
    if (num[i] == ' ') {
      numcount++;
    }
  }

  // int numlist[numcount];
  int *numlist = (int *)malloc(numcount * sizeof(int));

  int numlistcount = 0;

  int start = 0;
  for (int i = 0; i <= strcount; i++) {
    if (num[i] == ' ' || num[i] == '\0') {

      char temp[10];
      strcsub(temp, num, start, i);
      numlist[numlistcount] = atoi(temp);
      start = i + 1;
      numlistcount++;
    }
  }

  *nums = numlist;
  *numc = numcount;
}

bool safe_value(int *nums, int numcount) {

  int ascending;

  if (nums[0] < nums[1]) {
    ascending = 1;
  } else {
    ascending = 0;
  }

  for (int i = 1; i < numcount; i++) {
    if (ascending == 1) {
      if (nums[i] > nums[i - 1]) {
        if ((abs(nums[i] - nums[i - 1]) >= 1) &&
            (abs(nums[i] - nums[i - 1]) <= 3)) {
        } else {
          return false;
        }
      } else {
        return false;
      }
    } else {
      if (nums[i] < nums[i - 1]) {
        if ((abs(nums[i] - nums[i - 1]) >= 1) &&
            (abs(nums[i] - nums[i - 1]) <= 3)) {
        } else {
          return false;
        }
      } else {
        return false;
      }
    }
  }
  return true;
}

int main(int argc, char *argv[]) {
  printf("\nSTART\n");
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

  int safes = 0;
  for (int i = 0; i < lines; i++) {
    char line[MAX_LINE];
    fgets(line, MAX_LINE, listf);
    int *numlist;
    int numcount;
    split_number(line, &numlist, &numcount);

    if (safe_value(numlist, numcount)) {
      safes++;
    }
  }

  printf("Safe paths: %d\n", safes);

  // Close file
  fclose(listf);

  printf("\nEND\n");
  return EXIT_SUCCESS;
}
