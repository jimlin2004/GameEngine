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
    QJsonValue query(const QString& key) const;
private:
    QJsonDocument* json;
    QJsonObject* jsonRoot;

    void parse(QString& src) const;
};

#endif