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
    IAPlayer(std::string const &, irr::core::vector2df const &);
    ~IAPlayer();

public:
    virtual void compute();

private:
    Lua::LuaHandler handler;
};

#endif //CPP_INDIE_STUDIO_IAPLAYER_HPP
