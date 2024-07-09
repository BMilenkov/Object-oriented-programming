#include <stdio.h>
#define DENOVI 5
#define NEDELI 4
struct RabotnaNedela{
       int r_casovi[DENOVI];
};
typedef struct RabotnaNedela RabotnaNedela;
struct Rabotnik{
    char ime[50];
    RabotnaNedela rabotnaNedela [NEDELI];
};
typedef struct Rabotnik Rabotnik;
void readRabotnaNedela(RabotnaNedela *k){
    for(int i=0 ; i < DENOVI;i++){
        scanf("%d",&k->r_casovi[i]);
    }
}
void readRabotnik(Rabotnik *k){
    scanf("%s",k->ime);
    for(int i=0; i < NEDELI; i++){
        readRabotnaNedela(&k->rabotnaNedela[i]);
    }
}
void printRabotnaNedela(RabotnaNedela k){
    for(int i=0 ; i < DENOVI;i++){
        printf("%d ",k.r_casovi[i]);
    }
    printf("\n");
}
void printRabotnik(Rabotnik k){
    printf("%s\n",k.ime);
    for(int i=0; i < NEDELI; i++){
        printRabotnaNedela(k.rabotnaNedela[i]);
    }
}
void table(Rabotnik *r, int n){
    int sum,VKsum;
    printf("TABLE\n");
    printf("Rab\t1\t2\t3\t4\tVkupno\n");
    for(int i=0; i < n;i++){
        VKsum=0;
        printf("%s\t",r[i].ime);
        for(int j=0; j < NEDELI;j++){
            sum = 0;
            for(int k=0; k < DENOVI;k++){
                sum+=r[i].rabotnaNedela[j].r_casovi[k];
            }
            VKsum+=sum;
            printf("%d\t",sum);
        }
        printf("%d\n",VKsum);
        }
    }
int maxNedela(Rabotnik *r){
    int maxsum=0, sum,index;
    for(int j=0; j < NEDELI;j++){
        sum = 0;
        for(int k=0; k < DENOVI;k++){
            sum+=r->rabotnaNedela[j].r_casovi[k];
        }
        if(sum > maxsum){
        maxsum = sum;
        index = (j+1);
        }
    }
    return index;
}
int main(){
    int n;
    Rabotnik workers[20];
    scanf("%d", &n);
    for(int i=0; i<n ;i++){
        readRabotnik(&workers[i]);
    }
    //for(int i=0; i<n ;i++){
    //    printRabotnik(worker[i]);
    //}
    table(workers,n);
    printf("MAX NEDELA NA RABOTNIK: %s\n%d",workers[n/2].ime,maxNedela(&workers[n/2]));
    return 0;
}
