#include <iostream>
#include <cstring>

using namespace std;
enum typeC{
    smartphone,
    laptop
};
class Device{
private:
    char model[100];
    typeC type;
    static double duration;
    int year;
    void Copy(const Device &D){
        strcpy(this->model, D.model);
        this->type = D.type;
        this->year = D.year;
    }
public:
    explicit Device(char *model="", typeC type = smartphone, int year = 1990){
        strcpy(this->model, model);
        this->type = type;
        this->year = year;
    }
     double getDuration() const{
        if(year > 2015 && type == laptop)
            return duration + 2.0 + 2.0;
        else if(year > 2015 || type == laptop)
            return duration + 2.0;
        else
            return duration;
    }
    Device(const Device &D){
        Copy(D);
    }
    Device& operator =(const Device &D){
        if (this!=&D){
            Copy(D);
        }
        return *this;
    }
     friend ostream &operator <<(ostream &out, const Device &D){
        out<<D.model<<endl;
        if(D.type==smartphone)
            out<<"Mobilen "<<D.getDuration()<<endl;
        else
            out<<"Laptop "<<D.getDuration()<<endl;
         return out;
    }
    int getYear() const{
        return year;
    }
    static void setPocetniCasovi(double hours){
        duration = hours;
    }

};
class InvalidProductionDate{
public:
   void showMessage(){
        cout<<"Невалидна година на производство"<<endl;
    }
};
//static member out of a class!
double Device::duration = 1.0;
class MobileServis{
    char adress[100];
    Device *devices;
    int count;
    void Copy(const MobileServis &MS){
        strcpy(this->adress,MS.adress);
        this->count = MS.count;
        devices = new Device[MS.count];
        for(int i=0 ;i< MS.count ;i++){
            this->devices[i] = MS.devices[i];
        }
    }
public:
    MobileServis(char *adress = ""){
        strcpy(this->adress,adress);
        this->count = 0;
        devices = nullptr;
    }
    MobileServis (const MobileServis &MS){
        Copy(MS);
    }
    MobileServis &operator =(const MobileServis &MS){
        if(this != &MS){
            delete [] devices;
            Copy(MS);
        }
        return *this;
    }
    MobileServis & operator +=(const Device &D){
        if(D.getYear() > 2019 || D.getYear() < 2000){
            throw InvalidProductionDate();
        }
        Device *temp = new Device[count+1];
        for(int i =0;i < count;i++){
            temp[i] = devices[i];
        }
        temp[count++] = D;
        delete [] devices;
        devices = temp;
        return *this;
    }
    void pecatiCasovi(){
        cout<<"Ime: "<<adress<<endl;
        for(int i=0;i<count;i++){
            cout<<devices[i];
        }
    }
};
int main()
{
    int testCase;
    cin >> testCase;
    char ime[100];
    int tipDevice;
    int godina;
    int n;
    Device devices[50];
    if (testCase == 1){
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> tipDevice;
        cin >> godina;
        Device ig(ime, (typeC)tipDevice, godina);
        cin>>ime;
        MobileServis t(ime);
        cout<<ig;
    }
    if (testCase == 2){
        cout << "===== Testiranje na operatorot += ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (typeC)tipDevice, godina);
            t+=tmp;
        }
        t.pecatiCasovi();
    }
    if (testCase == 3){
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            try { cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (typeC)tipDevice, godina);
            t+=tmp;
        }
            catch (InvalidProductionDate e){
            e.showMessage();
            }
        }
        t.pecatiCasovi();
    }
    if (testCase == 4){
        cout <<"===== Testiranje na konstruktori ======"<<endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
            try {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (typeC)tipDevice, godina);
            t+=tmp;
        }
        catch (InvalidProductionDate e){
            e.showMessage();
        }
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }
    if (testCase == 5){
        cout << "===== Testiranje na static clenovi ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (typeC)tipDevice, godina);

            t+=tmp;
        }
        t.pecatiCasovi();
        cout << "===== Promena na static clenovi ======" << endl;
        Device::setPocetniCasovi(2);
        t.pecatiCasovi();
    }

    if (testCase == 6){
        cout << "===== Testiranje na kompletna funkcionalnost ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++) {
            try {
                cin >> ime;
                cin >> tipDevice;
                cin >> godina;
                Device tmp(ime, (typeC) tipDevice, godina);
                t += tmp;
            }
            catch (InvalidProductionDate e){
             e.showMessage();
            }
        }
        Device::setPocetniCasovi(3);
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }
    return 0;
}

