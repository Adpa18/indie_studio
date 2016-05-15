//
// Created by gaspar_q on 5/6/16.
//

#include <iostream>
#include <typeinfo>
#include <unistd.h>
#include "LuaHandler.hpp"
#include "FunctionConverter.hpp"
#include "LuaClass.hpp"

typedef struct s_test
{
    int x;
    int y;
}               t_test;

std::string tototempl("Test");

class testClass
{
public:
    testClass()
    {
        std::cout << "Nous sommes des prunes" << std::endl;
        toto = 0;
    }

public:
    static int l_tutumethod(lua_State *)
    {
        std::cout << "on appelle tutu" << std::endl;
        return 1;
    }

    static int l_newtest(lua_State *state)
    {
        Lua::LuaClass<testClass>   testClass1(false);

        std::cout << "\e[32mCREATION\e[0m" << std::endl;
        return 1;
    }

    static int l_destructest(lua_State *state)
    {
        testClass *testClass1 = Lua::LuaClass<testClass>::getThis();

        std::cout << "from lua deleting: " << testClass1 << std::endl;
        delete(testClass1);
        std::cout << "\e[31mDESTRUCTION\e[0m" << std::endl;
        return (1);
    }

private:
    int toto;
};

template <>
const std::string Lua::LuaClass<testClass>::className = "Test";

int main()
{
    lua_State   *state = Lua::acquireState();
    Lua::LuaHandler  handler;
    t_test  toto = {54, 32};
    Lua::LuaClass<testClass>   tutu;

    Lua::LuaClass<testClass>::LuaPrototype({
            {"new", testClass::l_newtest},
            {"toto", testClass::l_tutumethod},
            {"__gc", testClass::l_destructest}
    }).Register();
    handler.setScript("./iaBehaviour.lua");
//    Lua::LuaHandler &(*ftpr2)(const std::string &) = NULL;

//    ftpr2 = FunctionConverter::methodToFptr<Lua::LuaHandler &(*)(const std::string &)>(handler, &Lua::LuaHandler::operator[]);
//    ftpr2("toto");*
//    char *test = NULL;
//    char *test2 = NULL;
//    Lua::LuaHandler &(Lua::LuaHandler::*ftpr)(const std::string &) = &Lua::LuaHandler::operator[];
//    Lua::LuaHandler &(*ftpr2)(const std::string &);
//    void *decal = NULL;
//
//    std::cout << handler["computeIA"](2, 3) << std::endl;
    std::cout << handler["testuserdata"](&tutu) << std::endl;
    //    std::cout << handler["testargs"](2, 2.4, true, "On fait des test") << std::endl;
//    std::cout << "manger des haricots" << std::endl;
    lua_close(state);
//    Lua::close(state);
//    std::cout << "in c++ " << &handler << std::endl;
//    std::cout << "sizeof handler: " << sizeof(handler) << std::endl;
//    std::cout << "sizeof string: " << sizeof(std::string) << std::endl;
//    for (size_t i = 0, len = sizeof(handler); i < len; ++i)
//    {
//        if (i < 8)
//            test = (char *)(((size_t)test) | (size_t)(((unsigned char *)&handler)[i] << 8 * i));
//        else
//            test2 = (char *)(((size_t)test2) | (size_t)(((unsigned char *)&handler)[i] << 8 * i));
//        printf("%x.", ((unsigned char *)&handler)[i]);
//    }
//    std::cout << std::endl;
//    for (size_t i = 0, len = sizeof(ftpr); i < len; ++i)
//    {
//        decal = (void *)((size_t)decal | (((unsigned char *)&ftpr)[i] << i * 8));
//        printf("%x.", ((unsigned char *)&ftpr)[i]);
//        if (i < 8)
//            ((unsigned char *)&ftpr2)[i] = ((unsigned char *)&ftpr)[i];
//        else
//        {
//            ((unsigned char *)&ftpr)[i] = ((unsigned char *)&handler)[i - 8];
//            ((unsigned char *)&ftpr2)[i] = ((unsigned char *)&handler)[i - 8];
//        }
//    }
//    std::cout << std::endl;
//    printf("decal: %p\n", decal);
//
//    ((Lua::LuaHandler &(*)(const std::string &))&ftpr)("toto");
//    printf("%p\n", &);
//    printf("ret of call: %p ||| handler: %p\n", &ftpr2("toto"), &handler);
//    printf("fptr: %lx\n", ftpr);
//    printf("fptr2: %lx\n", ftpr2);
//    printf("base fptr: %lx\n", &Lua::LuaHandler::operator[]);
//    Lua::LuaHandler  &(Lua::LuaHandler::*ftp)(const std::string &) = &Lua::LuaHandler::operator[];
//    printf("%p\n", ftp);
//    printf("%p\n", &((Lua::LuaHandler &(*)(const std::string &))ftp)("toto"));
//
//    Lua::LuaHandler  &(*testfpt)(const std::string &) = (Lua::LuaHandler &(*)(const std::string &))((size_t)&handler + (size_t)decal);
//
//    printf("ftp: %p ||| obj: %p\n", testfpt, &handler);
//
//    testfpt("pénis");
//
//    printf("test2: %p %s\n", test2, test2);
//    printf("test: %p\n", test, test);
//    printf("%x\n", &Lua::LuaHandler::operator[]);
//    printf("%x\n", ftpr);
//    printf("%lu\n", sizeof(ftpr));
//    printf("\n%lx\n", typeid(&Lua::LuaHandler::operator[]).hash_code());
//    write(1, &ftpr, sizeof(&Lua::LuaHandler::operator[]));
//    write(1, (void *)&handler.operator[], 16);
//        printf("%lux\n", (size_t)&handler + (int)&Lua::LuaHandler::operator[]);
//    /*lua_State   *state;
//
//    state = luaL_newstate();
//    luaL_openlibs(state);
//    luaL_dofile(state, "./iaBehaviour.lua");
//    lua_getglobal(state, "computeIA");
//    lua_pushnumber(state, 4);
//    lua_pushnumber(state, 6);
//    lua_call(state, 2, 2);
//    std::cout << lua_tointeger(state, -1) << std::endl;
//    lua_pop(state, 1);
//    std::cout << lua_tointeger(state, -1) << std::endl;
//    lua_close(state);*/
//    return (0);
}