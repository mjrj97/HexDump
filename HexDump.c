#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* version = "1.0";

unsigned char* ReadFile(char* fileName, long fsize) {
  FILE *f = fopen(fileName, "rb");
  unsigned char *data = malloc(fsize + 1);
  fread(data, 1, fsize, f);
  fclose(f);

  data[fsize] = 0;
  return data;
}

long GetFileSize(char* fileName) {
  FILE *f = fopen(fileName, "rb");
  fseek(f, 0, SEEK_END);
  long fsize = ftell(f);
  fseek(f, 0, SEEK_SET);
  fclose(f);
  return fsize;
}

void PrintVersion() {
  printf("Version: ");
  printf(version);
  printf("\n");
}

void PrintHelp() {
  printf("Command-line options:\n");
  printf("   -v, --version       print version information\n");
  printf("   -h, --help          print usage information\n");
}

int main(int argc, char *argv[]) {
  if (argc > 1) {
    for (int i = 1; i < argc; i++) {
      if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0){
        PrintVersion();
      }
      else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0){
        PrintHelp();
      }
      else {
        printf("Unrecognized argument: ");
        printf(argv[i]);
        printf("\n");
      }
    }
  }
  else {
    printf("No arguments found. Use -h or --help to list commands.\n");
  }

  /*long fsize = GetFileSize(argv[1]);
  unsigned char *data = ReadFile(argv[1], fsize);

  for (int i = 0; i < fsize; i++)
    printf ("0x%x ", data[i]);
    */
  return 0;
}