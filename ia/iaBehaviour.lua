--
-- Created by IntelliJ IDEA.
-- User: gaspar_q
-- Date: 5/6/16
-- Time: 4:18 PM
-- To change this template use File | Settings | File Templates.
--

--mapmeta = {}
--
--function mapmeta.tostring (map)
--    return "{"..map.x..", "..map.y.."}";
--end
--
--function mapmeta.new (o)
--    setmetatable(o, mapmeta.mt)
--    return o;
--end
--
--mapmeta.prototype = {x=0, y=0};
--mapmeta.mt = {
--    __index = mapmeta.prototype,
--    __tostring = mapmeta.tostring
--}
--
--function computeIA(x, y)
--    return x + y;
--end
--
--function testargs(a, b, c, d)
--    print("a: "..a);
--    print("b: "..b);
--    print(c);
--    print(d);
--end
--
--testobj = {state = 4};

--todo implement the three behaviours
function easyBehaviour(bomberMap, iaPos)
    local i = 0;
    local lim = MapW * MapH;

    print("wid: "..MapW);
    print("hei: "..MapH);
--    print(bomberMap);
    while (i < lim) do
        local x = (i % MapW);
        local y = math.floor(i / MapW);
        print("------index: "..i.."------");
        print("lua x: "..x);
        print("lua y: "..y);
        local objs = bomberMap:objsAtPos(x, y);
        local j = 0;
        local type;
        repeat
--            print("before typeAtIndex");
            type = objs:typeAtIndex(j);
--            print("after typeAtIndex");
            if (type ~= nil) then
                print("for j = "..j.." | type: "..type);
            end
            j = j + 1;
        until (type == nil);
        i = i + 1;
        print("-----------------");
    end
    return (1);
end

function mediumBehaviour(bomberMap, iaPos)

end

function hardBehaviour(bomberMap, iaPos)

end

function testuserdata(tutu, titi)
    tutu:toto();
    local i = Jelly.new();
    i:jellow();
--    titi:jellow();
--    print(u);
--    local d = Test.new();
--    print(d);
--    d:toto();
--    Test.toto();
--    print(u);
--    u:toto();
--    d:toto();
--    local test = Map.new({4, 3});
--    print(test);
--    local a = testobj;
--    setmetatable(a, mapmeta);
--    print("a: '");
--    print(a:state);
--    print("'");
--    setmetatable(u, {state, script})
--    print("in lua: ")
--    print(u);
--    print(u:state);
--    print(getmetatable(u))
end

--function data()
--    return 2;
--end