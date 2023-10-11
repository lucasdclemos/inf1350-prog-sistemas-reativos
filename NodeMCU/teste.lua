local led1 = 0
local led2 = 6
local chave1 = 3
local chave2 = 4
local chave3 = 5
local chave4 = 8
local delay = 200000
local last = 0
local meusleds = {led1, led2}
local mytimer = tmr.create()

gpio.mode(chave1,gpio.INT,gpio.PULLUP)
gpio.mode(chave2,gpio.INT,gpio.PULLUP)
gpio.mode(chave3,gpio.INT,gpio.PULLUP)
gpio.mode(chave4,gpio.INT,gpio.PULLUP)

for _,ledi in ipairs (meusleds) do
    gpio.mode(ledi, gpio.OUTPUT)
    gpio.write(ledi, gpio.LOW);
end

local function piscapisca (t)
    for _,led in ipairs (meusleds) do
       gpio.write(led, bit.band(gpio.read(led)+1,1))
    end
end

local function apaga_led (level, timestamp)
    if timestamp - last < delay then return end
    last = timestamp
    for _,ledi in ipairs (meusleds) do
        gpio.write(ledi, gpio.LOW);
    end
    mytimer:stop()
end

gpio.trig(chave1, "down", apaga_led)
gpio.trig(chave2, "down", apaga_led)
gpio.trig(chave3, "down", apaga_led)
gpio.trig(chave4, "high", apaga_led)

mytimer:register(1000, tmr.ALARM_AUTO, piscapisca)
mytimer:start()