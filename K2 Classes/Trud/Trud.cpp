#include <iostream>
#include <cstring>

using namespace std;

class Exception{
public:
    void ShowMessage(){
        cout<<"Ne moze da se vnese dadeniot trud"<<endl;
    }
};
class Trud{
private:
    char type; // C- conference , J -journal
    int YearOfIssue;

    void Copy(const Trud &T){
        this->type = toupper(T.type);
        this->YearOfIssue = T.YearOfIssue;
    }
public:
    Trud( char type='C' , int YearOfIssue=1899){
        this->type = toupper(type);
        this->YearOfIssue = YearOfIssue;
    }
    char getType(){
        return type;
    }
    int getYearOfIssue(){
        return YearOfIssue;
    }
    Trud & operator = (const Trud &T){
        if(this!=&T){
            Copy(T);
        }
        return *this;
    }
   friend istream & operator >>(istream &in, Trud &T){
        in>>T.type>>T.YearOfIssue;
       return in;
    }
};
class Student{
protected:
    char name[30];
    int index;
    int year; //godina na upis;
    int marks[20];
    int passedExams;
public:
    Student(){}
    Student(char *name, int index, int year, int *marks, int passedExams){
        strcpy(this->name,name);
        this->index = index;
        this->year = year;
        for(int i =0 ;i< passedExams ;i++){
            this->marks[i] = marks[i];
        }
        this->passedExams = passedExams;
    }
    virtual double rang(){
        double sum=0.0;
        for(int i = 0 ;i < passedExams ;i++){
           sum+=marks[i];
        }
        return sum/passedExams;
    }
   friend ostream & operator <<(ostream &out, Student &s){
        out << s.index << " " << s.name << " " << s.year << " " << s.rang() << endl;
       return out;
    }
    int GodinaNaUpis(){
        return year;
    }
    int GetIndex(){
        return index;
    }
};
class PhDStudent : public  Student{
private:
    Trud *trudovi;
    int count;
    static int conferential;
    static int journal;
public:
    PhDStudent(){}
    PhDStudent(char *name, int index, int year, int *marks, int passedExams
    ,Trud *trudovi , int count) : Student(name, index,year,marks,passedExams){
       this->trudovi = new Trud[count];
       int okey=0;
       for(int i=0;i < count ; i++){
           try {
               if (trudovi[i].getYearOfIssue() < year) {
                   throw Exception();
               }
               else{
                   this->trudovi[okey] = trudovi[i];
                   okey++;
               }
           } catch (Exception e){
               e.ShowMessage();
           }
       }
       this->count = okey;
    }
    static void setC(int C){
        conferential = C;
    }
    static void setJ(int J){
        journal = J;
    }
    double rang(){
        double suma= 0.0;
        for(int i=0 ; i < count ;i++){
            if(trudovi[i].getType()=='C')
                suma+=conferential;
            else if(trudovi[i].getType()=='J')
                suma+=journal;
            }
        return Student::rang() + suma;
    }
    PhDStudent & operator +=(Trud &T){
        if(T.getYearOfIssue() < GodinaNaUpis()){
            throw Exception();
        }
        Trud *temp = new Trud[count+1];
        for(int i=0;i<count;i++){
            temp[i] = trudovi[i];
        }
        trudovi[count++] = T;
        delete [] trudovi;
        trudovi = temp;
        return *this;
    }
    friend ostream & operator <<(ostream &out,PhDStudent &PHD){
        out<<PHD.index<<" "<<PHD.name<<" "<<PHD.year<<" "<<PHD.rang()<<endl;
        return out;
    }
};
int PhDStudent::conferential = 1;
int PhDStudent :: journal =3;

int main(){
    int testCase;
    cin >> testCase;

    int god, indeks, n, god_tr, m, n_tr;
    int izbor; //0 za Student, 1 za PhDStudent
    char ime[30];
    int oceni[50];
    char tip;
    Trud trud[50];

    if (testCase == 1){
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        Student s(ime, indeks, god, oceni, n);
        cout << s;

        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++){
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 2) {
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i < m; i++) {
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0) {
                niza[i] = new Student(ime, indeks, god, oceni, n);
            } else {
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++) {
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;
        bool hasFound = true;
        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot +=
        try {
            for (int i = 0; i < m; i++) {
                PhDStudent *casted = dynamic_cast<PhDStudent *>(niza[i]);
                if (casted) {
                    if (casted->GetIndex() == indeks) {
                        *casted += t;
                        hasFound = false;
                    }
                }
            }
            if(hasFound){
                cout<<"Ne postoi PhD student so indeks "<<indeks<<endl;
            }
        } catch (Exception e) {
            e.ShowMessage();
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 3){
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += od Testcase 2
        bool hasFound = true;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot +=
        try {
            for (int i = 0; i < m; i++) {
                PhDStudent *casted = dynamic_cast<PhDStudent *>(niza[i]);
                if (casted) {
                    if (casted->GetIndex() == indeks) {
                        *casted += t;
                        hasFound = false;
                    }
                }
            }
            if(hasFound){
                cout<<"Ne postoi PhD student so indeks"<<indeks<<endl;
            }
        } catch (Exception e) {
            e.ShowMessage();
        }

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 4){
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++){
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 5){
        cout << "===== Testiranje na isklucoci ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += i spravete se so isklucokot
        bool hasFound = true;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot +=
        try {
            for (int i = 0; i < m; i++) {
                PhDStudent *casted = dynamic_cast<PhDStudent *>(niza[i]);
                if (casted) {
                    if (casted->GetIndex() == indeks) {
                        *casted += t;
                        hasFound = false;
                    }
                }
            }
            if(hasFound){
                cout<<"Ne postoi PhD student so indeks"<<indeks<<endl;
            }
        } catch (Exception e) {
            e.ShowMessage();
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 6){
        cout << "===== Testiranje na static clenovi ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        int conf, journal;
        cin >> conf;
        cin >> journal;

        //postavete gi soodvetnite vrednosti za statickite promenlivi

       PhDStudent::setC(conf);
       PhDStudent::setJ(journal);

        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }

    return 0;
}