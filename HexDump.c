#include <stdio.h>
#include <stdlib.h>

unsigned char* ReadFile(char* fileName, long fsize)
{
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

int main(int argc, char *argv[]) {
  long fsize = GetFileSize(argv[1]);
  unsigned char *data = ReadFile(argv[1], fsize);

  for (int i = 0; i < fsize; i++)
    printf ("0x%x ", data[i]);
    
  return 0;
}