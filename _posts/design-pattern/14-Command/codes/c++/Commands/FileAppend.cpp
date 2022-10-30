#include "FileAppend.h"
#include "../Project/Document.h"
#include <iostream>
#include <sstream>

using namespace TMIOSDP;

FileAppend::FileAppend(Document* document, const std::string& data)
    : mpRefDocument(document),
    mData(data)
{
}

void FileAppend::Execute()
{
    mpRefDocument->close();
    mpRefDocument->open(std::ios_base::app);
    mPreviousPos = mpRefDocument->tellp();
    mpRefDocument->write(mData);
    mpRefDocument->close();
}

void FileAppend::Rollback()
{
    mpRefDocument->close();
    mpRefDocument->open(std::ios::in);
    std::string originalData;
    originalData.resize(mPreviousPos);
    mpRefDocument->seekg(0);
    mpRefDocument->read(mPreviousPos, originalData);
    mpRefDocument->close();

    mpRefDocument->open(std::ios::out);
    mpRefDocument->write(originalData);
    mpRefDocument->close();
}