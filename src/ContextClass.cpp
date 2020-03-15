/**
 * Author:    Vivek Reddy Karri
 * Created:   March 2020.
 **/
#include "XMLParser.h"
#include <fstream>
#include <iostream>

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
        this->fsm->currState->ProcessCharacter(c);
    }
    this->endDocument();
    ifs.close();
}

/**
    Whener the user class goes out of scope this method is invoke and this inturn invokes the destructor of the
    State Controller class.
*/
XML_P::XMLContext::~XMLContext(){
    delete fsm;
}
