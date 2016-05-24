--
-- Created by IntelliJ IDEA.
-- User: gaspar_q
-- Date: 5/6/16
-- Time: 4:18 PM
-- To change this template use File | Settings | File Templates.
--

function dirTab()
    return {Vector2.creat(1, 0), Vector2.creat(-1, 0), Vector2.creat(0, 1), Vector2.creat(0, -1)}, {RIGHT, LEFT, UP, DOWN};
end

posSeen = {};

function findFirstImpasse(bomberMap, pos)
    posSeen[pos:getX() + pos:getY() * MapW] = true;
--    print("We are on ("..pos:getX()..", "..pos:getY()..")");
    for i=0,9 do
        local xloop = pos:getX() - 1 + (i % 3);
        local yloop = pos:getY() - 1 + math.floor(i / 3);

        if (posSeen[xloop + MapW * yloop] == nil and xloop < MapW and xloop >= 0 and yloop < MapH and yloop >= 0) then
            local tolook = bomberMap:objsAtPos(xloop, yloop);

--            print("We are checking ("..xloop..", "..yloop..")");
--            print("    this case has "..tolook:size().." type");
            if (tolook:size() == 0) then
--                print("from ("..pos:getX()..", "..pos:getY()..") case("..xloop..", "..yloop..") is empty");
                local togo = Vector2.creat(xloop, yloop);
--                print("to go: ("..togo:getX()..", "..togo:getY()..")");
--                togo:setX(xloop);
--                togo:setY(yloop);
                return (findFirstImpasse(bomberMap, togo));
            end
        end
    end
    return (pos);
end

function isCraignos(bomberMap, pos)
    local i = 0;
    local posToCheck = dirTab();

--    print("check pos: ("..pos:getX()..", "..pos:getY()..")");
    while (i <= 3 and (posToCheck[1] ~= nil or posToCheck[2] ~= nil or posToCheck[3] ~= nil or posToCheck[4] ~= nil)) do
        for j=1,4 do
            if (posToCheck[j] ~= nil) then
                local newpos = pos:add(posToCheck[j]:mul(i));

--                print("checking: ("..newpos:getX()..", "..newpos:getY()..")");
--                print("    result of ("..posToCheck[j]:getX()..", "..posToCheck[j]:getY()..") * "..i.." + ("..pos:getX()..", "..pos:getY()..")");
                if (newpos:getX() < MapW and newpos:getX() >= 0 and newpos:getY() < MapH and newpos:getY() >= 0) then
                    local tolook = bomberMap:objsAtPos(newpos:getX(), newpos:getY());

                    if (tolook:hasType(BLOCK) or tolook:hasType(BONUS) or tolook:hasType(OTHER)) then
                        posToCheck[j] = nil;
                    elseif (tolook:hasType(BOMB) or tolook:hasType(BOOM)) then
--                        print("is craignos");
                        return (true);
                    end
                else
                    posToCheck[j] = nil;
                end
            end
        end
        i = i + 1;
    end
--    print("is not craignos");
    return (false);
end

function getUncraignosMove(bomberMap, pos)
    local tocheck, moves = dirTab();
    local possib = {};
    local i = 0;

    for j=1,4 do
        local gonnasee = pos:add(tocheck[j]);
        if (bomberMap:objsAtPos(gonnasee:getX(), gonnasee:getY()):size() == 0 and isCraignos(bomberMap, gonnasee) == false) then
--            print("We found a pos: "..moves[j]);
            i = i + 1;
            possib[i] = moves[j];
--        else
--            print("Position "..moves[j].." not valid");
        end
--        print("index: "..j);
    end
    return possib, i;
end

function getPossiblePos(bomberMap, pos)
    local tocheck, moves = dirTab();
    local possib = {};
    local i = 0;

    for j=1,4 do
        local gonnasee = pos:add(tocheck[j]);
        local tocheck = bomberMap:objsAtPos(gonnasee:getX(), gonnasee:getY());
        if (tocheck:size() == 0 or tocheck:hasType(BONUS) or tocheck:hasType(ITEM)) then
            i = i + 1;
            possib[i] = moves[j];
        end
    end
    return possib, i;
end

function waitBombOrMove(bomberMap, pos, focus)
    local uncmov, nbmov = getUncraignosMove(bomberMap, pos);
    local possibMove, nbPossib = getPossiblePos(bomberMap, pos);

--    print("wait bomb or move from: ("..pos:getX()..", "..pos:getY()..")");
    if (pos:equal(focus)) then
--        print("-----------------it is equal-----------------");
        if (isCraignos(bomberMap, pos)) then
--            print("-----------------but craignos-----------------");
--            print("arrived to focus but craignos");
            return math.random(LEFT, DOWN), findFirstImpasse(bomberMap, pos);
        end
--        print("-----------------and not craignos-----------------");
        if (nbmov == 0) then
--            print("idle");
            return IDLE;
        end
        --bomb
--        print("bomb");
        posSeen = {};
        return DROPBOMB, findFirstImpasse(bomberMap, pos);
    end
--    print("move");
    --find impasse and move
    if (nbmov > 0) then
