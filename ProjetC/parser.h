#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

struct set{
    int nb;
    char **mots;
};
typedef struct set set;
extern int nbr_word(char *s,char separator);
extern int word_len(char *s,char separator);
extern char *extract_word(char *w,char separator, int *pl);
extern char *next_word(char *w,char separator);
extern set *make_set(char *s,char separator);
extern void print_set(set *id);
extern void free_set(set *id);
#endif

