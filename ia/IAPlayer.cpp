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

template <>
const std::string Lua::LuaClass<IAPlayer>::className = "IA";

const std::string     IAPlayer::easyLvl = "easyBehaviour";
const std::string     IAPlayer::mediumLvl = "mediumBehaviour";
const std::string     IAPlayer::hardLvl = "hardBehaviour";
Lua::LuaHandler       *IAPlayer::handler;

void IAPlayer::initIA(int width, int height)
{
    Lua::LuaClass<BomberMap>::LuaPrototype({
                                                   {"objsAtPos", objsAtPos},
                                                   {"getDangerAtPos", getDangerAtPos},
                                                   {"getNbOfType", getNbOfType}
                                           }).Register();
    Lua::LuaClass<irr::core::vector2df>::LuaPrototype({
                                                              {"new", Lua::LuaClass<irr::core::vector2df>::defaultConstructor},
                                                              {"creat", createPos},
                                                              {"getX", getX},
                                                              {"getY", getY},
                                                              {"setX", setX},
                                                              {"setY", setY},
                                                              {"mul", mul},
                                                              {"add", add},
                                                              {"equal", equal},
                                                              {"__gc", Lua::LuaClass<irr::core::vector2df>::defaultDestructor}
                                                      }).Register();
    Lua::LuaClass<std::vector<AGameObject *> >::LuaPrototype({
                                                                     {"new", Lua::LuaClass<std::vector<AGameObject *> >::defaultConstructor},
                                                                     {"typeAtIndex", typeAtIndex},
                                                                     {"posAtIndex", posAtIndex},
                                                                     {"size", size},
                                                                     {"hasType", hasType},
                                                                     {"__gc", Lua::LuaClass<std::vector<AGameObject *> >::defaultDestructor}
                                                             }).Register();
    Lua::LuaClass<IAPlayer>::LuaPrototype({
                                                  {"getPos", getIAPos},
                                                  {"bombDropSimul", simulateBombDrop},
                                                  {"getFocus", getIAFocusPos},
                                                  {"setFocus", setIAFocusPos}
                                          }).Register();
    Lua::setGlobalValue(width, "MapW");
    Lua::setGlobalValue(height, "MapH");
    Lua::setGlobalValue((int)AGameObject::Type::NONE, "NONE");
    Lua::setGlobalValue((int)AGameObject::Type::CHARACTER, "CHARACTER");
    Lua::setGlobalValue((int)AGameObject::Type::BOMB, "BOMB");
    Lua::setGlobalValue((int)AGameObject::Type::ITEM, "ITEM");
    Lua::setGlobalValue((int)AGameObject::Type::BLOCK, "BLOCK");
    Lua::setGlobalValue((int)AGameObject::Type::BONUS, "BONUS");
    Lua::setGlobalValue((int)AGameObject::Type::BOOM, "BOOM");
    Lua::setGlobalValue((int)AGameObject::Type::OTHER, "OTHER");
    Lua::setGlobalValue((int)ACharacter::IDLE, "IDLE");
    Lua::setGlobalValue((int)ACharacter::LEFT, "LEFT");
    Lua::setGlobalValue((int)ACharacter::RIGHT, "RIGHT");
    Lua::setGlobalValue((int)ACharacter::UP, "UP");
    Lua::setGlobalValue((int)ACharacter::DOWN, "DOWN");
    Lua::setGlobalValue((int)ACharacter::BOMB, "DROPBOMB");
    Lua::setGlobalValue((int)ACharacter::ACT, "ACT");
    handler = new Lua::LuaHandler("./ia/iaBehaviour.lua");
}

void IAPlayer::shutDownIA()
{
    Lua::LuaClass<BomberMap>::LuaPrototype().Unregister();
    Lua::LuaClass<irr::core::vector2df>::LuaPrototype().Unregister();
    Lua::LuaClass<std::vector<AGameObject *> >::LuaPrototype().Unregister();
    Lua::LuaClass<IAPlayer>::LuaPrototype().Unregister();
    Lua::acquireState(NULL, true);
    delete(handler);
}

