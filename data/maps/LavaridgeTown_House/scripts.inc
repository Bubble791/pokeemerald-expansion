LavaridgeTown_House_MapScripts::
	.byte 0

LavaridgeTown_House_EventScript_OldMan::
	msgbox LavaridgeTown_House_Text_WifeWarmingEggInHotSprings, MSGBOX_NPC
	end

LavaridgeTown_House_EventScript_Zigzagoon::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, CRY_MODE_NORMAL
	msgbox LavaridgeTown_House_Text_Zigzagoon, MSGBOX_DEFAULT
	waitmoncry
	release
	end

LavaridgeTown_House_Text_WifeWarmingEggInHotSprings:
    .string "我妻子正在温泉里暖着一个蛋。\p她在培育屋寄存了2只宝可梦，\n然后就发现了那个蛋！$"

LavaridgeTown_House_Text_Zigzagoon:
    .string "蛇纹熊：噗休！$"

