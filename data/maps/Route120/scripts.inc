@ LOCALID_BRIDGE_KECLEON_SHADOW is a second object which is identical to LOCALID_BRIDGE_KECLEON but has a reflection palette tag for the bridge shadow
Route120_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, Route120_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, Route120_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, Route120_OnLoad
	.byte 0

Route120_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Route120_EventScript_RemoveKecleonObject
	end

Route120_EventScript_RemoveKecleonObject::
	call_if_eq VAR_0x8009, 0, Route120_EventScript_RemoveBridgeKecleon
	call_if_eq VAR_0x8009, 1, Route120_EventScript_RemoveKecleon
	call_if_eq VAR_0x8009, 2, Route120_EventScript_RemoveKecleon
	call_if_eq VAR_0x8009, 3, Route120_EventScript_RemoveKecleon
	call_if_eq VAR_0x8009, 4, Route120_EventScript_RemoveKecleon
	call_if_eq VAR_0x8009, 5, Route120_EventScript_RemoveKecleon
	return

Route120_EventScript_RemoveBridgeKecleon::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject LOCALID_BRIDGE_KECLEON
	removeobject LOCALID_BRIDGE_KECLEON_SHADOW
	return

Route120_EventScript_RemoveKecleon::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject VAR_LAST_TALKED
	return

Route120_OnLoad:
	call_if_unset FLAG_REGI_DOORS_OPENED, Route120_EventScript_CloseAncientTomb
	call_if_set FLAG_RECEIVED_DEVON_SCOPE, Route120_EventScript_SetBridgeClearMetatiles
	call_if_unset FLAG_RECEIVED_DEVON_SCOPE, Route120_EventScript_SetBridgeKecleonMovement
	end

Route120_EventScript_CloseAncientTomb::
	setmetatile 7, 54, METATILE_General_RockWall_RockBase, TRUE
	setmetatile 7, 55, METATILE_General_RockWall_SandBase, TRUE
	return

Route120_EventScript_SetBridgeClearMetatiles::
	setmetatile 13, 15, METATILE_Fortree_WoodBridge1_Top, FALSE
	setmetatile 12, 16, METATILE_Fortree_WoodBridge1_Bottom, FALSE
	setmetatile 12, 17, METATILE_General_ReflectiveWater, FALSE
	setmetatile 13, 17, METATILE_General_ReflectiveWater, FALSE
	return

Route120_EventScript_SetBridgeKecleonMovement::
	setobjectmovementtype LOCALID_BRIDGE_KECLEON_SHADOW, MOVEMENT_TYPE_FACE_RIGHT
	return

Route120_OnTransition:
	call GabbyAndTy_EventScript_UpdateLocation
	call Route120_EventScript_SetWeather
	end

Route120_EventScript_SetWeather::
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	goto_if_le VAR_TEMP_1, 14, Route120_EventScript_SetSunnyWeather
	goto_if_le VAR_TEMP_1, 60, Route120_EventScript_TrySetRainyWeather
	goto_if_ge VAR_TEMP_1, 61, Route120_EventScript_SetCloudyWeather
	return

Route120_EventScript_SetCloudyWeather::
	setweather WEATHER_SUNNY_CLOUDS
	return

Route120_EventScript_SetSunnyWeather::
	setweather WEATHER_SUNNY
	return

Route120_EventScript_TrySetRainyWeather::
	goto_if_le VAR_TEMP_0, 7, Route120_EventScript_SetRainyWeather
	goto_if_le VAR_TEMP_0, 19, Route120_EventScript_SetSunnyWeather
	goto Route120_EventScript_SetRainyWeather
	end

Route120_EventScript_SetRainyWeather::
	setweather WEATHER_RAIN
	return

Route120_EventScript_BerryBeauty::
	lock
	faceplayer
	dotimebasedevents
	goto_if_set FLAG_DAILY_ROUTE_120_RECEIVED_BERRY, Route120_EventScript_ReceivedBerry
	msgbox Route120_Text_BerriesExpressionOfLoveIsntIt, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, Route120_EventScript_BerryLove
	call_if_eq VAR_RESULT, NO, Route120_EventScript_BerryNotLove
	specialvar VAR_RESULT, GetPlayerTrainerIdOnesDigit
	switch VAR_RESULT
	case 0, Route120_EventScript_GiveFigyBerry
	case 5, Route120_EventScript_GiveFigyBerry
	case 1, Route120_EventScript_GiveWikiBerry
	case 6, Route120_EventScript_GiveWikiBerry
	case 2, Route120_EventScript_GiveMagoBerry
	case 7, Route120_EventScript_GiveMagoBerry
	case 3, Route120_EventScript_GiveAguavBerry
	case 8, Route120_EventScript_GiveAguavBerry
	case 4, Route120_EventScript_GiveIapapaBerry
	case 9, Route120_EventScript_GiveIapapaBerry
	end

