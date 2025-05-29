.set LOCALID_WALLACE, 1
.set LOCALID_RIVAL, 2
.set LOCALID_BIRCH, 3

EverGrandeCity_ChampionsRoom_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, EverGrandeCity_ChampionsRoom_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, EverGrandeCity_ChampionsRoom_OnWarp
	map_script MAP_SCRIPT_ON_FRAME_TABLE, EverGrandeCity_ChampionsRoom_OnFrame
	.byte 0

EverGrandeCity_ChampionsRoom_OnTransition:
	call Common_EventScript_SetupRivalGfxId
	end

EverGrandeCity_ChampionsRoom_OnWarp:
	map_script_2 VAR_TEMP_1, 0, EverGrandeCity_ChampionsRoom_EventScript_PlayerTurnNorth
	.2byte 0

EverGrandeCity_ChampionsRoom_EventScript_PlayerTurnNorth::
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	end

EverGrandeCity_ChampionsRoom_OnFrame:
	map_script_2 VAR_TEMP_1, 0, EverGrandeCity_ChampionsRoom_EventScript_EnterRoom
	.2byte 0

EverGrandeCity_ChampionsRoom_EventScript_EnterRoom::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkUp4
	waitmovement 0
	delay 40
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandeCity_ChampionsRoom_Movement_PlayerApproachWallace
	waitmovement 0
	setvar VAR_TEMP_1, 1
	goto EverGrandeCity_ChampionsRoom_EventScript_Wallace
	releaseall
	end

EverGrandeCity_ChampionsRoom_Movement_PlayerApproachWallace:
	walk_up
	walk_up
	step_end

EverGrandeCity_ChampionsRoom_EventScript_Wallace::
	playbgm MUS_ENCOUNTER_CHAMPION, FALSE
	msgbox EverGrandeCity_ChampionsRoom_Text_IntroSpeech, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_WALLACE, EverGrandeCity_ChampionsRoom_Text_Defeat
	goto EverGrandeCity_ChampionsRoom_EventScript_Defeated
	end

EverGrandeCity_ChampionsRoom_EventScript_Defeated::
	playse SE_DOOR
	setmetatile 6, 1, METATILE_EliteFour_OpenDoorChampion_Frame, FALSE
	setmetatile 6, 2, METATILE_EliteFour_OpenDoorChampion_Opening, FALSE
	special DrawWholeMapView
	msgbox EverGrandeCity_ChampionsRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
	closemessage
	playse SE_DOOR
	checkplayergender
	call_if_eq VAR_RESULT, MALE, EverGrandeCity_ChampionsRoom_EventScript_PlayMayMusic
	call_if_eq VAR_RESULT, FEMALE, EverGrandeCity_ChampionsRoom_EventScript_PlayBrendanMusic
	addobject LOCALID_RIVAL
	call EverGrandeCity_ChampionsRoom_EventScript_RivalApproachPlayer
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, EverGrandeCity_ChampionsRoom_EventScript_MayAdvice
	goto_if_eq VAR_RESULT, FEMALE, EverGrandeCity_ChampionsRoom_EventScript_BrendanAdvice
	end

EverGrandeCity_ChampionsRoom_EventScript_PlayMayMusic::
	playbgm MUS_ENCOUNTER_MAY, FALSE
	return

EverGrandeCity_ChampionsRoom_EventScript_PlayBrendanMusic::
	playbgm MUS_ENCOUNTER_BRENDAN, FALSE
	return

EverGrandeCity_ChampionsRoom_EventScript_MayAdvice::
	msgbox EverGrandeCity_ChampionsRoom_Text_MayAdvice, MSGBOX_DEFAULT
	delay 40
	playse SE_PIN
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	call EverGrandeCity_ChampionsRoom_EventScript_RivalLookBackAndForth
	msgbox EverGrandeCity_ChampionsRoom_Text_MayItsAlreadyOver, MSGBOX_DEFAULT
	goto EverGrandeCity_ChampionsRoom_EventScript_BirchArrivesExitForHoF
	end

EverGrandeCity_ChampionsRoom_EventScript_BrendanAdvice::
	msgbox EverGrandeCity_ChampionsRoom_Text_BrendanAdvice, MSGBOX_DEFAULT
	delay 40
	playse SE_PIN
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	call EverGrandeCity_ChampionsRoom_EventScript_RivalLookBackAndForth
	msgbox EverGrandeCity_ChampionsRoom_Text_BrendanYouveWon, MSGBOX_DEFAULT
	goto EverGrandeCity_ChampionsRoom_EventScript_BirchArrivesExitForHoF
	end

