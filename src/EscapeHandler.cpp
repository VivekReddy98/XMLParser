#include "XMLParser.h"

XML_S::EscapeHandle::EscapeHandle(XML_S::Controller* controller){
   this->cntrl = controller;
   this->specialCharMap = {
                          {"&lt", "<"},
                          {"&gt", ">"},
                          {"&quot", "\""},
                          {"&amp","&"},
                          {"apos","\'"}
                          };
   this->tempString = "&";
}

void XML_S::EscapeHandle::ProcessCharacter(char inp){
  if (inp == ';'){
    if (this->specialCharMap.find(this->tempString) != this->specialCharMap.end()){
        this->cntrl->stringBody += this->specialCharMap[this->tempString];
    }
    //Clean UP
    this->tempString = "&";
    this->cntrl->currState = this->cntrl->stateInfo->entity;
  }
  else{
    std::string inp_s(1, inp);
    this->tempString += inp_s;
  }
}
