#include "FileImport.h"

#include "../Project/DocumentManager.h"
#include "../Project/Document.h"

#include <string>
#include "../Dependencies/pfd/portable-file-dialogs.h"

using namespace TMIOSDP;

FileImport::FileImport(DocumentManager* manager)
    : mpRefDocumentManager(manager)
{

}

void FileImport::Execute()
{
    auto openFile = pfd::open_file("Open Document", ".", { "All Files", "*" }, pfd::opt::multiselect);
    std::vector<std::string> paths = openFile.result();
    if (!paths.empty())
    {
        for (std::string& path : paths)
        {
            Document* newDocument = new Document(path);
            mpRefDocumentManager->addNewDocument(newDocument);
        }
    }
}