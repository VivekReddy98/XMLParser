/**
 * Author:    Vivek Reddy Karri
 * Created:   March 2020.
 * Project:   A SAX (Simple API for XML) style and forward only XML Parser.
 * Design:    Heavily Inspired from Java SAX Parser.
              Basically a state machine, processing every character once.
 * Complexity: Linear in number of characters.
 **/

#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>
#include <regex.h>
#include <fstream>


namespace XML_P{
    class XMLContext;
}

// All Possible States in the FSM.
namespace XML_S {
    class States;
    class Controller;
    class Base;
    class Init;
    class OpenArrow;
    class Cdata;
    class Attribute;
    class Entity;
    class Declaration;
    class EscapeHandle;
}

/**
    Some utility functions used elsewhere in the context of the project.
*/
std::string vector2path(std::vector<std::string>& path);
std::string ltrim(const std::string& s);
std::string rtrim(const std::string& s);
std::string trim(const std::string& s);

/**
    Class: XMLContext (Abstract Class)
    Usage: User have to inherit this Class and implement his own versions of the
           six virtual functionns can use these functions as Event Handlers,
           to perform anything on the data.
*/
class XML_P::XMLContext {

  public:
    XML_S::Controller* fsm;

    virtual void startDocument() = 0;
    virtual void endDocument() = 0;
    virtual void startElement(std::string& path, std::string& localelement) = 0;
    virtual void elementAttributes(std::string& path, std::unordered_map<std::string, std::string>& attributes) = 0;
    virtual void endElement(std::string& path, std::string& localelement) = 0;
    virtual void characters(std::string& body) = 0;
    XMLContext(std::string path);
    ~XMLContext();
    void Execute();
    std::string pathXML;
};

/**
    Class: XML_S::States
    Usage: Just a Simple container having all possible states.
*/
class XML_S::States{
  public:
    Base* init;
    Base* openArrow;
    Base* declaration;
    Base* cdata;
    Base* attribute;
    Base* entity;
    Base* escapeHandle;
};

/**
    Class: XML_S::Controller
    Usage: Has all the possible states accessed through this->stateInfo object.
           It Passes off the job of processing the character to whatever state present
           this->currState object.
*/
class XML_S::Controller{
  public:
    std::vector<std::string> currPath;
    XML_P::XMLContext *user;
    XML_S::Base *currState;
    XML_S::States *stateInfo;
    std::string localEntityName;
    std::string stringBody;

    ~Controller();
    Controller(XML_P::XMLContext* usr);
    void ProcessCharacter(char inp);
};

/**
    Class: XML_S::Base
    Usage: Interface to be inherited by all the states.
           Every Child Class should implement ProcessCharacter method.
*/
class XML_S::Base {
  public:
    virtual void ProcessCharacter(char inp) = 0;
};

/**
    Class: XML_S::Init
    Usage: The Initial State of the Machine.
*/
class XML_S::Init : public XML_S::Base
{
public:
    XML_S::Controller* cntrl;
    Init(XML_S::Controller* controller);
    void ProcessCharacter(char inp);
};

/**
    Class: XML_S::OpenArrow
    Usage: The current state resume to OpenArrow when the encountered input character in '<'
           Roughly Handles invoking of startElement() and endElement() functions of the user class.
*/
class XML_S::OpenArrow : public XML_S::Base
{
  public:
    int inEndTag;
    XML_S::Controller* cntrl;
    OpenArrow(XML_S::Controller* controller);
    void ProcessCharacter(char inp);
};

/**
    Class: XML_S::Declaration
    Usage: State changes to Declaration when the encountered input characters are '<?'
           Eg: <?xml version="1.0" standalone="yes"?>
*/
class XML_S::Declaration : public XML_S::Base
{
  private:
    std::string body;
    int inEnd;

  public:
    XML_S::Controller* cntrl;
    Declaration(XML_S::Controller* controller);
    void ProcessCharacter(char inp);
};

/**
    Class: XML_S::Cdata
    Usage: Handles CDATA sections and Comments,
           Technically, handles the sequence '<!'
*/
class XML_S::Cdata : public XML_S::Base
{
  private:
    int inCDataHeader;
    int inCDataFooter;
    std::string localtext;
    int inComment;

  public:
    XML_S::Controller* cntrl;
    Cdata(XML_S::Controller* controller);
    void ProcessCharacter(char inp);
};

/**
    Class: XML_S::Attribute
    Usage: Handles the Attributes of the elements enclosed inside < and >
           and invokes elementAttribute() method of the user class.
           Eg: <order id="1111">
*/
class XML_S::Attribute : public XML_S::Base
{
  private:
    std::string temp_key, temp_value;
    int inValue;

  public:
    XML_S::Controller* cntrl;
    Attribute(XML_S::Controller* controller);
    void ProcessCharacter(char inp);
};

/**
    Class: XML_S::Entity
    Usage: Handles the text contained inside an element/tag.
           Handles callinf characters() function of the user class.
*/
class XML_S::Entity : public XML_S::Base
{
  private:
    int canCData;

  public:
    XML_S::Controller* cntrl;
    Entity(XML_S::Controller* controller);
    void ProcessCharacter(char inp);
};

/**
    Class: XML_S::EscapeHandle
    Usage: Handles Escape Characters. Invoked when special characters are encountered in text.
*/
class XML_S::EscapeHandle : public XML_S::Base
{
  private:
    std::string tempString;
    std::unordered_map<std::string, std::string> specialCharMap;

  public:
    XML_S::Controller* cntrl;
    EscapeHandle(XML_S::Controller* controller);
    void ProcessCharacter(char inp);
};
