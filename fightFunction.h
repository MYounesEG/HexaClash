#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "classes.h"

int checkWiner(Takim team1,Takim team2)
{
    if (team1.totalHealth<=0)
        return 2;

    else if(team2.totalHealth<=0)
        return 1;

    else return 0;
}

int damage(int act,int defence,int maxs){
    return act*(1-defence/maxs);
}

int netHealt(int health,int damage1,int unite ){
    int damage1= damage1;
    return health-(damage1/unite);
}

void updateTotalHealth(Takim team1,Takim team2)
{
    for(int i=0;i<team1.birimSayisi;i++){
        team1.totalHealth+=team1.birimler[i].saglik*team1.birimler[i].sayi;
        team2.totalHealth+=team2.birimler[i].saglik*team2.birimler[i].sayi;
    }

}


void updateAttactDefence(Takim team1, Takim team2){
    for(int i=0;team1.birimSayisi;i++){
        team1.birimler[i].saldiri = team1.birimler[i].saldiri;
    }
}

void FIGHT(Takim insan_imparatorlugu,Takim ork_legi)
{
    updateTotalHealth(insan_imparatorlugu,ork_legi);

    /*
    do{
        insanSaldirisi_or();
        
        orksaldirisi();
        

    }while(checkWiner(...));
    */
}
