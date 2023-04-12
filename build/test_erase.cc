#include<vector>

int  main(){
    std::vector<int> a;
    a.push_back(1);
    auto tt = a.begin();
    a.erase(tt);
    //a.erase(tt);
    return 0;
}