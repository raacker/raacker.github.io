#pragma once
#include "Command.h"
#include <string>

namespace TMIOSDP
{
    class Document;
    class FileAppend : public Command
    {
    public:
        FileAppend(Document* document, const std::string& data);
        void Execute() override;
        void Rollback() override;
    private:
        Document* mpRefDocument;
        std::string mData;
        long mPreviousPos;
    };
}