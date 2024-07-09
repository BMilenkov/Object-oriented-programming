#include <stdio.h>
#include <string.h>
struct Voz{
    char relacija[50];
    float kms;
    int br_patnici;
};
typedef struct Voz Voz;
struct ZeleznickaStanica{
    char grad[20];
    Voz vozovi[30];
    int broj_na_vozovi;
};
typedef struct ZeleznickaStanica ZeleznickaStanica;
void readVoz(Voz *p){
    scanf("%s %f %d",p->relacija, &p->kms, &p->br_patnici);
}
void readZS(ZeleznickaStanica *p){
    scanf("%s %d",p->grad ,&p->broj_na_vozovi);
    for(int i=0; i< p->broj_na_vozovi ;i++){
        readVoz(&p->vozovi[i]);
    }
}
void najkratkaRelacija(ZeleznickaStanica* zs, int n, char* grad){
   int minKMS=0,flag =0, index, index1;
    for(int i=0 ;i<n; i++) {
        for (int j = 0; j < zs[i].broj_na_vozovi; j++) {
            if (!strcmp(zs[i].grad, grad)) {
                if (!flag) {
                    minKMS = zs[i].vozovi[j].kms;
                    index = i;
                    index1 = j;
                    flag = 1;
                } else if (flag) {
                    if (zs[i].vozovi[j].kms <= minKMS) {
                        minKMS = zs[i].vozovi[j].kms;
                        index = i;
                        index1 = j;
                    }
                }
            }
        }
    }
    printf("Najkratka relacija: %s (%d km)",zs[index].vozovi[index1].relacija,minKMS);
}
int main(){
    ZeleznickaStanica ZS[100];
    int n;
    char grad[20];
    scanf("%d", &n);
    for(int i=0; i<n; i++){
        readZS(&ZS[i]);
    }
    scanf("%s ", &grad);
    najkratkaRelacija(ZS,n,grad);
    return 0;
}