void	        IAPlayer::serialize(irr::io::IXMLWriter *xmlr) const
{
  irr::core::vector2df	pos = getMapPos();
  std::string		meshStr = getMesh();
  std::string		textureStr = getTexture();

  std::wstring		xValue = L"" + std::to_wstring(pos.X);
  std::wstring		yValue = L"" + std::to_wstring(pos.Y);
  std::wstring		mesh = L"" ;
  mesh.assign(meshStr.begin(), meshStr.end());

  std::wstring		texture = L"";
  texture.assign(textureStr.begin(), textureStr.end());

  std::wstring		playerName = L"";
  playerName.assign(getName().begin(), getName().end());

  xmlr->writeElement(L"IAPlayer", true,
		     L"x", xValue.c_str(),
		     L"y", yValue.c_str(),
		     L"mesh", mesh.c_str(),
		     L"texture", texture.c_str(),
		     L"name", playerName.c_str()
		     );
  xmlr->writeLineBreak();
}

//todo implement methods to get the type/pos of the object at index
IAPlayer::IAPlayer(std::string const &name, irr::core::vector2df const &pos, const std::string &mesh, const std::string &texture, int player, const std::string &diff) :
    ACharacter(name, pos, mesh, texture, player),
    behaviour(diff),
    focus(pos.X, pos.Y)
{
}

IAPlayer::~IAPlayer()
{

}

void IAPlayer::compute()
{
    Lua::setGlobalValue(BomberMap::getMap(), "bomberMap");
    this->action(static_cast<ACharacter::ACTION>((*IAPlayer::handler)[behaviour](this)));
}

void IAPlayer::setDifficulty(const std::string &difficulty)
{
    behaviour = difficulty;
}

const std::string &IAPlayer::getDifficultyFromCode(PlayerInfo::IAStrength strength)
{
    switch (strength)
    {
        case PlayerInfo::EASY:
            return IAPlayer::easyLvl;
        case PlayerInfo::MEDIUM:
            return IAPlayer::mediumLvl;
        case PlayerInfo::HARD:
            return IAPlayer::hardLvl;
        default:
            return IAPlayer::easyLvl;
    }
}

/*
 * Method for vector of gameobjects
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

int IAPlayer::size(lua_State *state)
{
    std::vector<AGameObject *>  *thisptr = Lua::LuaClass<std::vector<AGameObject *>>::getThis();

    lua_pushinteger(state, static_cast<int>(thisptr->size()));
    return 1;
}

int IAPlayer::hasType(lua_State *state)
{
    std::vector<AGameObject *>  *thisptr = Lua::LuaClass<std::vector<AGameObject *> >::getThis();
    int type = Lua::LuaClass<std::vector<AGameObject *>>::getInteger(2);
    bool isOfType = false;

    for (std::vector<AGameObject *>::iterator it = thisptr->begin(), end = thisptr->end(); it != end; ++it)
    {
        if ((*it)->getType() == type)
            isOfType = true;
    }
    lua_pushboolean(state, isOfType);
    return true;
}

/*
 * Methods for the map
 */
int IAPlayer::objsAtPos(lua_State *)
{
    BomberMap *thisptr = Lua::LuaClass<BomberMap>::getThis();
    int x = Lua::LuaClass<BomberMap>::getInteger(2);
    int y = Lua::LuaClass<BomberMap>::getInteger(3);

    Lua::LuaClass<std::vector<AGameObject *> > toreturn(thisptr->getObjsFromVector2(irr::core::vector2df(x, y)));

    toreturn.dontDelete();
    return 1;
}

int IAPlayer::getNbOfType(lua_State *state)
{
    BomberMap *thisptr = Lua::LuaClass<BomberMap>::getThis();
    int x = Lua::LuaClass<BomberMap>::getInteger(2);
    int y = Lua::LuaClass<BomberMap>::getInteger(3);
    AGameObject::Type type = static_cast<AGameObject::Type >(Lua::LuaClass<BomberMap>::getInteger(4));
    std::vector<AGameObject *>  objs = thisptr->getObjsFromVector2(irr::core::vector2df(x, y));
    int nb = 0;

    for (std::vector<AGameObject *>::iterator it = objs.begin(), end = objs.end(); it != end; ++it)
    {
        if ((*it)->getType() == type)
            ++nb;
    }
    lua_pushinteger(state, static_cast<lua_Integer >(nb));
    return 1;
}

int IAPlayer::getDangerAtPos(lua_State *state)
{
    BomberMap *thisptr = Lua::LuaClass<BomberMap>::getThis();
    int x = Lua::LuaClass<BomberMap>::getInteger(2);
    int y = Lua::LuaClass<BomberMap>::getInteger(3);
    int ret = thisptr->getDangerAtPos(irr::core::vector2df(x, y));

    if (ret == -1)
        return 0;
    lua_pushinteger(state, static_cast<lua_Integer >(ret));
    return 1;
}

