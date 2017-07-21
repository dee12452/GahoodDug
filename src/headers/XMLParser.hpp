#ifndef XML_PARSER_HPP
#define XML_PARSER_HPP

#include <vector>

typedef struct Tag {
	std::vector<Tag *> subTags;
	std::string id;
	std::vector<std::pair<std::string, std::string>> attributes;
	std::string data;
} Tag;

typedef struct XMLObject {
	std::vector<Tag *> tags;
	std::string fileString;
} XMLObject;

class XMLParser {
private:
	XMLParser() {}
	~XMLParser() {}
	static void generateTags(XMLObject *);
	static void generateTags(Tag *, const std::string &, unsigned int &);

public:
	static XMLObject * loadXML(const char *);
	static void destroyXMLObject(XMLObject *);
};

#endif 