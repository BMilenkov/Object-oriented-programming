#include <iostream>
#include <cstring>
using namespace std;
class SpaceObject{
private:
    char name[100];
    char type[100];
    int distanceFromEarth;
public:
    SpaceObject(char *name="", char *type="", int distanceFromEarth=0){
        strcpy(this->name,name);
        strcpy(this->type,type);
        this->distanceFromEarth = distanceFromEarth;
    }
    SpaceObject(const SpaceObject &SO){
        strcpy(this->name,SO.name);
        strcpy(this->type,SO.type);
        this->distanceFromEarth = SO.distanceFromEarth;
    }
    ~SpaceObject(){}
    void print(){
        cout<<name<<" ("<<type<<") - distance: "<<distanceFromEarth<<" light years away from Earth"<<endl;
    }
    int getDFE(){
        return distanceFromEarth;
    }
    char *getName(){
        return name;
    }
    friend class Alien;
};
class Alien{
private:
    char nameAlien[100];
    int age;
    char homePLanet[100];
    int numObj;
    SpaceObject spaceObjects[10];
public:
    Alien(){
        strcpy(nameAlien,"");
        age=0;
        numObj = 0;
        strcpy(this->homePLanet,"");
    }
    Alien(char *nameAlien, int age, char *homePlanet,int numObj, SpaceObject *spaceObjects){
        strcpy(this->nameAlien,nameAlien);
        this->age=age;
        this->numObj = numObj;
        strcpy(this->homePLanet,homePlanet);
        for(int i=0; i<numObj; i++){
            this->spaceObjects[i] = spaceObjects[i];
        }
    }
    Alien(const Alien &alien) {
        strcpy(this->nameAlien, alien.nameAlien);
        this->age = alien.age;
        this->numObj = alien.numObj;
        strcpy(this->homePLanet, alien.homePLanet);
        for (int i = 0; i < alien.numObj; i++) {
            this->spaceObjects[i] = alien.spaceObjects[i];
        }
    }
    ~Alien(){}
    SpaceObject getObjectClosestToEarth(){
        SpaceObject x;
        int min, flag = 1;
        for(int i=0; i <numObj; i++){
            if(flag){
            min = spaceObjects[i].getDFE();
            flag=0;
        }
            else if(!flag){
                if(spaceObjects[i].getDFE() < min){
                min = spaceObjects[i].getDFE();
                x = spaceObjects[i];
                }
            }
        }
        return x;
    }
    void print(){
        cout<<"Alein NameFile: "<<nameAlien<<endl;
        cout<<"Alien age: "<<age<<endl;
        cout<<"Alien homePLanet: "<<homePLanet<<endl;
        cout<<"Favourite space object closest to earth: ";
       getObjectClosestToEarth().print();
    }
};
/*
int main(){
    // MAINOT E MOJ- no need of set methods
    char AN[100], HomePlanet[100];
    int n, age;
    cin>>AN>>age>>HomePlanet>>n;
    char SCN[100], type[100];
    int distance;
    SpaceObject SC[n];
    for(int i=0; i<n; i++){
        cin>>SCN>>type>>distance;
        SC[i] = SpaceObject(SCN,type,distance);
    }
    Alien alien(AN,age,HomePlanet,SC,n);
    alien.print();
    return 0;
}
 */
int main()
{
    char name[100], homePlanet[100];
    int age, numObj;
    cin>>name>>age>>homePlanet>>numObj;
    //Testing default constructor for SpaceObject
    SpaceObject spaceObjects[numObj];
    for(int i=0; i<numObj; i++)
    {
        char spaceObjectName[100], spaceObjectType[100];
        int distanceFromEarth;
        cin>>spaceObjectName>>spaceObjectType>>distanceFromEarth;
        //Testing constructor with arguments for SpaceObject
        spaceObjects[i]=SpaceObject(spaceObjectName, spaceObjectType, distanceFromEarth);
    }
    //Testing default constructor for Alien
    Alien alien;
    //Testing constructor with arguments for Alien and copy constructor for Alien
    alien=Alien(name, age, homePlanet, numObj, spaceObjects);
    Alien alien2 = Alien(alien);

    alien2.print();
    return 0;
}