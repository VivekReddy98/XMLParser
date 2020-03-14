#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>
#include <regex>
#include "XMLParser.h"

XML_S::OpenArrow::OpenArrow(XML_S::Controller* controller){
     this->cntrl = controller;
     this->inEndTag = 0;
}

void XML_S::OpenArrow::ProcessCharacter(char inp){
  // std::cout << "State : OpenARROW" << std::endl;
  std::regex entityName ("[a-z]|[A-Z]|[0-9]|_|-|[.]");
  std::regex endName ("[\r\t\f\v ]");
  std::string inp_s(1, inp);
  if (std::regex_match (inp_s, entityName) && this->inEndTag == 0){
      this->cntrl->localEntityName += inp_s;
  }
  else if((std::regex_match (inp_s, endName) || inp == '>') && this->inEndTag == 0){
      this->cntrl->currPath.push_back(this->cntrl->localEntityName);
      std::string path = vector2path(this->cntrl->currPath);
      this->cntrl->user->startElement(path, this->cntrl->localEntityName);
      this->cntrl->localEntityName = "";
      if (inp == '>'){
          this->cntrl->currState = this->cntrl->stateInfo->entity;
      }
      else{
          this->cntrl->currState = this->cntrl->stateInfo->attribute;
      }

  }
  else if (inp == '>' && this->inEndTag == 1){
      std::string popped_element = this->cntrl->currPath.back();
      this->cntrl->currPath.pop_back();
      std::string path = vector2path(this->cntrl->currPath);
      if (!this->cntrl->currPath.empty()){
         this->cntrl->user->endElement(path, popped_element);
      }
      this->cntrl->localEntityName = "";
      this->cntrl->currState = this->cntrl->stateInfo->entity;
      this->inEndTag = 0;
  }
  else if(inp == '/'){
     this->inEndTag = 1;
  }
  else if (inp == '?'){
     this->cntrl->currState = this->cntrl->stateInfo->declaration;
  }
}
