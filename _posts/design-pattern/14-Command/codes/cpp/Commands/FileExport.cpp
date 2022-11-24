#include "FileExport.h"

#include "../Project/Document.h"

#include <string>
#include "../Dependencies/pfd/portable-file-dialogs.h"

using namespace TMIOSDP;

FileExport::FileExport(Document* document)
    : mpRefDocument(document)
{

}

void FileExport::Execute()
{
    auto saveFile = pfd::save_file("Save Document", ".", { "All Files", "*" });
    std::string path = saveFile.result();
    if (!path.empty())
    {
        mpRefDocument->saveAs(path);
    }
}