Route120_EventScript_GiveFigyBerry::
	setvar VAR_0x8004, ITEM_FIGY_BERRY
	goto Route120_EventScript_GiveBerry
	end

Route120_EventScript_GiveWikiBerry::
	setvar VAR_0x8004, ITEM_WIKI_BERRY
	goto Route120_EventScript_GiveBerry
	end

Route120_EventScript_GiveMagoBerry::
	setvar VAR_0x8004, ITEM_MAGO_BERRY
	goto Route120_EventScript_GiveBerry
	end

Route120_EventScript_GiveAguavBerry::
	setvar VAR_0x8004, ITEM_AGUAV_BERRY
	goto Route120_EventScript_GiveBerry
	end

Route120_EventScript_GiveIapapaBerry::
	setvar VAR_0x8004, ITEM_IAPAPA_BERRY
	goto Route120_EventScript_GiveBerry
	end

Route120_EventScript_GiveBerry::
	giveitem VAR_0x8004
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_DAILY_ROUTE_120_RECEIVED_BERRY
	msgbox Route120_Text_BerryIsRareRaiseItWithCare, MSGBOX_DEFAULT
	release
	end

Route120_EventScript_ReceivedBerry::
	msgbox Route120_Text_IllGetMoreBerriesFromBerryMaster, MSGBOX_DEFAULT
	release
	end

Route120_EventScript_BerryLove::
	msgbox Route120_Text_YesYouUnderstand, MSGBOX_DEFAULT
	return

Route120_EventScript_BerryNotLove::
	msgbox Route120_Text_MakeYourOwnImpressions, MSGBOX_DEFAULT
	return

Route120_EventScript_Steven::
	lock
	faceplayer
	goto_if_set FLAG_NOT_READY_FOR_BATTLE_ROUTE_120, Route120_EventScript_StevenAskReadyForBattle
	msgbox Route120_Text_StevenGreeting, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Route120_EventScript_StevenNotReady
	goto Route120_EventScript_StevenBattleKecleon
	end

Route120_EventScript_StevenNotReady::
	msgbox Route120_Text_StevenIllWaitHere, MSGBOX_DEFAULT
	setflag FLAG_NOT_READY_FOR_BATTLE_ROUTE_120
	release
	end

Route120_EventScript_StevenAskReadyForBattle::
	msgbox Route120_Text_StevenReadyForBattle, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Route120_EventScript_StevenNotReady
	goto Route120_EventScript_StevenBattleKecleon
	end

Route120_EventScript_StevenBattleKecleon::
	msgbox Route120_Text_StevenShowMeYourPower, MSGBOX_DEFAULT
	closemessage
	call_if_eq VAR_FACING, DIR_NORTH, Route120_EventScript_PlayerApproachKecleonNorth
	call_if_eq VAR_FACING, DIR_WEST, Route120_EventScript_PlayerApproachKecleonWest
	applymovement LOCALID_ROUTE120_STEVEN, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	delay 20
	msgbox Route120_Text_StevenUsedDevonScope, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_BRIDGE_KECLEON, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	applymovement LOCALID_BRIDGE_KECLEON, Movement_KecleonAppears
	waitmovement 0
	waitse
	playmoncry SPECIES_KECLEON, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setwildbattle SPECIES_KECLEON, 30
	setvar VAR_0x8009, 0
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Route120_EventScript_RemoveBridgeKecleonPostBattle
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, Route120_EventScript_RemoveBridgeKecleonPostBattle
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, Route120_EventScript_RemoveBridgeKecleonPostBattle
	goto Route120_EventScript_StevenGiveDeconScope
	end

Route120_EventScript_RemoveBridgeKecleonPostBattle::
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject LOCALID_BRIDGE_KECLEON
	removeobject LOCALID_BRIDGE_KECLEON_SHADOW
	fadescreenswapbuffers FADE_FROM_BLACK
	goto Route120_EventScript_StevenGiveDeconScope
	end

