#include <fstream>
#include "XMLParser.h"

XML_S::Base::Base(XML_P::XMLContext* usr){
    this->user = usr;
    this->currState = new XML_S::Init(this);
}

void XML_S::Base::ProcessCharacter(char inp){
    this->currState->ProcessCharacter(inp);
}
