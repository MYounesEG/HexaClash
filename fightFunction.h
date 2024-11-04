#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "classes.h"

bool isIn(char string1[], char string2[]);
int checkWiner(Takim* insanImparatorlugu, Takim* OrkLegi, FILE* file);
void UpdateCriticChance(Takim* insanImparatorlugu,Takim* OrcLejyonu,FILE* file);
float netDamage(float totalAct,float totalDefence); //net hasar icin
void updateAttactDefence(Takim* team1, Takim* team2, FILE* file);    //yorgunluga gore saldiri ve savunma durumunun guncellenmesi
void SaldiriSavunma(Takim* saldiran,Takim* savunan,int step, FILE* file);
void FIGHT(Takim* insan_imparatorlugu,Takim* ork_legi);


bool isIn(char string1[], char string2[]) //Aradgimiz deger icinde var mi
{
    if(strstr(string1,string2)!= NULL)
        return true;
    else  return false;
}

int checkWiner(Takim* insanImparatorlugu, Takim* OrkLegi, FILE* file)
{
    float totalUnitInsan = 0;
    float totalUnitOrk = 0;

    for(int i=0; i<insanImparatorlugu->birimSayisi ; i++)
        totalUnitInsan += insanImparatorlugu->birimler[i].sayi;
    for(int i=0; i<OrkLegi->birimSayisi ; i++)
        totalUnitOrk += OrkLegi->birimler[i].sayi;

    if(totalUnitInsan<=0)
    {
        fprintf(file,"\n\n\t\tInsanlar hepsi oldu, Orklar kazandi");
        insanImparatorlugu->kahramanSayisi=0;
        insanImparatorlugu->canavarSayisi=0;

        return 2;
    }
    else if(totalUnitOrk<=0)
    {
        fprintf(file,"\n\n\t\tOrklar hepsi oldu,Insanlar kazandi");
        OrkLegi->kahramanSayisi=0;
        OrkLegi->canavarSayisi=0;

        return 1;

    }
    else
        return 0;

}

