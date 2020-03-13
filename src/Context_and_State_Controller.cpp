#include "XMLParser.h"
#include <fstream>
#include <iostream>

XML_S::Controller::Controller(XML_P::XMLContext* usr){
    this->user = usr;
    this->stateInfo = new XML_S::States();
    this->stateInfo->init = new XML_S::Init(this);
    this->stateInfo->openArrow = new XML_S::OpenArrow(this);
    // this->stateInfo->declaration = new XML_S::Declaration(this);
    // this->stateInfo->comment = new XML_S::Comment(this);
    this->stateInfo->cdata= new XML_S::Cdata(this);
    this->stateInfo->attribute = new XML_S::Attribute(this);
    this->stateInfo->entity = new XML_S::Entity(this);
    this->currState = this->stateInfo->init;
    this->localEntityName = "";
}

void XML_S::Controller::ProcessCharacter(char inp){
    this->currState->ProcessCharacter(inp);
}

XML_P::XMLContext::XMLContext(std::string path){
    this->pathXML = path;
    this->fsm = new XML_S::Controller(this);
}

void XML_P::XMLContext::Execute(){
    std::ifstream ifs;
    std::cout << this->pathXML << std::endl;
    ifs.open(this->pathXML, std::ifstream::in);

    if (!ifs)
    {
    	std::cout << " Error opening input file " << std::endl ;
    	return ;
    }

    char c;
    while(!ifs.eof()){
        ifs.get(c);
        std::cout << c << std::endl;
        this->fsm->currState->ProcessCharacter(c);
    }
    ifs.close();
}

XML_P::XMLContext::~XMLContext(){
    delete fsm;
}

XML_S::Controller::~Controller(){
    delete this->stateInfo->init;
    delete this->stateInfo->openArrow;
    delete this->stateInfo->declaration;
    delete this->stateInfo->cdata;
    delete this->stateInfo->attribute;
    delete this->stateInfo->entity;
    // delete this;
}
