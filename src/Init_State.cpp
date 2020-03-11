#include "XMLParser.h"

XML_S::Init::Init(XML_S::Controller* controller){
     this->cntrl = controller;
}

void XML_S::Init::ProcessCharacter(char inp){
    if (inp == '<'){
        this->cntrl->currState = this->cntrl->stateInfo->openArrow;
    }
}


XML_S::OpenArrow::OpenArrow(XML_S::Controller* controller){
     this->cntrl = controller;
}

void XML_S::OpenArrow::ProcessCharacter(char inp){
  std::regex entityName ("[a-z]|[A-Z]|[0-9]|_|-|.");
  sting inp_s = inp;
  if (std::regex_match (inp_s,entityName)){
      this->cntrl->localEntityName += inp_s;
  }
}
