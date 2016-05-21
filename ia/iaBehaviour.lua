--
-- Created by IntelliJ IDEA.
-- User: gaspar_q
-- Date: 5/6/16
-- Time: 4:18 PM
-- To change this template use File | Settings | File Templates.
--

--todo implement the three behaviours
function easyBehaviour(bomberMap, iaPos)
    local i = 0;
    local lim = MapW * MapH;

--    print("wid: "..MapW);
--    print("hei: "..MapH);
--    print("iapos("..iaPos:getX()..", "..iaPos:getY()..")");
    while (i < lim) do
        local x = (i % MapW);
        local y = math.floor(i / MapW);
        local objs = bomberMap:objsAtPos(x, y);
        local j = 0;
        local type;
        repeat
            type = objs:typeAtIndex(j);
            if (type ~= nil) then
--                print("Object n°"..j.." at ("..x..", "..y..") of type "..type);
            end
            j = j + 1;
        until (type == nil);
        i = i + 1;
    end
    return (math.random(IDLE, ACT));
end

function mediumBehaviour(bomberMap, iaPos)

end

function hardBehaviour(bomberMap, iaPos)

end