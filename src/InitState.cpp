/**
 * Author:    Vivek Reddy Karri
 * Created:   March 2020.
 **/
#include "XMLParser.h"

XML_S::Init::Init(XML_S::Controller* controller){
     this->cntrl = controller;
}

void XML_S::Init::ProcessCharacter(char inp){
    this->cntrl->user->startDocument();
    if (inp == '<'){
        this->cntrl->currState = this->cntrl->stateInfo->openArrow;
    }
}
