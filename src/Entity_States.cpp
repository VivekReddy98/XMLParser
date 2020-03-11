#include "XMLParser.h"
#include <regex>

XML_S::Entity::Entity(XML_S::Controller* controller){
     this->cntrl = controller;
}

void XML_S::Init::ProcessCharacter(char inp){
    std::regex entityName ("[a-z]|[A-Z]|[0-9]|_|-|.");
    sting inp_s = inp;
    if (inp = ''){
        this->cntrl->currState = this->cntrl->stateInfo->openArrow;
    }
}
