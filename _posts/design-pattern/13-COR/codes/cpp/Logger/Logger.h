#pragma once
#include <string>

namespace TMIOSDP
{
    class Logger
    {
    public:
        enum class Severity : int
        {
            WARNING,
            INFO,
            DEBUG,
            ERROR,
        };
        Logger(){};
        virtual ~Logger() {};
        virtual void log(const std::string& message, Severity severity) = 0;
        std::string getPrefix(Severity severity);
    };

    class EmailLogger : public Logger
    {
    private:
        EmailLogger(const std::string& emailAddress);
    public:
        ~EmailLogger(){}
        static EmailLogger* createEmailLogger(const std::string& emailAddress);
        EmailLogger() : Logger() {};
        void log(const std::string& message, Severity severity) override;
    private:
        std::string mEmailAddress;
    };

    class FileLogger : public Logger
    {
    private:
        FileLogger(const std::string& filename);
    public:
        ~FileLogger(){}
        static FileLogger* createFileLogger(const std::string& filename);
        FileLogger() : Logger() {};
        void log(const std::string& message, Severity severity) override;
    private:
        std::string mFilename;
    };

    class GithubLogger : public Logger
    {
    private:
        GithubLogger(const std::string& githubToken);
    public:
        ~GithubLogger(){}
        static GithubLogger* createGithubLogger(const std::string& githubToken);
        GithubLogger() : Logger() {};
        void log(const std::string& message, Severity severity) override;
    private:
        std::string mGithubToken;
    };

    class SlackLogger : public Logger
    {
    private:
        SlackLogger(const std::string& username);
    public:
        ~SlackLogger(){}
        static SlackLogger* createSlackLogger(const std::string& username);
        SlackLogger() : Logger() {};
        void log(const std::string& message, Severity severity) override;
    private:
        std::string mSlackUsername;
    };
}