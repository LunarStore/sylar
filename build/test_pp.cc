#include<memory>

#include<iostream>

class base: public std::enable_shared_from_this< base >{
    public:
        //std::shared_ptr<base> get(){ /*return shared_from_this();*/ }
        virtual ~base(){
            std::cout << "~base"<<std::endl;
        }
};

class derive: public base{

};

void test1(){
    base *b = new base();
    // std::cout<< b->get().use_count() << std::endl;
    std::shared_ptr<base> b1(b);
    std::weak_ptr<base> tmp(b1);
    // std::cout<< b1->get().use_count()<< std::endl;

    std::shared_ptr<base> b2 = b1;
    // std::cout<< "b1:" << b1->get().use_count()<< std::endl;
    //     std::cout<<"b2:" << b2->get().use_count()<< std::endl;

    std::shared_ptr<base> b3(b);
    // std::cout<< "b1:" << b1->get().use_count()<< std::endl;
    // std::cout<<"b2:" << b2->get().use_count()<< std::endl;
    // std::cout<< "b3:" <<b3->get().use_count()<< std::endl;
}

void test2(){
    derive* p = new derive;
    std::shared_ptr<derive> d(p);

    std::shared_ptr<base> b = d;

    std::shared_ptr<derive> tt = std::dynamic_pointer_cast<derive>(b);

    std::shared_ptr<derive> cc(p);

    d.reset();
    return;
}

int main(){
    test2();
    return 0;
}