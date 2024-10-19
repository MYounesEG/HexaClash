#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "classes.h"


//Aradgimiz deger icinde var mi
bool isIn(char string1[], char string2[])
{
    if(strstr(string1,string2)!= NULL)
        return false;
    else return true;
}


int checkWiner(Takim insanImparatorlugu, Takim OrkLegi)
{
    int totalUnitInsan = 0;
    int totalUnitOrk = 0;
    for(int i=0; i<insanImparatorlugu.birimSayisi ; i++)
        totalUnitInsan += insanImparatorlugu.birimler[i].sayi;
    for(int i=0; i<OrkLegi.birimSayisi ; i++)
        totalUnitOrk += OrkLegi.birimler[i].sayi;

    if(totalUnitInsan==0)
        return 2;
    else if(totalUnitOrk==0)
        return 1;
    else
        return 0;

}


void UpdateCriticChance(Takim* insanImparatorlugu,Takim* OrcLejyonu)
{
     //Ork Legi kritik vurus etkisi
    for(int i=0; i<OrcLejyonu->birimSayisi; i++)//
    {
         float oldCritic= OrcLejyonu->birimler[i].kritik_sans;

         //Ork Legi kahramanin kritik vurusa etkisi
        if(isIn(OrcLejyonu->kahramanlar->etkilenen,OrcLejyonu->birimler[i].isim) && isIn(OrcLejyonu->kahramanlar->bonus_turu," kritik") ){
            OrcLejyonu->birimler[i].kritik_sans = OrcLejyonu->birimler[i].kritik_sans*(100+OrcLejyonu->kahramanlar->bonus_degeri)/100.0;
            printf("Ork Legi kahraman etkisinin kritik vurusa etkisi\n");
            printf("%s:%.1f *1.%d(bonus degeri) = %.1f yeni kritik vurus \n",OrcLejyonu->birimler[i].isim,oldCritic,OrcLejyonu->kahramanlar->bonus_degeri,OrcLejyonu->birimler[i].kritik_sans);
             printf("\n");
        }

        //Ork Legi canavarın kritik vurusa etkisi
        if(isIn(OrcLejyonu->canavarlar->etkilenen,OrcLejyonu->birimler[i].isim) && isIn(OrcLejyonu->canavarlar->etki_turu," kritik") ){
            OrcLejyonu->birimler[i].kritik_sans = OrcLejyonu->birimler[i].kritik_sans*(100+OrcLejyonu->canavarlar->etki_degeri)/100.0;
            printf("Ork Legi canavar etkisinin kritik vurusa etkisi\n");
            printf("%s: %.1f *1.%d(bonus degeri)=%.1f yeni kritik vurus  \n",OrcLejyonu->birimler[i].isim,oldCritic,OrcLejyonu->canavarlar->etki_degeri,OrcLejyonu->birimler[i].kritik_sans);
             printf("\n");
        }

        //Ork Legi elit egitimin  vurusa etkisi
        if(isIn(OrcLejyonu->arastirma_seviyesi.isim,"elit_egitim"))
        {
            OrcLejyonu->birimler[i].kritik_sans = OrcLejyonu->birimler[i].kritik_sans*(100+OrcLejyonu->arastirma_seviyesi.oran)/100.0;
            printf("Ork Legi elit egitimin kritik vurusa  etkisi\n");
            printf("%s: %.1f *1.%d(bonus degeri) = %.1f yeni kritik vurus \n",OrcLejyonu->birimler[i].isim,oldCritic,OrcLejyonu->arastirma_seviyesi.oran,OrcLejyonu->birimler[i].kritik_sans);
             printf("\n");

        }
    }
     //insan imparatorlugu kritik vurus etkisi
    for(int i=0; i<insanImparatorlugu->birimSayisi; i++)//
    {
        float oldCritic = insanImparatorlugu->birimler[i].kritik_sans;

        //insan imparatorlugunun kahramanin kritik vurusa etkisi
        if(isIn(insanImparatorlugu->kahramanlar->etkilenen,insanImparatorlugu->birimler[i].isim),isIn(insanImparatorlugu->kahramanlar->bonus_turu,"kritik")) {
            insanImparatorlugu->birimler[i].kritik_sans = insanImparatorlugu->birimler[i].kritik_sans*(100+insanImparatorlugu->kahramanlar->bonus_degeri)/100.0;
            printf("insan impartorlugu kahraman etkisinin kritik vurusa etkisi\n");
            printf("%s: %.1f *1.%d(bonus degeri) = %.1f yeni kritik vurus  \n",insanImparatorlugu->birimler[i].isim,oldCritic,insanImparatorlugu->kahramanlar->bonus_degeri,insanImparatorlugu->birimler[i].kritik_sans);
             printf("\n");

        }
        //insan imparatorlugunun canavarın kritik vurusa etkisi
        if(isIn(insanImparatorlugu->canavarlar->etkilenen,insanImparatorlugu->birimler[i].isim) && isIn(insanImparatorlugu->canavarlar->etki_turu,"kritik") ){
            insanImparatorlugu->birimler[i].kritik_sans = insanImparatorlugu->birimler[i].kritik_sans*(100+insanImparatorlugu->canavarlar->etki_degeri)/100.0;
            printf("insan imparatorlugu canavar etkisinin kritik vurusa  etkisi\n");
            printf("%s: %.1f *1.%d(bonus degeri) = %.1f yeni kritik vurus \n",insanImparatorlugu->birimler[i].isim,oldCritic,insanImparatorlugu->canavarlar->etki_degeri,insanImparatorlugu->birimler[i].kritik_sans);
             printf("\n");
        }

        //insan imparatorlugunun elit egitimin kritik vurusa etkisi

        if(isIn(insanImparatorlugu->arastirma_seviyesi.isim,"elit_egitim"))
        {
            insanImparatorlugu->birimler[i].kritik_sans = insanImparatorlugu->birimler[i].kritik_sans*(100+insanImparatorlugu->arastirma_seviyesi.oran)/100.0;
             printf("insan imparatorlugunun elit egitimin kritik vurusa  etkisi\n");
            printf("%s: %.1f *1.%d(bonus degeri) = %.1f yeni kritik vurus\n",insanImparatorlugu->birimler[i].isim,oldCritic,insanImparatorlugu->arastirma_seviyesi.oran,insanImparatorlugu->birimler[i].kritik_sans);
             printf("\n");
        }

    }


}

