/**
 * Author:    Vivek Reddy Karri
 * Created:   March 2020.
 **/
#include "XMLParser.h"
#include <regex>

XML_S::Declaration::Declaration(XML_S::Controller* controller){
   this->cntrl = controller;
   this->body = "";
   this->inEnd = 0;
}

void XML_S::Declaration::ProcessCharacter(char inp){
    if (inp == '>' && this->inEnd == 1){
        std::string temp = "XML DESCRIPTION TAG: ";
        temp += this->body;
        temp = trim(temp);
        this->cntrl->user->characters(temp);
        this->cntrl->currState = this->cntrl->stateInfo->entity;

        // Clean Up
        this->body = "";
        this->inEnd = 0;
    }
    else if(inp == '?'){
        this->inEnd = 1;
    }
    else{
      std::string inp_s(1, inp);
      this->body += inp_s;
    }
}
