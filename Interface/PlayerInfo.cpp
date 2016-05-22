//
// Created by veyrie_f on 5/22/16.
//

#include "PlayerInfo.hpp"

PlayerInfo::PlayerInfo(std::string const &name, std::string const &skin, bool bIsIa, PlayerInfo::IAStrength strength) :
        m_name(name),
        m_skin(skin),
        m_isIa(bIsIa),
        m_strength(strength)
{

}

PlayerInfo::~PlayerInfo()
{

}

std::string const &PlayerInfo::GetName() const
{
    return m_name;
}

std::string const &PlayerInfo::GetSkin() const
{
    return m_skin;
}

bool PlayerInfo::GetIsIA() const
{
    return m_isIa;
}

PlayerInfo::IAStrength PlayerInfo::GetIAStrength() const
{
    return m_strength;
}