void UpdateCriticChance(Takim* insanImparatorlugu,Takim* OrcLejyonu,FILE* file)
{
    //Ork Legi kritik vurus etkisi
    for(int i=0; i<OrcLejyonu->birimSayisi; i++)//
    {
        float oldCritic= OrcLejyonu->birimler[i].kritik_sans;

        //Ork Legi kahramanin kritik vurusa etkisi
        if(isIn(OrcLejyonu->kahramanlar->etkilenen,OrcLejyonu->birimler[i].isim) && isIn(OrcLejyonu->kahramanlar->bonus_turu," kritik") )
        {
            OrcLejyonu->birimler[i].kritik_sans = OrcLejyonu->birimler[i].kritik_sans*(100+OrcLejyonu->kahramanlar->bonus_degeri)/100.0;
            fprintf(file,"Ork Legi kahraman etkisinin kritik vurusa etkisi\n");
            fprintf(file,"%s:%.2f * %.2f(bonus degeri) = %.2f yeni kritik vurus \n",OrcLejyonu->birimler[i].isim,oldCritic,1+OrcLejyonu->kahramanlar->bonus_degeri/100.0,OrcLejyonu->birimler[i].kritik_sans);
            fprintf(file,"\n");
        }

        //Ork Legi canavarın kritik vurusa etkisi
        if(isIn(OrcLejyonu->canavarlar->etkilenen,OrcLejyonu->birimler[i].isim) && isIn(OrcLejyonu->canavarlar->etki_turu," kritik") )
        {
            OrcLejyonu->birimler[i].kritik_sans = OrcLejyonu->birimler[i].kritik_sans*(100+OrcLejyonu->canavarlar->etki_degeri)/100.0;
            fprintf(file,"Ork Legi canavar etkisinin kritik vurusa etkisi\n");
            fprintf(file,"%s: %.2f * %.2f(bonus degeri)=%.2f yeni kritik vurus  \n",OrcLejyonu->birimler[i].isim,oldCritic,1 + OrcLejyonu->canavarlar->etki_degeri/100.0,OrcLejyonu->birimler[i].kritik_sans);
            fprintf(file,"\n");
        }

        //Ork Legi elit egitimin  vurusa etkisi
        if(isIn(OrcLejyonu->arastirma_seviyesi.isim,"elit_egitim"))
        {
            OrcLejyonu->birimler[i].kritik_sans = OrcLejyonu->birimler[i].kritik_sans*(100+OrcLejyonu->arastirma_seviyesi.oran)/100.0;
            fprintf(file,"Ork Legi elit egitimin kritik vurusa  etkisi\n");
            fprintf(file,"%s: %.2f * %.2f(bonus degeri) = %.2f yeni kritik vurus \n",OrcLejyonu->birimler[i].isim,oldCritic,1 + OrcLejyonu->arastirma_seviyesi.oran / 100.0,OrcLejyonu->birimler[i].kritik_sans);
            fprintf(file,"\n");

        }
    }
    //insan imparatorlugu kritik vurus etkisi
    for(int i=0; i<insanImparatorlugu->birimSayisi; i++)//
    {
        float oldCritic = insanImparatorlugu->birimler[i].kritik_sans;

        //insan imparatorlugunun kahramanin kritik vurusa etkisi
        if(isIn(insanImparatorlugu->kahramanlar->etkilenen,insanImparatorlugu->birimler[i].isim)&&isIn(insanImparatorlugu->kahramanlar->bonus_turu,"kritik"))
        {

            insanImparatorlugu->birimler[i].kritik_sans = insanImparatorlugu->birimler[i].kritik_sans*(100+insanImparatorlugu->kahramanlar->bonus_degeri)/100.0;
            fprintf(file,"insan impartorlugu kahraman etkisinin kritik vurusa etkisi\n");
            fprintf(file,"%s: %.2f * %.2f(bonus degeri) = %.2f yeni kritik vurus  \n",insanImparatorlugu->birimler[i].isim,oldCritic,1 + insanImparatorlugu->kahramanlar->bonus_degeri / 100.0,insanImparatorlugu->birimler[i].kritik_sans);
            fprintf(file,"\n");

        }
        //insan imparatorlugunun canavarın kritik vurusa etkisi
        if(isIn(insanImparatorlugu->canavarlar->etkilenen,insanImparatorlugu->birimler[i].isim) && isIn(insanImparatorlugu->canavarlar->etki_turu,"kritik") )
        {

            insanImparatorlugu->birimler[i].kritik_sans = insanImparatorlugu->birimler[i].kritik_sans*(100+insanImparatorlugu->canavarlar->etki_degeri)/100.0;
            fprintf(file,"insan imparatorlugu canavar etkisinin kritik vurusa  etkisi\n");
            fprintf(file,"%s: %.2f * %.2f(bonus degeri) = %.2f yeni kritik vurus \n",insanImparatorlugu->birimler[i].isim,oldCritic,1 + insanImparatorlugu->canavarlar->etki_degeri / 100.0,insanImparatorlugu->birimler[i].kritik_sans);
            fprintf(file,"\n");
        }

        //insan imparatorlugunun elit egitimin kritik vurusa etkisi

        if(isIn(insanImparatorlugu->arastirma_seviyesi.isim,"elit_egitim"))
        {
            insanImparatorlugu->birimler[i].kritik_sans = insanImparatorlugu->birimler[i].kritik_sans*(100+insanImparatorlugu->arastirma_seviyesi.oran)/100.0;
            fprintf(file,"insan imparatorlugunun elit egitimin kritik vurusa  etkisi\n");
            fprintf(file,"%s: %.2f * %.2f(bonus degeri) = %.2f yeni kritik vurus\n",insanImparatorlugu->birimler[i].isim,oldCritic,1 + insanImparatorlugu->arastirma_seviyesi.oran / 100.0,insanImparatorlugu->birimler[i].kritik_sans);
            fprintf(file,"\n");
        }

    }


}

float netDamage(float totalAct,float totalDefence) //net hasar icin
{
    return totalAct *(1-(totalDefence / totalAct));
}

void updateAttactDefence(Takim* team1, Takim* team2,FILE* file)//yorgunluga gore saldiri ve savunma durumunun guncellenmesi
{
    fprintf(file,"\nYourgunluk hesaplama !\n");
    for(int i=0; i<team1->birimSayisi; i++)
    {
        team1->birimler[i].saldiri *= 0.9;
        team1->birimler[i].savunma *= 0.9;
        fprintf(file,"%s :\n\tsaldiri = %0.f\n\tsavunma = %0.f",team1->birimler[i].isim,team1->birimler[i].saldiri,team1->birimler[i].savunma);
    }
    for(int i=0; i<team2->birimSayisi; i++)
    {
        team2->birimler[i].saldiri *= 0.9;
        team2->birimler[i].savunma *= 0.9;
        fprintf(file,"%s :\n\tsaldiri = %0.f\n\tsavunma = %0.f",team2->birimler[i].isim,team2->birimler[i].saldiri,team2->birimler[i].savunma);

    }

}

