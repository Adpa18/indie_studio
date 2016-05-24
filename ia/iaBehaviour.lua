--
-- Created by IntelliJ IDEA.
-- User: gaspar_q
-- Date: 5/6/16
-- Time: 4:18 PM
-- To change this template use File | Settings | File Templates.
--

function dirTab()
    return {[RIGHT] = Vector2.creat(1, 0), [LEFT] = Vector2.creat(-1, 0), [UP] = Vector2.creat(0, 1), [DOWN] = Vector2.creat(0, -1)};
end

function ripairs(t)
    local max = 1
    while t[max] ~= nil do
        max = max + 1
    end
    local function ripairs_it(t, i)
        i = i-1
        local v = t[i]
        if v ~= nil then
            return i,v
        else
            return nil
        end
    end
    return ripairs_it, t, max
end

function getDirFromCode(code)
    return (dirTab()[code]);
end

posSeen = {};

function isInMap(pos)
    if (pos:getX() < 0 or pos:getX() >= MapW or
        pos:getY() < 0 or pos:getY() >= MapH) then
        return (false);
    end
    return (true);
end

function canMoveOnPos(pos)
--    local tocheck = bomberMap:objsAtPos(pos:getX(), pos:getY());
    local tocheck = bomberMap:getDangerAtPos(pos:getX(), pos:getY());

    if (tocheck ~= NONE  or
            isInMap(pos) == false) then
        return (false);
    end
    return true;
end

function getPossiblePos(pos)
    local tocheck = dirTab();
    local possib = {};
    local i = 0;

--    print("from ("..pos:getX()..", "..pos:getY()..")");
    for k, dir in pairs(tocheck) do
        local gonnasee = pos:add(dir);
        if (canMoveOnPos(gonnasee)) then
            i = i + 1;
            possib[i] = k;
--            print("move "..k.." is possible");
--        else
--            print("move "..k.." is impossible");
--            print("position ("..gonnasee:getX()..", "..gonnasee:getY()..") is unreachable");
        end
    end
--    print(i.." moves possible");
    return possib, i;
end

function findFirstImpasse(pos)
    local directions = dirTab();

    posSeen[pos:getX() + pos:getY() * MapW] = true;
--    print("We are on ("..pos:getX()..", "..pos:getY()..")");
    for _, dir in pairs(directions) do
        local togo = pos:add(dir);

--        print("pos("..pos:getX()..", "..pos:getY()..") + dir("..dir:getX()..", "..dir:getY()..") = togo("..togo:getX()..", "..togo:getY()..")");
        if (posSeen[togo:getX() + MapW * togo:getY()] == nil and canMoveOnPos(togo)) then
--            local tolook = bomberMap:objsAtPos(xloop, yloop);

--            print("We are checking ("..xloop..", "..yloop..")");
--            print("    this case has "..tolook:size().." type");
--            if (tolook:size() == 0) then
--                print("from ("..pos:getX()..", "..pos:getY()..") case("..xloop..", "..yloop..") is empty");
--                local togo = Vector2.creat(xloop, yloop);
--                print("to go: ("..togo:getX()..", "..togo:getY()..")");
--                togo:setX(xloop);
--                togo:setY(yloop);
            return (findFirstImpasse(togo));
        end
    end
    return (pos);
end

--[[function isCraignos(pos)
    local i = 0;
    local posToCheck = dirTab();

--    print("check pos: ("..pos:getX()..", "..pos:getY()..")");
    while (i <= 3 and (posToCheck[1] ~= nil or posToCheck[2] ~= nil or posToCheck[3] ~= nil or posToCheck[4] ~= nil)) do
--        print("for i = "..i);
        for k, dir in ripairs(posToCheck) do
            local newpos = pos:add(dir:mul(i));
            local tolook = bomberMap:objsAtPos(newpos:getX(), newpos:getY());
            --            print("move: "..k);
--            if (posToCheck[j] ~= nil) then

--                                print("checking: ("..newpos:getX()..", "..newpos:getY()..")");
--                                print("    result of ("..dir:getX()..", "..dir:getY()..") * "..i.." + ("..pos:getX()..", "..pos:getY()..")");

            if (tolook:hasType(BOMB) or tolook:hasType(BOOM)) then
--                                            print("is craignos");
                return (true);
            elseif (canMoveOnPos(newpos) == false) then
--                    print("----removing "..k.."----");
                table.remove(posToCheck, k);
            end
--            end
        end
        i = i + 1;
    end
--    print("is not craignos");
    return (false);
end]]

