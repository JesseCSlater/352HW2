#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

char buf[512];

/**
 * 
 * @author
 * John Mindrup
 * @brief
 * Added functionality to count the number of vowels in the buffer
 * Added a function which detects if a character is a vowel
 * I recall hearing that function calls are slow but a 10 case if statement with ||s seemed gross
 * 
 * @param c 
 * @return int 
 */
int isVowel(char c)
{
  switch(c)
  {
    case 'a':
    case 'A':
    case 'e':
    case 'E':
    case 'i':
    case 'I':
    case 'o':
    case 'O':
    case 'u':
    case 'U':
    return 1;
    default:
    return 0;
  }
}

void
wc(int fd, char *name)
{
  int i, n;
  int l, w, c, inword, v;

  l = w = c = v = 0;
  inword = 0;
  while((n = read(fd, buf, sizeof(buf))) > 0){
    for(i=0; i<n; i++){
      c++;
      if(buf[i] == '\n')
        l++;
      if (isVowel(buf[i]))
        v++;
      if(strchr(" \r\t\n\v", buf[i]))
        inword = 0;
      else if(!inword){
        w++;
        inword = 1;
      }
    }
  }
  if(n < 0){
    printf("wc: read error\n");
    exit(1);
  }
  printf("%d %d %d %d %s\n", l, w, c, v, name);
}

int
main(int argc, char *argv[])
{
  int fd, i;

  if(argc <= 1){
    wc(0, "");
    exit(0);
  }

  for(i = 1; i < argc; i++){
    if((fd = open(argv[i], 0)) < 0){
      printf("wc: cannot open %s\n", argv[i]);
      exit(1);
    }
    wc(fd, argv[i]);
    close(fd);
  }
  exit(0);
}
