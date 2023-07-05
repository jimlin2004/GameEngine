#include "runtime/compile/CompileProcess.h"

CompileProcess::CompileProcess(QTextBrowser* _textBrowerPtr)
    : consolePtr(_textBrowerPtr)
{
}

CompileProcess::~CompileProcess()
{
}

void CompileProcess::start(const std::string& projectDirPath)
{
    std::filesystem::create_directory(projectDirPath + "/build");
    connect(&this->process, &QProcess::readyReadStandardOutput, this, &CompileProcess::parseOutput);
    connect(&this->process, &QProcess::readyReadStandardError, this, &CompileProcess::parseStandError);
    connect(&this->process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &CompileProcess::finished);
    this->process.setProgram("CMD.exe");
    this->process.start();
    // this->process->start("python " + QString::fromStdString(projectDirPath + "/test.py"));
    this->process.waitForStarted();
    this->process.write(QString::fromStdString("ping 127.0.0.1\r\n").toLocal8Bit());
    // // this->process->write(QString::fromStdString("cd " + projectDirPath + "/build\r\n").toLocal8Bit());
    // this->process->write(QString::fromStdString("cd " + projectDirPath + "\r\n").toLocal8Bit());
    // this->process->write(QString::fromStdString("python test.py\r\n").toLocal8Bit());
    // // this->process->write(QString::fromStdString("cmake -G \"MinGW Makefiles\" ..\r\n").toLocal8Bit());
    this->process.closeWriteChannel();
    // this->process->waitForFinished();
    // this->process->close();
}

void CompileProcess::parseStandError()
{
    while (this->process.canReadLine())
    {
        qFatal("%s", QString::fromLocal8Bit(this->process.readLine()).toStdString().c_str());
    }
}

void CompileProcess::finished(int exitCode, QProcess::ExitStatus exitStatus)
{
    Q_UNUSED(exitCode);
    Q_UNUSED(exitStatus);
    this->process.close();
}

void CompileProcess::parseOutput()
{
    // qDebug() << QString::fromLocal8Bit(this->process.readAllStandardOutput()).toStdString().c_str();
    while (this->process.canReadLine())
    {
        qDebug("%s", QString::fromLocal8Bit(this->process.readLine()).toStdString().c_str());
    }
}