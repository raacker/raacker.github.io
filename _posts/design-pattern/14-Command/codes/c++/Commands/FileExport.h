#pragma once
#include "Command.h"

namespace TMIOSDP
{
    class Document;
    class FileExport : public Command
    {
    public:
        FileExport(Document* document);
        void Execute() override;
    private:
        Document* mpRefDocument;
    };
}