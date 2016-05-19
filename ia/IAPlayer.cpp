//
// Created by gaspar_q on 5/9/16.
//

#include <BomberMap.hpp>
#include "IAPlayer.hpp"

template <>
const std::string Lua::LuaClass<BomberMap>::className = "BomberMap";

template <>
const std::string Lua::LuaClass<irr::core::vector2df>::className = "Vector2";

const std::string     IAPlayer::easyLvl = "easyBehaviour";
const std::string     IAPlayer::mediumLvl = "mediumBehaviour";
const std::string     IAPlayer::hardLvl = "hardBehaviour";

//todo implement methods to get the type/pos of the object at index
IAPlayer::IAPlayer(std::string const &name, irr::core::vector2df const &pos, const std::string &mesh, const std::string &texture, int player) :
    ACharacter(name, pos, mesh, texture, player),
    handler(),
    map(BomberMap::getMap()),
    behaviour(IAPlayer::easyLvl)
{
    map.dontDelete();
    Lua::LuaClass<BomberMap>::LuaPrototype({
                                                   {"typeAtIndex", typeAtIndex},
                                                   {"posAtIndex", posAtIndex}
                                           }).Register();
    Lua::LuaClass<irr::core::vector2df>::LuaPrototype({
                                                              {"new", Lua::LuaClass<irr::core::vector2df>::defaultConstructor},
                                                              {"getX", getX},
                                                              {"getY", getY},
                                                              {"__gc", Lua::LuaClass<irr::core::vector2df>::defaultDestructor}
                                                      }).Register();
    handler.setScript("./ia/iaBehaviour.lua");
}

IAPlayer::~IAPlayer()
{

}

void IAPlayer::compute()
{
    Lua::LuaClass<irr::core::vector2df> pos(getMapPos());

    pos.dontDelete();
    this->action(static_cast<ACharacter::ACTION>(handler[behaviour](&map, &pos)));
}

void IAPlayer::setDifficulty(const std::string &difficulty)
{
    behaviour = difficulty;
}

/*
 * Methods for the map
 */
int IAPlayer::typeAtIndex(lua_State *state)
{
    BomberMap   *thisptr = Lua::LuaClass<BomberMap>::getThis();
    int     index = Lua::LuaClass<BomberMap>::getInteger(2);

    if ((size_t)index >= thisptr->getCharacters().size())
        return 0;
    lua_pushinteger(state, thisptr->getCharacters()[index]->getType());
    return 1;
}

int IAPlayer::posAtIndex(lua_State *state)
{
    BomberMap   *thisptr = Lua::LuaClass<BomberMap>::getThis();
    int     index = Lua::LuaClass<BomberMap>::getInteger(2);

    if ((size_t)index >= thisptr->getCharacters().size())
        return 0;

    Lua::LuaClass<irr::core::vector2df> toreturn(thisptr->getCharacters()[index]->getMapPos());
    toreturn.dontDelete();
    return 1;
}

/*
 * Methods for the vector2df
 */

int IAPlayer::getX(lua_State *state)
{
    irr::core::vector2df    *thisptr = Lua::LuaClass<irr::core::vector2df>::getThis();

    lua_pushnumber(state, thisptr->X);
    return 1;
}

int IAPlayer::getY(lua_State *state)
{
    irr::core::vector2df    *thisptr = Lua::LuaClass<irr::core::vector2df>::getThis();

    lua_pushnumber(state, thisptr->Y);
    return 1;
}
