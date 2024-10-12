#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "classes.h"
#include "readfunctions.h"

#define lineSize 200


bool in(char str1[],char str2[]);
void kok(char kelime[]);
int getValue(char line[]);
void gotoLine(FILE*f,char line[],int start,char order[]);
void  gotoChar(FILE*f,char order);
void nextLine(FILE *f,char line[]);
void readTakim(Takim* team,char fileName[]);


bool in(char str1[],char str2[])
{
    if(strstr(str1,str2)!=NULL)
        return true;
    return false;

}

//rt
void kok(char kelime[])
{
    // kelimenin kokunu bulmak


    char words[][30]=
    {
        "tum",
        "piyade",
        "okcu",
        "suvari",
        "kusatma_makine",
        "ork_dovuscu",
        "mizrakci",
        "varg_binici",
        "trol",
        "Alparslan",
        "Fatih_Sultan_Mehmet",
        "Mete_Han",
        "Yavuz_Sultan_Selim",
        "Tugrul_Bey",
        "Goruk_Vahsi",
        "Thruk_Kemikkiran",
        "Vrog_Kafakiran",
        "Ugar_Zalim",
        "Ejderha",
        "Agri_Dagi_Devleri",
        "Tepegoz",
        "Samur",
        "Kara_Troll",
        "Golge_Kurtlari",
        "Camur_Devleri",
        "Ates_Iblisi",
        "Makrog_Savas_Beyi",
        "Buz_Devleri",
        "savunma",
        "saldiri",
        "kritik"
    };


    printf("\nkok(%s)\n\n",kelime);
    kelime[0]=tolower(kelime[0]);
    for (int i = 0; i < sizeof(words) / sizeof(words[0]); i++)
    {
        if (strstr(kelime, words[i]))
        {
            strcpy(kelime, words[i]);  // kelimeyi sadece eşleşen kısım ile değiştir
            return ;
        }
    }
}

int getValue(char line[])
{
    for (int i=0; i<strlen(line); i++)
        if(isdigit(line[i]))
            return atoi(line+i);
}

void nextLine(FILE *f,char line[])
{
    fgets(line,lineSize,f);
}
void gotoChar(FILE*f,char order)
{
    fgetc(f);
    while(fgetc(f)!=order);

    /*

    char karakter;

    karakter = fgetc(f);

    while(karakter!=order)
        karakter = fgetc(f);

    return;

    */
}

void gotoInFile(FILE*f,char line[],int start,char order[])
{
    fseek(f,start,SEEK_SET);

    do
    {

        nextLine(f,line);
    }
    while(!in(line,order));
}


void readTakim(Takim* team,char fileName[])
{

    FILE* f=fopen(fileName,"r");
    char* part;

    char line [lineSize]= {0};

    if (f==NULL)
    {
        printf("Failed open %s",fileName);
        exit(1);
    }


    gotoInFile(f,line,0,team->TakimName);


    int startIndex = ftell(f);

    {
        //birimler

        gotoInFile(f,line,startIndex,"birimler");
        nextLine(f,line);

        team->birimSayisi = 0;
        do
        {
            sscanf(line,"%s",team->birimler[team->birimSayisi].isim);

            kok(team->birimler[team->birimSayisi].isim);
            team->birimler[team->birimSayisi].sayi=getValue(line);
            team->birimSayisi++;
            nextLine(f,line);
////next line
        }
        while(!in(line,"}"));  // stop when find the end of birimler block


        readBirim(team);//kutucuk
    }

    {
        //kahramanlar

        gotoInFile(f,line,startIndex,"kahramanlar");

        team->kahramanSayisi = 0;


        for(  part = strstr(line,"[") ; part!=NULL ; part = strstr(part+1," \""))
        {
            sscanf(part,"%s",team->kahramanlar[team->kahramanSayisi].isim);
            kok(team->kahramanlar[team->kahramanSayisi++].isim);
        }

        readKahraman(team);

        printf("kahrman sayisi = %d\n",team->kahramanSayisi);
        for(int i=0; i<team->kahramanSayisi; i++)
        {
            printf("%s--\n",team->kahramanlar[i].isim);
            printf("%s--\n",team->kahramanlar[i].bonus_turu);
            printf("%d--\n",team->kahramanlar[i].bonus_degeri);
            printf("%s--\n",team->kahramanlar[i].etkilenen);
        }
    }

    fseek(f,startIndex,SEEK_SET);

    {
        //canavarlar

        gotoInFile(f,line,startIndex,"canavarlar");

        team->canavarSayisi = 0;
        //char* part; // daha onceden tanimlandi

        for(  part = strstr(line,"[") ; part!=NULL ; part = strstr(part+1," \""))
        {
            sscanf(part,"%s",team->canavarlar[team->canavarSayisi].isim);
            kok(team->canavarlar[team->canavarSayisi].isim);
            team->canavarSayisi++;

        }
        readCanavar(team);
    }

    fseek(f,startIndex,SEEK_SET);

    {
        //arastirma sevyesi

        gotoInFile(f,line,startIndex,"arastirma_seviyesi");

        nextLine(f,line);

        kok(team->arastirma_seviyesi.isim);
        team->arastirma_seviyesi.seviye=getValue(line);
        readArastirma_seviyesi(team);
    }

    fclose(f);
}
