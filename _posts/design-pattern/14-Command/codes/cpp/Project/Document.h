#pragma once
#include <string>
#include <fstream>

namespace TMIOSDP
{
    class FileHandle;
    class Document
    {
    public:
        Document(const std::string& fullPath);
        ~Document();
        void open(std::ios_base::openmode mode);
        void saveAs(const std::string& filePath);
        void close();
        void describe();
        uintmax_t size();
        long tellp();
        void seekp(long pos);
        long tellg();
        void seekg(long pos);
        void read(long size, std::string& data);
        void write(const std::string& data);
    private:
        FileHandle* mpFileHandle;
    };
}