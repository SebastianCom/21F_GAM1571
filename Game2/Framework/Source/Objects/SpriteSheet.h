#pragma once
#include "Framework.h"

namespace fw {

struct SpriteInfo
{
    SpriteInfo(std::string name, fw::vec2 scale, fw::vec2 offset)
    {
        SpriteName = name;
        UVScale = scale;
        UVOffset = offset;
    }
    ~SpriteInfo()
    {

    }
    std::string SpriteName = "";
    fw::vec2 UVScale = vec2(0,0);
    fw::vec2 UVOffset = vec2(0,0);
};

class SpriteSheet
{
public:
    SpriteSheet();
    virtual ~SpriteSheet();

    SpriteInfo GetSpriteInfo(std::string name);
    int GetSheetWidth();
    std::vector<SpriteInfo>(SpriteObjects);
   
protected:
    int m_SheetWidth = 0;
  
};

} // namespace fw
