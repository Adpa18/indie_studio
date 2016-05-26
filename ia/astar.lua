--
-- Created by IntelliJ IDEA.
-- User: gaspar_q
-- Date: 5/26/16
-- Time: 10:44 AM
-- To change this template use File | Settings | File Templates.
--

Queue = {};
Stack = {};

function Queue.new()
    return {first = 0, last = -1};
end

function Queue.push(list, value)
    local topush = list.first - 1;
    list.first = topush;
    list[topush] = value;
end

function Queue.pop(list)
    local last = list.last;
    if list.first > last then
        return nil;
    end
    local value = list[last];
    list[last] = nil;
    list.last = last - 1;
    return value;
end

function Stack.new()
    return {first = 0, last = -1};
end

function Stack.push(list, value)
    local topush = list.first - 1;
    list.first = topush;
    list[topush] = value;
end

function Stack.pop(list)
    local first = list.first;
    if first > list.last then
        return nil;
    end
    local value = list[first];
    list[first] = nil;
    list.first = first + 1;
    return value;
end

function getHeuristique(pos, focus, cost)
    local dist = math.sqrt(math.pow(focus:getX() - pos:getX(), 2) + math.pow(focus:getY() - pos:getY(), 2));
    return dist + cost;
end

--todo push in queue and stack depending on heuristique
function astarGetNextPos(currPos, focus)
    local runQueue = Queue.new();
    local saveStack = Stack.new();
    local popedValue;
    local possib;
    local cost = 0;

    runQueue:push(currPos);
    repeat
        popedValue = runQueue:pop();
        if (popedValue == nil) then
            popedValue = saveStack:pop();
        end
        if (popedValue ~= nil) then
            cost = cost + 1;
            possib = getPossiblePos(popedValue);
            for k, dir in possib do

            end
        end
    until (popedValue == nil)
end