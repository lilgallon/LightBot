//    This file is part of LightBot.
//
//    LightBot is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    LightBot is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with LightBot.  If not, see <http://www.gnu.org/licenses/>.

#include "Utils.h"

float Utils::abs(float value){
    if(value>0)
        return value;
    return -value;
}

std::string Utils::getTime(){
    time_t t = time(0); // Time from now (0)
    struct tm* now = localtime(&t);

    std::string hour,min,sec;

    // reformat -> get 10:02:05 instead of 10:2:5 for exemple
    if(now->tm_hour>=10){
        hour = std::to_string(now->tm_hour);
    }else{
          hour = "0" + std::to_string(now->tm_hour);
    }

    if(now->tm_min>=10){
        min = std::to_string(now->tm_min);
    }else{
        min = "0" + std::to_string(now->tm_min);
    }

    if(now->tm_sec>=10){
        sec = std::to_string(now->tm_sec);
    }else{
        sec = "0" + std::to_string(now->tm_sec);
    }
    //delete now; don't delete now otherwise it crashes (wtf)
    return "[" + hour + ":" + min + ":" + sec + "] ";
}

std::vector<std::string> Utils::split(const std::string &str, const std::string &delim)
{
    std::vector<std::string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if(pos == std::string::npos) pos = str.length();
        std::string token = str.substr(prev, pos-prev);
        if(!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while(pos < str.length() && prev < str.length());
    return tokens;
}
