#pragma once 

#include "Document.h"
#include <list>

namespace TMIOSDP
{
    class DocumentManager
    {
    public:
        DocumentManager();
        ~DocumentManager();
        void addNewDocument(Document* newDocument);
        void closeDocument(Document* newDocument);

        std::list<Document*> mDocuments;
    };
}