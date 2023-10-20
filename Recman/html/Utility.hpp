#include <vector> 
#include <string> 

#include <algorithm>

namespace html {
    const std::vector<std::string> selfClosingTags = {
        "!doctype", 
        "!DOCTYPE",
        "area", 
        "base", 
        "br", 
        "col", 
        "embed", 
        "hr", 
        "img", 
        "input", 
        "link", 
        "meta", 
        "param", 
        "source", 
        "track", 
        "wbr"
    };

    bool isSelfClosing(std::string tagName) {
        auto iter = std::find(selfClosingTags.begin(), selfClosingTags.end(), tagName); 
        if(iter == selfClosingTags.end()) 
            return false; 

        return true;
    }
}