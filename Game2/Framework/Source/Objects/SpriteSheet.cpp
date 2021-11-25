#include "CoreHeaders.h"
#include "SpriteSheet.h"
#include "../Libraries/rapidjson/document.h"

namespace fw
{

    fw::SpriteSheet::SpriteSheet()
    {

        // Load json spritesheet.
        const char* json = fw::LoadCompleteFile("Data/Textures/Sprites.json", nullptr);
        rapidjson::Document document;
        document.Parse(json);
        delete[] json;

        rapidjson::Value& widthValue = document["Width"];
        m_SheetWidth = widthValue.GetInt();
        int bp = 1;
        rapidjson::Value& spriteArray = document["Sprites"];

        for (rapidjson::SizeType i = 0; i < spriteArray.Size(); i++)
        {
            rapidjson::Value& sprite = spriteArray[i];

            std::string spriteName = sprite["Name"].GetString();
            fw::vec2 spriteScale = fw::vec2(sprite["W"].GetInt(), sprite["H"].GetInt());
            fw::vec2 spriteOffset = fw::vec2(sprite["X"].GetInt(), sprite["Y"].GetInt());

            SpriteInfo NewSprite = SpriteInfo(spriteName, spriteScale, spriteOffset);

            SpriteObjects.push_back(NewSprite);

        }
    }

    fw::SpriteSheet::~SpriteSheet()
    {
    }

    SpriteInfo fw::SpriteSheet::GetSpriteInfo(std::string name)
    {
        for (int i = 0; i < 23; i++)
        {
            if (name == SpriteObjects[i].SpriteName)
            {
                return SpriteObjects[i];
            }
        }
    }
    float SpriteSheet::GetSheetWidth()
    {
        return m_SheetWidth;
    }
}

