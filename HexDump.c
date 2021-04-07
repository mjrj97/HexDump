#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const char* version = "1.3";

//Prints the data as a hex dump in console.
void PrintDump(unsigned char *data, int fsize) {
  char ascii[17];
  ascii[16] = 0;
  unsigned int i;

  for (i = 0; i < fsize; i++) {
    if (i%16 == 0)
      printf("%08x ", i);
    ascii[i % 16] = data[i] >= ' ' && data[i] <= '~' ? data[i] : '.';
    printf ("%02x ", data[i]);
    if (i%16 == 15)
      printf("%s\n", ascii);
  }
  for (i = fsize%16; i < 16; i++) {
    ascii[i % 16] = ' ';
    printf ("   ");
    if (i == 15)
      printf("%s\n", ascii);
  }
}

//Loads the bytes from a file.
void LoadData(const char *fileName) {
  FILE *f = fopen(fileName, "rb");
  fseek(f, 0, SEEK_END);
  unsigned int fsize = ftell(f);
  fseek(f, 0, SEEK_SET);
  unsigned char *data = malloc(fsize + 1);
  fread(data, 1, fsize, f);
  fclose(f);
  data[fsize] = 0;

  PrintDump(data, fsize);

  free(data);
}

// Returns 1 if the file exists and 0 if not.
int FileExists(const char *fileName)
{
    FILE *file;
    if ((file = fopen(fileName, "r")))
    {
        fclose(file);
        return 1;
    }
    return 0;
}

// Prints the possible command-line options.
void PrintHelp() {
  printf("Command-line options:\n");
  printf("   -v, --version       print version information\n");
  printf("   -h, --help          print usage information\n");
}

int main(int argc, char *argv[]) {
  clock_t begin = clock();

  if (argc > 1) {
    for (int i = 1; i < argc; i++) {
      if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0){
        printf("Version: %s\n", version);
      }
      else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0){
        PrintHelp();
      }
      else {
        if (FileExists(argv[i]) == 1) {
          LoadData(argv[i]);
        }
        else {
          printf("Couldnt' find file: %s\n", argv[i]);
        }
      }
    }
  }
  else {
    printf("No arguments found. Use -h or --help to list commands.\n");
  }

  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Time: %lf s", time_spent);

  return 0;
}