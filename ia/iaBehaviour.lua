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
    return (1);
end

function mediumBehaviour(bomberMap, iaPos)

end

function hardBehaviour(bomberMap, iaPos)

end

function testuserdata(u)
--    print(u);
    local d = Test.new();
    print(d);
    d:toto();
--    Test.toto();
    print(u);
    u:toto();
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