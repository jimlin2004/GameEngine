#include "ProjectParser.h"

ProjectParser::ProjectParser()
    : jsonParser(new JsonParser())
    , projectDirname(std::string())
    , projectName(std::string())
{

}

ProjectParser::~ProjectParser()
{
    delete this->jsonParser;
}

void ProjectParser::load(const char* const filePath)
{
    this->jsonParser->load(filePath);

    QFileInfo fileInfo(filePath);
    this->projectDirname = fileInfo.absolutePath().toStdString();
    QJsonObject projectProperty = this->jsonParser->query("Project").toObject();
    this->projectName = projectProperty.value("Name").toString().toStdString();
}