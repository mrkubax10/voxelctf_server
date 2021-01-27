#include "utils.hpp"
std::vector<std::string> split(std::string str,char ch){
    std::stringstream s(str);
    std::vector<std::string> out;
    std::string item;
    while(getline(s,item,ch)){
        out.push_back(item);
    }
    return out;
}