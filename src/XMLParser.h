#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>

namespace XML_P{
    class XMLContext;
}

namespace XML_S {
    class Base;
    class Init;
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
    XML_S::Base* fsm;

  public:
    virtual void startDocument() = 0;
    virtual void endDocument() = 0;
    virtual void startElement(std::string& path, std::string& localelement, std::unordered_map& attributes) = 0;
    virtual void endElement(std::string& path, std::string& localelement, std::unordered_map& attributes) = 0;
    virtual void characters(std::string& body) = 0;
    XMLContext(std::string path);
    Execute();
};


class XML_S::Base {
  protected:
    std::vector<std::string> currPath;
    XML_P::XMLContext *user;
    XML_S::Base *currState;

  public:
    Base(XML_P::XMLContext* usr);
    virtual void ProcessCharacter(char inp);
};

class XML_S::Init
    : public XML_S::Base
{
  protected:
    XML_S::Base *stateMetaData;

  public:
    Init(XML_S::Base* usr);
    ~Init();
    void ProcessCharacter(char inp);
};
