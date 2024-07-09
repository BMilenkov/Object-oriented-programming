#include <stdio.h>
#include <string.h>
struct Proizvod{
    char BC[20];
    int price;
    int number;
};
typedef struct Proizvod Proizvod;
struct Narachka{
    char name[15];
    Proizvod products[10];
    int naracani[10];
    int count;
};
typedef struct Narachka Narachka;
void readProizvod(Proizvod *p){
    scanf("%s %d %d ", p->BC, &p->price,&p->number);
}
void readNarachka(Narachka *p){
    scanf("%s %d", p->name,&p->count);
    for(int i=0;i < p->count ;i++){
        readProizvod(&p->products[i]);
    }
    for(int i=0;i < p->count ;i++){
        scanf("%d" ,&p->naracani[i]);
    }
}
void pecatiFaktura(Narachka n) {
    printf("Faktura za %s", n.name);
    for (int i = 0; i < n.count; i++) {
        if (n.products[i].number < n.naracani[i])
            printf("Fakturata ne moze da se izgotvi");
        return;
    }
    Proizvod tmp;
    for (int i = 0; i < n.count; i++) {
        for (int j = 0; j < n.count; j++) {
            if (strcmp(n.products[i].BC, n.products[j].BC) < 0) {
                tmp = n.products[i];
                n.products[i] = n.products[j];
                n.products[j] = tmp;
            }
        }
    }
    for (int i = 0; i < n.count; i++){
        printf("%s %d %d %d",n.products[i].BC,n.products[i].price ,n.naracani[i],n.naracani[i]*n.products[i].price);
    }
}
int main(){
    Narachka narachka;
    readNarachka(&narachka);
    pecatiFaktura(narachka);
    return 0;
}