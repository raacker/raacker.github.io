#include "DocumentManager.h"

using namespace TMIOSDP;

DocumentManager::DocumentManager()
{

}

DocumentManager::~DocumentManager()
{
    for (Document* doc : mDocuments)
    {
        delete doc;
    }
    mDocuments.clear();
}


void DocumentManager::addNewDocument(Document* newDocument)
{
    mDocuments.push_back(newDocument);
}

void DocumentManager::closeDocument(Document* newDocument)
{
    mDocuments.remove(newDocument);
    delete newDocument;
}