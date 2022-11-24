#include "Originator.h"

#include "alpaca/alpaca.h"

using namespace TMIOSDP;

void OriginatorMemento::WrapData(const Originator& originator)
{
    alpaca::serialize(originator.GetInfo(), mData);
}

void OriginatorMemento::UnwrapData(Originator& originator)
{
    std::error_code ec;
    originator.SetInfo(alpaca::deserialize<Originator::PersonalInfo>(mData, ec));
}

Originator::Originator()
{
}

Originator::~Originator()
{
    while (!mStateHistory.empty())
    {
        OriginatorMemento* topState = mStateHistory.top();
        mStateHistory.pop();
        delete topState;
    }
}


void Originator::PersonalInfo::PrintCurrentInfo()
{
    std::cout << "Name : " << name << "\n";
    std::cout << "Address : " << address << "\n";
    std::cout << "Tel : " << tel << "\n\n";
}

void Originator::PrintCurrentInfo()
{
    mInfo.PrintCurrentInfo();
}

const Originator::PersonalInfo& Originator::GetInfo() const
{
    return mInfo;
}
void Originator::SetInfo(const Originator::PersonalInfo& info)
{
    mInfo = info;
}

void Originator::SaveState()
{
    mStateHistory.push(new OriginatorMemento());
    OriginatorMemento* state = mStateHistory.top();
    state->WrapData(*this);
}

void Originator::RestoreState()
{
    OriginatorMemento* topState = mStateHistory.top();
    topState->UnwrapData(*this);

    mStateHistory.pop();
    delete topState;
}
