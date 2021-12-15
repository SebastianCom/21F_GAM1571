#include "Framework.h"
#include "DataTypes.h"

class PlayerController
{
public:
    PlayerController();
    virtual ~PlayerController();

    void OnEvent(fw::Event* pEvent);

    bool IsUpHeld()    { return m_Up; }
    bool IsDownHeld()  { return m_Down; }
    bool IsLeftHeld()  { return m_Left; }
    bool IsRightHeld() { return m_Right; }
    bool IsPushHeld()  { return m_Push; }
    bool IsPullHeld() { return m_Pull; }

    bool m_Up;
    bool m_Down;
    bool m_Left;
    bool m_Right;
    bool m_Push;
    bool m_Pull;

protected:

};
