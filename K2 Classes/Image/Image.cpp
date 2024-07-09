#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

class Image{
protected:
    char *name;
    char owner[50];
    int width;
    int height;
public:
    Image( char *name = "untitled" ,  char * owner ="unknown" , int width =800
            ,int height =800){
        this->name = new char[strlen(name)+1];
        strcpy(this->name,name);
        strcpy(this->owner, owner);
        this->width= width;
        this->height = height;
    }
    virtual int fileSize(){
        return width * height * 3;
    }
    friend ostream & operator <<(ostream &out, Image &I){
        out<<I.name<<" "<<I.owner<<" "<<I.fileSize()<<endl;
        return out;
    }
   bool operator > (Image &I){
       return fileSize() > I.fileSize();
    }
    ~Image(){
        delete [] name;
    }
};
class TransparentImage : public  Image{
protected:
    bool transparency;
public:
    TransparentImage(  char *name = "untitled" , char * owner ="unknown" , int width =800
            ,int height =800, bool transparency = true)
            : Image(name,owner,width,height){
        this->transparency = transparency;
    }
   int fileSize(){
        if(transparency){
            return width*height*4;
        }
        return width*height+(width*height)/8;
    }
    friend ostream & operator <<(ostream &out, TransparentImage &I){
        out<<I.name<<" "<<I.owner<<" "<<I.fileSize()<<endl;
        return out;
    }
    bool operator > (TransparentImage &I){
        return fileSize() > I.fileSize();
    }
};
class  Folder{
protected:
    char nameFolder[255];
    char Username[50];
    Image *images[100];
    int count;
public:
    Folder( char *nameFolder="",char *Username = "unknown"){
        strcpy(this->nameFolder , nameFolder);
        strcpy(this->Username ,Username);
        this->count = 0;
    }
    int folderSize(){
        int sum=0;
        for(int i=0;i<count ;i++){
            sum+= images[i]->fileSize();
        }
        return sum;
    }
    Image * getMaxFile()const {
        int max = 0, index;
        for (int i = 0; i < count; i++) {
            if (images[i]->fileSize() > max) {
                max = images[i]->fileSize();
                index = i;
            }
        }
        return images[index];
    }
    Folder & operator+=(Image &I){
        TransparentImage *casted = dynamic_cast<TransparentImage*>(&I);
        if(casted){
        images[count++] = new TransparentImage(*casted);
        }
        else {
            images[count++] = new Image(I);
        }
        return *this;
    }
   friend ostream & operator <<(ostream &out, Folder &F){
        out<<F.nameFolder<<" "<<F.Username<<endl;
        out<<"--"<<endl;
       for (int i = 0; i < F.count; i++){
           out<<*F.images[i];
       }
       out<<"--"<<endl<<"Folder size: "<<F.folderSize();
   }
    Image * operator [](int i){
        if(i > 0 && i <= count)
            return images[i];
        else
            return nullptr;
         }
};

Folder &max_folder_size(Folder *folders, int n){
    int max=0, index;
    for (int i = 0; i < n; i++) {
        if (folders[i].folderSize() > max) {
            max = folders[i].folderSize();
            index = i;
        }
    }
    return folders[index];

}

int main() {

    int tc; // Test Case

    char name[255];
    char user_name[51];
    int w, h;
    bool tl;

    cin >> tc;

    if (tc==1){
        // Testing constructor(s) & operator << for class File

        cin >> name;
        cin >> user_name;
        cin >> w;
        cin >> h;


        Image f1;

        cout<< f1;

        Image f2(name);
        cout<< f2;

        Image f3(name, user_name);
        cout<< f3;

        Image f4(name, user_name, w, h);
        cout<< f4;
    }
    else if (tc==2){
        // Testing constructor(s) & operator << for class TextFile
        cin >> name;
        cin >> user_name;
        cin >> w >> h;
        cin >> tl;

        TransparentImage tf1;
        cout<< tf1;

        TransparentImage tf4(name, user_name, w, h, tl);
        cout<< tf4;
    }
    else if (tc==3){
        // Testing constructor(s) & operator << for class Folder
        cin >> name;
        cin >> user_name;

        Folder f3(name, user_name);
        cout<< f3;
    }
    else if (tc==4){
        // Adding files to folder
        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image * f;
        TransparentImage *tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }
        cout<<dir;
    }
    else if(tc==5){
        // Testing getMaxFile for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image* f;
        TransparentImage* tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }
        cout<< *(dir.getMaxFile());
    }
    else if(tc==6){
        // Testing operator [] for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image* f;
        TransparentImage* tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }

        cin >> sub; // Reading index of specific file
        cout<< *dir[sub];
    }
    else if(tc==7){
        // Testing function max_folder_size
        int folders_num;

        Folder dir_list[10];

        Folder dir;
        cin >> folders_num;

        for (int i=0; i<folders_num; ++i){
            cin >> name;
            cin >> user_name;
            dir = Folder(name, user_name);


            Image* f;
            TransparentImage *tf;

            int sub, fileType;

            while (1){
                cin >> sub; // Should we add subfiles to this folder
                if (!sub) break;

                cin >>fileType;
                if (fileType == 1){ // Reading File
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    f = new Image(name,user_name, w, h);
                    dir += *f;
                }
                else if (fileType == 2){
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    cin >> tl;
                    tf = new TransparentImage(name,user_name, w, h, tl);
                    dir += *tf;
                }
            }
            dir_list[i] = dir;
        }

        cout<<max_folder_size(dir_list, folders_num);
    }
    return 0;
}