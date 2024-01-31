--@meta

--@class Input
Input = {};

--@param key: int
function Input:isKeyPressed(key)
    return cpp_Input_isKeyPressed(key);
end

--@param void
function Input:getMouseX()
    return cpp_Input_getMouseX();
end

--@param void
function Input:getMouseY()
    return cpp_Input_getMouseY();
end