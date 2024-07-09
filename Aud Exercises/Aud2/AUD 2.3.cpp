
#include <iostream>
#include <cstring>
using namespace std;
class Datum{
private:
    int day;
    int month;
    int year;
public:
    Datum(){
        day = 1;
        month= 1;
        year= 2021;
    }
    Datum(int _day, int _month, int _year){
        day = _day;
        month = _month;
        year = _year;
    }
    ~Datum(){} //DESTRUCTOR!!!
    Datum( const Datum &d){
     // cout<<"COPY- CONSTRUCTOR for Datum IS CALLED!!!"<<endl;
        day = d.day;
        month = d.month;
        year = d.year;
    }
    int getDay(){return day;}
    int getMonth(){return month;}
    int getYear(){return year;}
    void print(){
        cout<<"DAY:"<<day<<" Month:"<<month<<" Year:"<<year<<endl;
    }
    int is_equal(const Datum &datum){
        if(day==datum.day)
            return 1;
        else
            return 0;
    }
};
class Vraboten{
private:
    char name[20];
    int salary;
    Datum datum;
public:
    Vraboten(){
        strcpy(name,"");
        salary = 0;
    }
    Vraboten(char *_name, int _salary, Datum _datum){
        strcpy(name,_name);
        salary = _salary;
        datum = _datum;
    }
    ~Vraboten(){} //DESTRUCTOR
    Vraboten(const Vraboten &d){

        strcpy(name,d.name);
        salary = d.salary;
        datum = d.datum;
    }
    void print(){
        cout<<"NAME:"<<name<<" Salary:"<<salary<<" Datum:"<<datum.getDay()<<"."<<datum.getMonth()<<"."<<datum.getYear()<<endl;
    }
    int getSalary(){
        return salary;
    }
    Datum getDate(){
        return datum;
    }
};
Vraboten highestPaid(Vraboten *employees, int n){
    int max = 0, index;
    for(int i=0; i < n; i++){
        if(employees[i].getSalary() > max){
            max = employees[i].getSalary();
            index = i;
        }
    }
    return employees[index];
}
int compare(Datum d1, Datum d2) {
    if (d1.getYear() > d2.getYear()) return 1;
    else if (d1.getYear() < d2.getYear()) return 2;
    else if (d1.getMonth() > d2.getMonth()) return 1;
    else if (d1.getMonth() < d2.getMonth()) return 2;
    else if (d1.getDay() > d2.getDay()) return 1;
    else if (d1.getDay() < d2.getDay()) return 2;
    else return 0;
}
Vraboten YoungestEmployee(Vraboten *employees, int n) {
    Datum date = employees[0].getDate();
    int index;
   for(int i=0; i<n ;i++){
       if(compare(employees[i].getDate(), date)==1){
          date = (employees[i].getDate());
            index = i;
       }
   }
    return employees[index];
}
int main(){
    Vraboten employees[50];
    int n;
    char name[20];
    int salary,day,month,year;
    cin>>n;
    for(int i=0; i < n; i++) {
        cin >> name >> salary>>day>>month>>year;
        Datum date(day,month,year);
        employees[i] = Vraboten(name, salary,date);
    }
    cout<< "NAJPLATEN VRABOTEN E: "<<endl;
    highestPaid(employees,n).print();
    cout<< "NAJMLAD VRABOTEN E: "<<endl;
    YoungestEmployee(employees,n).print();

    return 0;
}