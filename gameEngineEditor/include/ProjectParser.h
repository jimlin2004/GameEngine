#ifndef PROJECT_PARSER_H
#define PROJECT_PARSER_H

#include <QFileInfo>
#include <string>
#include "JsonParser.h"

class ProjectParser
{
public:
    ProjectParser();
    ~ProjectParser();

    void load(const char* const filePath);
private:
    JsonParser* jsonParser;
    std::string projectDirname;
};

#endif