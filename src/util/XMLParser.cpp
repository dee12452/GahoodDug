#include "XMLParser.hpp"

#include <SDL2/SDL_log.h>
#include <SDL2/SDL_rwops.h>

#define TAG "XMLParser"

static void recursiveDeleteTag(Tag *);

XMLObject * XMLParser::loadXML(const char *file) {
	SDL_RWops *ctx = SDL_RWFromFile(file, "rb");
	if (ctx == NULL) {
		SDL_Log("%s: Failed to load file \"%s\"\n", TAG, file);
		return NULL;
	}
	XMLObject *obj = new XMLObject;
	char buf[1];
	buf[0] = '\0';
	while (SDL_RWread(ctx, buf, sizeof(char), 1)) {
		obj->fileString += buf[0];
	}
	generateTags(obj);
	return obj;
}

void XMLParser::generateTags(XMLObject *obj) {
	for (unsigned int i = 0; i < obj->fileString.length();) {
		//Found a tag!
		if (obj->fileString[i] == '<' && obj->fileString[i + 1] != '/') {
			i++;

			//I don't care about the prolog or comments
			if (obj->fileString[i] == '?' || obj->fileString[i] == '!') {
				while (obj->fileString[i] != '>') {
					i++;
				}
				i++; continue;
			}

			//Get the tag
			Tag *tag = new Tag;

			//Get the id
			tag->id = "";
			while (i < obj->fileString.length()
				&& obj->fileString[i] != ' '
				&& obj->fileString[i] != '\n'
				&& obj->fileString[i] != '\r'
				&& obj->fileString[i] != '/'
				&& obj->fileString[i] != '>') {
				tag->id += obj->fileString[i];
				i++;
			}

			//Get attributes and keys
			while (obj->fileString[i] != '>'
				&& obj->fileString[i] != '/') {

				//Found an attribute
				if (obj->fileString[i] != ' '
					&& obj->fileString[i] != '\n'
					&& obj->fileString[i] != '\r') {
					std::string attr = "";
					std::string key = "";
					while (obj->fileString[i] != '=') {
						attr += obj->fileString[i];
						i++;
					}
					i++;
					while (obj->fileString[i] == ' '
						|| obj->fileString[i] == '\n'
						|| obj->fileString[i] == '\r') i++;
					int numQuotes = 0;
					while (numQuotes < 2) {
						if (obj->fileString[i] == '"') {
							i++;
							numQuotes++;
							continue;
						}
						key += obj->fileString[i];
						i++;
					}
					tag->attributes.push_back(std::pair<std::string, std::string>(attr, key));
				}
				else {
					i++;
				}
				//End found attribute

			}

			//At the end of a tag, check to see if has subtags
			//Has no subtags
			if (obj->fileString[i] == '/') {
				i++;
			}
			//Has subtags
			else {
				i++;
				generateTags(tag, obj->fileString, i);
			}

			obj->tags.push_back(tag);
		}
		i++;
	}
}

void XMLParser::generateTags(Tag *parent, const std::string &fileStr, unsigned int &i) {
	while (i < fileStr.length()) {

		//Found data
		if (fileStr[i] != ' '
			&& fileStr[i] != '\n'
			&& fileStr[i] != '\r'
			&& fileStr[i] != '<') {
			parent->data = "";
			while (fileStr[i] != '<') {
				parent->data += fileStr[i];
				i++;
			}
			while (fileStr[i] != '>') i++;
			i++;
			return;
		}

		//Found a tag!
		else if (fileStr[i] == '<') {
			i++;

			//I don't care about the prolog or comments either
			if (fileStr[i] == '?' 
				|| fileStr[i] == '!') {
				while (fileStr[i] != '>') {
					i++;
				}
				i++; continue;
			}

			//Found the end tag, go back
			else if (fileStr[i] == '/') {
				while (fileStr[i] != '>') {
					i++;
				}
				i++; 
				return;
			}

			//Get the tag
			Tag *tag = new Tag;

			//Get the id
			tag->id = "";
			while (i < fileStr.length()
				&& fileStr[i] != ' '
				&& fileStr[i] != '\n'
				&& fileStr[i] != '\r'
				&& fileStr[i] != '/'
				&& fileStr[i] != '>') {
				tag->id += fileStr[i];
				i++;
			}

			//Get attributes and keys
			while (fileStr[i] != '>'
				&& fileStr[i] != '/') {

				//Found an attribute
				if (fileStr[i] != ' '
					&& fileStr[i] != '\n'
					&& fileStr[i] != '\r') {
					std::string attr = "";
					std::string key = "";
					while (fileStr[i] != '=') {
						attr += fileStr[i];
						i++;
					}
					i++;
					while (fileStr[i] == ' '
						|| fileStr[i] == '\n'
						|| fileStr[i] == '\r') i++;
					int numQuotes = 0;
					while (numQuotes < 2) {
						if (fileStr[i] == '"') {
							i++;
							numQuotes++;
							continue;
						}
						key += fileStr[i];
						i++;
					}
					tag->attributes.push_back(std::pair<std::string, std::string>(attr, key));
				}
				else {
					i++;
				}
				//End found attribute

			}

			//At the end of a tag, check to see if has subtags
			//Has no subtags
			if (fileStr[i] == '/') {
				i++;
			}
			//Has subtags
			else {
				i++;
				generateTags(tag, fileStr, i);
			}

			parent->subTags.push_back(tag);
		}
		i++;
	}
}

void XMLParser::destroyXMLObject(XMLObject *obj) {
	if (obj == NULL) return;
	for (unsigned int i = 0; i < obj->tags.size(); i++) {
		recursiveDeleteTag(obj->tags[i]);
		obj->tags[i] = NULL;
	}
	obj->tags.clear();
	delete obj;
}

void recursiveDeleteTag(Tag *tag) {
	if (tag == NULL) return;
	for (unsigned int i = 0; i < tag->subTags.size(); i++) {
		recursiveDeleteTag(tag->subTags[i]);
		tag->subTags[i] = NULL;
	}
	tag->subTags.clear();
	delete tag;
}
