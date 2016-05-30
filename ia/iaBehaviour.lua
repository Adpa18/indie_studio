--
-- Created by IntelliJ IDEA.
-- User: gaspar_q
-- Date: 5/6/16
-- Time: 4:18 PM
-- To change this template use File | Settings | File Templates.
--

bomberMap = {};

function dofile(file)
    local lib = assert(loadfile(file));
    return lib();
end

--[[
--Define:
--  -   dirTab
--  -   getDirFromCode
--  -   isInMap
--  -   canMoveOnPos
--  -   getPossiblePos
 ]]
dofile("./ia/positionDirection.lua");

--[[
--Define:
 ]]
dofile("./ia/astar.lua");

--[[
--Used for positions that are already saw
 ]]
posSeen = {};

--[[
--Find the first impasse in the map
 ]]
function findFirstImpasse(pos)
    local directions = dirTab();

    posSeen[pos:getX() + pos:getY() * MapW] = true;
    for _, dir in pairs(directions) do
        local togo = pos:add(dir);

        if (posSeen[togo:getX() + MapW * togo:getY()] == nil and canMoveOnPos(togo)) then
            return (findFirstImpasse(togo));
        end
    end
    return (pos);
end

function canDropBomb(iaplayer)
    local nextFocus;
    local pos = iaplayer:getPos();
    local directions = dirTab();

    if (canMoveSafelyOnPos(iaplayer:getPos()) == false) then
        return nil;
    end
    for _, dir in pairs(directions) do
        local tocheck = pos:add(dir);
        if (bomberMap:objsAtPos(tocheck:getX(), tocheck:getY()):hasType(OTHER) or bomberMap:getNbOfType(pos:getX(), pos:getY(), CHARACTER) > 1) then
            posSeen = {};
            nextFocus = iaplayer:bombDropSimul();
            if (nextFocus ~= nil) then
                return nextFocus;
            end
        end
    end
    return nil;
end

--[[
--Choose if the IA will move, drop a bomb or idle
 ]]
function waitBombOrMove(iaplayer, lastCaseMove)
    local possibMove, nbPossib = getPossibleSafePos(iaplayer:getPos());
    local fimp;
    local nextFocus;

    if (iaplayer:getPos():equal(iaplayer:getFocus())) then
        posSeen = {}
        fimp = findFirstImpasse(iaplayer:getPos());
        if (nbPossib == 0 and canMoveSafelyOnPos(iaplayer:getPos())) then
            return IDLE;
        end
        --[[posSeen = {};
        local nextFocus = iaplayer:bombDropSimul();
        if (nextFocus == nil) then
            return (IDLE);
        end
        return DROPBOMB, nextFocus;]]
    end
    nextFocus = canDropBomb(iaplayer);
    if (nextFocus ~= nil) then
        return DROPBOMB, nextFocus;
    end
    return lastCaseMove(possibMove, nbPossib), fimp;
end

function runIa(iaplayer, lastCaseMove)
    local fimp;
    local action;

    action, fimp = waitBombOrMove(iaplayer, lastCaseMove);
    if (fimp ~= nil) then
        iaplayer:setFocus(fimp);
    end
    return action;
end

--todo implement the three behaviours
--[[
--Function for an IA easy behaviour
 ]]
function easyBehaviour(iaplayer)
--    local fimp;
--    local action;
--    local focusPos = iaplayer:getFocus();
--    local iaPos = iaplayer:getPos();

--    if (focusPos:getX() == -1 and focusPos:getY() == -1) then
--        posSeen = {};
--        fimp = findFirstImpasse(iaPos);
--        action = math.random(LEFT, DOWN);
--    else
--        action, fimp = waitBombOrMove(iaplayer, function (possibMove, nbPossib)
--            if (nbPossib > 0) then
--                return possibMove[math.random(1, nbPossib)];
--            end
--            return math.random(LEFT, DOWN);
--        end);
--    end

--    if (fimp ~= nil) then
--        iaplayer:setFocus(fimp);
--    end
    return (runIa(iaplayer, function (possibMove, nbPossib)
        if (nbPossib > 0) then
            return possibMove[math.random(1, nbPossib)];
        end
        return math.random(LEFT, DOWN);
    end));
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

  if (tolook == BLOCK or tolook == BOMB or tolook == BOOM) then
    return findFirstSafe(bomberMap, iaPos);
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

function mediumBehaviour(iaplayer)
    return DROPBOMB;
--  return runIa(iaplayer, function (possibMove, nbPossib)
--      local acttoRet;
--
--      if (iaplayer:getPos():equal(iaplayer:getFocus()) == false) then
--          acttoRet = astarGetNextPos(iaplayer:getPos(), iaplayer:getFocus());
--      end
--      if (acttoRet == nil) then
--          if (nbPossib > 0) then
--              return (possibMove[math.random(1, nbPossib)]);
--          end
--          return (math.random(LEFT, DOWN));
--      end
--      if (canMoveSafelyOnPos(iaplayer:getPos()) and canMoveSafelyOnPos(iaplayer:getPos():add(getDirFromCode(acttoRet))) == false) then
--          return (IDLE);
--      end
--      return (acttoRet);
--  end);
end

function hardBehaviour(iaPos, focusPos)

end
