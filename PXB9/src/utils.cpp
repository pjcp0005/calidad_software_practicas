/**
 * @file utils.cpp
 * @author Francisco Javier Martín-Lunas Escobar (fjme0008@red.ujaen.es)
 * @brief Implementación de las utilidades de manipulación de cadenas.
 * @version 0.1
 * @date 2025-10-18
 *
 * @copyright Copyright (c) 2026
 */
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
