
#include <stdio.h>
struct Laptop{
    char Company[100];
    float MonitorSize;
    int Touch;
    int price;
};
typedef struct Laptop Laptop;
struct ITStore{
    char name[100];
    char location[100];
    Laptop available[100];
    int LaptopNum;
};
typedef struct ITStore ITStore;
void readLaptop(Laptop *s){
    scanf("%s%f%d%d",s->Company,&s->MonitorSize,&s->Touch,&s->price);
}
void readITStore(ITStore *k){
    scanf("%s%s%d",k->name,k->location,&k->LaptopNum);
    for(int i = 0; i < (k->LaptopNum); i++){
        readLaptop(&k->available[i]);
    }
}
void print(ITStore a) {
    printf("%s %s\n", a.name, a.location);
    for (int i = 0; i < (a.LaptopNum); i++) {
        if((int)(a.available[i].MonitorSize*10)%10==0){
            printf("%s %.0f %d\n", a.available[i].Company, a.available[i].MonitorSize, a.available[i].price);
        }
        else{
            printf("%s %.1f %d\n", a.available[i].Company, a.available[i].MonitorSize, a.available[i].price);
        }
    }
}
void najeftina_ponuda(ITStore *s,int n){
    int minPrice = 20000000, index; //ne eleganten nacin za minimumot!!!
    for(int i=0; i < n; i++) {
        for (int j = 0; j < s->LaptopNum; j++) {
            if ((s[i].available[j].price < minPrice) && (s[i].available[j].Touch == 1)) {
                minPrice = s[i].available[j].price;
                index = i;
            }
        }
    }
    printf("Najeftina ponuda ima prodavnicata:\n%s %s\n",s[index].name,s[index].location);
    printf("Najniskata cena iznesuva: %d",minPrice);
}
int main(){
    ITStore s[100];
    int n;
    scanf("%d",&n);
    for(int i=0; i < n;i++){
        readITStore(&s[i]);
    }
    for(int i=0; i < n;i++){
        print(s[i]);
    }
    najeftina_ponuda(s,n);
    return 0;
}