local mqtt = require("mqtt_library")
local linha = 0
local coluna = 0
local matriz = {}
local jogador = 1 -- 1 -> X ou 2 -> O
local acabou = 0 -- 1 se acabou
local control = 0

function controller(msg)
  print(msg)
  if (msg == "1") then
    if(linha == 2) then 
      linha = 0
    else
      linha = linha + 1
    end
  elseif (msg == "2") then
    if(coluna == 2) then 
      coluna = 0
    else
      coluna = coluna + 1
    end
  elseif (msg == "3") then
    confirm_play(linha, coluna)
    
  end
end



-- recebe mensagens mqtt
function mqttcb(t,m)
  if(t == "paraloveA14") then
  end
  print("MENSAGEM RECEBIDA: "..m)
  controller(m)
  
    
end

function love.load()
  print(love.graphics.getWidth())
  for i=0, 2, 1 do
    matriz[i] = {} -- nova linha
    for j=0, 2, 1 do
        matriz[i][j] = 0
        --print(matriz[i][j])
    end
end
  imagem_xis = love.graphics.newImage("/images/xis.png")
  imagem_bola = love.graphics.newImage("/images/bola.png")

  mqtt_client = mqtt.client.create("139.82.100.100", 7981, mqttcb)
  -- Trocar XX pelo ID da etiqueta do seu NodeMCU
  mqtt_client:connect("cliente love A14")
  mqtt_client:subscribe({"paraloveA14"})
end

function love.update(dt)
  mqtt_client:handler()  
end

function confirm_play(linha, coluna)
  if(matriz[linha][coluna] == 0) then
    matriz[linha][coluna] = jogador
    verifica_tabuleiro()
    if(jogador == 1) then
      jogador = 2
    else
      jogador = 1
    end
    linha = 0
    coluna = 0
  else
    linha = 0
    coluna = 0
  end
end


function love.draw()
  love.graphics.setColor(1, 1, 1)
  love.graphics.line(0, love.graphics.getHeight()/3, love.graphics.getWidth(), love.graphics.getHeight()/3)
  love.graphics.line(0, 2*(love.graphics.getHeight()/3), love.graphics.getWidth(), 2*(love.graphics.getHeight()/3))
  love.graphics.line(love.graphics.getWidth()/3, 0, (love.graphics.getWidth()/3), love.graphics.getHeight())
  love.graphics.line(2*(love.graphics.getWidth()/3), 0, 2*(love.graphics.getWidth()/3), love.graphics.getHeight())
  fontenv = love.graphics.newFont(12)
  love.graphics.setFont(fontenv)
  love.graphics.print("LINHA: "..(linha+1).." / COLUNA: "..(coluna+1), 340, 0)
  for i = 0, 2, 1 do
    for j = 0, 2, 1 do
      if (matriz[i][j] == 1) then
        love.graphics.draw(imagem_xis, 60+(280*j), 60+(200*i), 0, 0.2, 0.2)
      elseif (matriz[i][j] == 2) then
        love.graphics.draw(imagem_bola, 60+(280*j), 60+(200*i), 0, 0.2, 0.2)
      end
    end
  end
  
  if(acabou==1) then
    fontenv = love.graphics.newFont(50)
    love.graphics.setFont(fontenv)
    love.graphics.print("ACABOU",300,260)
  end
end

function verifica_tabuleiro ()
    if matriz[0][0] == matriz[0][1] and matriz[0][0] == matriz[0][2] and matriz[0][0]~=0 then
        print("acabou")
        acabou = 1
    end
    if matriz[1][0] == matriz[1][1] and matriz[1][0] == matriz[1][2] and matriz[1][0]~=0 then
        print("acabou")
        acabou = 1
    end
    if matriz[2][0] == matriz[2][1] and matriz[2][0] == matriz[2][2] and matriz[2][0]~=0 then
        print("acabou")
        acabou = 1
    end
    if matriz[0][0] == matriz[1][0] and matriz[0][0] == matriz[2][0] and matriz[0][0]~=0 then
        print("acabou")
        acabou = 1
    end
    if matriz[0][1] == matriz[1][1] and matriz[0][1] == matriz[2][1] and matriz[0][1]~=0 then
        print("acabou")
        acabou = 1
    end
    if matriz[0][2] == matriz[1][2] and matriz[0][2] == matriz[2][2] and matriz[0][2]~=0 then
        print("acabou")
        acabou = 1
    end
    if matriz[0][0] == matriz[1][1] and matriz[0][0] == matriz[2][2] and matriz[0][0]~=0 then
        print("acabou")
        acabou = 1
    end
    if matriz[0][2] == matriz[1][1] and matriz[0][2] == matriz[2][0] and matriz[0][2]~=0 then
        print("acabou")
        acabou = 1
    end
end