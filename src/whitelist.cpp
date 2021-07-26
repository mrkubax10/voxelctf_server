#include "whitelist.hpp"
#include <algorithm>
#include <fstream>
Whitelist::Whitelist(){

}
void Whitelist::addToWhitelist(std::string playerName){
    if(Whitelist::isInWhitelist(playerName))
        return;
    Whitelist::whitelistData.push_back(playerName);
}
void Whitelist::removeFromWhitelist(std::string playerName){
    if(!Whitelist::isInWhitelist(playerName))
        return;
    Whitelist::whitelistData.erase(std::find(Whitelist::whitelistData.begin(),Whitelist::whitelistData.end(),playerName));
}
bool Whitelist::isInWhitelist(std::string playerName){
    return (std::find(Whitelist::whitelistData.begin(),Whitelist::whitelistData.end(),playerName)!=Whitelist::whitelistData.end());
}
bool Whitelist::isEnabled(){
    return Whitelist::enabled;
}
void Whitelist::setEnabled(bool enabled){
    Whitelist::enabled=enabled;
}
std::vector<std::string>& Whitelist::getContent(){
    return Whitelist::whitelistData;
}
void Whitelist::load(){
    std::fstream file;
    file.open("whitelist.txt");
    if(!file.good())
        return;
    std::string line;
    while(getline(file,line)){
        Whitelist::whitelistData.push_back(line);
    }
    file.close();
}
void Whitelist::save(){
    std::fstream file;
    file.open("whitelist.txt",std::ios::out);
    for(int i=0; i<Whitelist::whitelistData.size(); i++){
        file<<Whitelist::whitelistData[i]<<std::endl;
    }
    file.close();
}