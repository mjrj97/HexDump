#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* version = "1.1";

// Reads the file a the specified location and size.
unsigned char* ReadFile(const char* fileName, long fsize) {
  FILE *f = fopen(fileName, "rb");
  unsigned char *data = malloc(fsize + 1);
  fread(data, 1, fsize, f);
  fclose(f);

  data[fsize] = 0;
  return data;
}

// Returns the size of the file in bytes.
long GetFileSize(const char* fileName) {
  FILE *f = fopen(fileName, "rb");
  fseek(f, 0, SEEK_END);
  long fsize = ftell(f);
  fseek(f, 0, SEEK_SET);
  fclose(f);
  return fsize;
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

// Prints the version of the program.
void PrintVersion() {
  printf("Version: ");
  printf(version);
  printf("\n");
}

// Prints the possible command-line options.
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
        if (FileExists(argv[i]) == 1) {
          long fsize = GetFileSize(argv[1]);
          unsigned char *data = ReadFile(argv[1], fsize);

          /*for (int i = 0; i < fsize; i++)
            printf ("0x%x ", data[i]);*/

          char ascii[17];
          ascii[16] = "\0";

          for (int i = 0; i < fsize; i++) {
            if (i%16 == 0 && i != 0)
            {
              printf(ascii);
              printf("\n");
            }
            if (i%16 == 0)
            {
              printf("%08x ", i);
            }
            printf ("%02x ", data[i]);
            if (((unsigned char*)data)[i] >= ' ' && ((unsigned char*)data)[i] <= '~') {
			        ascii[i % 16] = ((unsigned char*)data)[i];
		        } else {
			        ascii[i % 16] = '.';
		        }
          }

          free(data);
        }
        else {
          printf("Couldnt' find file: ");
          printf(argv[i]);
          printf("\n");
        }
      }
    }
  }
  else {
    printf("No arguments found. Use -h or --help to list commands.\n");
  }

  return 0;
}