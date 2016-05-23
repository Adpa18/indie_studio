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
    static Lua::LuaHandler       handler;

public:
    IAPlayer(std::string const &, irr::core::vector2df const &, const std::string &, const std::string &, int);
    ~IAPlayer();

public:
    virtual void compute();
  virtual void	        serialize(irr::io::IXMLWriter *xmlr) const;
    void setDifficulty(const std::string &difficulty);
    const std::string   &getDifficulty(void) const;

public:
    static void initIA();
    static void shutDownIA();

private:
    static int  typeAtIndex(lua_State *state);
    static int  posAtIndex(lua_State *state);
    static int  size(lua_State *state);
    static int  hasType(lua_State *state);
    static int  objsAtPos(lua_State *state);
    static int  createPos(lua_State *state);
    static int  getX(lua_State *state);
    static int  getY(lua_State *state);
    static int  setX(lua_State *state);
    static int  setY(lua_State *state);
    static int  mul(lua_State *state);
    static int  add(lua_State *state);
    static int  equal(lua_State *state);

private:
    std::string behaviour;
    irr::core::vector2df focus;
};

#endif //CPP_INDIE_STUDIO_IAPLAYER_HPP
