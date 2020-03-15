/**
 * Author:    Vivek Reddy Karri
 * Created:   March 2020.
 **/
#include "XMLParser.h"

/*
   Whenever, any child class of XMLContext class is created, the constructor for StateController is invoked.
   So, this is invoked once and is in the very beginning of the project.
**/
XML_S::Controller::Controller(XML_P::XMLContext* usr){
    this->user = usr;
    this->stateInfo = new XML_S::States();
    this->stateInfo->init = new XML_S::Init(this);
    this->stateInfo->openArrow = new XML_S::OpenArrow(this);
    this->stateInfo->declaration = new XML_S::Declaration(this);
    this->stateInfo->cdata= new XML_S::Cdata(this);
    this->stateInfo->attribute = new XML_S::Attribute(this);
    this->stateInfo->entity = new XML_S::Entity(this);
    this->stateInfo->escapeHandle = new XML_S::EscapeHandle(this);
    this->currState = this->stateInfo->init;
    this->localEntityName = "";
    this->stringBody = "";
}

void XML_S::Controller::ProcessCharacter(char inp){
    this->currState->ProcessCharacter(inp);
}

// Manual Destructor to clean up all the heap allocated objects/States
XML_S::Controller::~Controller(){
    delete this->stateInfo->init;
    delete this->stateInfo->openArrow;
    delete this->stateInfo->declaration;
    delete this->stateInfo->cdata;
    delete this->stateInfo->attribute;
    delete this->stateInfo->entity;
    delete this->stateInfo->escapeHandle;
    delete this->stateInfo;
    // delete this;
}
