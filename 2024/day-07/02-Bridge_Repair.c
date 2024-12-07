// Advent of code 2024 Day-07 Part-02

// Bridge Repair

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

void int_to_ternary_str(int n, int digits, char *ternary_str) {

  // Set all bits to zero
  for (int i = 0; i < digits; i++) {
    (ternary_str)[i] = '0';
  }

  // Convert dec to base 3
  for (int j = digits - 1; n > 0 && j >= 0; j--) {
    switch (n % 3) {
    case 0:
      (ternary_str)[j] = '0';
      break;
    case 1:
      (ternary_str)[j] = '1';
      break;
    case 2:
      (ternary_str)[j] = '2';
      break;
    }

    n = n / 3;
  }
}

unsigned long concat_int(unsigned long a, unsigned long b) {
  // Calculate the length of the two integers
  int len_a = snprintf(NULL, 0, "%lu", a);
  int len_b = snprintf(NULL, 0, "%lu", b);

  // Allocate memory for the concatenated string
  char *concat_str = (char *)malloc(len_a + len_b + 1);
  if (concat_str == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(1);
  }

  // Concatenate the integers as strings
  snprintf(concat_str, len_a + len_b + 1, "%lu%lu", a, b);

  // Convert the concatenated string back to an integer
  unsigned long result = strtol(concat_str, NULL, 10);

  // Free the allocated memory
  free(concat_str);

  return result;
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

  unsigned long calibration_result = 0;

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
    unsigned long ans =
        strtol(sans, NULL, 10); // Convert the string to an integer

    // Initialize an array of numbers
    int *nums = NULL;
    int nums_count = 0;
    int from = pos + 2; // Start from the character after the colon

    // For each character in the line
    for (int j = pos + 2; j < (strlen(line)); j++) {
      // Check if the character is a space or newline (one number ends)
      if (line[j] == ' ' || line[j] == '\n') {
        // Copy the string from the last space to the current space into snum
        // (the number as string)
        char snum[j - from];
        strncpy(snum, line + from, j - from);
        snum[j - from] = '\0';
        from = j + 1;

        // Add the number to the array of numbers
        nums_count++;
        nums = realloc(nums, nums_count * sizeof(int));
        nums[nums_count - 1] = atoi(snum);
      }
    }

    /* The idea is to find the number of operations possible (number of spaces),
     * and using that to create a binary number with specified digits. Iterating
     * through all the binary numbers from 0 to that digit will give all
     * possible 0's and 1's. Considering one as addition (0) and another as
     * multiplication (1), we can bruteforce all possible operations */

    char operations[nums_count - 1];

    // For each possible operation (2^(n-1))
    for (int k = 0; k < (pow(3, nums_count - 1)); k++) {

      int_to_ternary_str(k, nums_count - 1, operations);

      unsigned long verify_sum = nums[0];
      for (int m = 0; m < nums_count - 1; m++) {
        if (operations[m] == '0') {
          verify_sum += nums[m + 1];
        } else if (operations[m] == '1') {
          verify_sum *= nums[m + 1];
        } else if (operations[m] == '2') {
          verify_sum = concat_int(verify_sum, nums[m + 1]);
        }
      }

      if (verify_sum == ans) {
        calibration_result += ans;
        break;
      }
    }
  }

  printf("Calibration Result: %lu\n", calibration_result);

  // Close the file
  fclose(f);

  // printf("END\n");
  return EXIT_SUCCESS;
}
