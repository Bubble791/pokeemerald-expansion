.set LOCALID_NURSE, 1

MauvilleCity_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MauvilleCity_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

MauvilleCity_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_MAUVILLE_CITY
	call Common_EventScript_UpdateBrineyLocation
	goto MauvilleCity_PokemonCenter_1F_EventScript_SetMauvilleOldManGfx
	end

MauvilleCity_PokemonCenter_1F_EventScript_SetMauvilleOldManGfx::
	special SetMauvilleOldManObjEventGfx
	end

MauvilleCity_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_Woman1::
	msgbox MauvilleCity_PokemonCenter_1F_Text_ManOverThereSaysWeirdThings, MSGBOX_NPC
	end

MauvilleCity_PokemonCenter_1F_EventScript_Woman2::
	msgbox MauvilleCity_PokemonCenter_1F_Text_MyDataUpdatedFromRecordCorner, MSGBOX_NPC
	end

MauvilleCity_PokemonCenter_1F_EventScript_Youngster::
	msgbox MauvilleCity_PokemonCenter_1F_Text_RecordCornerSoundsFun, MSGBOX_NPC
	end

MauvilleCity_PokemonCenter_1F_Text_ManOverThereSaysWeirdThings:
    .string "那边那个人总是在说些\n奇怪的话！\p那个怪人真有趣，\n我想我不可能忘了他！$"

MauvilleCity_PokemonCenter_1F_Text_MyDataUpdatedFromRecordCorner:
    .string "我去联机俱乐部的记录角时，\n武斗镇的流行词的资料就更新了。\p现在这部分资料和我朋友的\n一模一样！$"

MauvilleCity_PokemonCenter_1F_Text_RecordCornerSoundsFun:
    .string "宝可梦中心楼上\n开了个联机俱乐部，\p不知道是干什么的，\n但听起来挺好玩。我要去看看！$"