//net hasar icin
int netDamage(int totalAct,int totalDefence)
{
    return totalAct *(1-((float)totalDefence / totalAct));
}



//yorgunluga gore saldiri ve savunma durumunun guncellenmesi
void updateAttactDefence(Takim* team1, Takim* team2)
{
    for(int i=0; i<team1->birimSayisi; i++)
    {

        team1->birimler[i].saldiri =  team1->birimler[i].saldiri*0.9;
        team2->birimler[i].saldiri =  team2->birimler[i].saldiri*0.9;
        team1->birimler[i].savunma = team1->birimler[i].savunma*0.9;
        team2->birimler[i].savunma = team2->birimler[i].savunma*0.9;

    }

}



void insanSaldiri_OrkSavunma(Takim* insanImparatorlugu,Takim* OrcLejyonu,int step)
{
    insanImparatorlugu->totalAct=0;
    OrcLejyonu->totalDefence = 0;

   printf("\n\n Insan imparatolugu saldirisi \n\n");
 //////// insanlarin saldiri gucunu hesaplamak
    for(int i=0; i<insanImparatorlugu->birimSayisi; i++)
    {

        int BirimSaldiri=0;


        ///kritik vurusa gore guncelleme
        int oran = (1.0/insanImparatorlugu->birimler[i].kritik_sans)*200.0;
        if((step+1) % oran == 0){
            BirimSaldiri+= insanImparatorlugu->birimler[i].saldiri*insanImparatorlugu->birimler[i].sayi*1.5;
            printf("%s: %d birim * %d saldiri gucu = %d toplam saldirisi \n",insanImparatorlugu->birimler[i].isim,insanImparatorlugu->birimler[i].sayi,insanImparatorlugu->birimler[i].saldiri,BirimSaldiri);
             printf("\n");
        }

        else{
            BirimSaldiri+= insanImparatorlugu->birimler[i].saldiri*insanImparatorlugu->birimler[i].sayi;
            printf("%s: %d birim * %d saldiri gucu = %d toplam saldirisi\n",insanImparatorlugu->birimler[i].isim,insanImparatorlugu->birimler[i].sayi,insanImparatorlugu->birimler[i].saldiri,BirimSaldiri);
             printf("\n");
        }


        if(isIn(insanImparatorlugu->kahramanlar->etkilenen,insanImparatorlugu->birimler[i].isim) && isIn(insanImparatorlugu->kahramanlar->bonus_turu,"saldiri")){
            BirimSaldiri*=(1+insanImparatorlugu->kahramanlar->bonus_degeri/100.0);
            printf("Insan imparatorlugu saldirisina kahraman etkisi\n");
            printf("%s: %d birim * %d saldiri gucu *1.%d(bonus degeri) = %d toplam saldirisi\n",insanImparatorlugu->birimler[i].isim,insanImparatorlugu->birimler[i].sayi,insanImparatorlugu->birimler[i].saldiri,insanImparatorlugu->kahramanlar->bonus_degeri,BirimSaldiri);
            printf("\n");
        }

        if(isIn(insanImparatorlugu->canavarlar->etkilenen,insanImparatorlugu->birimler[i].isim),isIn(insanImparatorlugu->canavarlar->etki_turu,"saldiri")) {
            BirimSaldiri*=(1+insanImparatorlugu->canavarlar->etki_degeri/100.0);
             printf("Insan imparatorlugu saldirisina Canavar etkisi\n");
            printf("%s: %d birim * %d saldiri gucu *1.%d(bonus degeri) = %d toplam saldirisi \n",insanImparatorlugu->birimler[i].isim,insanImparatorlugu->birimler[i].sayi,insanImparatorlugu->birimler[i].saldiri,insanImparatorlugu->kahramanlar->bonus_degeri,BirimSaldiri);
             printf("\n");

        }

        if(isIn(insanImparatorlugu->arastirma_seviyesi.isim,"saldiri_gelistirmesi"))
        {

            BirimSaldiri *= (1+insanImparatorlugu->arastirma_seviyesi.oran/100.0);
             printf("Insan imparatorlugu saldirisina saldiri gelistirme etkisi\n");
            printf("%s: %d birim * %d saldiri gucu *1.%d(bonus degeri) = %d toplam saldirisi\n",insanImparatorlugu->birimler[i].isim,insanImparatorlugu->birimler[i].sayi,insanImparatorlugu->birimler[i].saldiri,insanImparatorlugu->arastirma_seviyesi.oran,BirimSaldiri);
             printf("\n");
        }

        if(isIn(insanImparatorlugu->arastirma_seviyesi.isim,"kusatma_ustaligi") && isIn(insanImparatorlugu->birimler[i].isim,"kusatma_makine"))
        {
            BirimSaldiri *=( 1+insanImparatorlugu->arastirma_seviyesi.oran/100.0);
            printf("Insan imparatorlugu saldirisina kusatma ustaligi etkisi\n");
             printf("%s: %d birim * %d saldiri gucu *1.%d(bonus degeri) = %d toplam saldirisi\n",insanImparatorlugu->birimler[i].isim,insanImparatorlugu->birimler[i].sayi,insanImparatorlugu->birimler[i].saldiri,insanImparatorlugu->arastirma_seviyesi.oran,BirimSaldiri);
              printf("\n");
        }

        insanImparatorlugu->totalAct+=BirimSaldiri;
    }
     printf("insan imparatorlugunun toplam saldiri gucu %d \n",insanImparatorlugu->totalAct);

      printf("\n");

    for(int i=0; i<OrcLejyonu->birimSayisi; i++)  ///orklarin savunma gucunu hesaplamak
    {

        int Birimsavunma=0;

        Birimsavunma+=OrcLejyonu->birimler[i].savunma*OrcLejyonu->birimler[i].sayi;



        if(isIn(OrcLejyonu->kahramanlar->etkilenen,OrcLejyonu->birimler[i].isim) && isIn(OrcLejyonu->kahramanlar->bonus_turu,"savunma") ){
            Birimsavunma*=(1+OrcLejyonu->kahramanlar->bonus_degeri/100.0);
            printf("Ork Legi savunmaya kahraman etkisi\n ");
            printf("%s: %d birim * %d savunma gucu *1.%d(bonus degeri) = %d toplam savunmasi \n",OrcLejyonu->birimler[i].isim,OrcLejyonu->birimler[i].sayi,OrcLejyonu->birimler[i].savunma,OrcLejyonu->kahramanlar->bonus_degeri,Birimsavunma);
             printf("\n");
        }
        if(isIn(OrcLejyonu->canavarlar->etkilenen,OrcLejyonu->birimler[i].isim) && isIn(OrcLejyonu->canavarlar->etki_turu,"savunma") ){
            Birimsavunma*=(1+OrcLejyonu->canavarlar->etki_degeri/100.0);
             printf("Ork Legi savunmaya canavar etkisi \n");
            printf("%s: %d birim * %d savunma gucu *1.%d(bonus degeri) = %d toplam savunmasi \n",OrcLejyonu->birimler[i].isim,OrcLejyonu->birimler[i].sayi,OrcLejyonu->birimler[i].savunma,OrcLejyonu->canavarlar->etki_degeri,Birimsavunma);
             printf("\n");

        }


        if(isIn(OrcLejyonu->arastirma_seviyesi.isim,"savunma_ustaligi"))
        {
            Birimsavunma *= (1+OrcLejyonu->arastirma_seviyesi.oran/100.0);
             printf("Ork Legi savunmaya savunma usataligi etkisi \n");
             printf("%s: %d birim * %d savunma gucu *1.%d(bonus degeri) = %d toplam savunmasi \n",OrcLejyonu->birimler[i].isim,OrcLejyonu->birimler[i].sayi,OrcLejyonu->birimler[i].savunma,OrcLejyonu->arastirma_seviyesi.oran,Birimsavunma);
              printf("\n");
        }

        OrcLejyonu->totalDefence+=Birimsavunma;

    }
        printf("Ork Leginin toplam savunmasi %d \n",OrcLejyonu->totalDefence);
         printf("\n");

    //\net hasarin hesaplanmasi
    int netHasar = netDamage(insanImparatorlugu->totalAct,OrcLejyonu->totalDefence);
    //eger net hasar negatif cıkarsa sifira esitle
    if(netHasar<0)
        netHasar=0;

    printf("net hasar : %d\n", netHasar);




    for(int i=0; i<OrcLejyonu->birimSayisi; i++)
    {

         float damage = ((OrcLejyonu->birimler[i].savunma*OrcLejyonu->birimler[i].sayi)/(float)OrcLejyonu->totalDefence)*netHasar;
         printf("%s birimin %f hasar miktari ",OrcLejyonu->birimler[i].isim,damage);
        printf("\n");
        int death = damage/OrcLejyonu->birimler[i].saglik;
        printf("%s birimden %d kisi oldu \n",OrcLejyonu->birimler[i].isim,death);
         printf("\n");
        //Birimlerin toplam olu sayilerinin belirlenmesi ve mevcut birim sayisisindan eksiltilmesi
         death = death > 0 ? death : 0;
         OrcLejyonu->birimler[i].sayi -= death;

        //birimlerin saglik durumlarinin guncellenmesi
        OrcLejyonu->birimler[i].saglik -= (netHasar/OrcLejyonu->birimler[i].sayi) > 0 ? (netHasar/OrcLejyonu->birimler[i].sayi) : 0;
         if(OrcLejyonu->birimler[i].saglik==0){
            OrcLejyonu->birimler[i].sayi=0;
         }
    }

}

