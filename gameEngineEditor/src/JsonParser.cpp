#include "JsonParser.h"

JsonParser::JsonParser()
    : json(new QJsonDocument())
{

}

JsonParser::~JsonParser()
{
    delete this->json;
}

void JsonParser::load(const char* const filePath) const
{
    QFile file(filePath);
    if (!file.open(QFile::ReadOnly))
    {
        qDebug("[Error] Can not open file");
    }

    QString src = QString::fromUtf8(file.readAll());
    file.close();

    this->parse(src);
}

void JsonParser::parse(QString& src) const
{
    QJsonParseError jsonError;
    *(this->json) = QJsonDocument::fromJson(src.toUtf8(), &jsonError);
    if (jsonError.error != QJsonParseError::NoError && this->json->isNull())
        qDebug() << "[Error] Json file parse error: " << jsonError.error;
    return;
}