Route120_EventScript_StevenGiveDeconScope::
	applymovement LOCALID_ROUTE120_STEVEN, Common_Movement_WalkInPlaceFasterDown
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox Route120_Text_StevenGiveDevonScope, MSGBOX_DEFAULT
	giveitem ITEM_DEVON_SCOPE
	setflag FLAG_RECEIVED_DEVON_SCOPE
	msgbox Route120_Text_StevenGoodbye, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ROUTE120_STEVEN, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 50
	setfieldeffectargument 0, 1
	dofieldeffect FLDEFF_NPCFLY_OUT
	delay 15
	removeobject LOCALID_ROUTE120_STEVEN
	waitfieldeffect FLDEFF_NPCFLY_OUT
	setmetatile 13, 15, METATILE_Fortree_WoodBridge1_Top, FALSE
	setmetatile 12, 16, METATILE_Fortree_WoodBridge1_Bottom, FALSE
	setmetatile 12, 17, METATILE_General_ReflectiveWater, FALSE
	setmetatile 13, 17, METATILE_General_ReflectiveWater, FALSE
	special DrawWholeMapView
	release
	end

Route120_EventScript_PlayerApproachKecleonNorth::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

Route120_EventScript_PlayerApproachKecleonWest::
	applymovement LOCALID_PLAYER, Route120_Movement_ApproachKecleonWest
	waitmovement 0
	return

Route120_Movement_ApproachKecleonWest:
	walk_down
	walk_left
	step_end

Route120_EventScript_BridgeKecleon::
	msgbox Kecleon_Text_SomethingUnseeable, MSGBOX_NPC
	end

Route120_EventScript_RouteSignFortree::
	msgbox Route120_Text_RouteSignFortree, MSGBOX_SIGN
	end

Route120_EventScript_RouteSign121::
	msgbox Route120_Text_RouteSign121, MSGBOX_SIGN
	end

Route120_EventScript_Colin::
	trainerbattle_single TRAINER_COLIN, Route120_Text_ColinIntro, Route120_Text_ColinDefeat
	msgbox Route120_Text_ColinPostBattle, MSGBOX_AUTOCLOSE
	end

Route120_EventScript_Robert::
	trainerbattle_single TRAINER_ROBERT_1, Route120_Text_RobertIntro, Route120_Text_RobertDefeat, Route120_EventScript_RegisterRobert
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route120_EventScript_RematchRobert
	msgbox Route120_Text_RobertPostBattle, MSGBOX_DEFAULT
	release
	end

Route120_EventScript_RegisterRobert::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route120_Text_RobertRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_ROBERT_1
	release
	end

Route120_EventScript_RematchRobert::
	trainerbattle_rematch TRAINER_ROBERT_1, Route120_Text_RobertRematchIntro, Route120_Text_RobertRematchDefeat
	msgbox Route120_Text_RobertPostRematch, MSGBOX_AUTOCLOSE
	end

Route120_EventScript_Lorenzo::
	trainerbattle_single TRAINER_LORENZO, Route120_Text_LorenzoIntro, Route120_Text_LorenzoDefeat
	msgbox Route120_Text_LorenzoPostBattle, MSGBOX_AUTOCLOSE
	end

Route120_EventScript_Jenna::
	trainerbattle_single TRAINER_JENNA, Route120_Text_JennaIntro, Route120_Text_JennaDefeat
	msgbox Route120_Text_JennaPostBattle, MSGBOX_AUTOCLOSE
	end

Route120_EventScript_Jeffrey::
	trainerbattle_single TRAINER_JEFFREY_1, Route120_Text_JeffreyIntro, Route120_Text_JeffreyDefeat, Route120_EventScript_RegisterJeffrey
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route120_EventScript_RematchJeffrey
	msgbox Route120_Text_JeffreyPostBattle, MSGBOX_DEFAULT
	release
	end

Route120_EventScript_RegisterJeffrey::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route120_Text_JeffreyRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_JEFFREY_1
	release
	end

Route120_EventScript_RematchJeffrey::
	trainerbattle_rematch TRAINER_JEFFREY_1, Route120_Text_JeffreyRematchIntro, Route120_Text_JeffreyRematchDefeat
	msgbox Route120_Text_JeffreyPostRematch, MSGBOX_AUTOCLOSE
	end

