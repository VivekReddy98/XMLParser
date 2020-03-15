/**
 * Author:    Vivek Reddy Karri
 * Created:   March 2020.
 **/
#include "XMLParser.h"
#include <regex>

XML_S::Cdata::Cdata(XML_S::Controller* controller){
   this->cntrl = controller;
   this->inCDataHeader = 0;
   this->inCDataFooter = 0;
   this->localtext = "";
   this->inComment = 0;
}

void XML_S::Cdata::ProcessCharacter(char inp){
   if(inp == '-'){
      this->inComment += 1;
   }
   else if (inp == '['){
      this->inCDataHeader += 1;
   }
   else if (inp == ']'){
      this->inCDataFooter += 1;
   }
   else if ((inp != '-' && this->inComment == 2) || this->inCDataHeader == 1 || inp == ']'){
      // Dont do anything, this is just a comment
   }
   else if (this->inComment == 4){
      this->inComment = 0;
   }
   else if (inp == '>' && this->inCDataFooter>=2){
      this->cntrl->stringBody += this->localtext;
      this->cntrl->currState = this->cntrl->stateInfo->entity;
      this->localtext = "";
      this->inCDataHeader = 0;
      this->inCDataFooter = 0;
   }
   else {
      std::string inp_s(1, inp);
      this->localtext += inp_s;
   }
}