EverGrandeCity_ChampionsRoom_EventScript_BirchArrivesExitForHoF::
	closemessage
	addobject LOCALID_BIRCH
	applymovement LOCALID_BIRCH, EverGrandeCity_ChampionsRoom_Movement_BirchArrives
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox EverGrandeCity_ChampionsRoom_Text_BirchArriveRatePokedex, MSGBOX_DEFAULT
	call ProfBirch_EventScript_RatePokedex
	msgbox EverGrandeCity_ChampionsRoom_Text_BirchCongratulations, MSGBOX_DEFAULT
	applymovement LOCALID_WALLACE, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	delay 20
	applymovement LOCALID_WALLACE, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox EverGrandeCity_ChampionsRoom_Text_WallaceComeWithMe, MSGBOX_DEFAULT
	closemessage
	delay 30
	applymovement LOCALID_WALLACE, EverGrandeCity_ChampionsRoom_Movement_WallaceExitStart
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandeCity_ChampionsRoom_Movement_PlayerExitStart
	applymovement LOCALID_BIRCH, Common_Movement_WalkInPlaceFasterUp
	applymovement LOCALID_RIVAL, EverGrandeCity_ChampionsRoom_Movement_RivalFollows
	waitmovement 0
	delay 20
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox EverGrandeCity_ChampionsRoom_Text_WallaceWaitOutside, MSGBOX_DEFAULT
	checkplayergender
	call_if_eq VAR_RESULT, MALE, EverGrandeCity_ChampionsRoom_EventScript_MayCongratulations
	call_if_eq VAR_RESULT, FEMALE, EverGrandeCity_ChampionsRoom_EventScript_BrendanCongratulations
	closemessage
	applymovement LOCALID_WALLACE, EverGrandeCity_ChampionsRoom_Movement_WallaceExit
	applymovement OBJ_EVENT_ID_PLAYER, EverGrandeCity_ChampionsRoom_Movement_PlayerExit
	waitmovement 0
	setflag FLAG_HIDE_PETALBURG_GYM_GREETER
	warp MAP_EVER_GRANDE_CITY_HALL_OF_FAME, 7, 16
	waitstate
	releaseall
	end

EverGrandeCity_ChampionsRoom_EventScript_MayCongratulations::
	msgbox EverGrandeCity_ChampionsRoom_Text_MayCongratulations, MSGBOX_DEFAULT
	return

EverGrandeCity_ChampionsRoom_EventScript_BrendanCongratulations::
	msgbox EverGrandeCity_ChampionsRoom_Text_BrendanCongratulations, MSGBOX_DEFAULT
	return

EverGrandeCity_ChampionsRoom_EventScript_RivalApproachPlayer::
	applymovement LOCALID_RIVAL, EverGrandeCity_ChampionsRoom_Movement_RivalApproachPlayer
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

EverGrandeCity_ChampionsRoom_EventScript_RivalLookBackAndForth::
	applymovement LOCALID_RIVAL, EverGrandeCity_ChampionsRoom_Movement_RivalLookBackAndForth
	waitmovement 0
	return

EverGrandeCity_ChampionsRoom_Movement_PlayerExitStart:
	walk_up
	walk_up
	step_end

EverGrandeCity_ChampionsRoom_Movement_PlayerExit:
	walk_up
	delay_16
	walk_up
	delay_8
	set_invisible
	step_end

EverGrandeCity_ChampionsRoom_Movement_RivalApproachPlayer:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_up
	walk_in_place_faster_right
	step_end

EverGrandeCity_ChampionsRoom_Movement_RivalLookBackAndForth:
	walk_in_place_faster_up
	delay_16
	walk_in_place_faster_right
	delay_16
	walk_in_place_faster_up
	delay_8
	walk_in_place_faster_right
	delay_16
	step_end

EverGrandeCity_ChampionsRoom_Movement_RivalFollows:
	walk_right
	walk_up
	step_end

EverGrandeCity_ChampionsRoom_Movement_WallaceExitStart:
	walk_up
	walk_up
	walk_in_place_faster_down
	step_end

