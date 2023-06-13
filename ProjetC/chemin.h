#ifndef CHEMIN_H
#define CHEMIN_H

#include "util.h"


//operations sur les chemins
extern noeud *goTo(noeud *src, set *id);
extern noeud *goTo_bis(noeud *src, set *id);
extern set *get_Chemin_Absolu(noeud *n);
extern bool isAbsolute(char *s);
extern bool isParent(noeud *n1, noeud *n2);
#endif
