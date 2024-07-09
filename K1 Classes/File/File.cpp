#include<iostream>
#include<cstring>
using namespace std;
enum Extension{
    txt, pdf, exe
};
class File{
private:
    char *name;
    Extension ext;
    char *owner;
    int size;
    void Copy(const File &file){
        this->name = new char[strlen(file.name)+1];
        strcpy(this->name,file.name);
        this->owner = new char[strlen(file.owner)+1];
        strcpy(this->owner,file.owner);
        this->size = file.size;
        this->ext = file.ext;
    }
public:
    //2in1 constructing
    File(char *name=" ", char *owner=" ", int size=0, Extension ext = (Extension)0){
       this->name = new char[strlen(name)+1];
        strcpy(this->name,name);
        this->owner = new char[strlen(owner)+1];
        strcpy(this->owner,owner);
        this->size = size;
        this->ext = ext;
    }
    File(const File &file){
        Copy(file);
    }
    File & operator=(const File &file){
        if(this!=&file) {
            delete[] name;
            delete[] owner;
            Copy(file);
        }
        return *this;
    }
    ~File(){
        delete [] name;
        delete [] owner;
    }
    void  print(){
        cout<<"File NameFile: "<<name;
        if(ext==0){
            cout<<".pdf";
        }
        else if(ext==1){
            cout<<".txt";
        } else
            cout<<".exe";
        cout<<endl;
        cout<<"File owner: "<<owner<<endl;
        cout<<"File size: "<<size<<endl;
    }
    bool equals(const File &that){
        if(strcmp(this->name,that.name)==0 && strcmp(this->owner,that.owner)==0
        && this->ext==that.ext)
            return true;
        else
            return false;
    }
    bool equalsType(const File & that){
        if(strcmp(this->name,that.name)==0  && this->ext==that.ext)
            return true;
        else
            return false;
    }
};
class Folder{
private:
    char *NameFolder;
    int NumOfFiles;
    File *files;
    void Copy(const Folder &folder){
        this->NameFolder = new char[strlen(folder.NameFolder) + 1];
        strcpy(this->NameFolder, folder.NameFolder);
        this->NumOfFiles=folder.NumOfFiles;
        this->files = new File[folder.NumOfFiles];
        for (int i = 0; i < NumOfFiles; i++) {
            this->files[i]=folder.files[i];
        }
    }
public:
    Folder(){}
    Folder(const char* name){
        this->NameFolder = new char[strlen(name) + 1];
        strcpy(this->NameFolder, name);
        this->NumOfFiles=0;
        //files = new File[0];
        files = nullptr;
    }
    ~Folder(){
        delete [] files;
        delete [] NameFolder;
    }
    Folder(const Folder &folder){
        Copy(folder);
    }
    Folder &operator=(const Folder &folder){
        if(this!=&folder) {
            delete[] files;
            delete[] NameFolder;
            Copy(folder);
        }
        return *this;
    }
    void print() {
        cout << "Folder NameFile: " << this->NameFolder << endl;
        for(int i = 0 ; i < NumOfFiles; i++)
            files[i].print();
    }
    void add(const File &file){
        File *temp = new File [NumOfFiles+1];
        for(int i=0; i < NumOfFiles ;i++){
            temp[i] = files[i];
        }
        temp[NumOfFiles++] = file;
        delete [] files;
        files = temp;
    }
    void remove(const File &file) {
        int count = 0;
        for(int i=0; i<NumOfFiles; i++) {
            if(files[i].equals(file) == false) {
                count++;
            }
        }
        File * tmp = new File[count];
        count = 0;
        for (int i = 0; i < NumOfFiles; i++) {
            if (files[i].equals(file)==false) {
                tmp[count++] = files[i];
            }
        }
        delete [] files;
        files = tmp;
        NumOfFiles = count;
    }
};
int main() {
    char fileName[20];
    char fileOwner[20];
    int ext;
    int fileSize;

    int testCase;
    cin >> testCase;
    if (testCase == 1) {
        cout << "======= FILE CONSTRUCTORS AND = OPERATOR =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File created = File(fileName, fileOwner, fileSize, (Extension) ext);
        File copied = File(created);
        File assigned = created;

        cout << "======= CREATED =======" << endl;
        created.print();
        cout << endl;
        cout << "======= COPIED =======" << endl;
        copied.print();
        cout << endl;
        cout << "======= ASSIGNED =======" << endl;
        assigned.print();
    }
    else if (testCase == 2) {
        cout << "======= FILE EQUALS & EQUALS TYPE =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File first(fileName, fileOwner, fileSize, (Extension) ext);
        first.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File second(fileName, fileOwner, fileSize, (Extension) ext);
        second.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File third(fileName, fileOwner, fileSize, (Extension) ext);
        third.print();

        bool equals = first.equals(second);
        cout << "FIRST EQUALS SECOND: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equals = first.equals(third);
        cout << "FIRST EQUALS THIRD: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        bool equalsType = first.equalsType(second);
        cout << "FIRST EQUALS TYPE SECOND: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equalsType = second.equals(third);
        cout << "SECOND EQUALS TYPE THIRD: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

    }
    else if (testCase == 3) {
        cout << "======= FOLDER CONSTRUCTOR =======" << endl;
        cin >> fileName;
        Folder folder(fileName);
        folder.print();

    }
    else if (testCase == 4) {
        cout << "======= ADD FILE IN FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0) {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        folder.print();
    }
    else {
        cout << "======= REMOVE FILE FROM FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0) {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File file(fileName, fileOwner, fileSize, (Extension) ext);
        folder.remove(file);
        folder.print();
    }
    return 0;
}