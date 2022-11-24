#include "FileReadContent.h"
#include "../Project/Document.h"
#include <iostream>
#include <sstream>

using namespace TMIOSDP;

FileReadContent::FileReadContent(Document* document)
    : mpRefDocument(document)
{
}

void FileReadContent::Execute()
{
    mpRefDocument->open(std::ios::in);
    mpRefDocument->describe();
    mpRefDocument->close();
}