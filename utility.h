#ifndef UTILITY_HEADER_H
#define UTILITY_HEADER_H

/* 
 *
 * utility.h: The header file of functions such as reading files in a directory
 * Author: Kan Ouivirach
 * Credit: http://en.wikipedia.org/wiki/Dirent.h
 *
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

using namespace std;

char *dup_str(const char *s);
char **get_all_files(const char *path);

#endif
