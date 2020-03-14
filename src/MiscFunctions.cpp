#include "XMLParser.h"
#include <vector>
#include <string>
#include <regex>

std::string vector2path(std::vector<std::string>& pathVector){
    std::string path = "/";
    for (int i = 0; i < pathVector.size(); i++){
        path += pathVector[i];
        path += "/";
    }
    return path;
}

std::string ltrim(const std::string& s) {
	return std::regex_replace(s, std::regex("^\\s+"), std::string(""));
}

std::string rtrim(const std::string& s) {
	return std::regex_replace(s, std::regex("\\s+$"), std::string(""));
}

std::string trim(const std::string& s) {
	return ltrim(rtrim(s));
}
