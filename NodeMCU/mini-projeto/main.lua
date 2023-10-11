local mqtt = require("mqtt_library")

function love.load()
  imagem_xis = love.graphics.newImage("/imagens/xis.png")
  imagem_bola = love.graphics.newImage("/imagens/bola.png")
  
  mqtt_client = mqtt.client.create("139.82.100.100",7981,mqttcb)
  mqtt_client:connect("cliente love")
  mqtt_client:subscribe({"paralove"})
end

function love.update(dt)
  
end

function love.draw()
  love.graphics.setColor(1, 1, 1)
  love.graphics.line(0,love.graphics.getHeight()/3, love.graphics.getWidth(), love.graphics.getHeight()/3)
  love.graphics.line(0,2*(love.graphics.getHeight()/3), love.graphics.getWidth(),2*(love.graphics.getHeight()/3))
  love.graphics.line(love.graphics.getWidth()/3,0, (love.graphics.getWidth()/3),love.graphics.getHeight())
  love.graphics.line(2*(love.graphics.getWidth()/3),0, 2*(love.graphics.getWidth()/3),love.graphics.getHeight())
  
end


-- POSIÇÕES DAS IMAGENS -- so mudar para bola ou xis em cada caso
-- linha1 coluna1 -> love.graphics.draw(imagem_bola, 45, 0, 0, 0.2, 0.2)
-- linha1 coluna2 -> love.graphics.draw(imagem_bola, 310, 0, 0, 0.2, 0.2)
-- linha1 coluna3 -> love.graphics.draw(imagem_xis, 575, 0, 0, 0.2, 0.2)
-- linha2 coluna1 -> love.graphics.draw(imagem_bola, 45, 200, 0, 0.2, 0.2)
-- linha2 coluna2 -> love.graphics.draw(imagem_xis, 310, 200, 0, 0.2, 0.2)
-- linha2 coluna3 -> love.graphics.draw(imagem_xis, 575, 200, 0, 0.2, 0.2)
-- linha3 coluna1 -> love.graphics.draw(imagem_bola, 45, 400, 0, 0.2, 0.2)
-- linha3 coluna2 -> love.graphics.draw(imagem_xis, 310, 400, 0, 0.2, 0.2)
-- linha3 coluna3 -> love.graphics.draw(imagem_xis, 575, 400, 0, 0.2, 0.2)

-- POSIÇÕES DAS BOLINHAS DE LINHA/COLUNA --
-- love.graphics.setColor(1, 0, 0)
-- linha1 -> love.graphics.circle("fill", 20, 100, 20)
-- linha2 -> love.graphics.circle("fill", 20, 300, 20)
-- linha3 -> love.graphics.circle("fill", 20, 500, 20)
-- coluna1 -> love.graphics.circle("fill", 135, 20, 20)
-- coluna2 -> love.graphics.circle("fill", 405, 20, 20)
-- coluna3 -> love.graphics.circle("fill", 675, 20, 20)