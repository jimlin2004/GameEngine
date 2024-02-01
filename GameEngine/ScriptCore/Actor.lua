--@meta

--@class Actor
Actor = {}

--@param o: table
function Actor:new()
    local instance = {}
    setmetatable(instance, self)
    self.__index = self
    instance.__entityID = cpp_getScriptEngineTargetEntityID()
    return instance
end