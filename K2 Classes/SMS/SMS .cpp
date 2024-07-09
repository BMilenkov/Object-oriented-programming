#include <iostream>
#include <cstring>
using namespace std;

class SMS{ //abstract class
protected:
    double price;
    char SentNumber[30];
    const static double percentage1; //all sms
    static double percentage2; //regular
    static double percentage3; // special
public:
    SMS(double price=0.0, char *SentNumber=""){
        this->price = price;
        strcpy( this->SentNumber ,SentNumber);
    }
    virtual double SMS_cena() = 0;
    char *getNumber()
    {
        return SentNumber;
    }
    friend ostream & operator<<(ostream &out,SMS &SMS){
        return out<<"Tel: "<<SMS.SentNumber<<" - cena: "<<SMS.SMS_cena()<<"den."<<endl;
    }
    virtual ~SMS(){}
};
const double SMS::percentage1 = 0.18;
double SMS::percentage2 = 3; //regular
double SMS ::percentage3 = 1.5; //special!
class RegularSMS : public SMS{
private:
    char MessageText[1000];
    bool roaming;
public:
    RegularSMS(char *SentNumber="",double price=0.0,
               char *MessageText="",
               bool roaming = true) : SMS(price, SentNumber){
        strcpy(this->MessageText ,MessageText);
        this->roaming = roaming;
    }
    double SMS_cena() override{
        int count;
        if(strlen(MessageText)%160==0){
            count = strlen(MessageText)/160;
        }
        else if (strlen(MessageText)%160 !=0){
            count =  strlen(MessageText)/160 + 1;
        }
        if(roaming){
            return count*(price*percentage2 + price);
        }
        else if(!roaming){
            return count*(price*percentage1 + price);
        }
    }
   static void set_rProcent(int p){
        percentage2 = (double) p/100;
    }
};
class SpecialSMS : public SMS{
private:
  bool charity;
public:
    SpecialSMS(char *SentNumber="",double price=0.0,
               bool charity = true) : SMS(price, SentNumber){
        this->charity = charity;
    }
    double SMS_cena() override{
        if(charity){
           return price;
        }
        else
            return price + price * percentage3;
    }
   static void set_sProcent( int p){
       percentage3 = (double)p/100;
    }
};
void vkupno_SMS(SMS** poraka, int n){
    int regular = 0;
    double RegularPrice = 0.0;
    int special = 0 ;
    double SpecialPrice = 0.0;
    for(int i=0; i<n ;i++){
        SpecialSMS *SSMS= dynamic_cast<SpecialSMS *>(poraka[i]);{
            if(SSMS == nullptr){
                regular++;
            RegularPrice+=poraka[i]->SMS_cena();
        }
            else if(SSMS != nullptr){
            special ++;
            SpecialPrice+=poraka[i]->SMS_cena();
            }
        }
    }
    cout<<"Vkupno ima "<<regular<<" regularni SMS poraki i nivnata cena e: "<<RegularPrice<<endl<<
          "Vkupno ima "<<special<<" specijalni SMS poraki i nivnata cena e: "<<SpecialPrice<<endl;
}
int main(){

    char tel[20], msg[1000];
    float cena;
    float price;
    int p;
    bool roam, hum;
    SMS  **sms;
    int n;
    int tip;

    int testCase;
    cin >> testCase;

    if (testCase == 1){
        cout << "====== Testing RegularSMS class ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++){
            cin >> tel;
            cin >> cena;
            cin.get();
            cin.getline(msg, 1000);
            cin >> roam;
            cout << "CONSTRUCTOR" << endl;
            sms[i] = new RegularSMS(tel, cena, msg, roam);
            cout << "OPERATOR <<" << endl;
            cout << *sms[i];
        }
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 2){
        cout << "====== Testing SpecialSMS class ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++){
            cin >> tel;
            cin >> cena;
            cin >> hum;
            cout << "CONSTRUCTOR" << endl;
            sms[i] = new SpecialSMS(tel, cena, hum);
            cout << "OPERATOR <<" << endl;
            cout << *sms[i];
        }
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 3){
        cout << "====== Testing method vkupno_SMS() ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i<n; i++){

            cin >> tip;
            cin >> tel;
            cin >> cena;
            if (tip == 1) {

                cin.get();
                cin.getline(msg, 1000);
                cin >> roam;

                sms[i] = new RegularSMS(tel, cena, msg, roam);

            }
            else {
                cin >> hum;

                sms[i] = new SpecialSMS(tel, cena, hum);
            }
        }

        vkupno_SMS(sms, n);
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 4){
        cout << "====== Testing RegularSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        cin >> tel;
        cin >> cena;
        cin.get();
        cin.getline(msg, 1000);
        cin >> roam;
        sms1 = new RegularSMS(tel, cena, msg, roam);
        cout << *sms1;

        cin >> tel;
        cin >> cena;
        cin.get();
        cin.getline(msg, 1000);
        cin >> roam;
        cin >> p;
        RegularSMS::set_rProcent(p);
        sms2 = new RegularSMS(tel, cena, msg, roam);
        cout << *sms2;

        delete sms1, sms2;
    }
    if (testCase == 5){
        cout << "====== Testing SpecialSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        cin >> tel;
        cin >> cena;
        cin >> hum;
        sms1 = new SpecialSMS(tel, cena, hum);
        cout << *sms1;

        cin >> tel;
        cin >> cena;
        cin >> hum;
        cin >> p;
        SpecialSMS::set_sProcent(p);
        sms2 = new SpecialSMS(tel, cena, hum);
        cout << *sms2;

        delete sms1, sms2;
    }

    return 0;
}
