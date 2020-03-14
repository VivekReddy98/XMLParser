#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>
#include <regex>
#include <fstream>      // std::ifstream
#include "XMLParser.h"

class userPrintClass
    : public XML_P::XMLContext
{
  public:
    userPrintClass(std::string path)
          : XML_P::XMLContext(path)
    { std::cout << "User class initialized" << std::endl; }
    void startDocument() {std::cout << "------------------Document Started !!! ---------------" << std::endl;}
    void endDocument() {std::cout << "--------------------Document Parsed !!! -----------------" << std::endl;}
    void startElement(std::string& path, std::string& localelement){
        std::cout << "startElement: => " << localelement << " Current Path: " << path << std::endl;
    }
    void elementAttributes(std::string& path, std::unordered_map<std::string, std::string>& attributes){
        std::cout << "              Attributes:  ";
        std::unordered_map<std::string, std::string>::iterator it = attributes.begin();
        while(it != attributes.end()) {
            std::cout<<it->first << " : "<< it->second << std::endl;
            it++;
        }
    }

    void endElement(std::string& path, std::string& localelement){
        std::cout << "endElement:   => " << localelement << " Current Path: " << path << std::endl;
    }
    void characters(std::string& body){
        std::cout << "              Text Inside:  => " << body << std::endl;
    }
};


int main(int argc, char **argv){
    if (argc != 2) throw std::runtime_error("Number of Arguments must be specified are two: \
                                            ./ParserEngine.exe {path to the xml file}");

    std::string xmlpath(argv[1]);
    userPrintClass* me = new userPrintClass(xmlpath);
    me->Execute();
    delete me;
    return 1;
}
