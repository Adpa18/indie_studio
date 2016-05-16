//
// Created by gaspar_q on 5/14/16.
//

#ifndef CPP_INDIE_STUDIO_LUACLASS_HPP
#define CPP_INDIE_STUDIO_LUACLASS_HPP

#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <memory>
#include <string.h>

extern "C" {
#include "lua-5.3.2/src/lua.h"
#include "lua-5.3.2/src/lualib.h"
#include "lua-5.3.2/src/lauxlib.h"
}

namespace Lua
{
    /**
     * \brief constants for internal Lua usage
     */
    static std::vector<std::string> registeredClasses;
    static const std::string luaPrefix = "luaL_";

    /**
     * \brief Function which will initialise the lua library and return the apropriate state
     * \param toset The lua state to set if you want to change the singleton
     * \return The pointer on the singleton that represent a lua state
     */
    static lua_State    *acquireState(lua_State *toset = NULL)
    {
        static lua_State   *state = NULL;

        if (toset == NULL && state == NULL)
        {
            state = luaL_newstate();
            luaL_openlibs(state);
        }
        else if (toset != NULL)
        {
            state = toset;
        }
        return (state);
    }

    /**
     * \brief Template class that overload a class to be a Lua usable class
     * \param classType the type of the class to overload
     */
    template <typename classType>
    class LuaClass
    {
    public:
        /**
         * \brief When you overload a class you have to specify the class name through this constant
         */
        static const std::string className;

    public:
        /**
         * \brief The principal constructor of a lua class that bind the metatable to the object
         * \param thisptr A pointer on the object to overload
         * \param todelete Tell if the object will be delete on ~LuaClass() call
         */
        LuaClass(classType *thisptr) :
                userData(NULL),
                thisptr(thisptr),
                state(acquireState()),
                todelete(true)
        {
            userData = static_cast<classType **>(lua_newuserdata(state, sizeof(*userData)));
            *userData = thisptr;
            luaL_getmetatable(state, (luaPrefix + className).c_str());
            lua_setmetatable(state, -2);
        }
        /**
         * \brief An other constructor that will be used like the constructor of the object
         * \param todelete Tells if the object will be delete on ~LuaClass() call
         * \param args The arguments of the constructor of the new object
         */
        template <typename ... Types>
        LuaClass(Types ... args) :
                LuaClass(new classType(args...))
        {
        }
        /**
         * \brief A default constructor like
         * \param todelete Tells if the object will be delete on ~LuaClass() call
         */
        LuaClass() :
                LuaClass(new classType())
        {
        }
        /**
         * \brief overload of referencing operator to get the adress of the real object
         * \return The adress of the real object
         */
        classType   *operator&()
        {
            return (thisptr);
        }
        /**
         * \brief Destructor that will delete the object only if the todelete construcor argument have been set to true
         */
        ~LuaClass()
        {
            if (todelete)
                delete(thisptr);
        }
        /**
         * \brief Tells to the class to not detele the object on destruction
         */
        void dontDelete(void)
        {
            todelete = false;
        }

    public:
        /**
         * \brief Nested class that will define the metatable of the LuaClass inside Lua
         */
        class LuaPrototype
        {
        public:
            /**
             * \brief The constructor only take a map of symbols to will be registered for the class
             * \param symbols All methods of the object
             */
            LuaPrototype(std::map<std::string, lua_CFunction> const &symbols = {}) :
                    symbols(symbols),
                    state(acquireState()),
                    registered(std::find(registeredClasses.begin(), registeredClasses.end(), className) != registeredClasses.end())
            {
            }

        public:
            /**
             * \brief Getter of prototype symbols
             * \return The table of methods of the prototypes
             */
            const std::map<std::string, lua_CFunction>  &getSymbols(void) const
            {
                return (symbols);
            }
            /**
             * \brief Convert the map into a luaL_Reg array needed by luaL_setfuncs
             * \return A unique ptr (for garbage collection) of luaL_Reg[] that can be used for metatable registration
             */
            std::unique_ptr<luaL_Reg[]>    getRegs(void) const
            {
                luaL_Reg    *regs;
                size_t      i = 0;

                regs = new luaL_Reg[symbols.size() + 1];
                for (std::map<std::string, lua_CFunction>::const_iterator it = symbols.begin(), end = symbols.end(); it != end; ++it, ++i)
                {
                    regs[i].func = it->second;
                    regs[i].name = it->first.c_str();
                }
                regs[i].name = NULL, regs[i].func = NULL;
                return (std::unique_ptr<luaL_Reg[]>(regs));
            }
            /**
             * \brief Getter for the lua state of the prototype
             * \return The lua state currently used by the prototype
             */
            const lua_State   *getState(void) const
            {
                return (state);
            }
            /**
             * \brief The access operator for assiging a new function to the prototype
             * \param name The name that will bind the function you will assign
             * \return A reference on the function binded by name
             */
            lua_CFunction &operator[](const std::string &name)
            {
                return (symbols[name]);
            }
            /**
             * \brief A simple getter ultra-const to get the function binded by name
             * \param name The name of the function to get
             * \return The function binded by name
             */
            lua_CFunction const &operator[](const std::string &name) const
            {
                return (symbols.find(name)->second);
            }
            /**
             * \brief Will register the prototype into a lua metatable, it will allow you to use the LuaClass into lua script
             */
            void Register()
            {
                if (isRegistered())
                    return;
                registered = true;
                luaL_newmetatable(state, (luaPrefix + className).c_str());
                luaL_setfuncs(state, &getRegs()[0], 0);
                lua_pushvalue(state, -1);
                lua_setfield(state, -1, "__index");
                lua_setglobal(state, className.c_str());
                registeredClasses.push_back(className);
            }
            /**
             * \brief Tells if the prototypes have already been registered, this works even if a new LuaPrototype object is created
             * \return If the Prototypes have already been registered
             */
            bool isRegistered(void) const
            {
                return (registered);
            }

        private:
            std::map<std::string, lua_CFunction>    symbols;
            lua_State *state;
            bool    registered;
        };
        /**
         * \brief Allows you to get the 'this' pointer when a method is called
         * \param n The correspond to the index of the object to get in the lua stack (1 if you are nice)
         * \return The this arguments if you call it in very first inside the method
         */
        static classType *getThis(int n = 1)
        {
            return *(classType **)luaL_checkudata(acquireState(), n, (luaPrefix + className).c_str());
        }
        /**
         * \brief An implementation of the most basic constructor for a lua class
         * \return The index of the new instance in the lua stack
         */
        static int defaultConstructor(lua_State *)
        {
            Lua::LuaClass<classType>   thisptr;

            thisptr.dontDelete();
            return (1);
        }
        /**
         * \brief An implementation of the most basic destructor for a lua class
         */
        static int defaultDestructor(lua_State *)
        {
            classType   *thisptr = getThis();

            delete(thisptr);
            return (1);
        }

    private:
        classType   **userData;
        classType   *thisptr;
        bool        todelete;

    protected:
        lua_State   *state;
    };
};

#endif //CPP_INDIE_STUDIO_LUACLASS_HPP
