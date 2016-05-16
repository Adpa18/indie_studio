//
// Created by gaspar_q on 5/9/16.
//

#include <BomberMap.hpp>
#include "IAPlayer.hpp"

const std::string     IAPlayer::easyLvl = "easyBehaviour";
const std::string     IAPlayer::mediumLvl = "mediumBehaviour";
const std::string     IAPlayer::hardLvl = "hardBehaviour";

//todo implement methods to get the type/pos of the object at index
IAPlayer::IAPlayer(std::string const &name, irr::core::vector2df const &pos) :
    ACharacter(name, pos, "./media/ziggs_mad.png", "./media/ziggs_mad.png", 42),
    handler(),
    map(BomberMap::getMap())
{
    Lua::LuaClass<BomberMap>::LuaPrototype({
                                                   {"typeAtIndex", NULL},
                                                   {"posAtIndex", NULL}
                                           }).Register();
}

IAPlayer::~IAPlayer()
{

}

void IAPlayer::compute()
{
    this->action(handler[behaviour](map, getMapPos()));
}

void IAPlayer::setDifficulty(const std::string &difficulty)
{
    behaviour = difficulty;
}
