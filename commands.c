//
//  commands.c
//  commands
//
//  Created by William McCarthy on 103//20.
//  Copyright © 2020 William McCarthy. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXLINE 1000
#define ARGC_ERROR 1
#define FILE_ERROR 2


void echo_commands(int argc, const char* argv[]) {
  while (--argc > 0) {
    printf("%s%s", *++argv, (argc > 1) ? " " : "");
  }
  printf("\n\n");
}

size_t getline_(FILE* fin, char* s, int lim) {
  char* p = s;
  int c = 0;
  while (--lim && (c=fgetc(fin)) != EOF && c != '\n') {
    *s++ = c;
  }
  if (c == '\n') { *s++ = c; }
  *s = '\0';

  return s - p;
}

void process_commands(int argc, const char* argv[]) {
  char line[MAXLINE];
  long lineno = 0;
  int c, found = 0;
  bool except = false, number_lines = false, extra_arg = false;
  FILE* fin = NULL;

  if (argc < 3) {
    fprintf(stderr, "Uaage: ./find -f filename -x -n pattern\n");
    exit(ARGC_ERROR);
  }

  while (--argc > 0 & (*++argv)[0] == '-') {
    extra_arg = false;
    while (!extra_arg && (c = *++argv[0]) != '\0') {
      switch(c) {
      case 'f':
        ++argv;
        --argc;
        if ((fin = fopen(argv[0], "r")) <= 0) {   // increment argv, get filename
          fprintf(stderr, "Could not open file: '%s'\n", argv[0]);
        }
        extra_arg = true;
        break;    // break switch, will also break inner while due to finding char
      case 'x':  except = true;  break;           // turn on DON'T find given pattern
      case 'n':  number_lines = true;  break;     // turn on line numbering
      default: printf("find: illegal option %c\n", c); argc = 0; found = -1; break;
      }
    }
  }

  if (argc != 1) { printf("no pattern specified\n");
  } else {
    while (getline_(fin, line, MAXLINE) > 0) {
      lineno++;
      bool found_it = strstr(line, *argv) != NULL;
      if ((!found_it && except) || (found_it && !except)) {
        if (number_lines) {
          printf("%ld: ", lineno);
        }
        printf("%s", line);
        found++;
      }
    }
  }
  fclose(fin);
  printf("\n");
}

int main(int argc, const char * argv[]) {
  echo_commands(argc, argv);

  process_commands(argc, argv);

  return 0;
}
