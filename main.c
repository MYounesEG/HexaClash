#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <unistd.h>
#include "classes.h"
#include "functions.h"
#include "gameInterface.h"
#include "fightFunction.h"

int main()
{
    int SenarioNumber;
    char senaryoFile[20] = "test.json";

    welcome();

    scanf("%d",&SenarioNumber);


   if(SenarioNumber) downloadFile(SenarioNumber,senaryoFile);


    Takim insan_imparatorlugu = {"insan_imparatorlugu"};

    Takim ork_legi = {"ork_legi"};

    readTakim(&insan_imparatorlugu,senaryoFile);
    printf("\n\n\n\n\n\n\n----------------------------------------------------------------------------\n\n\n\n\n\n\n");
    readTakim(&ork_legi,senaryoFile);


    renderInterface(insan_imparatorlugu,ork_legi);


    /**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
    /**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
    /**/FIGHT(&insan_imparatorlugu, &ork_legi) ;/**//**//**//**//**/
    /**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
    /**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

    renderInterface(insan_imparatorlugu,ork_legi);


    if(SenarioNumber) deleteFile(senaryoFile);


    return 0;
}
