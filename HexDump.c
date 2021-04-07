#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* version = "1.4";

// Loads the bytes from a file.
void DumpToConsole(unsigned char *fileName) {
  FILE *f = fopen(fileName, "rb");
  fseek(f, 0, SEEK_END);
  unsigned int fsize = ftell(f);
  fseek(f, 0, SEEK_SET);
  unsigned char *data = malloc(fsize + 1);
  fread(data, 1, fsize, f);
  fclose(f);
  data[fsize] = 0;

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

  free(data);
}

// Loads the bytes from a file.
void DumpToFile(unsigned char *fileName, unsigned char *destination) {
  FILE *f = fopen(fileName, "rb");
  fseek(f, 0, SEEK_END);
  unsigned int fsize = ftell(f);
  fseek(f, 0, SEEK_SET);
  unsigned char *data = malloc(fsize + 1);
  fread(data, 1, fsize, f);
  fclose(f);
  data[fsize] = 0;

  fopen(destination, "w");
  char ascii[17];
  ascii[16] = 0;
  unsigned int i;

  for (i = 0; i < fsize; i++) {
    if (i%16 == 0)
      fprintf(f, "%08x ", i);
    ascii[i % 16] = data[i] >= ' ' && data[i] <= '~' ? data[i] : '.';
    fprintf (f, "%02x ", data[i]);
    if (i%16 == 15)
      fprintf(f, "%s\n", ascii);
  }
  for (i = fsize%16; i < 16; i++) {
    ascii[i % 16] = ' ';
    fprintf (f, "   ");
    if (i == 15)
      fprintf(f, "%s\n", ascii);
  }
  printf("Hex dumped to: %s\n", destination);
  fclose(f);

  free(data);
}

// Returns 1 if the file exists and 0 if not.
int FileExists(unsigned char *fileName)
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
  printf("Files come in pairs [Source] [Destination], where the data from source is hex dumped into destination.\n");
  printf("Command-line options:\n");
  printf("   -v, --version       print version information\n");
  printf("   -h, --help          print usage information\n");
}

// Returns the integer corresponding to a command.
int GetCommand(unsigned char *arg) {
  int command = 0;

  if (strcmp(arg, "-v") == 0 || strcmp(arg, "--version") == 0)
    command = 1;
  else if (strcmp(arg, "-h") == 0 || strcmp(arg, "--help") == 0)
    command = 2;

  return command;
}

int main(int argc, char *argv[]) {
  if (argc > 1) {
    for (int i = 1; i < argc; i++) {
      int command = GetCommand(argv[i]);
      switch (command)
      {
        case 1:
          printf("Version: %s\n", version);
          break;

        case 2:
          PrintHelp();
          break;
      
        default:
          if (FileExists(argv[i]) == 1) {
            if (i < argc -1 && GetCommand(argv[i+1]) == 0)
            {
              DumpToFile(argv[i], argv[i+1]);
              i++;
            }
            else
              DumpToConsole(argv[i]);
          }
          else {
            printf("Couldnt' find file: %s\n", argv[i]);
          }
          break;
      }
    }
  }
  else {
    printf("No arguments found. Use -h or --help to list commands.\n");
  }

  return 0;
}