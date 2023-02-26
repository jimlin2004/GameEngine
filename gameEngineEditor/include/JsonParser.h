#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonParseError>
#include <QFile>
#include <QDebug>

class JsonParser
{
public:
    JsonParser();
    ~JsonParser();

    void load(const char* const filePath) const;
private:
    QJsonDocument* json;

    void parse(QString& src) const;
};

#endif