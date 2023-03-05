#include "JsonParser.h"

JsonParser::JsonParser()
    : json(new QJsonDocument())
    , jsonRoot(new QJsonObject())
{

}

JsonParser::~JsonParser()
{
    delete this->json;
    delete this->jsonRoot;
}

void JsonParser::load(const char* const filePath) const
{
    QFile file(filePath);
    if (!file.open(QFile::ReadOnly))
    {
        qCritical("[Error] Can not open file at %s\n", filePath);
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
    {
        qCritical() << "[Error] Json file parse error: " << jsonError.error << "\n";
        return;
    }
    *(this->jsonRoot) = this->json->object();
    return;
}

QJsonValue JsonParser::query(const QString& key) const
{
    return this->jsonRoot->value(key);
}