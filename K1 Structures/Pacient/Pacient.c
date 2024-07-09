
#include <stdio.h>
struct Pacient{
    char name[100];
    int zdravstveno;
    int br_pregledi;
};
typedef struct Pacient Pacient;
struct MaticenDoktor{
    char name[100];
    int br_pacienti;
    Pacient pacients[100];
    float cena;
};
typedef struct MaticenDoktor MaticenDoktor;
void readPacient(Pacient *k){
    scanf("%s %d %d",k->name,&k->zdravstveno,&k->br_pregledi);
}
void readDoktor(MaticenDoktor *k){
    scanf("%s %d %f",k->name,&k->br_pacienti,&k->cena);
    for(int i=0 ; i < k->br_pacienti; i++){
        readPacient(&k->pacients[i]);
    }
}
void printPacient(Pacient k){
    printf("%s %d %d\n",k.name,k.zdravstveno,k.br_pregledi);
}
void printDoktor(MaticenDoktor k){
    printf("%s %d %f\n",k.name,k.br_pacienti,k.cena);
    for(int i=0 ; i < k.br_pacienti; i++){
        printPacient(k.pacients[i]);
    }
}
void najuspesen_doktor(MaticenDoktor *k, int n){
    float zarabotka, maxzarabotka=0;
    int index, maxpregledi= 0,VKpregledi, i,j,pregledi,maxVKpregledi;
    for(int i=0; i < n;i++){
        zarabotka=0;
        pregledi=0;
        VKpregledi=0;
     for( int j=0;j < k[i].br_pacienti;j++){
            if(!k[i].pacients[j].zdravstveno){
                float proizvod = k[i].pacients[j].br_pregledi * k[i].cena;
                zarabotka+= proizvod;
                pregledi+= k[i].pacients[j].br_pregledi;
            }
         VKpregledi+= k[i].pacients[j].br_pregledi;
        }
     if(zarabotka > maxzarabotka) {
         maxzarabotka = zarabotka;
         index = i;
         maxpregledi = pregledi;
         maxVKpregledi = VKpregledi;
        }
     if(zarabotka == maxzarabotka){
         if(VKpregledi > maxVKpregledi){
             maxzarabotka = zarabotka;
             index=i;
             maxVKpregledi = VKpregledi;
         }
     }
    }
    printf("%s %.2f %d",k[index].name,maxzarabotka,maxVKpregledi);
}
int main(){
    MaticenDoktor doc[100];
    int n;
    scanf("%d",&n);
    for(int i=0; i < n;i++){
        readDoktor(&doc[i]);
        //printDoktor(doc[i]);
    }
    najuspesen_doktor(doc,n);
    return 0;
}
