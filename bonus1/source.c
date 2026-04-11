#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
  char buffer[40];
  int val;
  
  val = atoi(argv[1]);
  if (val < 10) {
    memcpy(buffer, argv[2], val * 4);
    if (val == 0x574f4c46) //1464814662
      execl("/bin/sh", "sh", 0);
    return 0;
  }
  return 1;
}