void SaldiriSavunma(Takim* saldiran,Takim* savunan,int step, FILE* file)
{
    fprintf(file,"\n\nAdim %d: %s saldirisi \n",step+1,saldiran->TakimName);

    fprintf(file,"\t1. Saldiri Gucu Hesaplamasu (Arastirma ve Canavar Etkileri Dahil):");
    saldiran->totalAct=0;
    savunan->totalDefence = 0;



    for(int i=0; i<saldiran->birimSayisi; i++)
    {
        saldiran->birimler[i].toplamSaldiri=1;

        fprintf(file,"\n\t* %s : %0.f birim x %0.f saldiri gucu",saldiran->birimler[i].isim,saldiran->birimler[i].sayi,saldiran->birimler[i].saldiri);

        saldiran->birimler[i].toplamSaldiri *= saldiran->birimler[i].saldiri*saldiran->birimler[i].sayi;


        ///kritik vurusa gore guncelleme
        float oran = (1.0/saldiran->birimler[i].kritik_sans)*200.0;
        if((step+1) % (int)oran == 0)
        {
            fprintf(file," x 1.5(kritik sans)");
            saldiran->birimler[i].toplamSaldiri*= 1.5;
        }



        if(isIn(saldiran->kahramanlar->etkilenen,saldiran->birimler[i].isim) && isIn(saldiran->kahramanlar->bonus_turu,"saldiri"))
        {
            fprintf(file," x %.2f (%s kahramanin bonusu)",(1+saldiran->kahramanlar->bonus_degeri/100.0),saldiran->kahramanlar->isim);
            saldiran->birimler[i].toplamSaldiri*=(1+saldiran->kahramanlar->bonus_degeri/100.0);
        }


        if(isIn(saldiran->canavarlar->etkilenen,saldiran->birimler[i].isim)&&isIn(saldiran->canavarlar->etki_turu,"saldiri"))
        {
            saldiran->birimler[i].toplamSaldiri*=(1+saldiran->canavarlar->etki_degeri/100.0);
            fprintf(file," x %.2f (%s canavarin etkisi)",(1+saldiran->canavarlar->etki_degeri/100.0),saldiran->canavarlar->isim);

        }

        if(isIn(saldiran->arastirma_seviyesi.isim,"saldiri_gelistirmesi") ||
                (
                    isIn(saldiran->arastirma_seviyesi.isim,"kusatma_ustaligi") &&
                    isIn(saldiran->birimler[i].isim,"kusatma_makine")
                )
          )
        {
            saldiran->birimler[i].toplamSaldiri *= (1+saldiran->arastirma_seviyesi.oran/100.0);
            fprintf(file," x %.2f (%s arastirma seviyesi)",1+saldiran->arastirma_seviyesi.oran/100.0,saldiran->arastirma_seviyesi.isim);
        }

        fprintf(file," = %0.f\n",saldiran->birimler[i].toplamSaldiri);

        saldiran->totalAct+=saldiran->birimler[i].toplamSaldiri;
    }

    fprintf(file,"\n\n\tToplam Saldiri Gucu (%s):\n\t",saldiran->TakimName);
    for(int i=0; i<saldiran->birimSayisi; i++)
        fprintf(file,"%c %.0f (%s) ",(i)?'+':'\0',saldiran->birimler[i].toplamSaldiri,saldiran->birimler[i].isim);
    fprintf(file," = %.0f",saldiran->totalAct);

    fprintf(file,"\n\t2. Savunma Gucu Hesaplamasi (%s):",savunan->TakimName);

    for(int i=0; i<savunan->birimSayisi; i++)
    {
        savunan->birimler[i].toplamSavunma=1;

        fprintf(file,"\n\t* %s : %0.f birim x %0.f savunma gucu",savunan->birimler[i].isim,savunan->birimler[i].sayi,savunan->birimler[i].savunma);

        savunan->birimler[i].toplamSavunma *= savunan->birimler[i].savunma*savunan->birimler[i].sayi;



        if(isIn(savunan->kahramanlar->etkilenen,savunan->birimler[i].isim) && isIn(savunan->kahramanlar->bonus_turu,"savunma"))
        {
            fprintf(file," x %.2f (%s kahramanin bonusu)",(1+savunan->kahramanlar->bonus_degeri/100.0),savunan->kahramanlar->isim);
            savunan->birimler[i].toplamSavunma*=(1+savunan->kahramanlar->bonus_degeri/100.0);
        }


        if(isIn(savunan->canavarlar->etkilenen,savunan->birimler[i].isim)&&isIn(savunan->canavarlar->etki_turu,"savunma"))
        {
            savunan->birimler[i].toplamSavunma*=(1+savunan->canavarlar->etki_degeri/100.0);
            fprintf(file," x %.2f (%s canavarin etkisi)",(1+savunan->canavarlar->etki_degeri/100.0),savunan->canavarlar->isim);

        }

        if(isIn(savunan->arastirma_seviyesi.isim,"savunma_ustaligi"))
        {
            savunan->birimler[i].toplamSavunma *= (1+savunan->arastirma_seviyesi.oran/100.0);
            fprintf(file," x %.2f (%s arastirma seviyesi)",1+savunan->arastirma_seviyesi.oran/100.0,savunan->arastirma_seviyesi.isim);
        }

        fprintf(file," = %0.f\n",savunan->birimler[i].toplamSavunma);

        savunan->totalDefence+=savunan->birimler[i].toplamSavunma;
    }


    fprintf(file,"\n\n\tToplam Savunma Gucu (%s):\n\t",savunan->TakimName);
    for(int i=0; i<savunan->birimSayisi; i++)
        fprintf(file,"%c %.0f (%s) ",(i)?'+':'\0',savunan->birimler[i].toplamSavunma,savunan->birimler[i].isim);

    fprintf(file," = %.0f",savunan->totalDefence);

    fprintf(file,"\n3. Net Hasar Hesaplamasi:\n");
    //\net hasarin hesaplanmasi
    float netHasar = netDamage(saldiran->totalAct,savunan->totalDefence);
    //eger net hasar negatif cıkarsa sifira esitle


    if(netHasar<0)
    {
        fprintf(file,"\tSavunma gucu daha yuksek oldu icin net hasar sifir ! \n");
        netHasar=0;
    }

    fprintf(file,"\t Net Hasar = %.2f * (1-(%.2f/%.2f)) = %.2f\n",saldiran->totalAct,savunan->totalDefence,saldiran->totalAct,netHasar);

    fprintf(file,"4. Orantili Hasar Dagilimi: %s %.2f hasar orantili olarakdagitilir:",savunan->TakimName,netHasar);

    for(int i=0; i<savunan->birimSayisi; i++)
    {
        savunan->birimler[i].saglik -= (netHasar*savunan->birimler[i].toplamSavunma/savunan->totalDefence) / savunan->birimler[i].sayi;

        if(savunan->birimler[i].saglik<=0)
        {
            savunan->birimler[i].saglik=0;
            savunan->birimler[i].sayi=0;
        }

        //Birimlerin toplam olu sayilerinin belirlenmesi ve mevcut birim sayisisindan eksiltilmesi

        if(savunan->birimler[i].sayi<=0)
        {
            savunan->birimler[i].saglik=0;
            savunan->birimler[i].sayi=0;
        }
        fprintf(file,"\n\t%s yeni saglik : %0.f",savunan->birimler[i].isim,savunan->birimler[i].saglik);

    }

    fprintf(file,"\n");
}



void FIGHT(Takim* insan_imparatorlugu,Takim* ork_legi)
{
    System("del savas_sim.txt");
    FILE* file = fopen("savas_sim.txt","w");

    UpdateCriticChance(insan_imparatorlugu,ork_legi,file);
    int step = 0;
    do
    {
        SaldiriSavunma(insan_imparatorlugu,ork_legi,step,file);
        step++;

        if((checkWiner(insan_imparatorlugu,ork_legi,file) != 0))
            break;

        if((step)%5==0)
            updateAttactDefence(insan_imparatorlugu,ork_legi,file);

        SaldiriSavunma(ork_legi,insan_imparatorlugu,step,file);
        step++;

    }
    while(checkWiner(insan_imparatorlugu,ork_legi,file) == 0);
    fprintf(file,"\n\n\n");


    fclose(file);
}
