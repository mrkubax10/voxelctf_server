#include "settings.hpp"
Settings::Settings(){
    Settings::port=1255;
    Settings::maxplayers=10;
    Settings::mapName="";
}
void Settings::load(std::string f){
    std::fstream file(f,std::ios::in);
    std::string line;
    while(getline(file,line)){
        if(split(line,'=')[0]=="port")
            Settings::port=std::stoi(split(line,'=')[1]);
        else if(split(line,'=')[0]=="maxplayers")
            Settings::maxplayers=std::stoi(split(line,'=')[1]);
        else if(split(line,'=')[0]=="map")
            Settings::mapName=split(line,'=')[1];
    }
}