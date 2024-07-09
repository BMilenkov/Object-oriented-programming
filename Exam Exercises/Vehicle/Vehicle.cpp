#include <iostream>
#include <cstring>
using namespace std;
class Vehicle{
private:
    char reg[9];
    char *name;
    int location;
    int capacity;
    float kms;
    void Copy(const Vehicle &V){
        name = new char[strlen(V.name)+1];
        strcpy(this->name, V.name);
        strcpy(this->reg, V.reg);
        this->location = V.location;
        this->capacity = V.capacity;
        this->kms = V.kms;
    }
public:
    Vehicle(char *reg = "", char *name="", int location=0, int capacity=0, float kms=0){
        name = new char[strlen(name)+1];
        strcpy(this->name, name);
        strcpy(this->reg, reg);
        this->location = location;
        this->capacity = capacity;
        this->kms = 0;
    }
    Vehicle(const Vehicle &V){
        Copy(V);
    }
    Vehicle &operator=(const Vehicle &V){
        if(this!=&V){
            delete [] name;
            Copy(V);
        }
        return *this;
        }
        friend class RideApp;
};
class RideApp{
private:
   char Name[20];
   Vehicle *vozila;
   int count;
   void Copy(const RideApp& RA){
       strcpy(this->Name,RA.Name);
       this->count = RA.count;
       vozila = new Vehicle[RA.count];
       for(int i=0; i<RA.count ;i++){
           this->vozila[i] = RA.vozila[i];
       }
   }
public:
    RideApp(char *Name=""){
        strcpy(this->Name,Name);
        this->count = 0;
        vozila = new Vehicle[0];
    }
    RideApp(const RideApp &RA){
       Copy(RA);
   }
    void signUpVehicle(const Vehicle &V){
       for(int i=0;i < count;i++){
           if(!strcmp(vozila[i].reg,V.reg))
               return;
       }
       Vehicle *temp = new Vehicle [count + 1];
       for(int i=0; i<count ;i++){
           temp[i] = vozila[i];
       }
       temp[count++] = V;
       delete [] vozila;
       vozila = temp;
   }
    void addRide(int area,int distancekms,int capacity){
        int minarea=9999999,id;
        float minkms=99999.9;
        for(int i=0;i<count;i++){
            if(vozila[i].capacity>=capacity){
                int razlika=abs(vozila[i].location-area);
                if(razlika<minarea){
                    minarea=razlika;
                    id=i;
                }
                else if(minarea==razlika && vozila[i].kms<minkms){
                    minkms= vozila[i].kms;
                    id=i;
                }
            }
        }
        vozila[id].location=area;
        vozila[id].kms+=distancekms;
    }
};