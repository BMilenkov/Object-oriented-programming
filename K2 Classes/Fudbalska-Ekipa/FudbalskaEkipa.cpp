//
// Created by user on 5/22/2023.
//
#include <iostream>
#include <cstring>
using namespace std;

class FudbalskaEkipa{
protected:
    char coach[100];
    int matchesGoals[10];
public:
    FudbalskaEkipa(char *coach, int *matchesGoals){
        strcpy(this->coach,coach);
        for(int i=0;i<10;i++){
            this->matchesGoals[i] = matchesGoals[i];
        }
    }
    virtual int uspeh()=0;
    FudbalskaEkipa & operator +=(int goals){
        int temp[10];
        for(int i=0;i<9;i++){
            temp[i] = matchesGoals[i+1];
        }
        temp[9] = goals;
        for(int i=0;i<10;i++){
            matchesGoals[i] = temp[i];
        }
        return *this;
    }
    bool operator > (FudbalskaEkipa &FT){
        return uspeh() > FT.uspeh();
    }
    virtual char* getName()=0;
    friend ostream &operator <<(ostream &out, FudbalskaEkipa &R){
       return out<<R.getName()<<endl<<R.coach<<endl<<R.uspeh()<<endl;
    }
};
class Klub:public FudbalskaEkipa{
private:
    char ClubName[20];
    int titles;
public:
    Klub(char *coach, int *matchesGoals, char *ClubName,int titles):
    FudbalskaEkipa(coach,matchesGoals){
        strcpy(this->ClubName, ClubName);
        this->titles = titles;
    }
    int uspeh(){
        int sum=0;
        for(int i=0;i<10;i++){
            sum+=matchesGoals[i];
        }
        return sum*3 + titles*1000;
    }
   char *getName(){
       return ClubName;
    }
};

class Reprezentacija:public FudbalskaEkipa{
private:
    char RepName[20];
    int competitions;
public:
    Reprezentacija(char *coach, int *matchesGoals,char *RepName, int competitions):
            FudbalskaEkipa(coach,matchesGoals){
        strcpy(this->RepName,RepName);
        this->competitions = competitions;
    }
    int uspeh(){
        int sum=0;
        for(int i=0;i<10;i++){
            sum+=matchesGoals[i];
        }
        return sum*3 + competitions * 50;
    }
    char *getName(){
        return RepName;
    }
};

FudbalskaEkipa *najdobarTrener(FudbalskaEkipa **ekipi, int n){
    int max=0, index;
    for(int i=0;i<n;i++){
        if(ekipi[i]->uspeh()>max){
            max = ekipi[i]->uspeh();
            index = i;
        }
    }
    cout<<*ekipi[index];
}

int main() {
    int n;
    cin >> n;
    FudbalskaEkipa **ekipi = new FudbalskaEkipa*[n];
    char coach[100];
    int goals[10];
    char x[100];
    int tg;
    for (int i = 0; i < n; ++i) {
        int type;
        cin >> type;
        cin.getline(coach, 100);
        cin.getline(coach, 100);
        for (int j = 0; j < 10; ++j) {
            cin >> goals[j];
        }
        cin.getline(x, 100);
        cin.getline(x, 100);
        cin >> tg;
        if (type == 0) {
            ekipi[i] = new Klub(coach, goals, x, tg);
        } else if (type == 1) {
            ekipi[i] = new Reprezentacija(coach, goals, x, tg);
        }
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== DODADI GOLOVI =====" << endl;
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        cout << "dodavam golovi: " << p << endl;
        *ekipi[i] += p;
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== NAJDOBAR TRENER =====" << endl;
    najdobarTrener(ekipi, n);
    for (int i = 0; i < n; ++i) {
        delete ekipi[i];
    }
    delete [] ekipi;
    return 0;
}