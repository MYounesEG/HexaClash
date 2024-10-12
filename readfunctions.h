#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "classes.h"

#define lineSize 200

void readKahraman(Takim* team);
void readCanavar(Takim* team);
void readBirim(Takim* team);
void readArastirma_seviyesi(Takim* team);


void readKahraman(Takim* team)
{

    FILE* kahramanFile = fopen("heroes.json","r");
    if(kahramanFile==NULL){
        printf("Failed open %s","heroes.json");
        exit(1);
    }else printf("opened %s secsfuly!\n","heroes.json");

    char line[lineSize]= {0};

    printf("kahraman sayisi : %d\n", team->kahramanSayisi);
    for (int i = 0 ; i < team->kahramanSayisi ; i++)
    {
        gotoInFile(kahramanFile,line,0,team->kahramanlar[i].isim);
        gotoChar(kahramanFile,':');
        getWord_F(kahramanFile,team->kahramanlar[i].bonus_turu);
        gotoInFile(kahramanFile,line,ftell(kahramanFile),"bonus_degeri");
        team->kahramanlar[i].bonus_degeri=getValue(line);
        gotoChar(kahramanFile,':');
        getWord_F(kahramanFile,team->kahramanlar[i].etkilenen);
    }

    for (int i=0;i< team->kahramanSayisi ;i++)//to-do (delete this after debug)
    {
        printf("\nKahraman Name = %s\n",team->kahramanlar[i].isim);
        printf("bonus turu = %s\n",team->kahramanlar[i].bonus_turu);
        printf("deger = %d\n",team->kahramanlar[i].bonus_degeri);
        printf("etkilenen = %s\n",team->kahramanlar[i].etkilenen);

    }
    fclose(kahramanFile);
}

void readCanavar(Takim* team)
{
    FILE* canavarFile = fopen("creatures.json","r");

        if(canavarFile==NULL)    {
        printf("Failed open %s","creatures.json");
        exit(1);
    }


    char line[lineSize]= {0};
    for (int i = 0 ; i < team->kahramanSayisi ; i++)
    {
        gotoInFile(canavarFile,line,0,team->canavarlar[i].isim);
        gotoInFile(canavarFile,line,ftell(canavarFile),"etki_degeri");
        team->canavarlar[i].etki_degeri=getValue(line);

        gotoChar(canavarFile,':');
        getWord_F(canavarFile,team->canavarlar[i].etki_turu);

        gotoChar(canavarFile,':');

        getWord_F(canavarFile,team->canavarlar[i].etkilenen);
    }

    for (int i=0;i< team->canavarSayisi ;i++)//to-do (delete this after debug)
    {
        printf("\ncanvar Name = %s\n",team->canavarlar[i].isim);
        printf("etki turu = %s\n",team->canavarlar[i].etki_turu);
        printf("deger = %d\n",team->canavarlar[i].etki_degeri);
        printf("etkilenen = %s\n",team->canavarlar[i].etkilenen);

    }
    fclose(canavarFile);
}

void readBirim(Takim* team)
{
    FILE* birimFile = fopen("unit_types.json","r");
     if(birimFile==NULL)    {
        printf("Failed open %s","unit_types.json");
        exit(1);
    }
    char line[lineSize]= {0};
    for (int i=0; i<team->birimSayisi; i++)
    {
        gotoInFile(birimFile,line,0,team->birimler[i].isim);
        nextLine(birimFile,line);
        team->birimler[i].saldiri=getValue(line);
        nextLine(birimFile,line);
        team->birimler[i].savunma=getValue(line);
        nextLine(birimFile,line);
        team->birimler[i].saglik=getValue(line);
        nextLine(birimFile,line);
        team->birimler[i].kritik_sans=getValue(line);
    }

    for (int i=0;i< team->birimSayisi ;i++)//to-do (delete this after debug)
    {
        printf("\nbirim Name = %s",team->birimler[i].isim);
        printf("    sayisi = %d\n",team->birimler[i].sayi);
        printf("\nsalidiri= %d\n",team->birimler[i].saldiri);
        printf("\nsavunma= %d\n",team->birimler[i].savunma);
        printf("\nsaglik= %d\n",team->birimler[i].saglik);
        printf("\nkritik_sans= %d\n",team->birimler[i].kritik_sans);
    }

    fclose(birimFile);
}

void readArastirma_seviyesi(Takim* team)
{
    FILE* ArastirmaFile = fopen("research.json","r");

         if(ArastirmaFile==NULL)    {
        printf("Failed open %s","research.json");
        exit(1);
    }

    char ArastirmaSeviyesi[15]= {0};
    char line[lineSize]= {0};

    gotoInFile(ArastirmaFile,line,0,team->arastirma_seviyesi.isim);

    int startIndex = ftell(ArastirmaFile);  //aradigimiz arastima bonusu baslangic indexi


    // senaryodaki arastirma etkileri sevyesine gore research.json dosyasindan ait oldugu seviyeye gore veri cekiyoruz
    sprintf(ArastirmaSeviyesi,"seviye_%d",team->arastirma_seviyesi.seviye);
    //ornegin senaryoda ("savunma_ustaligi": 3) yaziliyorsa , 3 sayiyi cekip "seviye_" ile birlestirerek "seviye_3" yazisi ile "research.json" dosyasindan arastirma etkisinin degerini cekebiliriz
    gotoInFile(ArastirmaFile,line,startIndex,ArastirmaSeviyesi);
    nextLine(ArastirmaFile,line);
    team->arastirma_seviyesi.oran=getValue(line);

    gotoChar(ArastirmaFile,':');

    getWord_F(ArastirmaFile,team->arastirma_seviyesi.etkilenen);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////bunu dusununun//////////////////////////////////////////////////////////////////////////////////


    printf("\narastirma sevyesi name : %s\n",team->arastirma_seviyesi.isim);
    printf("\narastirma sevyesi seviye : %d\n",team->arastirma_seviyesi.seviye);
    printf("\narastirma sevyesi oran : %d\n",team->arastirma_seviyesi.oran);
    printf("\narastirma sevyesi etkilenen : %s\n",team->arastirma_seviyesi.etkilenen);


    fclose(ArastirmaFile);
}
