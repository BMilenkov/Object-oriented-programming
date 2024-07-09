
#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;
enum type{
    denars = 1,
    euros,
    dolars
};
class Deposit{
    double amount;
    type type;
    double interest; //KAMATA
    int duration;
public:
    Deposit(double amount =0,enum type type = denars,double interest=0.1, int duration=1){
    this->amount = amount;
        this->type =type;
        this->interest= interest;
        this->duration = duration;
    }
    Deposit(const Deposit &D){
        this->amount = D.amount;
        this->type =D.type;
        this->interest= D.interest;
        this->duration = D.duration;
    }
    double totalValue(){
        return amount * pow(1+interest,duration);
    }
    double interestAmount(){
        return totalValue() - amount;
    }
    void print() {
        /*
         * [тип на депозит]
            Total Principal:  [почетен влог]
            Total Value: [вкупен износ по истекот на времетраењето]
            Total Interest: [износ на каматата која се заработува]
         * */
        if (type == 1)
            cout << "Denarski depozit" << endl;
        else if (type == 2)
            cout << "Devizen depozit vo EUR" << endl;
        else
            cout << "Devizen depozit vo USD" << endl;
        cout << "Total Principal: " << amount << endl;
        cout << "Total Value: " << totalValue() << endl;
        cout << "Total Interest: " << interestAmount() << endl;
    }
    enum type getType() {
        return type;
    }
    double getInterest(){
        return interest;
    }
};
class Branch{
private:
    char address[100];
    Deposit *deposits;
    int count;
    void Copy(const Branch &B){
        strcpy(this->address, B.address);
        this->count = B.count;
        for(int i = 0; i< B.count; i++){
            this->address[i] = B.address[i];
        }
    }
public:
    Branch(char *address = ""){
        strcpy(this->address, address);
        //this->deposits = nullptr;
        this->deposits = new Deposit[0];
        this->count = 0;
    }
    Branch(const Branch &B){
        Copy(B);
    }
    Branch & operator = (const Branch &B){
        if(this!=&B){
            delete [] deposits;
            Copy(B);
        }
        return *this;
    }
    ~Branch(){
        delete [] deposits;
    }
    void newDeposit(Deposit& d){
        Deposit *temp = new Deposit [count+1];
        for(int i =0; i< count;i++){
            temp[i] = deposits[i];
        }
        temp[count++] = d;
        delete [] deposits;
        deposits = temp;
    }
   void depositAnalysis(int v) {
       if (v < 1 || v > 3) {
           cout << "Error!" << endl;
           return;
       } else {
           int found = 0, index;
           double max = 0;
           for (int i = 0; i < count; i++) {
               if (deposits[i].getType() == (type) v) {
                   found++;
                   if (deposits[i].getInterest() > max) {
                       max = deposits[i].getInterest();
                       index = i;
                   }
               }
           }
           if (!found)
               cout << "Ne postoi aktiven deposit vo EUR/USD/MKD"<< endl;
           else
               deposits[index].print();
       }
   }
    void print() {
        /*
         *   [Адреса на филијала]:
  1. [Кредит1]
  2. [Кредит2]
  3. [Кредит3]
         */
        cout << address <<": " << endl;
        for (int i = 0; i < count; i++) {
            cout << i + 1 << ".";
            deposits[i].print();
            cout << endl;
        }
    }
    void removeAllDepositsFromType(const type &type){
        int counter;
        for(int i=0;i<count;i++){
            if(deposits[i].getType()==type){
                counter++;
            }
        }
        Deposit *temp = new Deposit[count-counter];
        for(int i=0;i<count;i++){
            if(deposits[i].getType()!=type)
                temp[i] = deposits [i];
        }
        count-=counter;
        delete [] deposits;
        deposits = temp;
    }
};
int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;
    int n, tip, godini;
    double iznos, kamata;
    char adresa[100];

    if (testCase == 1) {
        cout << "===== Testiranje na klasata Deposit ======" << endl;
        cin >> iznos >> kamata >> godini;
        cin >> tip; // 1-MKD, 2-EUR, 3-USD
        Deposit l(iznos, (type) tip, kamata, godini);
        cout << "Deposit constructor OK" << endl;
    } else if (testCase == 2) {
        cout << "===== Testiranje na klasata Deposit so dopolnitelni metodi ======" << endl;
        cin >> iznos >> kamata >> godini;
        cin >> tip; // 1-MKD, 2-EUR, 3-USD
        Deposit l(iznos, (type) tip, kamata, godini);
        l.print();

    } else if (testCase == 3) {
        cout << "===== Testiranje na klasata Branch so metodot print() ======" << endl;
//        Branch b("Strumica");
//        b.print();
    } else if (testCase == 4) {
        cout << "===== Testiranje na klasata Branch so metodot newDeposit() ======" << endl;
        Branch b("Strumica");
        cin >> n;
        for (int i = 0; i < n; i++) {
            //cin.get();
            cin >> iznos >> kamata >> godini;
            cin >> tip; // 1-MKD, 2-EUR, 3-USD
            Deposit l(iznos, (type) tip, kamata, godini);
            b.newDeposit(l);
        }
        b.print();
    } else if (testCase == 5) {
        cout << "===== Testiranje na metodot depositAnalysis() od klasata Branch ======" << endl;
        Branch b("Gevgelija");
        cin >> n;
        for (int i = 0; i < n; i++) {
            //cin.get();
            cin >> iznos >> kamata >> godini;
            cin >> tip; // 1-MKD, 2-EUR, 3-USD
            Deposit l(iznos, (type) tip, kamata, godini);
            b.newDeposit(l);
        }
        b.depositAnalysis(1);
        b.depositAnalysis(2);
        b.removeAllDepositsFromType((type) 2);
        b.depositAnalysis(2);
        b.depositAnalysis(3);
        b.depositAnalysis(4);
    } else if (testCase == 6) {
        cout << "===== Testiranje kompletna funkcionalnost ======" << endl;
        Branch b("Kavadarci");
        cin >> n;
        for (int i = 0; i < n; i++) {
            //cin.get();
            cin >> iznos >> kamata >> godini;
            cin >> tip; // 1-MKD, 2-EUR, 3-USD
            Deposit l(iznos, (type) tip, kamata, godini);
            b.newDeposit(l);
        }
        b.depositAnalysis(3);
        Branch b_new = b;
        b.print();
        b_new.print();
        //cin.get();
        cin >> iznos >> kamata >> godini;
        cin >> tip; // 1-MKD, 2-EUR, 3-USD
        Deposit l(iznos, (type) tip, kamata, godini);
        b.newDeposit(l);
        b.depositAnalysis(3);
        b.print();
        b_new.print();
    }
    return 0;
}