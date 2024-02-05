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

---@return TransformComponent
function Actor:getComponent(component)
    return cpp_actor_getComponent(component(), self.__entityID)
end