--        for d=1,nbmov do
--            print("index: "..d);
--            print("can move to: "..uncmov[d]);
--        end
        return uncmov[math.random(1, nbmov)];
    end
    if (nbPossib > 0) then
        return possibMove[math.random(1, nbPossib)];
    end
    return (IDLE);
end

--todo implement the three behaviours
function easyBehaviour(bomberMap, iaPos, focusPos)
--    print("wid: "..MapW);
--    print("hei: "..MapH);
--    print("iapos("..iaPos:getX()..", "..iaPos:getY()..")");
--    for i = 0,(MapW * MapH) do
--        local x = (i % MapW);
--        local y = math.floor(i / MapW);
--        local objs = bomberMap:objsAtPos(x, y);
--        local j = 0;
--        local type;
--        repeat
--            type = objs:typeAtIndex(j);
--            if (type ~= nil) then
--                print("Object n°"..j.." at ("..x..", "..y..") of type "..type);
--            end
--            j = j + 1;
--        until (type == nil);
--    end
--    if (bomberMap:objsAtPos(7, 7):hasType(BOMB)) then
--        print("(7, 7): has type bomb: true");
--    else
--        print("(7, 7): has type bomb: false");
--    end
    local fimp;
    local action;

    if (focusPos:getX() == -1 and focusPos:getY() == -1) then
        fimp = findFirstImpasse(bomberMap, iaPos);
        action = math.random(LEFT, DOWN);
    else
        action, fimp = waitBombOrMove(bomberMap, iaPos, focusPos);
    end

    if (fimp ~= nil) then
--        print("First impasse: ("..fimp:getX()..", "..fimp:getY()..")");
        focusPos:setX(fimp:getX());
        focusPos:setY(fimp:getY());
    end

--    if (action == nil) then
--        action = math.random(LEFT, DOWN);
--    end

    iaPos:del();
    return (action--[[math.random(IDLE, ACT)]]);
end

function findFirstSafe(bomberMap, iaPos)
  local dirX = { -1, 1, 0, 0 };
  local dirY = { 0, 0, 1, -1 };
  local distance = {};
  local direction = {};
  local tolook;

  for y=0,MapH do
    distance[y] = {};
    direction[y] = {};
    for x=0,MapW do
      distance[y][x] = bomberMap:getDangerAtPos(x, y);
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
  for i=1,20 do
    for y=0,MapH -1 do
      for x=0,MapW - 1 do
        if (distance[y][x] == dist) then
          if (distance[y][x + 1] == BOMB) then
            direction[y][x + 1] = direction[y][x];
            distance[y][x + 1]= dist + 1;
          elseif (distance[y][x + 1] == NONE) then
            return direction[y][x];
          end
          if (x > 0 and distance[y][x - 1] == BOMB) then
            direction[y][x - 1] = direction[y][x];
            distance[y][x - 1]= dist + 1;
          elseif (x > 0 and distance[y][x - 1] == NONE) then
            return direction[y][x];
          end
          if (distance[y + 1][x] == BOMB) then
            direction[y + 1][x] = direction[y][x];
            distance[y + 1][x]= dist + 1;
          elseif (distance[y + 1][x] == NONE) then
            return direction[y][x];
          end
          if (y > 0 and distance[y - 1][x] == BOMB) then
            direction[y - 1][x] = direction[y][x];
            distance[y - 1][x]= dist + 1;
          elseif (y > 0 and distance[y - 1][x] == NONE) then
            return direction[y][x];
          end
        end
      end
    end
  end
  return IDLE;
end

function getObjectif(bomberMap, iaPos)

  local dirX = { -1, 1, 0, 0 };
  local dirY = { 0, 0, 1, -1 };
  local tolook;
  local objectif = {};
  local choice;
  local dice;
  local hasexit = false;

  tolook = bomberMap:getDangerAtPos(iaPos:getX(), iaPos:getY());
  if (tolook == BLOCK or tolook == BOMB) then
    return findFirstSafe(bomberMap, iaPos);
  else
    choice = math.random(LEFT, DOWN);
  end
  for c=LEFT,DOWN do
    objectif[0] = iaPos:getX() + dirX[c];
    objectif[1] = iaPos:getY() + dirY[c];
    tolook = bomberMap:getDangerAtPos(objectif[0], objectif[1]);
    dice = math.random(0, 7);
    if (tolook == NONE) then
      hasexit = true;
    end
    if (tolook == OTHER and hasexit == true) then
      return DROPBOMB;
    end
  end
  if (hasexit == false) then
    return IDLE;
  end
  objectif[0] = iaPos:getX() + dirX[choice];
  objectif[1] = iaPos:getY() + dirY[choice];
  tolook = bomberMap:getDangerAtPos(objectif[0], objectif[1]);
  if (tolook == BLOCK or tolook == BOMB) then
    choice = 1;
    while (choice < 5) do
      objectif[0] = iaPos:getX() + dirX[choice];
      objectif[1] = iaPos:getY() + dirY[choice];
      tolook = bomberMap:getDangerAtPos(objectif[0], objectif[1]);
      if (tolook == BLOCK or tolook == BOMB) then
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

function mediumBehaviour(bomberMap, iaPos, focusPos)
  return getObjectif(bomberMap, iaPos);
end

function hardBehaviour(bomberMap, iaPos)

end
