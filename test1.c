#include <stdio.h>
#include <string.h>

char *findArgument(int argc, char *argv[], char *target) {
  for (int i = 0; i < argc; i++) {
    if (strcmp(argv[i], target) == 0) {
      if (i + 1 < argc) {
        return argv[i + 1];
      } else {
        return "";
      }
    }
  }
  return "";
}

int main(int argc, char *argv[]) {
  char *target = "--filename";
  char *filename = findArgument(argc, argv, target);
  if (strlen(filename) > 0) {
    printf("Filename: %s\n", filename);
  } else {
    printf("Filename not found\n");
  }
  return 0;
}
