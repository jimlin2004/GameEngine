#ifndef COMPILE_PROCESS_H
#define COMPILE_PROCESS_H

#include <QProcess>
#include <filesystem>
#include <string>
#include <QTextBrowser>
#include <QObject>

class CompileProcess: public QObject
{
    Q_OBJECT;
public:
    CompileProcess(QTextBrowser* _textBrowerPtr);
    ~CompileProcess();
    void start(const std::string& projectDirPath);
private:
    QTextBrowser* consolePtr;
    QProcess process;
private slots:
    void parseOutput();
    void parseStandError();
    void finished(int exitCode, QProcess::ExitStatus exitStatus);
};

#endif