#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "classes.h"
#include "functions.h"

int main(){
    char senaryoFile[] = "1.json";

    Takim insan_imparatorlugu = {"insan_imparatorlugu"};
    Takim ork_legi = {"ork_legi"};

    readTakim(&insan_imparatorlugu,senaryoFile);
    readTakim(&ork_legi,senaryoFile);



    return 0;
}
