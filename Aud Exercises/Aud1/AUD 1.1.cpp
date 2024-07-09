#include<iostream>
#include<cstring>
using namespace std;
class Book{
private:
    char *ime{};
    int *isbn{},pages{};
public:
    Book()= default;
    Book(char *ime,int *isbn,int pages){
        this->ime=new char[strlen(ime) + 1];
        strcpy(this->ime, ime);
        this->pages=pages;
        this->isbn=new int[5];
        for(int i=0;i<5;i++){
            this->isbn[i]=isbn[i];
        }

    }
    Book(const Book &b){
        ime=new char[strlen(b.ime) + 1];
        strcpy(ime, b.ime);
        isbn=new int[5];
        for(int i=0;i<5;i++){
            isbn[i]=b.isbn[i];
        }
        pages=b.pages;
    }
    ~Book(){
        delete[]ime;
        delete[]isbn;
    }
    Book &operator=(const Book &b){
        if(this!=&b){
            delete[]isbn;
            delete[]ime;
            ime=new char[strlen(b.ime) + 1];
            strcpy(ime, b.ime);
            isbn=new int[5];
            for(int i=0;i<5;i++){
                isbn[i]=b.isbn[i];
            }
            pages=b.pages;
        }
        return *this;
    }
    bool operator==(Book &b){
        for(int i=0;i<5;i++){
            if(isbn[i]!=b.isbn[i])return false;
        }
        return true;
    }
    friend ostream &operator<<(ostream &out,const Book &b){
        out << "Title: " << b.ime << " ISBN: [ ";
        for(int i=0;i<5;i++){
            out<<b.isbn[i]<<" ";
        }
        out<<"]"<<endl;
        return out;
    }
    friend class BorrowABook;
};
class BorrowABook{
private:
    char library[100]{};
    Book *books{};
    int num{};
public:
    explicit BorrowABook(char *library=""){
        strcpy(this->library,library);
        books= nullptr;
        num=0;
    }
    BorrowABook(const BorrowABook &b){
        strcpy(library,b.library);
        num=b.num;
        books=new Book[num];
        for(int i=0;i<num;i++)this->books[i]=b.books[i];
    }
    BorrowABook &operator=(const BorrowABook &b){
        if(this!=&b){
            delete[]books;
            strcpy(library,b.library);
            num=b.num;
            books=new Book[num];
            for(int i=0;i<num;i++)this->books[i]=b.books[i];
        }
        return *this;
    }
    ~BorrowABook(){
        delete[]books;
    }
    BorrowABook &operator+=(const Book &b){
        Book *tmp=new Book[num+1];
        for(int i=0;i<num;i++){
            tmp[i]=books[i];
        }
        tmp[num++]=b;
        delete[]books;
        books=tmp;
        return *this;
    }
    BorrowABook &operator-=(const Book &b){
        int flag=0;
        int id;
        for(int i=0;i<num;i++){
            if(books[i].operator==(const_cast<Book &>(b))){
                flag=1;
                id=i;
                break;
            }
        }
        if(flag) {
            Book *tmp = new Book[num - 1];
            int br = 0;
            for (int i = 0; i < num; i++) {
                if (i != id) {
                    tmp[br++] = books[i];
                }
            }
            num--;
            delete[]books;
            books = tmp;
            return *this;
        }
        return *this;

    }
    void printNumberOfPages(int max){
        cout<<library<<endl;
        for(int i=0;i<num;i++){
            if(books[i].pages > max){
                cout<<books[i];
            }
        }
    }

};

int main()
{
    BorrowABook library("FINKI-Library");
    int n;
    cin>>n;

    for (int i=0;i<n;i++)
    {
        char title[100];
        int isbn[5];
        int pages;

        cin>>title;

        for (int i=0;i<5;i++)
            cin>>isbn[i];

        cin>>pages;

        Book nov=Book(title,isbn,pages);

        //adding a new book
        library+=nov;

    }
    //the book which has the same isbn as some previous one
    char title[100];
    int isbn[5];
    int pages;
    cin>>title;
    for (int i=0;i<5;i++)
        cin>>isbn[i];
    cin>>pages;

    Book greshka=Book(title,isbn,pages);

    //deleting a book
    library-=greshka;

    library.printNumberOfPages(150);

    return 0;
}