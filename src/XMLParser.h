#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>
#include <regex.h>
#include <fstream>      // std::ifstream

// This Class has to be inherited b
namespace XML_P{
    class XMLContext;
}

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
    Any User class have to inherit from this interface and can use these functions as Event Handlers,
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

class XML_S::Base {
  public:
    virtual void ProcessCharacter(char inp) = 0;
};


class XML_S::Init : public XML_S::Base
{
public:
    XML_S::Controller* cntrl;
    Init(XML_S::Controller* controller);
    void ProcessCharacter(char inp);
};

class XML_S::OpenArrow : public XML_S::Base
{
  public:
    int inEndTag;
    XML_S::Controller* cntrl;
    OpenArrow(XML_S::Controller* controller);
    void ProcessCharacter(char inp);
};

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

class XML_S::Entity : public XML_S::Base
{
  private:
    int canCData;

  public:
    XML_S::Controller* cntrl;
    Entity(XML_S::Controller* controller);
    void ProcessCharacter(char inp);
};

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

// Utility Functions
std::string vector2path(std::vector<std::string>& path);
std::string ltrim(const std::string& s);
std::string rtrim(const std::string& s);
std::string trim(const std::string& s);
