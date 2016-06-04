//
// Created by gaspar_q on 6/4/16.
//

#ifndef CPP_INDIE_STUDIO_LUASCRIPT_HPP
# define CPP_INDIE_STUDIO_LUASCRIPT_HPP

# include "LuaClass.hpp"

namespace Lua
{
    class LuaScript
    {
    public:
        LuaScript();
        LuaScript(LuaScript const &);
        ~LuaScript();
        LuaScript   &operator=(LuaScript const &);

    public:
        lua_State   *operator*(void);

    private:
        lua_State   *state;
    };
};

#endif //CPP_INDIE_STUDIO_LUASCRIPT_HPP
