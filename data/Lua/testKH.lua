
-- Inputs ------------------------------------------
-- 输入参数
-- status
Exp = 0
HP = 0
HPMax = 0
Ki = 0
Mood = 0

-- source sprite props
S_PosX = 0
S_PosY = 0
S_Size = 0
S_Rot = 0
S_bWhite = false
S_Alive = true

-- target sprite props
T_PosX = 0
T_PosY = 0
T_Size = 0
T_Rot = 0
T_bWhite = false
T_Alive = true

-- Output information ----------------------------------------------------
-- 要输出显示的信息
Info = ""
InfoX = 0
InfoY = 0
IDuration = 0.7
IDelay = 0.02
IZOrder = 0.0
IFontName = "vag"
IFontSize = 18
CF0 = 255
CF1 = 255
CF2 = 255
CF3 = 255
IEdgeSize = 1.0
CE0 = 0
CE1 = 0
CE2 = 0
CE3 = 255

-- Sound effect ----------------------------------------------------
-- 若要播放音效，则将SoundPlay设为真，
-- 并选定sound/sounds.xml中的一段音效名称，赋值给SoundName
-- SoundPpd为播放速度，SoundVol为播放音量
SoundPlay = false
SoundName = ""
SoundSpd = 1.0
SoundVol = 1.0

----------------------------------------------------
function khMatch()	
	-- update state
	T_Size = T_Size + of.getLastFrameTime()*15;
	
	-- get relationship
	b1 = T_Size<S_Size
	DX = (T_PosX-S_PosX)
	DY = (T_PosY-S_PosY)
	Dist = math.sqrt(DX*DX+DY*DY)	
	b2 = Dist<math.abs(S_Size-T_Size)	
	
	scnSize = math.sqrt(of.getHeight()*of.getWidth())
	if not b1 then
		T_Alive = false
		
		dHP = -0.4*T_Size-5;
		HP = HP+dHP	
		
		Info = string.format("%.4f",dHP)		
		InfoX = S_PosX;
		InfoY = S_PosY-S_Size-scnSize/20.0;
		if InfoY<=scnSize/10 then
			InfoY = scnSize/10;
		end
		CF0 = 255
		CF1 = 0
		CF2 = 0
		CF3 = 255
		IEdgeSize = 1.0
		CE0 = 0
		CE1 = 0 
		CE2 = 0 
		CE3 = 120
		
		SoundName = "Shrink"
		SoundPlay = true
		
	end	
		
	if b1 and b2 then
		T_Alive = false		
		dExp = 15*T_Size/S_Size+100		
		Exp = Exp+dExp		
		Info = "Eat!"
		InfoX = T_PosX;
		InfoY = T_PosY-T_Size-scnSize/20.0;
		if InfoY<=0 then
			InfoY = scnSize/10;
		end
		CF0 = 0
		CF1 = 255
		CF2 = 0
		CF3 = 255
		IEdgeSize = 1.0
		CE0 = 0
		CE1 = 0 
		CE2 = 0 
		CE3 = 255
		
		SoundName = "Step"
		SoundPlay = true
	end	
	
end

----------------------------------------------------
function khDraw()
	--print("--khDraw--")
	
	
end
