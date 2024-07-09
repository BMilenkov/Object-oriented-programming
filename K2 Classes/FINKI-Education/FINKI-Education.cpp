#include <iostream>
#include <cstring>
using namespace std;

class Book { //ABSTRACT CLASS
protected:
    char ISBN[20];
    char tittle [50];
    char author[30];
    double price;
public:
    Book(char *ISBN ="", char *tittle="", char *author="", double price=0.0) {
        strcpy(this->ISBN , ISBN);
        strcpy(this->tittle,tittle);
        strcpy(this->author,author);
        this->price = price;
    }
    virtual double bookPrice()=0;
    bool operator > (Book &b1){
        return bookPrice()>b1.bookPrice();
    }
    Book(const Book &B)
    {
        strcpy(this->ISBN , B.ISBN);
        strcpy(this->tittle,B.tittle);
        strcpy(this->author,B.author);
        this->price =B. price;
    }
    friend ostream & operator<<(ostream &out, Book &t) {
        out << t.ISBN << ": " << t.tittle << ", " << t.author << " " << t.bookPrice() << endl;
        return out;
    }
        virtual ~Book(){}
};
class OnlineBook: public Book{
private:
    char *URL;
    int size;
public:
    OnlineBook(char *ISBN, char *tittle,
               char *author, double price,
               char *URL ,int size) : Book(ISBN,tittle,author,price){
        this->URL = new char[strlen(URL)+1];
        strcpy(this->URL,URL);
        this->size = size;
    } OnlineBook(){}

    double bookPrice(){
        if(size>20)
            return price*1.2;
        return price;
    }
    void setISBN(char *isbn){
        strcpy(this->ISBN ,isbn);
    }
    OnlineBook(const OnlineBook &OB): Book(OB) {
        this->URL = new char[strlen(OB.URL)+1];
        strcpy(this->URL,OB.URL);
        this->size = OB.size;
    }
    OnlineBook& operator =(const OnlineBook &OB) {
        if (this != &OB) {

            strcpy(this->ISBN, OB.ISBN);
            strcpy(this->tittle, OB.tittle);
            strcpy(this->author, OB.author);
            this->price = OB.price;
            delete[] URL;
            this->URL = new char[strlen(OB.URL) + 1];
            strcpy(this->URL, OB.URL);
            this->size = OB.size;
        }
        return *this;
    }
    ~OnlineBook(){
        delete [] URL;
    }
};
class PrintBook: public Book{
private:
    float weight;
    bool available;
public:
    PrintBook(char *ISBN, char *tittle,
              char *author, double price,
              float weight, bool available) :Book(ISBN,tittle,author,price) {
        this->weight = weight;
        this->available = available;
    }
    double bookPrice(){
        if(weight > 0.7)
            return price*1.15;
        return price;
    }
    PrintBook(const PrintBook &PB) : Book(PB){
        this->weight = PB.weight;
        this->available = PB.available;
    }
    PrintBook& operator =(const PrintBook &PB) {
        if (this != &PB) {

            strcpy(this->ISBN, PB.ISBN);
            strcpy(this->tittle, PB.tittle);
            strcpy(this->author, PB.author);
            this->price = PB.price;
            this->weight = PB.weight;
            this->available = PB.available;
        }
        return *this;
    }
    ~PrintBook(){}
};
void mostExpensiveBook (Book** books, int n){
    int online=0, index;
    int printed = 0;
    for(int i=0;i<n;i++){
       OnlineBook *castedOB= dynamic_cast<OnlineBook*>(books[i]);
        if(castedOB == nullptr){
            ++printed;
        }
        else
            ++online;
    }
    double max = books[0]->bookPrice();
    for(int i=0;i<n;i++){
        if(books[i]->bookPrice() > max){
            max = books[i]->bookPrice();
            index = i;
        }
    }
    cout<<"FINKI-Education"<<endl;
    cout<<"Total number of online books: "<<online<<endl;
    cout<<"Total number of print books: "<<printed<<endl;
    cout<<"The most expensive book is: "<<endl;
    cout<<*books[index];
}
int main(){

    char isbn[20], title[50], author[30], url[100];
    int size, tip;
    float price, weight;
    bool inStock;
    Book  **books;
    int n;

    int testCase;
    cin >> testCase;

    if (testCase == 1){
        cout << "====== Testing OnlineBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++){
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> url;
            cin >> size;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new OnlineBook(isbn, title, author, price, url, size);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 2){
        cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
        cin >> isbn;
        cin.get();
        cin.getline(title, 50);
        cin.getline(author, 30);
        cin >> price;
        cin >> url;
        cin >> size;
        cout << "CONSTRUCTOR" << endl;
        OnlineBook ob1(isbn, title, author, price, url, size);
        cout << ob1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        OnlineBook ob2(ob1);
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
        cout << "OPERATOR =" << endl;
        ob1 = ob2;
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
    }
    if (testCase == 3){
        cout << "====== Testing PrintBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++){
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> weight;
            cin >> inStock;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 4){
        cout << "====== Testing method mostExpensiveBook() ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i<n; i++){

            cin >> tip >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            if (tip == 1) {

                cin >> url;
                cin >> size;

                books[i] = new OnlineBook(isbn, title, author, price, url, size);

            }
            else {
                cin >> weight;
                cin >> inStock;

                books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            }
        }

        mostExpensiveBook(books, n);
    }

    for (int i = 0; i<n; i++) delete books[i];
    delete[] books;
    return 0;
}
