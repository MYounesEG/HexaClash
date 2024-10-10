#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//define like this
//readKahraman(Takim* team);


bool in(char str1[],char str2[]);
void kok(char kelime[]);
int getValue(char line[]);
void gotoInFile(FILE*f,char line[],int start,char order[]);
void readTakim(Takim* team,char fileName[]);


bool in(char str1[],char str2[])
{
    if(strstr(str1,str2)!=NULL)
        return true;
    return false;

}

void kok(char kelime[]){ // kelimenin kokunu bulmak
    char words[][20]={
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
        "savunma",
        "saldiri"};


        kelime[0]=tolower(kelime[0]);
        for (int i=0;i<sizeof(words)/20;i++)
            if(strstr(kelime,words[i]))
                strcpy(kelime,words[i]);

    }

int getValue(char line[]){
    for (int i=0;i<strlen(line);i++)
        if(isdigit(line[i]))
            return atoi(line+i);
}



void gotoInFile(FILE*f,char line[],int start,char order[]){

    fseek(f,start,SEEK_SET);
    do{
        fgets(line,sizeof(200),f);
    }while(!in(line,order));

}

void readTakim(Takim* team,char fileName[]){
    FILE* f ;
    char* part;

    char line [200]={0};

    if (f=fopen(fileName,"r"))
    {
        printf("Failed open %s",fileName);
        exit(1);
    }

    gotoInFile(f,line,0,team->TakimName);



    int startIndex = ftell(f);

    {//birimler

        gotoInFile(f,line,startIndex,"birimler");

        team.birimSayisi = 0;
        do{
            fgets(line,sizeof(200),f);
            sscanf(line,"%s" ,team->birimler[0].isim);
            kok(team->birimler[team.birimSayisi].isim);
            team->birimler[team.birimSayisi].sayi=getValue(line);
            team.birimSayisi++;

        }while(!in(line,"}")); // stop when find the end of birimler block


        readBirim(team);
    }

    {//kahramanlar

        gotoInFile(f,line,startIndex,"kahramanlar");

        team.kahramanSayisi = 0;


        for(  part = strstr(line,"\"") ; part!=NULL ; part = strstr(part+1,"\"") , team.kahramanSayisi++){
            scanf(part,"%s",team->kahramanlar[team.kahramanSayisi].isim);
            kok(team->kahramanlar[team.kahramanSayisi].isim);

        }
        readKahraman(team);
    }

    fseek(f,startIndex,SEEK_SET);

    {//canavarlar

        gotoInFile(f,line,startIndex,"canavarlar");

        team.canavarSayisi = 0;
        //char* part; // daha onceden tanimlandi

        for(  part = strstr(line,"\"") ; part!=NULL ; part = strstr(part+1,"\"") , team.canavarSayisi++){
            scanf(part,"%s",team->canavarlar[team.canavarSayisi].isim);
            kok(team->canavarlar[team.canavarSayisi].isim);

        }
        readCanavar(team);
    }

    fseek(f,startIndex,SEEK_SET);
    {//arastirma sevyesi

        gotoInFile(f,line,startIndex,"arastirma_seviyesi");


        fgets(line,sizeof(200),f);

        sscanf(line,"%s",team->arastirma_seviyesi.isim);
        kok(team->arastirma_seviyesi.isim);
        team->arastirma_seviyesi.seviye=getValue(line);
        readArastirma_seviyesi(team);
    }

    fclose(f);
}
