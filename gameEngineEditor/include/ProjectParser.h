#ifndef PROJECT_PARSER_H
#define PROJECT_PARSER_H

#include "json/json.hpp"
#include <string>

namespace GameEngineEditor
{
    class ProjectParser
    {
        using Json = nlohmann::json;
    public:
        ProjectParser();
        void load(const std::string& projectPath);

        inline std::string getProjectPath() const
        {
            return this->projectPath;
        }

        inline std::string getProjectDirname() const
        {
            return this->projectDirname;
        }

        inline std::string getProjectName() const
        {
            return this->projectName;
        }
    private:
        std::string projectPath;
        std::string projectDirname;
        std::string projectName;
    };
}

#endif