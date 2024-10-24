#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include "classes.h"
#include "readfunctions.h"

#define lineSize 200

void welcome();                                              // Say Hi to the user :)
bool in(char str1[],char str2[]);                            // return True if the str2 in str1
bool inFile(FILE* f,char str1[]);                            // check if the word is it in file
void root(char kelime[]);                                    // change the word for the original status
void getWord_S(char line[],char word[]);                     // get the first word in line
void getWord_F(FILE* f,char word[]);                         // gets the first word from the cursor position
int  getValue(char line[]);                                  // return the integer value of the sayi in the line
void gotoLine(FILE*f,char line[],int start,char order[]);    // go to the line where include the "order" (not : searching will start from the "start" point in the file)
void gotoChar(FILE*f,char order);                            // get the cursor to the place of "order" (not : searching will start from the cursor position)
void nextLine(FILE *f,char line[]);                          // get the next line
void downloadFile(int Senariosayi,char fileName[]);        // download the scenario file using the sayi
void deleteFile(char senaryoFile[]);                         // deleting file the scenario file using the fileName
void readTakim(Takim* team,char fileName[]);                 // reading all the team informations from the scenario file
void openLog();                                              // open the log file
void repeat();                                               // re run the program if the user want's to


void welcome()
{

    system("cls");
    char hex[]="47BCDE13",index=0;
    char color[]="color 00";

    printf("Created by:\n\n\n\n@Phoneix369\n\n@MYounesEG\n\n\n\n\n\t\t\t");

    system("pause&&cls");

    PlaySound("music\\music.wav", NULL, SND_FILENAME | SND_ASYNC);
    sleep(2);

    printf("\n\n\n\n\n\t\t\t\t\t\t");
    char string[]="W E L C O M E   ;)";
    for (int i=0; i<strlen(string); i++)
    {

        printf("%c",string[i]);
        fflush(stdout);
        usleep(1000);


        system(color);

        index++;
        //color[6]=hex[(index)%9];
        color[7]=hex[(index+1)%9];
    }

    sleep(3);

    system("cls");

    char ask[]="Please Enter a Scenario sayi : ";

    printf("\n\n\n\n\n\t\t\t\t\t");
    for (int i=0; i<strlen(ask); i++)
    {

        printf("%c",ask[i]);
        fflush(stdout);
        usleep(40);


        system(color);

        index++;
        //   color[6]=hex[(index)%6];
        color[7]=hex[(index+1)%6];
    }

}

bool in(char str1[],char str2[])
{
    if(strstr(str1,str2)!=NULL)
        return true;
    return false;

}

bool inFile(FILE* f, char str1[])
{
    fseek(f, 0, SEEK_SET);
    char line[lineSize] = {0};

    while (fgets(line, lineSize, f) != NULL)
    {
        if (in(line, str1))
        {
            return true; // word found
        }
    }

    return false; // word not found
}

void root(char kelime[])
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
        "Karakurt",
        "Samur",
        "Kara_Troll",
        "Golge_Kurtlari",
        "Camur_Devleri",
        "Ates_Iblisi",
        "Makrog_Savas_Beyi",
        "Buz_Devleri",
        "savunma_ustaligi",
        "saldiri_gelistirmesi",
        "elit_egitim",
        "kusatma_ustaligi",
        "savunma",
        "saldiri",
        "kritik"
    };


    kelime[0]=tolower(kelime[0]);
    for (int i = 0; i < sizeof(words) / sizeof(words[0]); i++)
    {
        if (strstr(kelime, words[i]))
        {
            strcpy(kelime, words[i]);  // kelimeyi sadece eşleşen kısım ile değiştir
            return ;
        }
    }
    printf("COUNDT found this word (%s)!\n",kelime);
}

void getWord_S(char line[],char word[])
{
    sscanf(line,"%s",word);
    root(word);
}

