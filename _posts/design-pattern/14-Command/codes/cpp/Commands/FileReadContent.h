#pragma once
#include "Command.h"
#include <string>

namespace TMIOSDP
{
    class Document;
    class FileReadContent : public Command
    {
    public:
        FileReadContent(Document* document);
        void Execute() override;
    private:
        Document* mpRefDocument;
    };
}