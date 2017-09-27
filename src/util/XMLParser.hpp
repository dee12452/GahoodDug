#ifndef XML_PARSER_HPP
#define XML_PARSER_HPP

/**
 * XML Parser will parse an XML file in a tree of Tag structs
 * XMLObject contains a list of the root tags, all sub tags are nested in the root tags
 * XML Parser will return NULL if it could not find the passed file
 * XML Parser has UNDEFINED BEHAVIOR if the xml file has incorrect format
 *	- only pass in valid XML files to the parser
 * 
 * NOTE: When deleting an XMLObject, make sure to use XMLParser::destroyXMLObject(XMLObject *obj);!
 *	- This will recursively delete all of the tags in XMLObject, if you don't you'll have a memory leak!
 */

#include <vector>
#include <string>

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
	static XMLObject * loadXML(const char *pathToXmlFile);
	static void destroyXMLObject(XMLObject *xmlObj);
};

#endif 