void getWord_F(FILE* f,char word[])
{
    fscanf(f,"%s",word);
    root(word);
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

void downloadFile(int Senariosayi,char senaryoFile[])
{

    system("cls");
    if (Senariosayi==0)
        return;
    if (!(Senariosayi<=10&&Senariosayi>=1))
    {
        printf("Plase Enter a vailed sayi ! \n\t\tExiting.....\n\n");
        exit(1);
    }




    char string[]="Downloading the scenario file\n\n\tplease wait........";
    int delay=1000;
    for (int i=0; i<strlen(string) - rand()%6; i++)
    {

        printf("%c",string[i]);
              fflush(stdout);
              usleep(delay);
        if(i==41)
            delay*=1000;
    }
    system("cls");





    sprintf(senaryoFile,"%d.json",Senariosayi);

    char downloadCommand [50]= {0};
    sprintf(downloadCommand,"curl https://yapbenzet.org.tr/%s -o %s  > nul 2>&1",senaryoFile,senaryoFile);

    system(downloadCommand);

    system("cls");
}

void deleteFile(char senaryoFile[])
{
    char deleteCommand [10]= {0};
    sprintf(deleteCommand,"del %s",senaryoFile);

    system(deleteCommand);
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
            getWord_S(line,team->birimler[team->birimSayisi].isim);
            team->birimler[team->birimSayisi].sayi=getValue(line);
            team->birimSayisi++;
            nextLine(f,line);
        }
        while(!in(line,"}"));  // stop when find the end of birimler block


        readBirim(team);//kutucuk
    }

    team->kahramanSayisi = 0;
    if(inFile(f,"kahramanlar"))
    {
        //kahramanlar

        gotoInFile(f,line,startIndex,"kahramanlar");



        for(  part = strstr(line,"[") ; part!=NULL ; part = strstr(part+1," \""))
        {
            getWord_S(part,team->kahramanlar[team->kahramanSayisi].isim);

            team->kahramanSayisi++;
        }

        if(team->kahramanSayisi!=0)
            readKahraman(team); // kahraman varsa bilgilerini dosyadan cek

    }

    fseek(f,startIndex,SEEK_SET);
    team->canavarSayisi = 0;
    if(inFile(f,"canavarlar"))
    {
        //canavarlar

        gotoInFile(f,line,startIndex,"canavarlar");

        //char* part; // daha onceden tanimlandi

        for(  part = strstr(line,"[") ; part!=NULL ; part = strstr(part+1," \""))
        {
            getWord_S(part,team->canavarlar[team->canavarSayisi].isim);
            team->canavarSayisi++;

        }
        if(team->canavarSayisi!=0)
            readCanavar(team); // canavar varsa bilgilerini dosyadan cek
    }

    fseek(f,startIndex,SEEK_SET);

    if(inFile(f,"arastirma_seviyesi"))
    {
        //arastirma sevyesi

        gotoInFile(f,line,startIndex,"arastirma_seviyesi");

        nextLine(f,line);

        getWord_S(line,team->arastirma_seviyesi.isim);

        team->arastirma_seviyesi.seviye=getValue(line);

        readArastirma_seviyesi(team);
    }

    fclose(f);
}

void openLog()
{

    system("savas_sim.txt");


    system("pause");

}

void repeat()
{

    char hex[]="47BCDE13",index=0;
    char color[]="color 00";
    system("cls");

    char str []= "\n\n\n\n\t\t\t\t\tThe war is end :) \n\n\n\n\t\t\t\t   Want to play again ? (1/0): ";

    for (int i=0; i<strlen(str); i++)
    {

        printf("%c",str[i]);
        fflush(stdout);
        usleep(70);


        system(color);

        index++;
        //color[6]=hex[(index)%9];
        color[7]=hex[(index+1)%9];
    }

    int again;
    scanf("%d",&again);
    system("cls");
    if(again)
    {

        PlaySound(NULL, NULL, 0);
        main();
    }
    else
    {
        index=0;
        printf("\n\n\n\n\n\n");
        char bye []= "\t\t\t\t\tG A M E O V E R\n\n\n\n\t\t\t\t     Thank you for playing.";
        for (int i=0; i<strlen(bye); i++)
        {

            printf("%c",bye[i]);
            fflush(stdout);
            usleep(100);


            system(color);

            index++;
            //color[6]=hex[(index)%6];
            color[7]=hex[(index+1)%6];
        }
    }
    printf("\n\n\n\n\n");
}
