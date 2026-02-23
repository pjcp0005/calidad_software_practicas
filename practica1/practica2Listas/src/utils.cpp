//
// Created by jmart on 18/10/2025.
//
#include "../include/utils.h"
#include <algorithm>
#include <cctype>

namespace utils {

    char toLow(unsigned char c){
        return static_cast<char>(std::tolower(c));
    }

    void toLowerInPlace(std::string &s){
        std::transform(s.begin(),s.end(),s.begin(),[](unsigned char c){return toLow(c);});
    }

    std::string lowerCopy(std::string s){
        toLowerInPlace(s);
        return s;
    }

    bool iContains(const std::string &h,const std::string &n) {
        bool val = true;
        if(!n.empty()){
            std::string haystack = h;
            std::string needle = n;
            toLowerInPlace(haystack);
            toLowerInPlace(needle);
            val = haystack.find(needle) != std::string::npos;
        }
        return val;
    }

}
