#include "JsonFunction.h"

namespace MyJson{
void printSpace(int n){
    while(n>0){
        std::cout << "    ";
        --n;
    }
}


bool isDigit(std::string &str){
    int n1=std::count(str.begin(), str.end(), '+');
    int n2=std::count(str.begin(), str.end(), '-');
    int n3=std::count(str.begin(), str.end(), '.');
    if(n1>1 || n2>1 || n3>1)
        return false;
    int i=0;
    if(str[i]=='+' || str[i]=='-' || str[i]=='.')
        ++i;
    while(str[i]=='0'){
        str.erase(i, 1);
    }
    for(; i<str.size(); ++i){
        if(str[i]=='+' || str[i]=='-')
            return false;
    }
    return true;
}

bool isBool(const std::string &str){
    return str=="true" or str=="false" or str=="null";
}

bool isString(const std::string &str){
    return str.front() == '\"' and str.back() == '\"';
}

}   //end namespace MyJson