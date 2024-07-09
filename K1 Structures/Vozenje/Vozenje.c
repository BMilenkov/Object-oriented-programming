#include <stdio.h>
struct Vozenje{
    char nameRide[100];
    int duration;
    float price;
    int discount;
};
typedef struct Vozenje Vozenje;
struct ZabavenPark{
    char namePark[100];
    char location[100];
    Vozenje rides[100];
    int cntrides;
};
typedef struct ZabavenPark ZabavenPark;
void readVozenje(Vozenje *k){
    scanf("%s %d %f %d",k->nameRide,&k->duration,&k->price,&k->discount );
}
void readPark(ZabavenPark *k){
    scanf("%s %s %d",k->namePark,k->location,&k->cntrides);
    for (int i=0; i< k->cntrides; i++){
        readVozenje(&k->rides[i]);
    }
}
void printVozenje(Vozenje k){
    printf("%s %d %.2f\n",k.nameRide,k.duration,k.price);
}
void printPark(ZabavenPark k){
    printf("%s %s\n",k.namePark,k.location);
    for (int i=0; i< k.cntrides; i++){
        printVozenje(k.rides[i]);
    }
}
void najdobar_park(ZabavenPark *park,int n){
    int br,index,maxbr=0, VKduration,maxVKduration=0;
        for(int i = 0 ;i < n; i++){
            br = 0;
            VKduration=0;
            for(int j=0; j < park[i].cntrides;j++){
                if(park[i].rides[j].discount)
                    br++;
                VKduration+=park[i].rides[j].duration;
            }
            if(br>maxbr){
                maxbr=br;
                index = i;
                maxVKduration = VKduration;
            }
            if(br==maxbr){
                if(VKduration > maxVKduration){
                    maxbr=br;
                    index = i;
                    maxVKduration = VKduration;
                }
            }
        }
    printf("Najdobar park: %s %s", park[index].namePark,park[index].location);
}
int main(){
    int n;
    ZabavenPark park[10];
    scanf("%d",&n);
    for (int i = 0; i < n; i++) {
        readPark(park+i);
    }
    for (int i = 0; i < n; i++) {
        printPark(park[i]);
    }
    najdobar_park(park,n);
    return 0;
}