/*
 * Methods for the vector2df
 */

int IAPlayer::createPos(lua_State *state)
{
    int x = Lua::LuaClass<irr::core::vector2df>::getInteger(1);
    int y = Lua::LuaClass<irr::core::vector2df>::getInteger(2);
    Lua::LuaClass<irr::core::vector2df> newpos(x, y);

    newpos.dontDelete();
    return 1;
}

int IAPlayer::getX(lua_State *state)
{
    irr::core::vector2df    *thisptr = Lua::LuaClass<irr::core::vector2df>::getThis();

    lua_pushinteger(state, static_cast<lua_Integer >(thisptr->X));
    return 1;
}

int IAPlayer::getY(lua_State *state)
{
    irr::core::vector2df    *thisptr = Lua::LuaClass<irr::core::vector2df>::getThis();

    lua_pushinteger(state, static_cast<lua_Integer >(thisptr->Y));
    return 1;
}

int IAPlayer::setX(lua_State *)
{
    irr::core::vector2df    *thisptr = Lua::LuaClass<irr::core::vector2df>::getThis();
    int toset = Lua::LuaClass<irr::core::vector2df>::getInteger(2);

    thisptr->X = toset;
    return 0;
}

int IAPlayer::setY(lua_State *)
{
    irr::core::vector2df    *thisptr = Lua::LuaClass<irr::core::vector2df>::getThis();
    int toset = Lua::LuaClass<irr::core::vector2df>::getInteger(2);

    thisptr->Y = toset;
    return 0;
}

int IAPlayer::mul(lua_State *)
{
    irr::core::vector2df    *thisptr = Lua::LuaClass<irr::core::vector2df>::getThis();
    int fact = Lua::LuaClass<irr::core::vector2df>::getInteger(2);
    irr::core::vector2df    multi = *thisptr * fact;
    Lua::LuaClass<irr::core::vector2df> torepush(multi);

    torepush.dontDelete();
    return 1;
}

int IAPlayer::add(lua_State *)
{
    irr::core::vector2df    *thisptr = Lua::LuaClass<irr::core::vector2df>::getThis();
    irr::core::vector2df    *toAdd = Lua::LuaClass<irr::core::vector2df>::getThis(2);
    irr::core::vector2df    addition = *thisptr + *toAdd;
    Lua::LuaClass<irr::core::vector2df> torepush(addition);

    torepush.dontDelete();
    return 1;
}

int IAPlayer::equal(lua_State *state)
{
    irr::core::vector2df    *thisptr = Lua::LuaClass<irr::core::vector2df>::getThis();
    irr::core::vector2df    *cmp = Lua::LuaClass<irr::core::vector2df>::getThis(2);

    lua_pushboolean(state, *thisptr == *cmp);
    return 1;
}

const std::string &IAPlayer::getDifficulty(void) const
{
    return behaviour;
}

int IAPlayer::getIAPos(lua_State *state)
{
    IAPlayer    *thisptr = Lua::LuaClass<IAPlayer>::getThis();
    Lua::LuaClass<irr::core::vector2df> toret(thisptr->getMapPos());

    toret.dontDelete();
    return 1;
}

int IAPlayer::simulateBombDrop(lua_State *state)
{
    IAPlayer    *thisptr = Lua::LuaClass<IAPlayer>::getThis();

    irr::core::vector2df    fallbackPos = BomberMap::getMap()->canDropBombSafely(thisptr->getBombContainer()->getBomb(), thisptr->getMapPos());
    if (fallbackPos == irr::core::vector2df(-1, -1))
        return (0);
    Lua::LuaClass<irr::core::vector2df> toret(fallbackPos);

    toret.dontDelete();
    return 1;
}

int IAPlayer::getIAFocusPos(lua_State *state)
{
    IAPlayer    *thisptr = Lua::LuaClass<IAPlayer>::getThis();
    Lua::LuaClass<irr::core::vector2df> topush(thisptr->focus);

    topush.dontDelete();
    return 1;
}

int IAPlayer::setIAFocusPos(lua_State *state)
{
    IAPlayer    *thisptr = Lua::LuaClass<IAPlayer>::getThis();
    irr::core::vector2df *toset = Lua::LuaClass<irr::core::vector2df>::getThis(2);

    thisptr->focus = *toset;
    return 0;
}
