#include "CoreHeaders.h"
#include "SpriteSheet.h"
#include "../Libraries/rapidjson/document.h"

namespace fw
{

    fw::SpriteSheet::SpriteSheet(char sheet)
    {

        // Load json spritesheet.
        if (sheet == 1)
        {
            const char* json = fw::LoadCompleteFile("Data/Textures/Sprites.json", nullptr);
            rapidjson::Document document;
            document.Parse(json);
            delete[] json;

            rapidjson::Value& widthValue = document["Width"];
            m_SheetWidth = widthValue.GetInt();

            rapidjson::Value& spriteArray = document["Sprites"];

            for (rapidjson::SizeType i = 0; i < spriteArray.Size(); i++)
            {
                rapidjson::Value& sprite = spriteArray[i];

                std::string spriteName = sprite["Name"].GetString();
                fw::vec2 spriteScale = fw::vec2(float(sprite["W"].GetInt()), float(sprite["H"].GetInt())) / float(m_SheetWidth);
                fw::vec2 spriteOffset = fw::vec2(float(sprite["X"].GetInt()), float(sprite["Y"].GetInt())) / float(m_SheetWidth);

                SpriteInfo NewSprite = SpriteInfo(spriteName, spriteScale, spriteOffset);

                SpriteObjects.push_back(NewSprite);

            }
        }
        else
        {
            const char* json = fw::LoadCompleteFile("Data/Textures/EnemySprites.json", nullptr);
            rapidjson::Document document;
            document.Parse(json);
            delete[] json;

            rapidjson::Value& widthValue = document["Width"];
            m_SheetWidth = widthValue.GetInt();

            rapidjson::Value& spriteArray = document["Sprites"];

            for (rapidjson::SizeType i = 0; i < spriteArray.Size(); i++)
            {
                rapidjson::Value& sprite = spriteArray[i];

                std::string spriteName = sprite["Name"].GetString();
                fw::vec2 spriteScale = fw::vec2(float(sprite["W"].GetInt()), float(sprite["H"].GetInt())) / float(m_SheetWidth);
                fw::vec2 spriteOffset = fw::vec2(float(sprite["X"].GetInt()), float(sprite["Y"].GetInt())) / float(m_SheetWidth);

                SpriteInfo NewSprite = SpriteInfo(spriteName, spriteScale, spriteOffset);

                SpriteObjects.push_back(NewSprite);

            }
        }
    }

    fw::SpriteSheet::~SpriteSheet()
    {
    }

    SpriteInfo fw::SpriteSheet::GetSpriteInfo(std::string name)
    {
        for (int i = 0; i < SpriteObjects.size(); i++)
        {
            if (name == SpriteObjects[i].SpriteName)
            {
                return SpriteObjects[i];
            }
        }
        SpriteInfo Default(std::string("Default"), fw::vec2(1,1), fw::vec2(0,0));
        return Default;
    }
    int SpriteSheet::GetSheetWidth()
    {
        return m_SheetWidth;
    }
}

