#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include "classes.h"
#include "functions.h"
#include "gameInterface.h"
#include "fightFunction.h"

int main()
{
    int SenarioNumber=5;
    char senaryoFile[10] = "5.json";
    char sentence[]="Please Enter a Senario number : ";
    for (int i=0;i<strlen(sentence);i++)
    {
        system("cls");
        for(int j=0;j<i+1;j++)
            printf("%c",sentence[j]);
        Sleep(0.2);
    }


//    scanf("%d",&SenarioNumber);

   // downloadFile(SenarioNumber,senaryoFile);

    Takim insan_imparatorlugu = {"insan_imparatorlugu"};

    Takim ork_legi = {"ork_legi"};

    readTakim(&insan_imparatorlugu,senaryoFile);
    printf("\n\n\n\n\n\n\n----------------------------------------------------------------------------\n\n\n\n\n\n\n");
    readTakim(&ork_legi,senaryoFile);


    grafik(insan_imparatorlugu,ork_legi);


/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**/FIGHT(&insan_imparatorlugu,&ork_legi);/**//**//**//**//**//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

    grafik(insan_imparatorlugu,ork_legi);
  //  deleteFile(senaryoFile);


    return 0;
}
