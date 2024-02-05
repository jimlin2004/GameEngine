-- GameEngineDebugger.listen()

local Test = {}
Test.__index = Test
setmetatable(Test, {__index = Actor})

function Test.new()
    local instance = Actor.new()
    setmetatable(instance, Test)
    instance.transformComponent = nil
    instance.rigidbody2DComponent = nil
    instance.temp = nil
    return instance
end

function Test:begin()
    self.transformComponent = self:getComponent(TransformComponent)
    self.rigidbody2DComponent = self:getComponent(Rigidbody2DComponent)
    self.temp = self.rigidbody2DComponent:getLinearVelocity()
end

function Test:update(deltaTime)
    if (Input:isKeyPressed(KeyCode.Key_SPACE)) then
        self.rigidbody2DComponent:applyLinearImpulseToCenter(Vec2(0, 1), true)
    end
end

return Test;