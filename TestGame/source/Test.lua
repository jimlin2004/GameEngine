-- GameEngineDebugger.listen()

local Test = {}
Test.__index = Test
setmetatable(Test, {__index = Actor})

function Test.new()
    local instance = Actor.new()
    setmetatable(instance, Test)
    instance.transformComponent = nil
    instance.rigidbody2DComponent = nil
    return instance
end

function Test:onKeyDownEvent(event)
    if (event:key() == KeyCode.Key_SPACE) then
        self.rigidbody2DComponent:setLinearVelocity(Vec2(self.rigidbody2DComponent:getLinearVelocity().x, 5))
        return true
    else
        return false
    end
end

function Test:onKeyUpEvent(event)
    if (event:key() == KeyCode.Key_A) then
        self.rigidbody2DComponent:setLinearVelocity(Vec2(0, self.rigidbody2DComponent:getLinearVelocity().y))
        return true
    elseif (event:key() == KeyCode.Key_D) then
        self.rigidbody2DComponent:setLinearVelocity(Vec2(0, self.rigidbody2DComponent:getLinearVelocity().y))
        return true
    else
        return false
    end
end

function Test:begin()
    self.transformComponent = self:getComponent(TransformComponent)
    self.rigidbody2DComponent = self:getComponent(Rigidbody2DComponent)
    self:addEventCallback("KeyDownEvent", self.onKeyDownEvent)
    self:addEventCallback("KeyUpEvent", self.onKeyUpEvent)
end

function Test:update(deltaTime)
    local velocity = self.rigidbody2DComponent:getLinearVelocity()
    if (Input:isKeyPressed(KeyCode.Key_D)) then
        self.rigidbody2DComponent:setLinearVelocity(Vec2(5, velocity.y))
    elseif (Input:isKeyPressed(KeyCode.Key_A)) then
        self.rigidbody2DComponent:setLinearVelocity(Vec2(-5, velocity.y))
    end
end

return Test;