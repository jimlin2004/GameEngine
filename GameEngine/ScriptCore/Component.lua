---GameEngine Components Lua definition file

---@class TransformComponent
---@field position Vec3
---@field rotation Vec3
---@field scale Vec3
TransformComponent = {
    position = Vec3,
    rotation = Vec3,
    scale    = Vec3
}

---@class Rigidbody2DComponent
Rigidbody2DComponent = {}
---@return Vec2
function Rigidbody2DComponent:getLinearVelocity()
    return Vec2()
end
---@param impulse Vec2
---@param wake boolean
function Rigidbody2DComponent:applyLinearImpulseToCenter(impulse, wake)
    return
end
---@param velocity Vec2
function Rigidbody2DComponent:setLinearVelocity(velocity)
    return
end