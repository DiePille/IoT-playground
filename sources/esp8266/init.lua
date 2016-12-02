--This file is init.lua
local IDLE_AT_STARTUP_MS = 10000;

tmr.alarm(1,IDLE_AT_STARTUP_MS,0,function()
    dofile("program.lua")--Write your program name in dofile
end)