---@class GameEngineDebugger
GameEngineDebugger = {}

---Start debugging
---@param port nil | string # default port = 12306
function GameEngineDebugger.listen(port)
    port = port or "12306"
    require "debugger":start "127.0.0.1:12306":event "wait"
end