EverGrandeCity_ChampionsRoom_Movement_WallaceExit:
	walk_up
	delay_8
	set_invisible
	step_end

EverGrandeCity_ChampionsRoom_Movement_BirchArrives:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_right
	walk_up
	walk_in_place_faster_left
	step_end

EverGrandeCity_ChampionsRoom_Text_IntroSpeech:
    .string "米可利：欢迎你，{PLAYER}{KUN}。关于琉璃市的那件事……\n你做得真是太华丽了，\l凭一己之力就扭转了危机。\p哦！\p说是一己之力解决了\n那件事不太妥当，\p应该说你和你的宝可梦\n齐心协力排除万难才是。\p我们训练家通过给予宝可梦道具\n并教授它们对战的新技巧来培育它们，\p但我们自己也从宝可梦\n那里获益良多。\p而这里就是检验像你这样的\n训练家修行成果的地方。\p现在！\p谁是全丰缘最能与自己的宝可梦\n华丽共舞之人？\p此时此处，展示给我看吧！$"

EverGrandeCity_ChampionsRoom_Text_Defeat:
    .string "我，冠军，输了……\p美妙得令人赞叹！\n优雅得令人眼红！\l这实在是太～辉煌耀眼了！！\p光荣属于你，{PLAYER}{KUN}！\p你是一名真正高贵的\n宝可梦训练家！$"

EverGrandeCity_ChampionsRoom_Text_PostBattleSpeech:
    .string "米可利：你的宝可梦在对战中……\p时而轻柔如风，\n时而又迅猛如雷。\p还带着一丝，\n无疑是从你那里耳濡目染所得的，\l轻盈而坚定的优雅。\p甚至连我都为你\n出色的表现而深深地着迷！\p此刻你已站上宝可梦联盟\n光荣的顶峰，\p我宣布你已成为\n丰缘地区的新……$"

EverGrandeCity_ChampionsRoom_Text_MayAdvice:
    .string "小遥：{PLAYER}{KUN}！\p挑战冠军前\n给你几个建议……$"

EverGrandeCity_ChampionsRoom_Text_MayItsAlreadyOver:
    .string "小遥：咦？\n什么？\p{PLAYER}{KUN}……\n难道说……\l已经结束了？$"

EverGrandeCity_ChampionsRoom_Text_BrendanAdvice:
    .string "小悠：{PLAYER}！\p挑战冠军前\n需要建议吗？……$"

EverGrandeCity_ChampionsRoom_Text_BrendanYouveWon:
    .string "小悠：{PLAYER}……\p你该不会……\n已经打败冠军了？$"

EverGrandeCity_ChampionsRoom_Text_BirchArriveRatePokedex:
    .string "小田卷博士：看吧？\n我说什么来着，{RIVAL}？\p早就告诉你{PLAYER}{KUN}\n不用我们担心！\p…… …… …… ……\n{PLAYER}{KUN}，你终于做到了。\p当我听说你在橙华道馆\n打败了你的父亲，\l我就预感你可能有机会……\p但是没想到你现在\n真的成为了冠军！\p啊，对了！\p你的图鉴完成得如何了？\n来，让我看一下。$"

EverGrandeCity_ChampionsRoom_Text_BirchCongratulations:
    .string "小田卷博士：总之恭喜你！\p现在，昂首挺胸地走进\n最后的房间吧！$"

EverGrandeCity_ChampionsRoom_Text_WallaceComeWithMe:
    .string "米可利：{PLAYER}{KUN}……\p不，请容我改口。\p新任冠军！\p跟我来。$"

EverGrandeCity_ChampionsRoom_Text_WallaceWaitOutside:
    .string "米可利：我很抱歉，不过……\p从这里开始，只有成为冠军的\n训练家才能进入。\p请你和小田卷博士一起\n在外面等候吧。$"

EverGrandeCity_ChampionsRoom_Text_MayCongratulations:
    .string "小遥：哎……\p…… …… …… ……\n…… …… …… ……\p我开玩笑啦！没关系！\n毕竟是规定嘛！\p{PLAYER}{KUN}！\n真的恭喜你！$"

EverGrandeCity_ChampionsRoom_Text_BrendanCongratulations:
    .string "小悠：什么？！…… …… ……\n…… …… …… ……\p既然是规定，那也没办法。\p{PLAYER}，去吧！\n恭喜你！$"

