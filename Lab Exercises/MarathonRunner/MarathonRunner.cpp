#include <iostream>
#include <cstring>
using namespace std;
class MarathonRunner{
protected:
    char *name;
    char country[40];
    double average_speed;
    double kms;
    double hours;
    void Copy(const MarathonRunner &M){
        this->name = new char [strlen(M.name)+1];
        strcpy(this->name ,M.name);
        strcpy(this->country ,  M.country);
        this->average_speed = M.average_speed;
        this->kms = M.kms;
        this->hours = M.hours;
    }
public:
    MarathonRunner(char *name="", char *country="", double average_speed =0.0,double kms=0.0,double hours=0.0){
        this->name = new char [strlen(name)+1];
        strcpy(this->name ,name);
        strcpy(this->country ,country);
        this->average_speed = average_speed;
        this->kms = kms;
        this->hours = hours;
    }
    MarathonRunner(const MarathonRunner &MR){
        Copy(MR);
    }
    MarathonRunner & operator=(const MarathonRunner &M){
        if(this!=&M){
            delete [] name;
            Copy(M);
        }
        return *this;
    }
    ~MarathonRunner(){
        delete [] name;
    }
    double rating(){
        return ((average_speed*0.45) + (kms*0.3) + (hours*0.25));
    }
    void print(){
        cout<<name<<" - "<<country<<endl;
        cout<<"Average speed: "<<average_speed<<endl;
        cout<<"Total distance: "<<kms<<endl;
        cout<<"Total time: "<<hours<<endl;
        cout<<"Rating: "<<rating()<<endl;
    }
};
class  EliteMarathonRunner: public MarathonRunner{
private:
    double averages;
    double totalL;
    double totalT;
    void Copy(const EliteMarathonRunner &EMR){
        this->averages = EMR.averages;
        this->totalL = EMR.totalL;
        this->totalT = EMR.totalT;
    }
public:
    EliteMarathonRunner(char *name="", char *country="", double average_speed =0.0,double kms=0.0,double hours=0.0, double averages =0.0,  double totalL = 0.0,double totalT =0.0): MarathonRunner(name,country,average_speed,kms, hours){
        this->averages = averages;
        this->totalT = totalT;
        this->totalL = totalL;

    }
    EliteMarathonRunner(const MarathonRunner &M, double averages,  double totalL,double totalT ): MarathonRunner(M){
        this->averages = averages;
        this->totalT = totalT;
        this->totalL = totalL;
    }
    EliteMarathonRunner(const EliteMarathonRunner &EMR): MarathonRunner(EMR){
        Copy(EMR);
    }
    EliteMarathonRunner &operator=(const EliteMarathonRunner &EMR){
        if(this!= &EMR){
            MarathonRunner::Copy(EMR);
            Copy(EMR);
        }
        return *this;
    }
    double eliteRating(){
        return 0.70*averages + 0.10*totalL + 0.30*totalT;
    }
    double rating(){
        return (eliteRating() + MarathonRunner::rating())/2;
    }
    void print(){
        MarathonRunner::print();
        cout<<"Elite Rating: "<<eliteRating()<<endl;
        cout<<"New Rating: "<<rating()<<endl;
    }

};

int main() {

    char name[50];
    char country[40];
    double avgSpeed;
    double distance;
    double time;
    double EliteavgSpeed;
    double Elitedistance;
    double Elitetime;

    MarathonRunner * RUNNERs = new MarathonRunner[5];
    EliteMarathonRunner * elRUNNERs = new EliteMarathonRunner[5];
    int n;
    cin >> n;

    if (n == 1) {

        cout << "MARATHON RUNNERS:" << endl;
        cout << "=====================================" << endl;
        for (int i = 0; i < 5; ++i) {
            cin >> name >> country >> avgSpeed >> distance >> time;
            RUNNERs[i] = MarathonRunner(name,country,avgSpeed,distance,time);
            RUNNERs[i].print();
        }
    }
    else if (n == 2) {

        for (int i=0; i < 5; ++i){
            cin >> name >> country >> avgSpeed >> distance >> time;
            cin >> EliteavgSpeed >> Elitedistance >> Elitetime;
            RUNNERs[i] = MarathonRunner(name,country,avgSpeed,distance,time);
            elRUNNERs[i] = EliteMarathonRunner(RUNNERs[i],EliteavgSpeed,Elitedistance,Elitetime);
        }

        cout << "NBA RUNNERS:" << endl;
        cout << "=====================================" << endl;
        for (int i=0; i < 5; ++i)
            RUNNERs[i].print();

        cout << "ELITE RUNNERS:" << endl;
        cout << "=====================================" << endl;
        for (int i=0; i < 5; ++i)
            elRUNNERs[i].print();

    }
    else if (n == 3) {

        for (int i=0; i < 5; ++i){
            cin >> name >> country >> avgSpeed >> distance >> time;
            cin >> EliteavgSpeed >> Elitedistance >> Elitetime;
            elRUNNERs[i] = EliteMarathonRunner(name, country, avgSpeed, distance, time,
                                               EliteavgSpeed,Elitedistance,Elitetime);
        }
        cout << "ELITE RUNNERS:" << endl;
        cout << "=====================================" << endl;
        for (int i=0; i < 5; ++i)
            elRUNNERs[i].print();

    }

    delete [] RUNNERs;
    delete [] elRUNNERs;
}
