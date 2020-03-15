/**
 * Author:    Vivek Reddy Karri
 * Created:   March 2020.
 **/
#include "XMLParser.h"
#include <regex>

XML_S::Entity::Entity(XML_S::Controller* controller){
   this->cntrl = controller;
   this->canCData = 0;
}

void XML_S::Entity::ProcessCharacter(char inp){

  std::regex ignore ("^[\r\t\f\v\n ]+$");
  if (inp == '<'){ //&& !std::regex_match (this->cntrl->stringBody, ignore)
      this->canCData = 1;
  }
  else if (inp != '!' && this->canCData == 1){
      if (!std::regex_match (this->cntrl->stringBody, ignore)){ 
        this->cntrl->stringBody = trim(this->cntrl->stringBody);
        this->cntrl->user->characters(this->cntrl->stringBody);
        this->cntrl->stringBody = "";
      }
      this->canCData = 0;
      this->cntrl->currState = this->cntrl->stateInfo->openArrow;
      this->cntrl->currState->ProcessCharacter(inp);
  }
  else if (inp == '!' && this->canCData == 1){
      this->cntrl->currState = this->cntrl->stateInfo->cdata;
  }
  else if (inp == '&'){
      this->cntrl->currState = this->cntrl->stateInfo->escapeHandle;
  }
  else {
      std::string inp_s(1, inp);
      this->cntrl->stringBody += inp_s;
  }

}