--[[function getUncraignosMove(possiblePos, pos)
    local possib = {};
    local i = 0;

    for _, poscode in pairs(possiblePos) do
--        print("code: "..poscode);
        local gonnasee = pos:add(getDirFromCode(poscode));
--        if (canMoveOnPos(gonnasee)) then
--            print("can move on ("..gonnasee:getX()..", "..gonnasee:getY()..")");
--        else
--            print("can not move on ("..gonnasee:getX()..", "..gonnasee:getY()..")");
--        end
        if (canMoveOnPos(gonnasee)]]--[[ and isCraignos(gonnasee) == false]]--[[) then
--            print("We found a move: "..poscode);
            i = i + 1;
            possib[i] = poscode;
--        else
--            print("Move "..poscode.." not valid");
        end
    end
    return possib, i;
end]]

function waitBombOrMove(pos, focus)
    local possibMove, nbPossib = getPossiblePos(pos);
--    local uncmov, nbmov = getUncraignosMove(possibMove, pos);

--    print("wait bomb or move from: ("..pos:getX()..", "..pos:getY()..")");
--    print("focus = ("..focus:getX()..", "..focus:getY()..")");
    if (pos:equal(focus)) then
--        print("-----------------it is equal-----------------");
--        if (isCraignos(pos)) then
--            print("-----------------but craignos-----------------");
--            posSeen = {};
--            if (nbPossib > 0) then
--                return possibMove[math.random(1, nbPossib)], findFirstImpasse(pos);
--            end
--            return IDLE, findFirstImpasse(pos);
--        end
--        print("-----------------and not craignos-----------------");
        if (nbPossib == 0) then
--            print("idle");
            return IDLE;
        end
        --bomb
--        print("bomb");
        posSeen = {};
        return DROPBOMB, findFirstImpasse(pos);
    end
--    print("move");
    --find impasse and move
    --[[if (nbmov > 0) then
--        for d=1,nbmov do
--            print("index: "..d);
--            print("can move to: "..uncmov[d]);
--        end
        return uncmov[math.random(1, nbmov)];
    else]]
    if (nbPossib > 0) then
        return possibMove[math.random(1, nbPossib)];
    end
    return (math.random(LEFT, DOWN));
end

--todo implement the three behaviours
function easyBehaviour(iaPos, focusPos)
    local fimp;
    local action;

--    bomberMap = bommap;
    if (focusPos:getX() == -1 and focusPos:getY() == -1) then
        posSeen = {};
        fimp = findFirstImpasse(iaPos);
        action = math.random(LEFT, DOWN);
--        print("first impasse = ("..fimp:getX()..", "..fimp:getY()..")");
    else
--        action = IDLE;
        action, fimp = waitBombOrMove(iaPos, focusPos);
    end

    if (fimp ~= nil) then
        focusPos:setX(fimp:getX());
        focusPos:setY(fimp:getY());
    end

--    bomberMap:getDangerAtPos(iaPos:getX(), iaPos:getY());
--    print("focus = ("..focusPos:getX()..", "..focusPos:getY()..")");

    iaPos:del();
    return (action);
end

