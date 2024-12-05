#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 4096
#define MAX_MATCHES 1000

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

  regex_t pattern;
  // Compile the regex pattern
  if (regcomp(&pattern, "mul\\([0-9]+,[0-9]+\\)|don't\\(\\)|do\\(\\)",
              REG_EXTENDED)) {
    fprintf(stderr, "Could not compile regex\n");
    return 1;
  }

  regex_t comma;
  if (regcomp(&comma, ",", REG_EXTENDED)) {
    fprintf(stderr, "Could not compile regex\n");
    return 1;
  }

  int sum = 0;
  int enabled = 1;

  // Process each line
  for (int i = 0; i < lines; i++) {
    char str[MAX_LINE];
    regmatch_t matches[1]; // Array to store the matches
    // Read 1 line from the file
    fgets(str, sizeof(str), listf);

    // Pointer to the start of the string
    const char *p = str;

    // Execute the regex pattern on the string
    while ((regexec(&pattern, p, 1, matches, 0)) == 0) {
      int start = matches[0].rm_so;
      int finish = matches[0].rm_eo;

      printf("Match start: %d; ", start);
      printf("Match finish: %d\n", finish);
      // Extract the single match from the string
      char match[finish - start + 1];
      strncpy(match, p + start, finish - start);
      match[finish - start] = '\0';

      printf("Match: %s\n", match);
      if (strncmp(match, "don't()", 7) == 0) {
        enabled = 0;
      } else if (strncmp(match, "do()", 4) == 0) {
        enabled = 1;
      }

      if (enabled == 1) {

        // Find the comma in the match
        regmatch_t comma_index[1];
        int comma_match_count = regexec(&comma, match, 1, comma_index, 0);

        // Create two strings to hold the numbers
        char cnum1[comma_index[0].rm_so - 4];
        char cnum2[sizeof(match) - comma_index[0].rm_so - 3];

        // Copy the substrings (matches) to the new strings
        strncpy(cnum1, match + 4, comma_index[0].rm_so - 4);
        strncpy(cnum2, match + comma_index[0].rm_so + 1,
                sizeof(match) - comma_index[0].rm_so - 3);
        // Null-terminate the strings
        cnum1[comma_index[0].rm_so - 4] = '\0';
        cnum2[sizeof(match) - comma_index[0].rm_so - 3] = '\0';

        // Convert the strings to integers

        int num1 = atoi(cnum1);
        int num2 = atoi(cnum2);

        sum += num1 * num2;
      }

      // Move the pointer to the end of the current match
      p += finish;
    }
  }

  // Free the compiled regex pattern
  regfree(&pattern);
  regfree(&comma);

  // Close file
  fclose(listf);

  printf("Sum from corrupted memory: %d\n", sum);

  return EXIT_SUCCESS;
}
