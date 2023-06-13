#ifndef PROJET_H
#define PROJET_H

#include "chemin.h"

extern int ligne;

extern void ls(set *id);
extern void cd(set *id);
extern void pwd(set *id);
extern void create(set *id, bool doss);
extern void rm(set *id);
extern void cp(set *id);
extern void mv(set *id);
extern void print(set *id);

#endif