//Ork saldirisi insan savunmasi
void OrkSaldiri_insanSavunma(Takim* insanImparatorlugu,Takim* OrcLejyonu,int step)
{
     insanImparatorlugu->totalDefence = 0;
     OrcLejyonu->totalAct=0;
  printf("\n\n Ork Legi saldirisi \n\n");

//Ork Legi saldırı gücü toplama döngüsü BURDA!!!!!
    for(int i=0; i<OrcLejyonu->birimSayisi; i++)
    {
        int BirimSaldiri=0;

        //kritik vurusa gore guncelleme
        int oran = (1.0/OrcLejyonu->birimler[i].kritik_sans)*200;
        if((step+1) % oran == 0){
            BirimSaldiri+= OrcLejyonu->birimler[i].saldiri*OrcLejyonu->birimler[i].sayi*1.5;
             printf("%s: %d birim * %d saldiri gucu = %d toplam saldirisi \n",OrcLejyonu->birimler[i].isim,OrcLejyonu->birimler[i].sayi,OrcLejyonu->birimler[i].saldiri,BirimSaldiri);
              printf("\n");
        }

        else{
            BirimSaldiri+= OrcLejyonu->birimler[i].saldiri*OrcLejyonu->birimler[i].sayi;
             printf("%s: %d birim * %d saldiri gucu = %d toplam saldirisi\n",OrcLejyonu->birimler[i].isim,OrcLejyonu->birimler[i].sayi,OrcLejyonu->birimler[i].saldiri,BirimSaldiri);
              printf("\n");
        }



        if(isIn(OrcLejyonu->kahramanlar->etkilenen,OrcLejyonu->birimler[i].isim) && isIn(OrcLejyonu->kahramanlar->bonus_turu,"saldiri") ){
            BirimSaldiri*=(1+OrcLejyonu->kahramanlar->bonus_degeri/100.0);
           printf("Ork Legi saldirisina Kahraman etkisi\n");
            printf("%s: %d birim * %d saldiri gucu *1.%d(bonus degeri) = %d toplam saldirisi\n",OrcLejyonu->birimler[i].isim,OrcLejyonu->birimler[i].sayi,OrcLejyonu->birimler[i].saldiri,OrcLejyonu->kahramanlar->bonus_degeri,BirimSaldiri);
             printf("\n");
          }

        if(isIn(OrcLejyonu->canavarlar->etkilenen,OrcLejyonu->birimler[i].isim) && isIn(OrcLejyonu->canavarlar->etki_turu,"saldiri") ){
            BirimSaldiri*=(1+OrcLejyonu->canavarlar->etki_degeri/100.0);
            printf("Ork Legi saldirisina Canavar etkisi\n");
            printf("%s: %d birim * %d saldiri gucu *1.%d(bonus degeri) = %d toplam saldirisi\n",OrcLejyonu->birimler[i].isim,OrcLejyonu->birimler[i].sayi,OrcLejyonu->birimler[i].saldiri,OrcLejyonu->canavarlar->etki_degeri,BirimSaldiri);
             printf("\n");
          }

        if(isIn(OrcLejyonu->arastirma_seviyesi.isim,"saldiri_gelistirmesi"))
        {
            BirimSaldiri *= (1+OrcLejyonu->arastirma_seviyesi.oran/100.0);
            printf("Ork Legi saldirisina Saldiri gelistirme etkisi\n");
            printf("%s: %d birim * %d saldiri gucu *1.%d(bonus degeri) = %d toplam saldirisi\n",OrcLejyonu->birimler[i].isim,OrcLejyonu->birimler[i].sayi,OrcLejyonu->birimler[i].saldiri,OrcLejyonu->arastirma_seviyesi.oran,BirimSaldiri);
             printf("\n");
        }

        OrcLejyonu->totalAct+=BirimSaldiri;

    }

      printf("Ork Leginin toplam saldirisi %d \n",OrcLejyonu->totalAct);
      printf("\n");

    for(int i=0; i<insanImparatorlugu->birimSayisi; i++)  //////// insanlarin savunma gucunu hesaplamak
    {

        int Birimsavunma=0;

        Birimsavunma+=insanImparatorlugu->birimler[i].savunma*insanImparatorlugu->birimler[i].sayi;
         printf("%s: %d birim * %d savunma gucu = %d toplam savunmasi\n",insanImparatorlugu->birimler[i].isim,insanImparatorlugu->birimler[i].sayi,insanImparatorlugu->birimler[i].savunma,Birimsavunma);
          printf("\n");


        if(isIn(insanImparatorlugu->kahramanlar->etkilenen,insanImparatorlugu->birimler[i].isim) && isIn(insanImparatorlugu->kahramanlar->bonus_turu,"savunma")){
            Birimsavunma*=(1+insanImparatorlugu->kahramanlar->bonus_degeri/100.0);
            printf("Insan imparatorlugu savunmasina kahraman etkisi\n");
            printf("%s: %d birim * %d savunma gucu *1.%d(bonus degeri) = %d toplam savunmasi \n",insanImparatorlugu->birimler[i].isim,insanImparatorlugu->birimler[i].sayi,insanImparatorlugu->birimler[i].savunma,insanImparatorlugu->kahramanlar->bonus_degeri,Birimsavunma);
             printf("\n");
        }

        if(insanImparatorlugu->canavarlar->etkilenen,insanImparatorlugu->birimler[i].isim && isIn(insanImparatorlugu->canavarlar->etki_turu,"savunma") ){
            Birimsavunma*=(1+insanImparatorlugu->canavarlar->etki_degeri/100.0);
              printf("insan imparatorluguna canavar etkisi\n");
              printf("%s: %d birim * %d savunma gucu *1.%d(bonus degeri ) = %d toplam savunmasi  %d \n",insanImparatorlugu->birimler[i].isim,insanImparatorlugu->birimler[i].sayi,insanImparatorlugu->birimler[i].savunma,insanImparatorlugu->canavarlar->etki_degeri,Birimsavunma);
               printf("\n");
        }

        if(isIn(insanImparatorlugu->arastirma_seviyesi.isim,"savunma_ustaligi"))
        {
            Birimsavunma *= 1+(insanImparatorlugu->arastirma_seviyesi.oran/100.0);
            printf("insan Imparatorlugunun savunmasina savunma_ustaligi etksi\n");
              printf("%s: %d birim * %d savunma gucu *1.%d(savunma ustaligi etkisi) = %d toplam savunmasi  \n",insanImparatorlugu->birimler[i].isim,insanImparatorlugu->birimler[i].sayi,insanImparatorlugu->birimler[i].savunma,insanImparatorlugu->arastirma_seviyesi.oran,Birimsavunma);
               printf("\n");
        }

        insanImparatorlugu->totalDefence+=Birimsavunma;
    }

    printf("insan imparatorlugunun toplam savunma gucu %d\n",insanImparatorlugu->totalDefence);
     printf("\n");



    //net hasarin hesaplanmasi
    int netHasar= netDamage(OrcLejyonu->totalAct,insanImparatorlugu->totalDefence);
    //eger net hasar negatif cıkarsa sifira esitle
    if(netHasar<0)
        netHasar=0;

    printf("net hasar : %d\n", netHasar);

    for(int i=0; i<insanImparatorlugu->birimSayisi; i++)
    {
        float damage = ((insanImparatorlugu->birimler[i].savunma*insanImparatorlugu->birimler[i].sayi)/(float)insanImparatorlugu->totalDefence)*netHasar;
         printf("%s birimin %f hasar miktari ",insanImparatorlugu->birimler[i].isim,damage);
          printf("\n");
        int death = damage/insanImparatorlugu->birimler[i].saglik;
        printf("%s birimden %d kisi oldu \n",insanImparatorlugu->birimler[i].isim,death);
         printf("\n");
        //Birimlerin toplam olu sayilerinin belirlenmesi ve mevcut birim sayisisindan eksiltilmesi
         death = death > 0 ? death : 0;
         OrcLejyonu->birimler[i].sayi -= death;

        //birimlerin saglik durumlarinin guncellenmesi
        insanImparatorlugu->birimler[i].saglik -= (netHasar/insanImparatorlugu->birimler[i].sayi) > 0 ? (netHasar/insanImparatorlugu->birimler[i].sayi) : 0;
         if(insanImparatorlugu->birimler[i].saglik==0){
            insanImparatorlugu->birimler[i].sayi=0;
         }


    }

}

void FIGHT(Takim* insan_imparatorlugu,Takim* ork_legi)
{
     UpdateCriticChance(insan_imparatorlugu,ork_legi);
    int step = 0;
    do
    {
        insanSaldiri_OrkSavunma(insan_imparatorlugu,ork_legi,step);

        step++;

        if(step%5==0)
        updateAttactDefence(insan_imparatorlugu,ork_legi);

        OrkSaldiri_insanSavunma(insan_imparatorlugu,ork_legi,step);
        step++;

    }
    while(checkWiner(*insan_imparatorlugu,*ork_legi));


}


