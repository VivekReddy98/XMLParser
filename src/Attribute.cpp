/**
 * Author:    Vivek Reddy Karri
 * Created:   March 2020.
 **/

#include "XMLParser.h"
#include <regex>

XML_S::Attribute::Attribute(XML_S::Controller* controller){
   this->cntrl = controller;
   this->inValue = 0;
}

void XML_S::Attribute::ProcessCharacter(char inp){

  // Handles most of the cases encountered in while extracting attribute information from the Entity.
  std::regex attribName ("[a-z]|[A-Z]|[0-9]|_|-|[.]");
  std::regex attribValue ("[a-z]|[A-Z]|[0-9]|_|-|[.][\r\t\f\v\n ]");

  std::string inp_s(1, inp);
  if (std::regex_match (inp_s, attribName) && this->inValue == 0){
      this->temp_key += inp_s;
  }
  else if(inp == '=' && this->inValue == 0){
      this->inValue = 1;
  }
  else if(std::regex_match (inp_s, attribValue) && this->inValue == 1){
      this->temp_value += inp_s;
  }
  else if(inp == '>' || (inp == '/' && this->inValue != 0)){
      std::unordered_map<std::string, std::string> attribMap;
      std::string path = vector2path(this->cntrl->currPath);
      attribMap[this->temp_key] = this->temp_value;
      this->cntrl->user->elementAttributes(path, attribMap);

      // Clean Up
      this->inValue = 0;
      this->temp_key = "";
      this->temp_value = this->temp_key;
      if (inp == '/') {
        this->cntrl->currState = this->cntrl->stateInfo->openArrow;
        this->cntrl->currState->ProcessCharacter(inp);
      }
      else if (inp == '>') this->cntrl->currState = this->cntrl->stateInfo->entity;
  }
  else if (inp == '/' && this->inValue == 0){
      this->cntrl->currState = this->cntrl->stateInfo->openArrow;
      this->cntrl->currState->ProcessCharacter(inp);
  }
}
