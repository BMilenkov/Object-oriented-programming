
#include <iostream>
#include <string.h>
using namespace std;
class EMail{
private:
    char sender[100];
    char reciever[100];
    char subject[50];
    char body[300];
public:
    EMail(char *_sender ="hasd", char *_reciever="sds",char *_subject="sda", char *_body="sds hi"){
        strcpy(sender,_sender);
        strcpy(reciever,_reciever);
        strcpy(subject,_subject);
        strcpy(body,_body);
    }
    // copy -> constructor is made!
    EMail(const EMail &mail){
        strcpy(sender,mail.sender);
        strcpy(reciever,mail.reciever);
        strcpy(subject,mail.subject);
        strcpy(body,mail.body);

    }
    void print_mail(){
        cout<<"FROM : "<<sender<<endl;
        cout<<"TO : "<<reciever<<endl;
        cout<<"-----------------------------"<<endl;
        cout<<"Subject : "<<subject<<endl;
        cout<<"-----------------------------"<<endl;
        cout<<"Body : "<<endl;
        cout<<body<<endl;
    }
};
int main(){
    char sender[100];
    char reciever[100];
    char subject[50];
    char body[100];
   cin>>sender>>reciever>>subject;
    //cin.getline(subject,50);
    cin.getline(body,300);
    EMail mail(sender,reciever,subject,body);
    mail.print_mail();
    return 0;
}