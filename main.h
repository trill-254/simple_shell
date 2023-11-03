#ifndef MAIN_H
#define MAIN_H

#include <unistd.h>
#include <sys/stat.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

void prompt(void);
char *read_line(void);
int main(void);

#endif /*Main_h*/
