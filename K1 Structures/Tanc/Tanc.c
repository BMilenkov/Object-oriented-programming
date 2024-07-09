
#include <stdio.h>
#include <string.h>
struct Tanc{
    char name[15];
    char country[15];
};
typedef struct Tanc Tanc;
struct Tancer{
    char ime[20];
    char prezime[20];
    Tanc dances[5];
};
typedef struct Tancer Tancer;
void readTanc(Tanc *k){
    scanf("%s %s",k->name,k->country);
}
void readTancer(Tancer *k){
    scanf("%s %s",k->ime,k->prezime);
    for(int i=0; i < 3;i++){
        readTanc(&k->dances[i]);
    }
}
void tancuvanje(Tancer *t, int n, char *zemja){
    for(int i=0; i<n ;i++){
        for(int j=0 ; j < 3 ; j++){
            if(!strcmp(t[i].dances[j].country,zemja)){
                printf("%s %s, %s\n",t[i].ime,t[i].prezime,t[i].dances[j].name);
                break;
            }
        }
    }
}
int main(){
    Tancer dancer[10];
    int n;
    char country[15];
    scanf("%d",&n);
    for(int i=0; i < n; i++){
        readTancer(&dancer[i]);
    }
    scanf("%s",country);
    tancuvanje(dancer,n,country);
    return 0;
}
