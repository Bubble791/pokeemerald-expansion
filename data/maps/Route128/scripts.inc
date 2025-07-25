Route128_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route128_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route128_OnFrame
	.byte 0

Route128_OnTransition:
	call_if_set FLAG_SYS_WEATHER_CTRL, Common_EventScript_SetAbnormalWeather
	end

Route128_OnFrame:
	map_script_2 VAR_ROUTE128_STATE, 1, Route128_EventScript_KyogreAwakenedScene
	.2byte 0

Route128_EventScript_KyogreAwakenedScene::
	lockall
	delay 20
	applymovement LOCALID_ROUTE128_ARCHIE, Route128_Movement_ArchieLookAround
	waitmovement 0
	msgbox Route128_Text_ArchieWhatHappened, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ROUTE128_ARCHIE, Route128_Movement_ArchieBackUp
	waitmovement 0
	msgbox Route128_Text_ArchieIOnlyWanted, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ROUTE128_MAXIE, Route128_Movement_MaxieApproachArchie
	waitmovement 0
	applymovement LOCALID_ROUTE128_ARCHIE, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox Route128_Text_MaxieDoYouUnderstandNow, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ROUTE128_MAXIE, Route128_Movement_MaxieApproachPlayer
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox Route128_Text_MaxieResposibilityFallsToArchieAndMe, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ROUTE128_ARCHIE, Route128_Movement_ArchieRunLeft
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	applymovement LOCALID_ROUTE128_MAXIE, Route128_Movement_MaxieWalkLeft
	waitmovement 0
	msgbox Route128_Text_MaxieThisDefiesBelief, MSGBOX_DEFAULT
	closemessage
	delay 40
	applymovement LOCALID_ROUTE128_MAXIE, Route128_Movement_MaxieExit
	applymovement LOCALID_ROUTE128_ARCHIE, Route128_Movement_ArchieExit
	waitmovement 0
	removeobject LOCALID_ROUTE128_MAXIE
	removeobject LOCALID_ROUTE128_ARCHIE
	delay 100
	setfieldeffectargument 0, 1
	dofieldeffect FLDEFF_NPCFLY_OUT
	waitfieldeffect FLDEFF_NPCFLY_OUT
	addobject LOCALID_ROUTE128_STEVEN
	applymovement LOCALID_ROUTE128_STEVEN, Route128_Movement_StevenApproachPlayer
	waitmovement 0
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	msgbox Route128_Text_StevenWhatIsHappening, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ROUTE128_STEVEN, Route128_Movement_StevenWalkUp
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	msgbox Route128_Text_StevenWholeWorldWillDrown, MSGBOX_DEFAULT
	applymovement LOCALID_ROUTE128_STEVEN, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	msgbox Route128_Text_StevenImGoingToSootopolis, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ROUTE128_STEVEN, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	delay 50
	setfieldeffectargument 0, 1
	dofieldeffect FLDEFF_NPCFLY_OUT
	delay 15
	removeobject LOCALID_ROUTE128_STEVEN
	waitfieldeffect FLDEFF_NPCFLY_OUT
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	setvar VAR_ROUTE128_STATE, 2
	releaseall
	end

Route128_Movement_Unused1:
	walk_fast_left
	step_end

Route128_Movement_Unused2:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

Route128_Movement_StevenWalkUp:
	walk_up
	step_end

Route128_Movement_StevenApproachPlayer:
	walk_fast_left
	step_end

Route128_Movement_ArchieLookAround:
	walk_fast_down
	walk_in_place_faster_left
	delay_16
	walk_in_place_faster_right
	delay_16
	delay_16
	walk_in_place_faster_down
	step_end

Route128_Movement_ArchieBackUp:
	lock_facing_direction
	walk_slow_up
	delay_16
	unlock_facing_direction
	step_end

Route128_Movement_ArchieRunLeft:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_in_place_faster_right
	step_end

Route128_Movement_ArchieExit:
	delay_16
	delay_16
	walk_fast_up
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

Route128_Movement_MaxieWalkLeft:
	walk_left
	walk_left
	delay_8
	delay_4
	step_end

Route128_Movement_MaxieApproachArchie:
	walk_left
	walk_in_place_faster_down
	step_end

Route128_Movement_MaxieExit:
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

Route128_Movement_MaxieApproachPlayer:
	walk_right
	walk_in_place_faster_down
	step_end

Route128_EventScript_Isaiah::
	trainerbattle_single TRAINER_ISAIAH_1, Route128_Text_IsaiahIntro, Route128_Text_IsaiahDefeat, Route128_EventScript_RegisterIsaiah
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route128_EventScript_RematchIsaiah
	msgbox Route128_Text_IsaiahPostBattle, MSGBOX_DEFAULT
	release
	end

