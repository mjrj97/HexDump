#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* version = "1.5";
const char hex[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
unsigned int fsize = 0;

// Generates hex dump as string ending with \0.
unsigned char* GenerateDump(unsigned char *data) {
  int i, j, rows = fsize/16;
  if (fsize%16 != 0)
    rows++;
  printf("%u\n", fsize);
  printf("%u\n", rows);
  unsigned char *dump = malloc(73*rows);
  for (i = 0; i < rows; i++) {
    int offset = i*73;
    
    char address[8];
    sprintf(address, "%08x", i*16);
    for (j = 0; j < 8; j++) {
      dump[offset + j] = address[j];
    }

    dump[i*73+8] = ' ';
    for (j = 0; j < 16; j++) {
      if (i*16+j < fsize) {
        unsigned char d = data[i*16+j];
        dump[offset+j*3+9] = hex[d/16];
        dump[offset+j*3+10] = hex[d%16];
        dump[offset+j*3+11] = ' ';
        dump[offset+57+j] = d >= ' ' && d <= '~' ? d : '.';
      } else {
        dump[offset+j*3+9] = ' ';
        dump[offset+j*3+10] = ' ';
        dump[offset+j*3+11] = ' ';
        dump[offset+57+j] = ' ';
      }
    }

    if (i != 0)
      dump[offset-1] = '\n';
  }
  dump[73*rows-1] = 0;
  return dump;
}

// Loads the bytes from a file.
unsigned char* LoadFile(unsigned char *fileName) {
  FILE *f = fopen(fileName, "rb");
  fseek(f, 0, SEEK_END);
  fsize = ftell(f);
  fseek(f, 0, SEEK_SET);
  unsigned char *data = malloc(fsize);
  fread(data, 1, fsize, f);
  fclose(f);
  return data;
}

// Hex dumps the file to the console.
void DumpToConsole(unsigned char *fileName) {
  unsigned char *data = LoadFile(fileName);
  printf("%s", GenerateDump(data));
  free(data);
}

// Hex dumps the file to another file.
void DumpToFile(unsigned char *fileName, unsigned char *destination) {
  unsigned char *data = LoadFile(fileName);
  FILE *f = fopen(destination, "w");
  fprintf(f, "%s", GenerateDump(data));
  fclose(f);
  free(data);
}

// Returns 1 if the file exists and 0 if not.
int FileExists(unsigned char *fileName) {
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
  if (strcmp(arg, "-v") == 0 || strcmp(arg, "--version") == 0)
    return 1;
  else if (strcmp(arg, "-h") == 0 || strcmp(arg, "--help") == 0)
    return 2;
  else
    return 0;
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