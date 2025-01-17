#include<iostream>
#include<cstring>
using namespace std;

class UserAlreadyExistsException
{
    char* username;
public:
    UserAlreadyExistsException(char *username="")
    {
        this->username = new char[strlen(username) + 1];
        strcpy(this->username, username);
    }
    void message()
    {
        cout << "User with username " << username << " already exists!"<<endl;
    }
};

class UserNotFoundException
{
    char* username;
public:
    UserNotFoundException(char *username="")
    {
        this->username = new char[strlen(username) + 1];
        strcpy(this->username, username);
    }

    void message()
    {
        cout << "User with username " << username << " was not found!"<<endl;
    }
};

class FriendsLimitExceededException
{
    int n;
public:
    FriendsLimitExceededException(int n=0)
    {
        this->n = n;
    }
    void message()
    {
        cout << "Can't have more than " << n << " friends."<<endl;
    }
};

class User
{
private:
    char username[50];
    int age;
    int friends;
    static int MAXFRIENDS;

public:
    User(char *username = "", int age = 18) : age(age)
    {
        strcpy(this->username, username);
        friends = 0;
    }
    friend ostream &operator<<(ostream &os, const User &user)
    {
        os << "Username: " << user.username << " Age: " << user.age << " # of friends: " << user.friends;
        return os;
    }
    User &operator++()
    {
        if(friends >= MAXFRIENDS)
        {
            throw FriendsLimitExceededException(MAXFRIENDS);
        }
        ++friends;
        return *this;
    }
    User &operator--()
    {
        --friends;
        return *this;
    }
    static void setLimit(int MaxFriends)
    {
        MAXFRIENDS = MaxFriends;
    }
    friend class SocialNetwork;

    ~User(){}
};
int User::MAXFRIENDS = 3;


class SocialNetwork
{
private:
    User *users;
    int n;
public:
    SocialNetwork()
    {
        n = 0;
        users = new User[n];
    }

    SocialNetwork &operator+=(User &u)
    {
        for(int i = 0; i < n; i++)
        {
            if(strcmp(u.username, users[i].username) == 0)
                throw UserAlreadyExistsException(u.username);
        }

        User *tmp = new User[n + 1];
        for (int i = 0; i < n; i++)
        {
            tmp[i] = users[i];
        }
        tmp[n++] = u;
        delete[] users;
        users = tmp;
        return *this;
    }

    void friendRequest(char *firstUsername, char *secondUsername)
    {
        bool b = false;
        for (int i = 0; i < n; i++)
        {
            if (strcmp(users[i].username, secondUsername) == 0)
            {
                b = true;
            }
        }

        if(b == false)
        {
            throw UserNotFoundException(secondUsername);
        }

        for (int i = 0; i < n; i++)
        {
            if (strcmp(users[i].username, firstUsername) == 0)
            {

                for (int j = 0; j < n; j++)
                {
                    if (strcmp(users[j].username, secondUsername) == 0)
                    {
                        try
                        {
                            ++users[i];
                        }
                        catch(FriendsLimitExceededException& e)
                        {
                            e.message();
                            return;
                        }

                        try
                        {
                            ++users[j];
                        }
                        catch(FriendsLimitExceededException& e)
                        {
                            e.message();
                            --users[i];
                        }

                        return;
                    }
                }

            }
        }

        throw UserNotFoundException(firstUsername);
    }
    friend ostream &operator<<(ostream &os, const SocialNetwork &network)
    {
        os << "Users: " << endl;
        for (int i=0; i<network.n; i++)
        {
            os << network. users[i] << endl;
        }
        return os;
    }
};
int main()
{
    SocialNetwork sn;
    int n;
    cin >> n;
    for (int i=0; i<n; i++)
    {
        char username[50];
        int age;
        cin >> username >> age;
        User u(username, age);

        try
        {
            sn += u;
        }
        catch(UserAlreadyExistsException& e)
        {
            e.message();
        }

    }

    cout << "Registration of users " << endl;
    cout << sn << endl;
    cout << "Friend requests " << endl;

    int friendships;
    cin >> friendships;
    for (int i=0; i<friendships; i++)
    {
        char username1[50], username2[50];
        cin >> username1 >> username2;

        try
        {
            sn.friendRequest(username1, username2);
        }
        catch(UserNotFoundException& e)
        {
            e.message();
        }

    }

    cout << sn << endl;

    cout << "CHANGE STATIC VALUE" << endl;

    int maxFriends;
    cin >> maxFriends;
    cin >> friendships;
    User::setLimit(maxFriends);
    for (int i=0; i<friendships; i++)
    {
        char username1[50], username2[50];
        cin >> username1 >> username2;

        try
        {
            sn.friendRequest(username1, username2);
        }
        catch(UserNotFoundException& e)
        {
            e.message();
        }
    }
    cout << sn;
    return 0;
}
