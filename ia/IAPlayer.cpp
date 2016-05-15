//
// Created by gaspar_q on 5/9/16.
//

#include <BomberMap.hpp>
#include "IAPlayer.hpp"

IAPlayer::IAPlayer(std::string const &name, irr::core::vector2df const &pos) :
    ACharacter(name, pos, "./media/ziggs_mad.png", "./media/ziggs_mad.png", 42),
    handler("./ia/iaBehaviour.lua")
{

}

IAPlayer::~IAPlayer()
{

}

void IAPlayer::compute()
{
    handler["computeIA"](&BomberMap::getMap());
}
