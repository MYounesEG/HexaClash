typedef struct Unit{
    char isim[30];
    int saldiri;
    int savunma;
    int saglik;
    int kritik_sans;

    int sayi;
}Unit;


typedef struct Hero{
    char isim[200];
    char bonus_turu[200];
    int bonus_degeri;
    char etkilenen[200];
}Hero;


typedef struct Monester{
    char isim[200];
    char bonus_turu[200];
    int bonus_degeri;
    char etkilenen[200];
}Monester;


typedef struct Research{
    char isim[30];
    int seviye;
    int oran;
    char etkilenen[30];

}Research;


typedef struct Takim{
    char TakimName[20];
    Unit birimler[8]; // max birim:8
    int birimSayisi;
    Hero kahramanlar[9]; // max kahraman : 9
    int kahramanSayisi;
    Monester canavarlar[11]; // max canavar :11
    int canavarSayisi;
    Research arastirma_seviyesi; // sadece bir tan olabilir
}Takim;


