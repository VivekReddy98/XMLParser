#include "XMLParser.h"
#include <regex>

XML_S::Entity::Entity(XML_S::Controller* controller){
   this->cntrl = controller;
   this->canCData = 0;
   this->stringBody = "";
}

XML_S::Attribute::Attribute(XML_S::Controller* controller){
   this->cntrl = controller;
   this->inValue = 0;
}

void XML_S::Attribute::ProcessCharacter(char inp){

  std::regex attribName ("[a-z]|[A-Z]|[0-9]|_|-|.");
  std::regex endName ("=");

  std::string inp_s = &inp;
  if (std::regex_match (inp_s, attribName) && inValue == 0){
      this->temp_key += inp_s;
  }
  else if(std::regex_match (inp_s, endName) && inValue == 0){
      this->inValue == 1;
  }
  else if(std::regex_match (inp_s, attribName) && inValue == 1){
      this->temp_value += inp_s;
  }
  else if(inp == '>'){
      std::unordered_map<std::string, std::string> attribMap;
      std::string path = vector2path(this->cntrl->currPath);
      attribMap[this->temp_key] = this->temp_value;
      this->cntrl->user->elementAttributes(path, attribMap);
      this->cntrl->currState = this->cntrl->stateInfo->attribute;
      this->inValue = 0;
      this->temp_key = "";
      this->temp_value = this->temp_key;
  }
}

void XML_S::Entity::ProcessCharacter(char inp){
  if (inp == '<' && this->canCData == 0){
      this->canCData = 1;
  }
  else if (inp != '!' && this->canCData == 0){
      this->cntrl->currState = this->cntrl->stateInfo->openArrow;
      this->cntrl->user->characters(this->stringBody);
      this->cntrl->currState->ProcessCharacter(inp);
  }
  else if (inp == '!'){
      this->cntrl->currState = this->cntrl->stateInfo->cdata;
  }
  else {
      std::string s = &inp;
      this->stringBody += s;
  }
}
