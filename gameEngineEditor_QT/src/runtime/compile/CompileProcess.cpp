#include "runtime/compile/CompileProcess.h"

CompileProcess::CompileProcess(QTextBrowser* _textBrowerPtr)
    : consolePtr(_textBrowerPtr)
    , isRunProject(false)
    , projectDirPath(std::string())
    , projectName(std::string())
{
    connect(&this->process, &QProcess::readyReadStandardOutput, this, &CompileProcess::parseOutput);
    connect(&this->process, &QProcess::readyReadStandardError, this, &CompileProcess::parseStandError);
    connect(&this->process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, &CompileProcess::finished);
}

CompileProcess::~CompileProcess()
{
}

void CompileProcess::compile(const std::string& projectDirPath)
{
    this->projectDirPath = projectDirPath;
    std::filesystem::create_directory(projectDirPath + "/build");
    this->process.setWorkingDirectory(QString::fromStdString(projectDirPath + "/build"));
    this->process.setProgram("CMD.exe");
    this->process.start();
    this->process.waitForStarted();
    // this->process.write(QString::fromStdString("cd " + projectDirPath + "/build\r\n").toLocal8Bit());
    this->process.write(QString::fromStdString("cmake -G \"MinGW Makefiles\" ..\r\n").toLocal8Bit());
    this->process.write(QString::fromStdString("mingw32-make\r\n").toLocal8Bit());
    this->process.write(QString::fromStdString("exit\r\n").toLocal8Bit());
    // this->process.closeWriteChannel();
}

void CompileProcess::run(const std::string& projectName, const std::string& projectDirPath)
{
    this->isRunProject = true;
    this->projectName = projectName;
    this->projectDirPath = projectDirPath;
    this->compile(projectDirPath);
}

void CompileProcess::parseStandError()
{
    this->process.setReadChannel(QProcess::StandardError);
    while (this->process.canReadLine())
    {
        qCritical("%s", QString::fromLocal8Bit(this->process.readLine()).toStdString().c_str());
    }
}

void CompileProcess::finished(int exitCode, QProcess::ExitStatus exitStatus)
{
    Q_UNUSED(exitCode);
    Q_UNUSED(exitStatus);
    this->process.close();
    if (this->isRunProject) //如果run按鍵被按下
    {
        this->callRunProcess();
    }
}

void CompileProcess::callRunProcess()
{
    qDebug("Running program\n");
    std::string program = this->projectDirPath + "/build/" + this->projectName + ".exe";
    if (std::filesystem::exists(program))
    {
        this->process.setWorkingDirectory(QString::fromStdString(this->projectDirPath + "/build"));
        this->process.setProgram(QString::fromStdString(program));
        this->process.start();
    }
    else
    {
        qCritical("File %s doesn't exists.\n", program);
    }
    this->isRunProject = false;
}

void CompileProcess::parseOutput()
{
    // qDebug() <<  QString::fromLocal8Bit(this->process.readAllStandardOutput()).toStdString().c_str();
    this->process.setReadChannel(QProcess::StandardOutput);
    while (this->process.canReadLine())
    {
        qDebug("%s", QString::fromLocal8Bit(this->process.readLine()).toStdString().c_str());
    }
}