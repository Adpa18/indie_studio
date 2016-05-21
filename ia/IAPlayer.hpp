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
    IAPlayer(std::string const &, irr::core::vector2df const &, const std::string &, const std::string &, int);
    ~IAPlayer();

public:
    virtual void compute();
    void setDifficulty(const std::string &difficulty);

private:
    static int  typeAtIndex(lua_State *state);
    static int  posAtIndex(lua_State *state);
    static int  objsAtPos(lua_State *state);
    static int  getX(lua_State *state);
    static int  getY(lua_State *state);

private:
    Lua::LuaHandler handler;
    std::string behaviour;
};

#endif //CPP_INDIE_STUDIO_IAPLAYER_HPP
