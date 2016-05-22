//
// Created by veyrie_f on 5/22/16.
//

#ifndef CPP_INDIE_STUDIO_PLAYERINFO_HPP
#define CPP_INDIE_STUDIO_PLAYERINFO_HPP

#include <iostream>

/*
 * \brief This class hold the info concerning a player
 */
class PlayerInfo
{
public:
    enum IAStrength
    { EASY, MEDIUM, HARD };

public:
    PlayerInfo(std::string const& name, std::string const& skin, bool bIsIa = false, IAStrength strength = EASY);
    ~PlayerInfo();

public:
    std::string const& GetName() const;
    std::string const& GetSkin() const;
    bool GetIsIA() const;
    IAStrength GetIAStrength() const;

private:
    std::string m_name;
    std::string m_skin;
    bool m_isIa;
    IAStrength m_strength;
};


#endif //CPP_INDIE_STUDIO_PLAYERINFO_HPP
