local Test = {}

function Test:new()
    self.__index = Actor
    setmetatable(self, {__index = Actor})
    local instance = Actor:new()
    return instance;
end

function Test:begin()
    print(Input:getMouseY())
end

function Test:update(deltaTime)
    if (Input:isKeyPressed(KeyCode.Key_A)) then
        print(self.__entityID)
        print(deltaTime)
    end
end

return Test;