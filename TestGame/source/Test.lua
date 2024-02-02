local Test = {}
Test.__index = Test
setmetatable(Test, {__index = Actor})

function Test.new()
    local instance = Actor.new()
    setmetatable(instance, Test)
    instance.temp = cpp_getTemp();
    return instance
end

function Test:begin()
end

function Test:update(deltaTime)
    print(self.temp.x)
    if (Input:isKeyPressed(KeyCode.Key_A)) then
        cpp_test()
    end
end

return Test;