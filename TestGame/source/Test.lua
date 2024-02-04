local Test = {}
Test.__index = Test
setmetatable(Test, {__index = Actor})

function Test.new()
    local instance = Actor.new()
    setmetatable(instance, Test)
    instance.temp = Vec2(0, 0);
    return instance
end

function Test:begin()
end

function Test:update(deltaTime)
    if (Input:isKeyPressed(KeyCode.Key_A)) then
        -- cpp_actor_getComponent(self.temp.typename)
        print(type(self.temp))
    end
end

return Test;