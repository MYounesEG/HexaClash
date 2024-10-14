#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "classes.h"
#include "functions.h"

int main()
{
    int SenarioNumber;

    char senaryoFile[10] = {0};

    printf("Enter Nerario number : ");
    scanf("%d",&SenarioNumber);

    downloadFile(SenarioNumber,senaryoFile);

    Takim insan_imparatorlugu = {"insan_imparatorlugu"};

    Takim ork_legi = {"ork_legi"};

    readTakim(&insan_imparatorlugu,senaryoFile);
    printf("\n\n\n\n\n\n\n----------------------------------------------------------------------------\n\n\n\n\n\n\n");
    readTakim(&ork_legi,senaryoFile);


/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**/FIGHT(insan_imparatorlugu,ork_legi);/**//**//**//**//**//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/


    deleteFile(senaryoFile);


    return 0;
}
