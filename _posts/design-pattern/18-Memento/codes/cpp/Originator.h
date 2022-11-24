#pragma once

#include <string>
#include <stack>
#include <vector>

namespace TMIOSDP
{
    class Originator;
    class OriginatorMemento
    {
    public:
        void WrapData(const Originator& originator);
        void UnwrapData(Originator& originator);
    private:
        std::vector<uint8_t> mData;
    };

    class Originator
    {
    public:
        struct PersonalInfo
        {
            std::string name;
            std::string address;
            std::string tel;

            void PrintCurrentInfo();
        };

        Originator();
        const PersonalInfo& GetInfo() const;
        void SetInfo(const PersonalInfo& info);
        void PrintCurrentInfo();
        void SaveState();
        void RestoreState();
    private:
        PersonalInfo mInfo;
        std::stack<OriginatorMemento*> mStateHistory;
    };
}