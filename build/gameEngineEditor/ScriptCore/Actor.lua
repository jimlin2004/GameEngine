---@meta

---@class Actor
---@field __entityID number User shouldn't use this field
Actor = {
    __entityID = nil
}
Actor.__index = Actor

---Class Actor's constructor
---@return Actor
function Actor.new()
    local instance = {}
    setmetatable(instance, Actor)
    instance.__entityID = cpp_getScriptEngineTargetEntityID()
    return instance
end

---@return TransformComponent | Rigidbody2DComponent
function Actor:getComponent(component)
    return cpp_actor_getComponent(component(), self.__entityID)
end

---@param eventType string
---@param callbackFunc function
function Actor:addEventCallback(eventType, callbackFunc)
    cpp_actor_addCallback(self, eventType, callbackFunc)
end

---invoked when game start
function Actor:begin()
    
end

---invoked per frame
---@param deltaTime number
function Actor:update(deltaTime)
    
end