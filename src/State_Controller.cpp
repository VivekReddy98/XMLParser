#include <fstream>
#include "XMLParser.h"

XML_S::Base::Controller(XML_P::XMLContext* usr){
    this->user = usr;
    this->stateInfo->init = new XML_S::Init(this);
    this->stateInfo->openArrow = new XML_S::OpenArrow(this);
    this->stateInfo->declaration = new XML_S::Declaration(this);
    this->stateInfo->comment = new XML_S::Comment(this);
    this->stateInfo->cdata= new XML_S::Cdata(this);
    this->stateInfo->attribute = new XML_S::Attribute(this);
    this->stateInfo->entity = new XML_S::Entity(this);
    this->currState = this->stateInfo->init;
    this->localEntityName = "";
}

void XML_S::Base::ProcessCharacter(char inp){
    this->currState->ProcessCharacter(inp);
}
