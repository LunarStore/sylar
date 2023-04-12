#include<sys/epoll.h>
#include<iostream>
#include<pthread.h>
#include<unistd.h>
    int pp[2];
void* fun(void*){
    sleep(3);
    std::cout<<"write"<<std::endl;
    write(pp[0], "ww", 2);
    return nullptr;
}
int main(){
    int efd = epoll_create(5);

    pthread_t pid;
    pipe(pp);
    epoll_event et = { 0 }, ets[10];
    //先注册后写最后epoll_wait,epoll_wait时会触发事件
    // et.data.fd = pp[0];
    // et.events = EPOLLIN | EPOLLET;
    // std::cout<< epoll_ctl(efd, EPOLL_CTL_ADD, pp[0], &et) << std::endl;
    //pthread_create(&pid, nullptr, fun, nullptr);
    write(pp[1], "ww", 2);
std::cout<<"11"<<std::endl;
    //sleep(2);
    //先写后注册再epoll_wait，epoll_wait时会触发可读事件
    et.data.fd = pp[0];
    et.events = EPOLLIN | EPOLLET;
    std::cout<< epoll_ctl(efd, EPOLL_CTL_ADD, pp[0], &et) << std::endl;
    epoll_wait(efd, ets, 10, -1);
    epoll_wait(efd, ets, 10, -1);
    std::cout<<"可以"<<std::endl;
    return 0;
}