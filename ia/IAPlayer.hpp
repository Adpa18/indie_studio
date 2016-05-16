//
// Created by gaspar_q on 5/9/16.
//

#ifndef CPP_INDIE_STUDIO_IAPLAYER_HPP
#define CPP_INDIE_STUDIO_IAPLAYER_HPP

#include <ACharacter.hpp>
#include "LuaHandler.hpp"

class IAPlayer : public ACharacter
{
public:
    static const std::string     easyLvl;
    static const std::string     mediumLvl;
    static const std::string     hardLvl;

public:
    IAPlayer(std::string const &, irr::core::vector2df const &);
    ~IAPlayer();

public:
    virtual void compute();
    void setDifficulty(const std::string &difficulty);

private:
    Lua::LuaHandler handler;
    Lua::LuaClass<BomberMap> map;
    std::string behaviour;
};

template <>
const std::string Lua::LuaClass<BomberMap>::className = "BomberMap";

#endif //CPP_INDIE_STUDIO_IAPLAYER_HPP
