#include "Logger.h"
#include <iostream>

#include <chrono>
#include "../date/date.h"

using namespace TMIOSDP;

std::string Logger::getPrefix(Severity severity)
{
    std::string logDate = date::format(" %H:%M:%S] ",
        std::chrono::system_clock::now());

    switch (severity)
    {
    case Severity::WARNING:
        return "[WARNING " + logDate;
    case Severity::INFO:
        return "[INFO " + logDate;
    case Severity::DEBUG:
        return "[DEBUG " + logDate;
    case Severity::ERROR:
        return "[ERROR " + logDate;
    default:
        return "[UNKNOWN " + logDate;
    }
}

EmailLogger::EmailLogger(const std::string& emailAddress)
    : mEmailAddress(emailAddress)
{
}
EmailLogger* EmailLogger::createEmailLogger(const std::string& emailAddress)
{
    return new EmailLogger(emailAddress);
}
void EmailLogger::log(const std::string& message, Severity severity)
{
    std::cout << "Sending a report email to recipient..." << std::endl;
    std::cout << getPrefix(severity) << message << std::endl;
}

FileLogger::FileLogger(const std::string& filename)
    : mFilename(filename)
{
}
FileLogger* FileLogger::createFileLogger(const std::string& filename)
{
    return new FileLogger(filename);
}
void FileLogger::log(const std::string& message, Severity severity)
{
    std::cout << "Writing .log file..." << std::endl;
    std::cout << getPrefix(severity) << message << std::endl;
}

GithubLogger::GithubLogger(const std::string& githubToken)
    : mGithubToken(githubToken)
{
}
GithubLogger* GithubLogger::createGithubLogger(const std::string& githubToken)
{
    return new GithubLogger(githubToken);
}
void GithubLogger::log(const std::string& message, Severity severity)
{
    std::cout << "Posting a Github issue..." << std::endl;
    std::cout << getPrefix(severity) << message << std::endl;
}

SlackLogger::SlackLogger(const std::string& username)
    : mSlackUsername(username)
{
}
SlackLogger* SlackLogger::createSlackLogger(const std::string& username)
{
    return new SlackLogger(username);
}
void SlackLogger::log(const std::string& message, Severity severity)
{
    std::cout << "Sending a Slack channel notification..." << std::endl;
    std::cout << getPrefix(severity) << message << std::endl;
}