//
// Created by gaspar_q on 5/9/16.
//

#include <BomberMap.hpp>
#include "IAPlayer.hpp"

template <>
const std::string Lua::LuaClass<BomberMap>::className = "BomberMap";

template <>
const std::string Lua::LuaClass<irr::core::vector2df>::className = "Vector2";

template <>
const std::string Lua::LuaClass<std::vector<AGameObject *> >::className = "GameObjectArray";

const std::string     IAPlayer::easyLvl = "easyBehaviour";
const std::string     IAPlayer::mediumLvl = "mediumBehaviour";
const std::string     IAPlayer::hardLvl = "hardBehaviour";
Lua::LuaHandler       IAPlayer::handler;

//todo implement methods to get the type/pos of the object at index
IAPlayer::IAPlayer(std::string const &name, irr::core::vector2df const &pos, const std::string &mesh, const std::string &texture, int player) :
    ACharacter(name, pos, mesh, texture, player),
    behaviour(IAPlayer::easyLvl)
{
}

IAPlayer::~IAPlayer()
{

}

void IAPlayer::compute()
{
    this->action(static_cast<ACharacter::ACTION>(IAPlayer::handler[behaviour](BomberMap::getMap(), new irr::core::vector2df(getMapPos()))));
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
    std::vector<AGameObject *> *thisptr = Lua::LuaClass<std::vector<AGameObject *> >::getThis();
    int index = Lua::LuaClass<BomberMap>::getInteger(2);

    if ((size_t)index >= thisptr->size())
        return 0;
    lua_pushinteger(state, (*thisptr)[index]->getType());
    return 1;
}

int IAPlayer::posAtIndex(lua_State *)
{
    std::vector<AGameObject *> *thisptr = Lua::LuaClass<std::vector<AGameObject *> >::getThis();
    int index = Lua::LuaClass<BomberMap>::getInteger(2);

    if ((size_t)index >= thisptr->size())
        return 0;

    Lua::LuaClass<irr::core::vector2df> toreturn((*thisptr)[index]->getMapPos());
    toreturn.dontDelete();
    return 1;
}

int IAPlayer::objsAtPos(lua_State *)
{
    BomberMap *thisptr = Lua::LuaClass<BomberMap>::getThis();
    int x = Lua::LuaClass<BomberMap>::getInteger(2);
    int y = Lua::LuaClass<BomberMap>::getInteger(3);

    Lua::LuaClass<std::vector<AGameObject *> > toreturn(thisptr->getObjsFromVector2(irr::core::vector2df(x, y)));

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

void IAPlayer::initIA()
{
    Lua::LuaClass<BomberMap>::LuaPrototype({
                                                   {"objsAtPos", objsAtPos}
                                           }).Register();
    Lua::LuaClass<irr::core::vector2df>::LuaPrototype({
                                                              {"new", Lua::LuaClass<irr::core::vector2df>::defaultConstructor},
                                                              {"getX", getX},
                                                              {"getY", getY},
                                                              {"__gc", Lua::LuaClass<irr::core::vector2df>::defaultDestructor}
                                                      }).Register();
    Lua::LuaClass<std::vector<AGameObject *> >::LuaPrototype({
                                                                     {"new", Lua::LuaClass<std::vector<AGameObject *> >::defaultConstructor},
                                                                     {"typeAtIndex", typeAtIndex},
                                                                     {"posAtIndex", posAtIndex},
                                                                     {"__gc", Lua::LuaClass<std::vector<AGameObject *> >::defaultDestructor}
                                                             }).Register();
    Lua::setGlobalValue(BomberMap::getMap()->getSize(), "MapW");
    Lua::setGlobalValue(BomberMap::getMap()->getSize(), "MapH");
    handler.setScript("./ia/iaBehaviour.lua");
}

void IAPlayer::shutDownIA()
{
    lua_close(Lua::acquireState());
}