function findFirstSafe(iaPos)
  local dirX = { -1, 1, 0, 0 };
  local dirY = { 0, 0, 1, -1 };
  local distance = {};
  local direction = {};
  local tolook;

  for y=0,MapH do
    distance[y] = {};
    direction[y] = {};
    for x=0,MapW do
      tolook = bomberMap:getDangerAtPos(x, y);
      if (tolook == OTHER) then
        distance[y][x] = BLOCK;
      end
      distance[y][x] = tolook;
      direction[y][x] = -1;
    end
  end
  if (iaPos:getX() - 1 >= 0 and distance[iaPos:getY()][iaPos:getX() - 1] ~= BLOCK) then
    direction[iaPos:getY()][iaPos:getX() - 1] = LEFT;
    distance[iaPos:getY()][iaPos:getX() - 1] = 1;
  end
  if (iaPos:getX() + 1 < MapW and distance[iaPos:getY()][iaPos:getX() + 1] ~= BLOCK) then
    direction[iaPos:getY()][iaPos:getX() + 1] = RIGHT;
    distance[iaPos:getY()][iaPos:getX() + 1] = 1;
  end
  if (iaPos:getY() + 1 < MapH and distance[iaPos:getY() + 1][iaPos:getX()] ~= BLOCK) then
    direction[iaPos:getY() + 1][iaPos:getX()] = UP;
    distance[iaPos:getY() + 1][iaPos:getX()] = 1;
  end
  if (iaPos:getY() - 1 >= 0 and distance[iaPos:getY() - 1][iaPos:getX()] ~= BLOCK) then
    direction[iaPos:getY() - 1][iaPos:getX()] = DOWN;
    distance[iaPos:getY() - 1][iaPos:getX()] = 1;
  end
  for j=LEFT, DOWN do
    tolook = bomberMap:getDangerAtPos(iaPos:getX() + dirX[j], iaPos:getY() + dirY[j]);
    if (tolook == NONE) then
      return j;
    end
  end
  local dist = 1;
  for i=1,30 do
    for y=0,MapH -1 do
      for x=0,MapW - 1 do
        if (distance[y][x] == dist) then
          if (distance[y][x + 1] == BOOM) then
            direction[y][x + 1] = direction[y][x];
            distance[y][x + 1]= dist + 1;
          elseif (distance[y][x + 1] == NONE) then
            return direction[y][x];
          end
          if (x > 0 and distance[y][x - 1] == BOOM) then
            direction[y][x - 1] = direction[y][x];
            distance[y][x - 1]= dist + 1;
          elseif (x > 0 and distance[y][x - 1] == NONE) then
            return direction[y][x];
          end
          if (distance[y + 1][x] == BOOM) then
            direction[y + 1][x] = direction[y][x];
            distance[y + 1][x]= dist + 1;
          elseif (distance[y + 1][x] == NONE) then
            return direction[y][x];
          end
          if (y > 0 and distance[y - 1][x] == BOOM) then
            direction[y - 1][x] = direction[y][x];
            distance[y - 1][x]= dist + 1;
          elseif (y > 0 and distance[y - 1][x] == NONE) then
            return direction[y][x];
          end
        end
      end
    end
  end
  -- le random qui debloque ^^'
  if (bomberMap:getDangerAtPos(iaPos:getX(), iaPos:getY()) == BOMB) then
    for c=LEFT,DOWN do
      tolook = bomberMap:getDangerAtPos(iaPos:getX() + dirX[c], iaPos:getY() + dirY[c]);
      if (tolook ~= BLOCK and tolook ~= BOMB) then
        return c;
      end
    end
  end
  return IDLE;
end

function getObjectif(iaPos)

  local dirX = { -1, 1, 0, 0 };
  local dirY = { 0, 0, 1, -1 };
  local tolook;
  local objectif = {};
  local choice;
  local dice;
  local hasexit = false;

--<<<<<<< HEAD
--  tolook = bomberMap:objsAtPos(iaPos:getX(), iaPos:getY());
--  if (tolook:hasType(BOMB) or tolook:hasType(BOOM)) then
--    return findFirstSafe(iaPos);
--=======
  tolook = bomberMap:getDangerAtPos(iaPos:getX(), iaPos:getY());
--<<<<<<< HEAD
--  if (tolook == BLOCK or tolook == BOMB) then
--    return findFirstSafe(iaPos);
-->>>>>>> cb0f730bb527cd37ce9f49244e0b40ace1011836
--=======
  if (tolook == BLOCK or tolook == BOMB or tolook == BOOM) then
    return findFirstSafe(bomberMap, iaPos);
-->>>>>>> 601129810d907b19feac186fbc834db03dacc9ad
  else
    choice = math.random(LEFT, DOWN);
  end
  for c=LEFT,DOWN do
    objectif[0] = iaPos:getX() + dirX[c];
    objectif[1] = iaPos:getY() + dirY[c];
    tolook = bomberMap:getDangerAtPos(objectif[0], objectif[1]);
    if (tolook == NONE) then
      hasexit = true;
    end
  end
  if (hasexit) then
    for c=LEFT,DOWN do
      objectif[0] = iaPos:getX() + dirX[c];
      objectif[1] = iaPos:getY() + dirY[c];
      tolook = bomberMap:getDangerAtPos(objectif[0], objectif[1]);
      if (tolook == OTHER or bomberMap:objsAtPos(objectif[0], objectif[1]):hasType(CHARACTER)) then
        return DROPBOMB;
      end
    end
  end
  if (hasexit == false) then
    return IDLE;
  end
  objectif[0] = iaPos:getX() + dirX[choice];
  objectif[1] = iaPos:getY() + dirY[choice];
  tolook = bomberMap:getDangerAtPos(objectif[0], objectif[1]);
  if (tolook == BLOCK or tolook == BOMB or tolook == BOOM) then
    choice = 1;
    while (choice < 5) do
      objectif[0] = iaPos:getX() + dirX[choice];
      objectif[1] = iaPos:getY() + dirY[choice];
      tolook = bomberMap:getDangerAtPos(objectif[0], objectif[1]);
      if (tolook == NONE) then
        break;
      end
      choice = choice + 1;
    end
    if (choice == 5) then
      choice = IDLE;
    end
  end
  return choice;
end

function mediumBehaviour(iaPos, focusPos)
  return getObjectif(iaPos);
end

function hardBehaviour(iaPos, focusPos)

end
