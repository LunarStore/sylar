#include<iostream>
#include<stdint.h>
using namespace std;
class base{
public:
    base(){
        cout << "base::base()" << endl;
    }
    /*virtual*/ ~base(){
        cout << "~base::base()" << endl;
    }
private:
    int m_elem;
};


class base1{
public:
    base1(){
        cout << "base1::base1()" << endl;
    }
  /* virtual*/  ~base1(){
        cout << "~base1::base1()" << endl;
    }
private:
    int m_elem;
};

class derive : public base, public base1{
public:
    derive(){
        cout << "derive::derive()"<<endl;
    }
    ~derive(){
        cout << "~derive::derive()"<<endl;
    }
private:
    int m_d;
};


int main(){
    base1* pb1 = nullptr;
    base* pb = nullptr;
    derive* pd = new derive();
    pb = (base*)pd;
    pb1 = (base1*)pd;
    cout << pd << "---" << pb << "---" << pb1 << "---" << (derive*)pb1  << "---" << (derive*)((void*)pb1)<< endl;
    delete pb1;
//    int *p = (int*)malloc(sizeof(int));
//    free(((char*)p) + 1);
    return 0;
}



