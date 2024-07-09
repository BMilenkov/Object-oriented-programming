
#include <iostream>
#include <cstring>
using namespace std;
class WebPage{
private:
    char url[100];
    char *content;
public:
    //2in1 Consturctor
    WebPage(char *url="https://finki.ukim.mk",char *content= "FINKI'SS WP"){
        strcpy(this->url,url);
        this->content = new char [strlen(content)+1];
        strcpy(this->content,content);
    }
    //COPY CONSTRUCTOR!
    WebPage(const WebPage & wp){
        strcpy(this->url,wp.url);
        this->content = new char [strlen(wp.content)+1];
        strcpy(this->content,wp.content);
    }
    //Operator =
    WebPage & operator =(const WebPage & wp) {
        if (this != &wp) {
            strcpy(this->url, wp.url);
            delete[] content;
            this->content = new char[strlen(wp.content) + 1];
            strcpy(this->content, wp.content);
        }
        *this;
    }
    //Destructor
    ~WebPage(){
        delete [] content;
    }
    void print(){
        cout<<"URL: "<<url<<endl;
        cout<<"Content: "<<content<<endl;
    }
    bool equal(const WebPage &wp){
        return strcmp(this->url,url)==0;
    }
    friend class WebServer; //Access to all private components!
};
class WebServer{
private:
    char name[30];
    WebPage *webpages;
    int n;
public:
    //Contructor
    WebServer(char *name){
        strcpy(this->name,name);
        this->n = 0;
        this->webpages = new WebPage [n];
    }
    //Copy-constructor
    WebServer(const WebServer &ws){
        strcpy(this->name,name);
        this->n = ws.n;
        this->webpages = new WebPage[n];
        for(int i=0; i < n;i++){
            this->webpages[i] = ws.webpages[i];
        }
    }
    // Operator = is made!
    WebServer & operator=(const WebServer &ws){
        if(this!=&ws){
            delete [] this->webpages;
            this->webpages = new WebPage[ws.n];
            this->n = ws.n;
            strcpy(this->name,ws.name);
            for(int i=0; i < n;i++){
                this->webpages[i] = ws.webpages[i];
            }
        }
        return *this;
    }//Destructor
    ~WebServer(){
        delete [] webpages;
    }
    void addPage(const WebPage &wp) {
     //Check if we already have the same WP in our WS!
        for (int i = 0; i < n; i++) {
            //if(webpages[i].equal(wp))
            //  return;
            //}
            if (strcmp(webpages[i].url, wp.url) == 0)
                return;
        }
        WebPage *temp = new WebPage[n+1];
            for(int i=0; i < n; i++){
                temp[i] = webpages[i];
            }
            temp[n++] = wp;
            delete [] webpages;
        webpages = temp;
    }
    void print(){
        cout<<"Server's NameFile: "<<name<<endl;
        cout<<"LIST ALL PAGES ON THE SERVER: "<<endl;
        for(int i = 0; i < n; i++){
            cout<<webpages[i].url<<endl<<webpages[i].content<<endl;
        }
    }
};
int main(){
    WebPage wp1 ("http://www.google.com", "The search engine");
    WebPage wp2 ("http://www.finki.ukim.mk", "FINKI");
    WebPage wp3 ("http://www.time.mk", "Daily news");
    WebServer ws(" Server ");
    ws.addPage(wp1) ;
    ws.addPage(wp2);
    ws.addPage(wp3) ;
    ws.print();
    cout<<wp1.equal(wp2)<<endl;
    /*
    WebPage wp;
    wp.print();
    WebPage wp1;
    wp1 = wp; //OPERATOR =
    wp1.print();
    WebPage wp3(wp); //Copy -constructor!
    wp3.print();
    cout<<wp1.daliseIsti(wp3);
    return 0;
*/
}