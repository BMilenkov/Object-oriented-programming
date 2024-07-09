#include <iostream>
#include <cstring>
using namespace std;

class MediaSegment{
protected:
    char tittle[100];
    char author[100];
    int duration; // in seconds;
    int size; //in MB
public:
    MediaSegment( char *tittle = "", char *author ="", int duration=0, int size =0){
        strcpy(this->tittle,tittle);
        strcpy(this->author, author);
        this->duration = duration;
        this->size = size;
    }
    virtual double price()=0;
};
enum audioType{
    mp3,
    wac,
    ogg,
    flac
};
class AudioRecording : virtual public MediaSegment {
private:
    audioType type1;
    short AudioChannels;
public:
    AudioRecording(char *tittle = "", char *author = "", int duration = 0, int size = 0,
                   int type1 = 1, short AudioChannels = 0)
            : MediaSegment(tittle, author, duration, size) {
        this->type1 = audioType(type1);
        this->AudioChannels = AudioChannels;
    }

    double price() {
        if (type1 == 3) {
            return 1.5 * duration * AudioChannels;
        }
        return duration * AudioChannels;
    }

    friend ostream &operator<<(ostream &out, AudioRecording &AR) {
        out << AR.tittle << " " << AR.author << " " << AR.duration << " " << AR.size << " " << AR.price()
            << endl;
        return out;
    }
};
enum Compresion{
    x264,Theora,AV1
};
class VideoRecording : virtual public MediaSegment{
    int VideoWidth;
    Compresion type2;
public:
    VideoRecording( char *tittle = "", char *author ="", int duration=0, int size =0,
            int VideoWidth=0,int type2 = 0)
            :MediaSegment(tittle, author,duration,size){
        this->VideoWidth = VideoWidth;
        this->type2 = Compresion(type2);
    }
    double price(){
        double price1 =0.0;
        if(VideoWidth <= 1920)
            price1 = 100*duration;
        else if(VideoWidth > 1920)
            price1 = 170*duration;
        if(type2==x264)
            return 1.5*price1;
        else if(type2 == Theora){
            return 0.9*price1;
        } else
            return
            price1;
    }
    friend ostream &operator<<(ostream &out, VideoRecording &VR) {
        out << VR.tittle << " " << VR.author <<
            " " << VR.duration << " " << VR.size << " " << VR.VideoWidth << " " << VR.price()
            << endl;
        return out;
    }
};
class MusicVideo :  public AudioRecording, public VideoRecording{
private:
    char PUBLICATION[10];
public:
    MusicVideo(char *tittle = "", char *author ="", int duration=0, int size =0,
               int type1 = 1, short AudioChannels = 0,int VideoWidth=0,int type2 = 0,
                       char *PUBLICATION = "")
           : AudioRecording(tittle,author,duration,size,type1,AudioChannels),
             VideoRecording(tittle,author,duration,size,VideoWidth,type2)
            {
        strcpy(this->PUBLICATION,PUBLICATION);
    }
    double price(){
        double price2= AudioRecording::price() + VideoRecording::price();
        if(!strcmp(PUBLICATION+4,"2010")){
            return 1.3*price2;
        }
    }
    friend ostream &operator<<(ostream &out, MusicVideo &MV) {
        out << MV.tittle<< " " << MV.author <<" "<<MV.PUBLICATION<<" "<<MV.duration
        <<" "<<MV.price()<<endl;
        return out;
    }
};
double total_price(MediaSegment **segments,int n){
    double sum=0.0;
    for(int i=0; i < n;i++){
        sum+=segments[i]->price();
    }
    return sum;
}
MusicVideo &cheapest_music_video(MediaSegment **segments,int n){
    MusicVideo *MV = nullptr;
    double min;
    bool flag;
    for(int i=0; i < n;i++){
      MusicVideo *casted = dynamic_cast<MusicVideo*>(segments[i]);
      if(casted){
          if(flag){
              min = casted->price();
              MV = casted;
          }
          else if(!flag){
              if(casted->price() < min){
                  min = casted->price();
                  MV = casted;
              }
          }
      }
    }
    return *MV;
}


