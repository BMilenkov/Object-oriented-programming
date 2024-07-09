
#include <stdio.h>
#include <string.h>
struct Igrac{
    char name[15];
    int game_level;
    int points;
};
typedef struct Igrac Igrac;
struct KompjuterskaIgra {
    char name[20];
    int counts;
    Igrac players[30];
};
typedef struct KompjuterskaIgra KompjuterskaIgra;
void readPlayer(Igrac *p){
    scanf("%s %d %d",p->name,&p->game_level,&p->points);
}
void readGame(KompjuterskaIgra *p){
    scanf("%s %d",p->name,&p->counts);
    for(int i=0; i < p->counts;i++){
        readPlayer(&p->players[i]);
    }
}
void najdobarIgrac(KompjuterskaIgra *lista, int n){
    char namegame[20];
    strcpy(namegame,lista[0].name);
    int users=0;
    for(int i = 1; i < n; i++){
       if(lista[i].counts > users){
           users = lista[i].counts;
           strcpy(namegame,lista[i].name);
        }
    }
    int max = 0;
    char nameplayer[20];
    for(int i=0; i<n ;i++){
        for(int j=0 ; j<lista[i].counts;j++){
            if(lista[i].players[j].points > max){
                max = lista[i].players[j].points;
                strcpy(nameplayer,lista[i].players[j].name);
            }
        }
    }
    printf("Najdobar igrac e igracot so korisnicko ime %s koj ja igra igrata %s",nameplayer,namegame);
}
int main(){
    KompjuterskaIgra game[100];
    int n;
    scanf("%d",&n);
    for(int i=0; i<n; i++){
        readGame(&game[i]);
    }
    najdobarIgrac(game,n);
    return 0;
}