--@meta

--@class Actor
Actor = {
    __entityID = nil
}
Actor.__index = Actor

--@param void
function Actor.new()
    local instance = {}
    setmetatable(instance, Actor)
    instance.__entityID = cpp_getScriptEngineTargetEntityID()
    return instance
end