Route128_EventScript_RegisterIsaiah::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route128_Text_IsaiahRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_ISAIAH_1
	release
	end

Route128_EventScript_RematchIsaiah::
	trainerbattle_rematch TRAINER_ISAIAH_1, Route128_Text_IsaiahRematchIntro, Route128_Text_IsaiahRematchDefeat
	msgbox Route128_Text_IsaiahPostRematch, MSGBOX_AUTOCLOSE
	end

Route128_EventScript_Katelyn::
	trainerbattle_single TRAINER_KATELYN_1, Route128_Text_KatelynIntro, Route128_Text_KatelynDefeat, Route128_EventScript_RegisterKatelyn
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, Route128_EventScript_RematchKatelyn
	msgbox Route128_Text_KatelynPostBattle, MSGBOX_DEFAULT
	release
	end

Route128_EventScript_RegisterKatelyn::
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route128_Text_KatelynRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_KATELYN_1
	release
	end

Route128_EventScript_RematchKatelyn::
	trainerbattle_rematch TRAINER_KATELYN_1, Route128_Text_KatelynRematchIntro, Route128_Text_KatelynRematchDefeat
	msgbox Route128_Text_KatelynPostRematch, MSGBOX_AUTOCLOSE
	end

Route128_EventScript_Alexa::
	trainerbattle_single TRAINER_ALEXA, Route128_Text_AlexaIntro, Route128_Text_AlexaDefeat
	msgbox Route128_Text_AlexaPostBattle, MSGBOX_AUTOCLOSE
	end

Route128_EventScript_Ruben::
	trainerbattle_single TRAINER_RUBEN, Route128_Text_RubenIntro, Route128_Text_RubenDefeat
	msgbox Route128_Text_RubenPostBattle, MSGBOX_AUTOCLOSE
	end

Route128_EventScript_Wayne::
	trainerbattle_single TRAINER_WAYNE, Route128_Text_WayneIntro, Route128_Text_WayneDefeat
	msgbox Route128_Text_WaynePostBattle, MSGBOX_AUTOCLOSE
	end

Route128_EventScript_Harrison::
	trainerbattle_single TRAINER_HARRISON, Route128_Text_HarrisonIntro, Route128_Text_HarrisonDefeat
	msgbox Route128_Text_HarrisonPostBattle, MSGBOX_AUTOCLOSE
	end

Route128_EventScript_Carlee::
	trainerbattle_single TRAINER_CARLEE, Route128_Text_CarleeIntro, Route128_Text_CarleeDefeat
	msgbox Route128_Text_CarleePostBattle, MSGBOX_AUTOCLOSE
	end

Route128_Text_ArchieWhatHappened:
    .string "水梧桐：怎么会这样……\n这惨状……\p难道我……犯下大错了？$"

Route128_Text_ArchieIOnlyWanted:
    .string "我……\n我只想……$"

Route128_Text_MaxieDoYouUnderstandNow:
    .string "赤焰松：现在明白了吗，\n水梧桐？\p你总算明白你所谓的梦想\n酿成多大的灾难了吗？\p我们得抓紧时间！\n我们得在局势彻底\l失控前做些什么！$"

Route128_Text_MaxieResposibilityFallsToArchieAndMe:
    .string "赤焰松：{PLAYER}，不用说了……\p我知道自己没资格\n批评水梧桐……\p但事已至此，以我们人类的力量而言，\n恐怕已经无力回天了。\p但我们也不能只是\n束手无策地旁观。\p我和水梧桐必须承担起责任\n来终结我们造成的这一切……$"

Route128_Text_MaxieThisDefiesBelief:
    .string "赤焰松：难以置信……\p那些超古代宝可梦……\p它们的力量简直超乎想象。\n它们打破了自然的平衡……$"

Route128_Text_StevenWhatIsHappening:
    .string "大吾：{PLAYER}{KUN}！\n这究竟……？$"

Route128_Text_StevenWholeWorldWillDrown:
    .string "太糟糕了……\p足以烤干大地的热浪之后，\n又是淹没一切的洪水。\p这样下去的话，整个丰缘地区……\n不，是整个世界都会毁灭的。\p巨大的雨云不断\n从琉璃市上空飘来……\p那里究竟发生了什么？\p没时间思考了……\n答案应该就在琉璃市那里……$"

Route128_Text_StevenImGoingToSootopolis:
    .string "{PLAYER}{KUN}……\n我不知道你怎么打算，\l但千万不要勉强。\p好了，\n我先去琉璃市了。$"

