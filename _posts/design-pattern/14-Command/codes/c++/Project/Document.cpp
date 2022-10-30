#include "Document.h"
#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

namespace TMIOSDP
{
    class FileHandle
    {
    public:
        FileHandle(const std::string& path)
            : mFullPath(path)
        {
        }
        void open(std::ios_base::openmode mode)
        {
            std::fstream* pFile = new std::fstream();
            pFile->open(mFullPath, mode);

            if (!pFile->is_open())
            {
                delete pFile;
            }
            else
            {
                mpStream = pFile;
            }
        }
        void close()
        {
            if (mpStream != NULL)
            {
                std::fstream* pFile = dynamic_cast<std::fstream*>(mpStream);
                if (pFile != NULL) pFile->close();
                delete mpStream;
            }
            mpStream = NULL;
        }
        void readContent()
        {
            std::ostringstream sstr;
            sstr << mpStream->rdbuf();
            mFileContent = sstr.str();
        }
        void saveAs(const std::string& _path)
        {
            std::filesystem::path path{ _path };
            std::filesystem::create_directories(path.parent_path());

            std::ofstream ofs(path);
            ofs << mFileContent;
            ofs.close();
        }
        const std::string& content()
        {
            return mFileContent;
        }
        std::string parentPath()
        {
            return mFullPath.parent_path();
        }
        std::string filename()
        {
            return mFullPath.filename();
        }
        uintmax_t size()
        {
            return std::filesystem::file_size(mFullPath);
        }
        long tellp()
        {
            return mpStream->tellp();
        }
        void seekp(long pos)
        {
            mpStream->seekp(pos);
        }
        long tellg()
        {
            return mpStream->tellg();
        }
        void seekg(long pos)
        {
            mpStream->seekg(pos);
        }
        void read(long size, std::string& data)
        {
            mpStream->read(&data[0], size);
        }
        void write(const std::string& data)
        {
            *mpStream << data;
        }

    private:
        std::filesystem::path mFullPath;
        std::string mFileContent;
        std::iostream* mpStream;
    };
}

using namespace TMIOSDP;

Document::Document(const std::string& fullPath)
{
    mpFileHandle = new FileHandle(fullPath);
}

Document::~Document()
{
    mpFileHandle->close();
    delete mpFileHandle;
}
void Document::open(std::ios_base::openmode mode)
{
    mpFileHandle->open(mode);
    mpFileHandle->readContent();
}
void Document::saveAs(const std::string& filePath)
{
    mpFileHandle->saveAs(filePath);
}
void Document::close()
{
    mpFileHandle->close();
}

// This is not fancy but hey...
void Document::describe()
{
    std::cout << "File Name: " << mpFileHandle->filename() << std::endl;
    std::cout << "File Path: " << mpFileHandle->parentPath() << std::endl;
    std::cout << "File Size: " << mpFileHandle->size() << std::endl;
    std::cout << "File Content: " << std::endl;
    std::cout << mpFileHandle->content() << "\n" << std::endl;
}

uintmax_t Document::size()
{
    return mpFileHandle->size();
}
long Document::tellp()
{
    return mpFileHandle->tellp();
}
void Document::seekp(long pos)
{
    mpFileHandle->seekp(pos);
}
long Document::tellg()
{
    return mpFileHandle->tellg();
}
void Document::seekg(long pos)
{
    mpFileHandle->seekg(pos);
}
void Document::read(long size, std::string& data)
{
    mpFileHandle->read(size, data);
}
void Document::write(const std::string& data)
{
    mpFileHandle->write(data);
}