#include "JsonObject.h"
#include "JsonArray.h"
#include "JsonFunction.h"

namespace MyJson{

JsonObject & JsonObject::operator=(const JsonObject &rhs) {
    if(this!=&rhs){
        token=rhs.token;
    }
    return *this;
}

bool JsonObject::parseObject() {
    for(auto p=token.cbegin()+1; p<token.cend()-1; ){
        if(isString(*p))
            value.push_back(*p);
        else{
            std::cout << "Invalid string type: " << *p << ".\n";
            return false;
        }
        if(p+1>=token.cend()-1){
            std::cout << "Missing valid input after " << *p << ".\n";
            return false;
        }
        if(*(p+1) != ":"){
            std::cout << "Need \":\" between " << *p << " and " << *(p+1) << ".\n";
            return false;
        }
        if(p+2>=token.cend()-1){
            std::cout << "Missing valid input after " << *(p+1) << ".\n";
            return false;
        }

        //判断值的类型
        if((*(p+2) != "{") and (*(p+2)) != "["){
            valueString[*p]=*(p+2);
            if((p+3 < token.cend()-1) and (*(p+3) != ",")){
                std::cout << "Missing \",\" between " << *(p+2) << " and " << *(p+3) << ".\n";
                return false;
            }
            p+=4;
        } else if((*(p+2)) == "{"){
            valueString[*p]="object";
            vector<string> temp{};
            int nBrace=1;
            auto p2=p+2;
            while(nBrace>0){
                temp.push_back(*p2++);
                if(*p2=="{")
                    ++nBrace;
                if(*p2=="}")
                    --nBrace;
            }
            temp.push_back(*p2);
            valueJObject[*p]=JsonObject{temp};
            if(!valueJObject[*p].parseObject())
                return false;
            if((p2+1 < token.cend()-1) and (*(p2+1) != ",")){
                std::cout << "Missing \",\" between " << *(p2) << " and " << *(p2+1) << ".\n";
                return false;
            }
            p=p2+2;
        } else if(*(p+2) == "["){
            valueString[*p]="array";
            vector<string> temp{};
            int nBracket=1;
            auto p3=p+2;
            while(nBracket>0){
                temp.push_back(*p3++);
                if(*p3=="[")
                    ++nBracket;
                if(*p3=="]")
                    --nBracket;
            }
            temp.push_back(*p3);
            valueJArray[*p]=JsonArray{temp};
            if(!valueJArray[*p].parseArray())
                return false;
            if((p3+1 < token.cend()-1) and (*(p3+1) != ",")){
                std::cout << "Missing \",\" between " << *(p3) << " and " << *(p3+1) << ".\n";
                return false;
            }
            p=p3+2;
        }
    }
    return true;
}

//bool JsonObject::parseObject() {
//    for(auto p=token.cbegin()+1; p<token.cend()-1; ){
//        value.push_back(*p);
//        if(((*(p+2)) != "{") and (*(p+2)) != "["){
//            valueString[*p]=*(p+2);
//            p+=4;
//        } else if((*(p+2)) == "{"){
//            valueString[*p]="object";
//            vector<string> temp{};
//            int nBrace=1;
//            auto p2=p+2;
//            while(nBrace>0){
//                temp.push_back(*p2++);
//                if(*p2=="{")
//                    ++nBrace;
//                if(*p2=="}")
//                    --nBrace;
//            }
//            temp.push_back(*p2);
//            valueJObject[*p]=JsonObject{temp};
//            p=p2+2;
//        } else if(*(p+2) == "["){
//            valueString[*p]="array";
//            vector<string> temp{};
//            int nBracket=1;
//            auto p3=p+2;
//            while(nBracket>0){
//                temp.push_back(*p3++);
//                if(*p3=="[")
//                    ++nBracket;
//                if(*p3=="]")
//                    --nBracket;
//            }
//            temp.push_back(*p3);
//            valueJArray[*p]=JsonArray{temp};
//            p=p3+2;
//        }
//    }
//    return true;
//}

void JsonObject::readObject(int n, bool isEnter) {
    if(isEnter){
        //std::cout << std::endl;
        printSpace(n-1);
    }
    std::cout << "{\n";
    for(const auto &i: value){
        printSpace(n);
        std::cout << i << " : ";
        if(valueString[i] == "array"){
            valueJArray[i].readArray(n+1, false);
        } else if(valueString[i] == "object"){
            valueJObject[i].readObject(n+1, false);
        } else{
            std::cout << valueString[i];
        }
        if(i!=value.back())
            std::cout << ",\n";
        else
            std::cout << "\n";
    }
    printSpace(n-1);
    std::cout << "}";
}

void JsonObject::showObject() {
    std::cout << "{\n";
    for(const auto &i: value){
        std::cout << i << " : " << valueString[i];
        if(i!=value.back())
            std::cout << ",\n";
        else
            std::cout << "\n";
    }
    std::cout << "}\n";
}

JsonObject & JsonObject::object(const string &index) {
    valueJObject[index].showObject();
    return valueJObject[index];
}

JsonArray & JsonObject::array(const string &index) {
    valueJArray[index].showArray();
    return valueJArray[index];
}

void JsonObject::clear() {
    token.clear();
    value.clear();
    valueString.clear();
    valueJObject.clear();
    valueJArray.clear();
}

}   //end namespace MyJson