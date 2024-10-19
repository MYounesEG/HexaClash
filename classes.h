// classes.h
#ifndef CLASSES_H
#define CLASSES_H


typedef struct Unit{
    char isim[30];
    float saldiri;
    float savunma;
    float saglik;
    float kritik_sans;

    float sayi;
}Unit;


typedef struct Hero{
    char isim[100];
    char bonus_turu[100];
    float bonus_degeri;
    char etkilenen[100];
}Hero;


typedef struct Monester{
    char isim[100];
    char etki_turu[100];
    float etki_degeri;
    char etkilenen[100];
}Monester;




typedef struct Research{
    char isim[50];
    int seviye;
    float oran;

    char etkilenen[50];

}Research;


typedef struct Takim{
    char TakimName[40];
    Unit birimler[8]; // max birim:8
    int birimSayisi;
    Hero kahramanlar[9]; // max kahraman : 9
    int kahramanSayisi;
    Monester canavarlar[11]; // max canavar :11
    int canavarSayisi;
    Research arastirma_seviyesi; // sadece bir tan olabilir
    float totalHealth;
    float totalAct;
    float totalDefence;
}Takim;


#endif // CLASSES_H
