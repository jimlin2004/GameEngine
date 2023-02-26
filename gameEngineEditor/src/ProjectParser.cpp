#include "ProjectParser.h"

ProjectParser::ProjectParser()
    : jsonParser(new JsonParser())
{

}

ProjectParser::~ProjectParser()
{
    delete this->jsonParser;
}

void ProjectParser::load(const char* const filePath)
{
    this->jsonParser->load(filePath);

    this->projectDirname = QFileInfo(filePath).absolutePath().toStdString();
}