#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>
#include <regex>
#include "XMLParser.h"

std::string vector2path(std::vector<std::string>& pathVector){
    std::string path = "/";
    for (int i = 0; i < pathVector.size(); i++){
        path += pathVector[i];
        path += "/";
    }
    return path;
}

XML_S::Init::Init(XML_S::Controller* controller){
     this->cntrl = controller;
}

void XML_S::Init::ProcessCharacter(char inp){
    this->cntrl->user->startDocument();
    if (inp == '<'){
        this->cntrl->currState = this->cntrl->stateInfo->openArrow;
    }
}

XML_S::OpenArrow::OpenArrow(XML_S::Controller* controller){
     this->cntrl = controller;
}

void XML_S::OpenArrow::ProcessCharacter(char inp){
  std::regex entityName ("[a-z]|[A-Z]|[0-9]|_|-|.");
  std::regex endName ("[\r\t\f\v ]");
  std::string inp_s = &inp;
  if (std::regex_match (inp_s,entityName)){
      this->cntrl->localEntityName += inp_s;
  }
  else if(std::regex_match (inp_s, endName)){
      this->cntrl->currPath.push_back(this->cntrl->localEntityName);
      std::string path = vector2path(this->cntrl->currPath);
      this->cntrl->user->startElement(path, this->cntrl->localEntityName);
      this->cntrl->currState = this->cntrl->stateInfo->entity;
  }
  else if(inp == '/'){
    std::string path = vector2path(this->cntrl->currPath);
    this->cntrl->user->endElement(path, this->cntrl->currPath.back());
    this->cntrl->currPath.pop_back();
  }
}
