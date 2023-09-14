local meublip
local player

tabela_blip = {}
max_voltas = 4
max_imortais = 2
imortais_atingidos = 0
num_aleatorio = love.math.random(1, 10)
start = love.timer.getTime()
situacao = "jogando"

local function newblip (vel)
  local x, y = 0, 0
  local tam = 40
  local voltas = 1
  return {
    update = function (dt)
      local width, _ = love.graphics.getDimensions( )
      x = x+(vel+1)*dt*40
      if x > width then
        voltas = voltas + 1
        x = 0
      end
    end,
    morto = false,
    affected = function (pos)
      if pos>x and pos<x+tam then
      -- "pegou" o blip
        if voltas > max_voltas then
          imortais_atingidos = imortais_atingidos + 1
          return false
        else 
          return true
        end
      else
        return false
      end
    end,
    draw = function ()
      if voltas > max_voltas then
        love.graphics.setColor(1, 0, 0)
      else
        love.graphics.setColor(0, 0, 1)
      end
      love.graphics.rectangle("line", x, y, tam, 10)
    end, 
    verifica_imortal = function ()
      if voltas > max_voltas then
        return true
      else
        return false
      end
    end
  }
end

local function newplayer ()
  local x, y = 0, 200
  local tam = 30
  local width, height = love.graphics.getDimensions( )
  return {
  try = function ()
    return x + tam/2
  end,
  update = function (dt)
    x = x + 0.5*30*dt
    if x > width then
      x = 0
    end
  end,
  draw = function ()
    love.graphics.setColor(1, 1, 1)
    love.graphics.rectangle("line", x, y, tam, 10)
  end
  }
end

function love.keypressed (key)
  if key == 'space' then
    pos = player.try()
    for i = 1, #tabela_blip do
      if tabela_blip[i].affected(pos) == true then
        tabela_blip[i].morto = true 
      else
        if imortais_atingidos > max_imortais then
          situacao = "perdeu"
        end
      end
    end
   
  end
end


function love.load()
  player =  newplayer()
  for i = 1, 5 do
    tabela_blip[i] = newblip(love.math.random(20)/4) 
  end
end

function love.draw()
  if situacao == "jogando" then
    player.draw()
    for i = 1, #tabela_blip do
      if tabela_blip[i].morto == false then
        tabela_blip[i].draw();  
      end
    end
  elseif situacao == "ganhou" then
    local fonte = love.graphics.newFont(40)
    local texto = love.graphics.newText(fonte, "Ganhou")
    love.graphics.draw(texto, love.graphics.getWidth()/2, love.graphics.getHeight()/2)
  elseif situacao == "perdeu" then
    local fonte = love.graphics.newFont(40)
    local texto = love.graphics.newText(fonte, "Perdeu")
    love.graphics.draw(texto, love.graphics.getWidth()/2, love.graphics.getHeight()/2)
  end
end

function love.update(dt)
  if situacao == "jogando" then
    if num_aleatorio <= 5 and love.timer.getTime() - start >= 5 then
      print("novo blip")
      tabela_blip[#tabela_blip + 1] = newblip(love.math.random(20)/4)
      start = love.timer.getTime()
    end
    num_aleatorio = love.math.random(1, 10)
    player.update(dt)
    local blips_vivos = #tabela_blip
    local blips_imortais = 0
    for i = 1, #tabela_blip do
      tabela_blip[i].update(dt)
      if tabela_blip[i].verifica_imortal() == true and tabela_blip[i].morto == false then
        blips_imortais = blips_imortais + 1
      end
      if tabela_blip[i].morto == true then
        blips_vivos = blips_vivos - 1
      end
    end
    if blips_imortais == blips_vivos then
      situacao = "ganhou"
    end
    if blips_vivos == 0 then
      situacao = "ganhou"
    end
  end
end
  
function love.quit ()
  love.window.close()
  os.exit()
end 