Route120_EventScript_Jennifer::
	trainerbattle_single TRAINER_JENNIFER, Route120_Text_JenniferIntro, Route120_Text_JenniferDefeat
	msgbox Route120_Text_JenniferPostBattle, MSGBOX_AUTOCLOSE
	end

Route120_EventScript_Chip::
	trainerbattle_single TRAINER_CHIP, Route120_Text_ChipIntro, Route120_Text_ChipDefeat
	msgbox Route120_Text_ChipPostBattle, MSGBOX_AUTOCLOSE
	end

Route120_EventScript_Clarissa::
	trainerbattle_single TRAINER_CLARISSA, Route120_Text_ClarissaIntro, Route120_Text_ClarissaDefeat
	msgbox Route120_Text_ClarissaPostBattle, MSGBOX_AUTOCLOSE
	end

Route120_EventScript_Angelica::
	trainerbattle_single TRAINER_ANGELICA, Route120_Text_AngelicaIntro, Route120_Text_AngelicaDefeat
	msgbox Route120_Text_AngelicaPostBattle, MSGBOX_AUTOCLOSE
	end

Route120_EventScript_Keigo::
	trainerbattle_single TRAINER_KEIGO, Route120_Text_KeigoIntro, Route120_Text_KeigoDefeat
	msgbox Route120_Text_KeigoPostBattle, MSGBOX_AUTOCLOSE
	end

Route120_EventScript_Riley::
	trainerbattle_single TRAINER_RILEY, Route120_Text_RileyIntro, Route120_Text_RileyDefeat
	msgbox Route120_Text_RileyPostBattle, MSGBOX_AUTOCLOSE
	end

Route120_EventScript_Leonel::
	trainerbattle_single TRAINER_LEONEL, Route120_Text_LeonelIntro, Route120_Text_LeonelDefeat
	msgbox Route120_Text_LeonelPostBattle, MSGBOX_AUTOCLOSE
	end

Route120_EventScript_Callie::
	trainerbattle_single TRAINER_CALLIE, Route120_Text_CallieIntro, Route120_Text_CallieDefeat
	msgbox Route120_Text_CalliePostBattle, MSGBOX_AUTOCLOSE
	end

Route120_Text_StevenGreeting:
    .string "大吾：嗯？{PLAYER}{KUN}，\n好久不见。\p这里好像有什么看不见\n的东西，对吧？\p对着这个看不见的障碍\n使用这个道具的话……\p不，与其说明，\n不如直接使用展示\l给你看更有趣。\p{PLAYER}{KUN}，\n你的宝可梦准备好战斗了吗？$"

Route120_Text_StevenIllWaitHere:
    .string "大吾：还没有吗？\p那我在这里等着你，\n去准备吧。$"

Route120_Text_StevenReadyForBattle:
    .string "大吾：{PLAYER}{KUN}，\n你的宝可梦准备好战斗了吗？？$"

Route120_Text_StevenShowMeYourPower:
    .string "大吾：{PLAYER}{KUN}，\n让我见识下你作为训练家的实力吧！$"

Route120_Text_StevenUsedDevonScope:
    .string "大吾使用了得文侦测镜。\p看不见的宝可梦\n完全现形了！\p受惊的宝可梦攻击过来了！$"

Route120_Text_StevenGiveDevonScope:
    .string "大吾：原来如此……\n你的战斗方式很有趣呢。\p比起在我们在武斗镇初见时，\n你的宝可梦成长了不少。\p这个得文侦测镜\n送给你，\p说不定还有其他隐藏了\n身形的宝可梦呢。$"

Route120_Text_StevenGoodbye:
    .string "大吾：{PLAYER}{KUN}，\p我很喜欢看到训练家和宝可梦\n共同努力一起成长，\p你做得很不错。\p那么，后会有期。$"

Kecleon_Text_SomethingUnseeable:
    .string "有什么看不见的东西挡在路上。$"

Kecleon_Text_WantToUseDevonScope:
    .string "有什么看不见的东西挡在路上。\p要使用得文侦测镜吗？$"

Kecleon_Text_UseDevonScopeMonAttacked:
    .string "{PLAYER}使用了得文侦测镜。\p看不见的宝可梦\n完全现形了！\p受惊的宝可梦攻击过来了！$"

Route120_Text_RouteSignFortree:
    .string "120号道路\n{LEFT_ARROW}茵郁市$"

Route120_Text_RouteSign121:
    .string "{RIGHT_ARROW}121号道路\n{LEFT_ARROW}120号道路$"
