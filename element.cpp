#include "includes.h"

void CElement::add_show_callback(tShowCallback showCallback)
{
    m_show_callback = showCallback;
}

bool CElement::can_show()
{
    return m_show_callback != nullptr ? m_show_callback() : true;
}

void CElement::think(Vector2 pos, Vector2 size)
{

}