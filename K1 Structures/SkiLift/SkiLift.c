#include <stdio.h>
#include <string.h>
struct Igrac{
    char name[15];
    int level;
    int points;
};
typedef struct Igrac Igrac;
void readIgrac(Igrac *p){
    scanf("%s %d %d",p->name,&p->level,&p->points);
}
struct KompjuterskaIgra{
    char name[20];
    Igrac igraci[30];
    int number;
};
typedef struct KompjuterskaIgra KompjuterskaIgra;
void readKompIgra(KompjuterskaIgra *p){
    scanf("%s %d",p->name,&p->number);
        for (int i = 0; i < p->number; ++i) {
            readIgrac(&p->igraci[i]);
        }
    }
void najdobarIgrac(KompjuterskaIgra *lista, int n){
    int mostpopular=0 ,index;
    for(int i=0;i<n;i++){
       if(lista[i].number>mostpopular){
           mostpopular = lista[i].number;
           index = i;
        }
    }
    char name[10];
    char gameName[20];
    int maxpoints ,index1;
    for(int j=0; j<lista[index].number;j++){
        if(lista[index].igraci[j].points > maxpoints){
            maxpoints = lista[index].igraci[j].points;
           // strcpy(name,lista[index].igraci[j].name);
            //strcpy(gameName,lista[index].name);
            index1 = j;
        }
        if(lista[index].igraci[j].points == maxpoints){
            if(lista[index].igraci[j].level > lista[index].igraci[index1].level){
                index1 = j;
            }
        }
    }
    printf("Najdobar igrac e igracot so korisnicko ime %s koj ja igra igrata %s",lista[index].igraci[index1].name,lista[index].name);
}
int main(){
    KompjuterskaIgra igri[10];
    int n;
    scanf("%d",&n);
    for (int i = 0; i < n; i++) {
        readKompIgra(&igri[i]);
    }
    najdobarIgrac(igri,n);
    return 0;
}