int main() {

    int test_case_num;
    cin>>test_case_num;


    // for MediaSegment
    char title[100];
    char author[1000];
     int size;
    int duration;


    // for AudioRecording
    //-------------------
     short channels;

    // AudioFormat:
    // 0 - mp3
    // 1 - wav
    // 2 - ogg
    // 3 - flac
     short format;


    // for VideoRecording
    //-------------------
    short width;

    // VideoCompression:
    // 0 - x264
    // 1 - Theora
    // 2 - AV1
    int compression;


    // for MusicVideo
    //-------------------
    char publication_date[9];


    if (test_case_num == 1){
        cout<<"Testing class AudioRecording and operator<<"<<std::endl;
        cin.get();
        cin.getline(title,100);
        cin.getline(author, 100);
        //cin.get();
        cin >> duration >> size;
        cin >> format >> channels;

        AudioRecording a(title, author, duration, size, format, channels);

        cout<<a;

    }

    else if (test_case_num == 2){
        cout<<"Testing class VideoRecording and operator<<"<<std::endl;
        cin.get();
        cin.getline(title,100);
        cin.getline(author, 100);
        //cin.get();
        cin >> duration >> size;
        cin >> width >> compression;

        VideoRecording v(title, author, duration, size, width, compression);

        cout<<v;

    }

    else if (test_case_num == 3){
        cout<<"Testing class MusicVideo and operator<<"<<std::endl;

        cin.get();
        cin.getline(title,100);
        cin.getline(author, 100);
        //cin.get();
        cin >> duration >> size;

        cin >> format >> channels;
        cin >> width >> compression;

        cin.get();
        cin.getline(publication_date, 9);
        MusicVideo mv(title, author, duration, size, format, channels, width, compression, publication_date);

        cout << mv;
    }

    else if (test_case_num == 4){
        cout<<"Testing function: total_price "<<std::endl;

        MediaSegment ** m;

        int num_media_segments;
        cin >> num_media_segments;

        // 1 - AudioRecording
        // 2 - VideoRecording
        // 3 - MusicVideo
        short media_type;

        m = new MediaSegment*[num_media_segments];

        for (int i=0; i<num_media_segments; i++) {

            cin >> media_type;

            cin.get();
            cin.getline(title,100);
            cin.getline(author, 100);
            //cin.get();
            cin >> duration >> size;

            switch(media_type) {
                case 1:
                    cin >> format >> channels;
                    m[i] = new AudioRecording(title, author, duration, size, format, channels);
                    break;
                case 2:
                    cin >> width >> compression;
                    m[i] = new VideoRecording(title, author, duration, size, width, compression);
                    break;
                case 3:
                    cin >> format >> channels;
                    cin >> width >> compression;
                    cin.get();
                    cin.getline(publication_date, 9);
                    m[i] = new MusicVideo(title, author, duration, size, format, channels, width, compression, publication_date);
                    break;
            }
        }

        //for (int i=0;i<num_media_segments; i++){
        //    cout << *m[i];
        //}

        cout<< "Total price is: " << total_price(m, num_media_segments);

        delete [] m;

    }
    else if (test_case_num == 5){
        cout<<"Testing function: cheapest_music_video "<<std::endl;

        MediaSegment ** m;

        int num_media_segments;
        cin >> num_media_segments;

        // 1 - AudioRecording
        // 2 - VideoRecording
        // 3 - MusicVideo
        short media_type;

        m = new MediaSegment*[num_media_segments];

        for (int i=0; i<num_media_segments; i++) {

            cin >> media_type;

            cin.get();
            cin.getline(title,100);
            cin.getline(author, 100);
            //cin.get();
            cin >> duration >> size;

            switch(media_type) {
                case 1:
                    cin >> format >> channels;
                    m[i] = new AudioRecording(title, author, duration, size, format, channels);
                    break;
                case 2:
                    cin >> width >> compression;
                    m[i] = new VideoRecording(title, author, duration, size, width, compression);
                    break;
                case 3:
                    cin >> format >> channels;
                    cin >> width >> compression;
                    cin.get();
                    cin.getline(publication_date, 9);
                    m[i] = new MusicVideo(title, author, duration, size, format, channels, width, compression, publication_date);
                    break;
            }
        }

        cout << cheapest_music_video(m, num_media_segments);

        delete [] m;
    }

    return 0;
}

