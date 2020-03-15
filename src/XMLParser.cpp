/**
 * Author:    Vivek Reddy Karri
 * Created:   March 2020.
 **/
#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>
#include <regex>
#include <fstream>      // std::ifstream
#include "XMLParser.h"

/**
    Class: Example Class to demonstrate the usage.
    Functionality: Just prints out whatever recieved from the controller
 **/
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

std::string getLastName(std::string localelement){
    char delim = '/'; // our delimiter


    std::istringstream ss(localelement);
    std::string token;

    std::vector<std::string> tokens;
    while(std::getline(ss, token, delim)) {
      tokens.push_back(token);
    }
    return tokens.back();
}

class userOrderClass
      : public XML_P::XMLContext
{
public:
  std::unordered_map<std::string, std::string> tempMap;
  std::string latestElement;
  userOrderClass(std::string path)
        : XML_P::XMLContext(path)
  { std::cout << "User class initialized" << std::endl; }
  void startDocument() {std::cout << "------------------Document Started !!! ---------------" << std::endl;}
  void endDocument() { std::cout << "--------------------Document Parsed !!! -----------------" << std::endl;}
  void startElement(std::string& path, std::string& localelement){
      this->latestElement = localelement;
  }
  void elementAttributes(std::string& path, std::unordered_map<std::string, std::string>& attributes){
      std::string lastelem = getLastName(path);
      if (lastelem == "order") this->tempMap = attributes;
  }

  void endElement(std::string& path, std::string& localelement){
      this->latestElement = getLastName(path);
  }
  void characters(std::string& body){
      int orderQuan;
      std::size_t pos;
      if (this->latestElement == "amount"){
          orderQuan = stoi(body, &pos);
          if (orderQuan > 100 && pos == body.size()){
              std::cout << "Amount: " << orderQuan << " Order ID:  " << this->tempMap["id"] << std::endl;
          }
      }

  }
};


int main(int argc, char **argv){
    if (argc < 2 || argc > 3) throw std::runtime_error("Number of Arguments must be specified are three or two: \
                                            ./ParserEngine.exe {path to the xml file} {order(optional)}");

    std::string xmlpath(argv[1]);

    if (argc == 3 && (strcmp(argv[2], "order") == 0)){
      userOrderClass* me2 = new userOrderClass(xmlpath);
      me2->Execute();
      delete me2;
    }
    else{
      userPrintClass* me = new userPrintClass(xmlpath);
      me->Execute();
      delete me;
    }
    return 1;
}
