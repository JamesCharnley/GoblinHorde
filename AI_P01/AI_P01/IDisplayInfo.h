#pragma once
#include <string>

class IDisplayInfo
{
public:

    virtual void DisplayInfo(std::string& _stringRef) = 0;
};