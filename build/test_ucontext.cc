#include<ucontext.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

int main(){
    ucontext_t ctx;
    getcontext(&ctx);
    ctx.uc_link = nullptr;
    ctx.uc_stack.ss_sp = (void*)malloc(1024);
    ctx.uc_stack.ss_size = 1024;
    swapcontext(&ctx, &ctx);

    cout << "over";
    return 0;
}