#include "users.h"
using namespace std;
Users::Users(string name, string user, string password)
{
    this->name = name;
    this->user = user;
    this->password = password;
}
void Users::Set(string name, string user, string password, bool GM)
{
    this->name = name;
    this->user = user;
    this->password = password;
    this->GM = GM;
}
ostream& operator<<(ostream& os, Users& user)
{
    os << user.name << "\t\t" << user.user << "\t\t" << user.password << "\t\t" << user.GM;
    return os;
}
istream& operator>>(istream& is, Users& user)
{
    is >> user.name >> user.user >> user.password >> user.GM;
    return is;
}