#include "Utility.hpp"

#include <stdexcept> 
#include <string> 
#include <map> 
#include <stack>

namespace html {
    class Element {
    public: 
        using string_iterator = std::string::iterator;
        Element(std::string); 

        static std::vector<Element> get(std::string);

        std::string name; 
        std::map<std::string, std::string> attributes; 
        std::string content; 
    private: 
        void parseAttributes(string_iterator&);
    };

    Element::Element(std::string markup) {
        auto iter = markup.begin(); 
        while(*++iter == ' ')
            ;

        if(*iter != '<') 
            throw new std::invalid_argument("Invlaid markup passed to html::Element constructor");
        
        while(*++iter == ' ')
            ;

        while(*iter != ' ' && *iter != '>') 
            name.push_back(*iter++);

        
        if(*iter != '>') 
            parseAttributes(iter);
        
        if(isSelfClosing(name))
            return; 
        
        iter++;
        std::stack<std::string> elementStack;
        while(true) {
            if(iter == markup.end()) 
                throw std::invalid_argument("No closing tag found for the element");

            if(*iter == '<') {
                std::string temp;
                if(*++iter == '/') {
                    if(elementStack.empty()) 
                        return;

                    while(*++iter != '>') 
                        temp.push_back(*iter);

                    elementStack.pop();
                    content.append("</" + temp);
                }
                else {
                    while(*iter != ' ' && *iter != '>') 
                        temp.push_back(*iter++);
                    if(!isSelfClosing(temp))
                        elementStack.push(temp);    
                    content.append("<" + temp);
                }
                temp.clear();
            }
            else 
                content.push_back(*iter++);
        }
    }

    void Element::parseAttributes(string_iterator& iter) {
        while(*++iter == ' ')
            ;

        if(*iter == '>') 
            return; 

        size_t i = 0; 
        std::string aName, aValue;
        while(true) {
            while(*iter != '=') 
                aName.push_back(*iter++);
            iter++; 
            while(*++iter != '"') 
                aValue.push_back(*iter);

            attributes.insert({aName, aValue});
            aName.clear(); 
            aValue.clear();

            while(*++iter == ' ' || *iter == '/')
                ;

            if(*iter == '>') 
                break; 
        } 
    }

    std::vector<Element> Element::get(std::string markup) {
        std::vector<Element> elements; 
        auto iter = markup.begin(); 

        while(iter != markup.end()) {
            if(*iter == '<' && *(iter+1) != '/') 
                elements.push_back(Element(std::string(iter-1, markup.end())));


            iter++;
        }

        return elements;
    }
}