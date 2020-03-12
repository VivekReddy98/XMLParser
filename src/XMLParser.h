#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>
#include <regex.h>
#include <fstream>      // std::ifstream

namespace XML_P{
    class XMLContext;
}

namespace XML_S {
    struct States;
    class Controller;
    class Base;
    class Init;
    class OpenArrow;
    class Declaration;
    class Comment;
    class Cdata;
    class Attribute;
    class Entity;
}

/**
    Any User class have to inherit from this interface and can use these functions as Event Handlers,
    to perform anything on the data.
*/
class XML_P::XMLContext {
  protected:
    XML_S::Controller* fsm;

  public:
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

struct XML_S::States{
    Base* init;
    Base* openArrow;
    Base* declaration;
    Base* cdata;
    Base* attribute;
    Base* entity;
};


class XML_S::Controller{
  public:
    std::vector<std::string> currPath;
    XML_P::XMLContext *user;
    XML_S::Base *currState;
    struct XML_S::States *stateInfo;
    std::string localEntityName;

    ~Controller();
    Controller(XML_P::XMLContext* usr);
    void ProcessCharacter(char inp);
};

class XML_S::Base {
  public:
    virtual void ProcessCharacter(char inp) = 0;
};


class XML_S::Init
    : public XML_S::Base
{
  public:
    XML_S::Controller* cntrl;
    Init(XML_S::Controller* controller);
    void ProcessCharacter(char inp);
};

class XML_S::OpenArrow
    : public XML_S::Base
{
  public:
    XML_S::Controller* cntrl;
    OpenArrow(XML_S::Controller* controller);
    void ProcessCharacter(char inp);
};

class XML_S::Declaration
    : public XML_S::Base
{
  public:
    XML_S::Controller* cntrl;
    Declaration(XML_S::Controller* controller);
    void ProcessCharacter(char inp);
};

class XML_S::Cdata
    : public XML_S::Base
{
  public:
    XML_S::Controller* cntrl;
    Cdata(XML_S::Controller* controller);
    void ProcessCharacter(char inp);
};

class XML_S::Attribute
    : public XML_S::Base
{
  public:
    std::string temp_key, temp_value;
    int inValue;
    XML_S::Controller* cntrl;
    Attribute(XML_S::Controller* controller);
    void ProcessCharacter(char inp);
};

class XML_S::Entity
    : public XML_S::Base
{
  public:
    int canCData;
    std::string stringBody;
    XML_S::Controller* cntrl;
    Entity(XML_S::Controller* controller);
    void ProcessCharacter(char inp);
};

std::string vector2path(std::vector<std::string>& path);
