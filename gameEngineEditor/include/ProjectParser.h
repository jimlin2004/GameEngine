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
    inline std::string getProjectDirname() const { return projectDirname; }
    inline std::string getProjectName() const { return projectName; }
private:
    JsonParser* jsonParser;
    std::string projectDirname;
    std::string projectName;
};

#endif