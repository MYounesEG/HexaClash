#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "classes.h"
#include "functions.h"
#include "gameInterface.h"

int main()
{
    int SenarioNumber;

    char senaryoFile[10] = {0};

    printf("Enter Serario number : ");
    scanf("%d",&SenarioNumber);

    downloadFile(SenarioNumber,senaryoFile);

    Takim insan_imparatorlugu = {"insan_imparatorlugu"};

    Takim ork_legi = {"ork_legi"};

    readTakim(&insan_imparatorlugu,senaryoFile);
    printf("\n\n\n\n\n\n\n----------------------------------------------------------------------------\n\n\n\n\n\n\n");
    readTakim(&ork_legi,senaryoFile);


    printf("SHOWING THE GRAFIK !\n");
    printf("SHOWING THE GRAFIK !\n");
    printf("SHOWING THE GRAFIK !\n");
    printf("SHOWING THE GRAFIK !\n");
    grafik(insan_imparatorlugu,ork_legi);


/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**///FIGHT(insan_imparatorlugu,ork_legi);/**//**//**//**//**//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

    //grafik(insan_imparatorlugu,ork_legi);
    deleteFile(senaryoFile);


    return 0;
}
