-- MUDAR meu id!!!!
require "station"
local meuid = "2110013"

local m = mqtt.Client("clientid " .. meuid, 120)

function publica(c)
  c:publish("paranodeXX","alo de " .. meuid,0,0, 
            function(client) print("mandou!") end)
end

function novaInscricao (c)
  local msgsrec = 0
  function novamsg (c, t, m)
    print ("mensagem ".. msgsrec .. ", topico: ".. t .. ", dados: " .. m)
    msgsrec = msgsrec + 1
  end
  c:on("message", novamsg)
end

function conectado (client)
  publica(client)
  client:subscribe("paraloveXX", 0, novaInscricao)
end 

m:connect("139.82.100.100", 7981, false, 
             conectado,
             function(client, reason) print("failed reason: "..reason) end)
