---@meta

---@class Input
Input = {};

---@param key KeyCode
function Input:isKeyPressed(key)
    return cpp_Input_isKeyPressed(key);
end

---@return number # Returns the X coordinate axis of the mouse
function Input:getMouseX()
    return cpp_Input_getMouseX();
end

---@return number # Returns the Y coordinate axis of the mouse
function Input:getMouseY()
    return cpp_Input_getMouseY();
end