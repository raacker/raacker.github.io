#pragma once
#include "Command.h"

namespace TMIOSDP
{
    class DocumentManager;
    class FileImport : public Command
    {
    public:
        FileImport(DocumentManager* manager);
        void Execute() override;
    private:
        DocumentManager* mpRefDocumentManager;
    };
}