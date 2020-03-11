#include "XMLParser.h"

XML_S::Base::Init(XML_S::Base* currState){
    this->stateMetaData = currState;
}

XML_S::Base::~Init(){
    delete this;
}

void XML_S::Base::ProcessCharacter(char inp){

}
