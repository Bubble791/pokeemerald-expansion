SootopolisCity_Gym_1F_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SootopolisCity_Gym_1F_OnFrame
	map_script MAP_SCRIPT_ON_RESUME, SootopolisCity_Gym_1F_OnResume
	map_script MAP_SCRIPT_ON_LOAD, SootopolisCity_Gym_1F_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, SootopolisCity_Gym_1F_OnTransition
	.byte 0

SootopolisCity_Gym_1F_OnTransition:
	setvar VAR_ICE_STEP_COUNT, 1
	end

SootopolisCity_Gym_1F_OnResume:
	setstepcallback STEP_CB_SOOTOPOLIS_ICE
	end

SootopolisCity_Gym_1F_OnLoad:
	call SootopolisCity_Gym_1F_EventScript_CheckSetStairMetatiles
	special SetSootopolisGymCrackedIceMetatiles
	end

SootopolisCity_Gym_1F_EventScript_CheckSetStairMetatiles::
	goto_if_lt VAR_ICE_STEP_COUNT, 8, SootopolisCity_Gym_1F_EventScript_StopCheckingStairs  @ All stairs ice
	goto_if_lt VAR_ICE_STEP_COUNT, 28, SootopolisCity_Gym_1F_EventScript_OpenFirstStairs
	goto_if_lt VAR_ICE_STEP_COUNT, 67, SootopolisCity_Gym_1F_EventScript_OpenFirstAndSecondStairs
	setmetatile 8, 4, METATILE_SootopolisGym_Stairs, FALSE
	setmetatile 8, 5, METATILE_SootopolisGym_Stairs, FALSE
SootopolisCity_Gym_1F_EventScript_OpenFirstAndSecondStairs::
	setmetatile 8, 10, METATILE_SootopolisGym_Stairs, FALSE
	setmetatile 8, 11, METATILE_SootopolisGym_Stairs, FALSE
SootopolisCity_Gym_1F_EventScript_OpenFirstStairs::
	setmetatile 8, 15, METATILE_SootopolisGym_Stairs, FALSE
	setmetatile 8, 16, METATILE_SootopolisGym_Stairs, FALSE
SootopolisCity_Gym_1F_EventScript_StopCheckingStairs::
	return

SootopolisCity_Gym_1F_OnFrame:
	map_script_2 VAR_ICE_STEP_COUNT, 8, SootopolisCity_Gym_1F_EventScript_UnlockFirstStairs
	map_script_2 VAR_ICE_STEP_COUNT, 28, SootopolisCity_Gym_1F_EventScript_UnlockSecondStairs
	map_script_2 VAR_ICE_STEP_COUNT, 67, SootopolisCity_Gym_1F_EventScript_UnlockThirdStairs
	map_script_2 VAR_ICE_STEP_COUNT, 0, SootopolisCity_Gym_1F_EventScript_FallThroughIce
	.2byte 0

SootopolisCity_Gym_1F_EventScript_UnlockFirstStairs::
	addvar VAR_ICE_STEP_COUNT, 1
	delay 40
	playse SE_ICE_STAIRS
	call SootopolisCity_Gym_1F_EventScript_CheckSetStairMetatiles
	special DrawWholeMapView
	end

SootopolisCity_Gym_1F_EventScript_UnlockSecondStairs::
	addvar VAR_ICE_STEP_COUNT, 1
	delay 40
	playse SE_ICE_STAIRS
	call SootopolisCity_Gym_1F_EventScript_CheckSetStairMetatiles
	special DrawWholeMapView
	end

SootopolisCity_Gym_1F_EventScript_UnlockThirdStairs::
	addvar VAR_ICE_STEP_COUNT, 1
	delay 40
	playse SE_ICE_STAIRS
	call SootopolisCity_Gym_1F_EventScript_CheckSetStairMetatiles
	special DrawWholeMapView
	end

SootopolisCity_Gym_1F_EventScript_FallThroughIce::
	lockall
	delay 20
	applymovement OBJ_EVENT_ID_PLAYER, SootopolisCity_Gym_1F_Movement_FallThroughIce
	waitmovement 0
	playse SE_FALL
	delay 60
	warphole MAP_SOOTOPOLIS_CITY_GYM_B1F
	waitstate
	end

SootopolisCity_Gym_1F_Movement_FallThroughIce:
	set_invisible
	step_end

SootopolisCity_Gym_1F_EventScript_Juan::
	trainerbattle_single TRAINER_JUAN_1, SootopolisCity_Gym_1F_Text_JuanIntro, SootopolisCity_Gym_1F_Text_JuanDefeat, SootopolisCity_Gym_1F_EventScript_JuanDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	goto_if_eq VAR_RESULT, TRUE, SootopolisCity_Gym_1F_EventScript_JuanRematch
	goto_if_unset FLAG_RECEIVED_TM_WATER_PULSE, SootopolisCity_Gym_1F_EventScript_GiveWaterPulse2
	goto_if_unset FLAG_BADGE06_GET, SootopolisCity_Gym_1F_EventScript_GoGetFortreeBadge
	msgbox SootopolisCity_Gym_1F_Text_JuanPostBattle, MSGBOX_DEFAULT
	release
	end

SootopolisCity_Gym_1F_EventScript_JuanDefeated::
	message SootopolisCity_Gym_1F_Text_ReceivedRainBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox SootopolisCity_Gym_1F_Text_ExplainRainBadgeTakeThis, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_SOOTOPOLIS_GYM
	setflag FLAG_BADGE08_GET
	setflag FLAG_HIDE_SOOTOPOLIS_CITY_RESIDENTS
	setflag FLAG_HIDE_SOOTOPOLIS_CITY_STEVEN
	setflag FLAG_HIDE_SOOTOPOLIS_CITY_WALLACE
	setvar VAR_SOOTOPOLIS_CITY_STATE, 6
	clearflag FLAG_HIDE_SOOTOPOLIS_CITY_MAN_1
	setvar VAR_0x8008, 8
	call Common_EventScript_SetGymTrainers
	call SootopolisCity_Gym_1F_EventScript_GiveWaterPulse
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox SootopolisCity_Gym_1F_Text_RegisteredJuan, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_JUAN_MATCH_CALL
	release
	end

SootopolisCity_Gym_1F_EventScript_GiveWaterPulse::
	giveitem ITEM_TM_WATER_PULSE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_BagIsFull
	msgbox SootopolisCity_Gym_1F_Text_ExplainWaterPulse, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_WATER_PULSE
	return

SootopolisCity_Gym_1F_EventScript_GiveWaterPulse2::
	giveitem ITEM_TM_WATER_PULSE
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	msgbox SootopolisCity_Gym_1F_Text_ExplainWaterPulse, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM_WATER_PULSE
	release
	end

SootopolisCity_Gym_1F_EventScript_GoGetFortreeBadge::
	msgbox SootopolisCity_Gym_1F_Text_GoGetFortreeBadge, MSGBOX_DEFAULT
	release
	end

SootopolisCity_Gym_1F_EventScript_JuanRematch::
	trainerbattle_rematch_double TRAINER_JUAN_1, SootopolisCity_Gym_1F_Text_JuanPreRematch, SootopolisCity_Gym_1F_Text_JuanRematchDefeat, SootopolisCity_Gym_1F_Text_JuanRematchNeedTwoMons
	msgbox SootopolisCity_Gym_1F_Text_JuanPostRematch, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_1F_EventScript_GymGuide::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_SOOTOPOLIS_GYM, SootopolisCity_Gym_1F_EventScript_GymGuidePostVictory
	msgbox SootopolisCity_Gym_1F_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

SootopolisCity_Gym_1F_EventScript_GymGuidePostVictory::
	msgbox SootopolisCity_Gym_1F_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

SootopolisCity_Gym_1F_EventScript_LeftGymStatue::
	lockall
	goto_if_set FLAG_BADGE08_GET, SootopolisCity_Gym_1F_EventScript_GymStatueCertified
	goto SootopolisCity_Gym_1F_EventScript_GymStatue
	end

SootopolisCity_Gym_1F_EventScript_RightGymStatue::
	lockall
	goto_if_set FLAG_BADGE08_GET, SootopolisCity_Gym_1F_EventScript_GymStatueCertified
	goto SootopolisCity_Gym_1F_EventScript_GymStatue
	end

SootopolisCity_Gym_1F_EventScript_GymStatueCertified::
	msgbox SootopolisCity_Gym_1F_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

SootopolisCity_Gym_1F_EventScript_GymStatue::
	msgbox SootopolisCity_Gym_1F_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

SootopolisCity_Gym_1F_Text_GymGuideAdvice:
    .string "嗨，怎么样，向冠军目标\n冲刺的{PLAYER}？\p琉璃市的道馆馆主亚当\n是使用水属性宝可梦的大师，\p但要走到他面前，还要\n先通过冰结成的地面……\p很抱歉，我只能\n给你这一点建议。\p这条路，你要凭\n自己的智慧通过！$"

SootopolisCity_Gym_1F_Text_GymGuidePostVictory:
    .string "哟，被誉为丰缘第一的亚当\n都输给你了！\p好了！看看你的训练家卡，\p如果你得到了所有徽章，\n就向宝可梦联盟出发吧！$"

SootopolisCity_Gym_1F_Text_JuanIntro:
    .string "让我来考考你。\n你知道吗？\l啊，我没必要这么腼腆。\p是我教给了米可利\n关于宝可梦的一切。\p我曾经放弃了道馆馆主的职位，\n将道馆托付给了米可利\p但是现在我又\n不得不回来。\p啊，闲话说得够多了。\n让我们开始比试吧？\p请你见证\n我们的艺术。\p由我和宝可梦塑造的\n华丽的水之幻影！$"

@ NOTE: This defeat text actually causes a buffer overflow. It's about 50 bytes too long for
@ the gDisplayedStringBattle buffer that it's put into, and it stomps all over the gBattleTextBuffs
@ after, as well as the otherwise unused array after that. One wonders if that's the reason for
@ the existence of that unused array of ints.
SootopolisCity_Gym_1F_Text_JuanDefeat:
    .string "啊哈哈哈，好，好极了！\n你是赢家！\p在你身上，我看到了能\n克服一切的技巧的华丽光耀。\p然而，与我甚至米可利相比，\n你还欠缺优雅。\p也许我该借你\n一套衣服？\p…… …… ……\n…… …… ……\p哈哈哈，\n我只是在说笑！\p比起我的衣服，\n我更该给你这个，雨滴徽章。$"

SootopolisCity_Gym_1F_Text_ReceivedRainBadge:
    .string "{PLAYER}从亚当那里\n得到了雨滴徽章。$"

SootopolisCity_Gym_1F_Text_ExplainRainBadgeTakeThis:
    .string "有了雨滴徽章，\n你所有的宝可梦都会完全\l服从你的每个指示。\p你也能使用秘传招式攀瀑\n攀登瀑布了。\p然后，为了不让你\n忘记这场对战，收下这个……$"

SootopolisCity_Gym_1F_Text_ExplainWaterPulse:
    .string "我交给你的这个招式学习器\n里面是水之波动。\p使用它时偶尔会因为超声波\n使目标陷入混乱。\p…… …… ……$"

SootopolisCity_Gym_1F_Text_RegisteredJuan:
    .string "把道馆馆主亚当\n登记到宝可导航里了。$"

SootopolisCity_Gym_1F_Text_JuanPostBattle:
    .string "收集了丰缘地区所有的\n道馆徽章的训练家应该\l朝向最后的目的地前进，\p那就是宝可梦联盟。\p向着丰缘的最东方，\n前往那名为彩悠的岛屿吧。\p那里便是\n宝可梦联盟之所在。$"

SootopolisCity_Gym_1F_Text_GoGetFortreeBadge:
    .string "在丰缘地区仅剩\n最后1枚徽章了。\p如果你想挑战宝可梦联盟，\n你必须先获得茵郁市道馆的徽章。$"

SootopolisCity_Gym_1F_Text_GymStatue:
    .string "琉璃市宝可梦道馆$"

SootopolisCity_Gym_1F_Text_GymStatueCertified:
    .string "琉璃市宝可梦道馆\p亚当认可的训练家：\n{PLAYER}$"

SootopolisCity_Gym_1F_Text_JuanPreRematch:
    .string "亚当：啊，这间道馆终于恢复了\n它往日的风和日丽……\p但我们年轻的台风又再度袭来\n考验我们了！\p好的，我的朋友，\n当然！\p只要你想，\n我随时愿意与你共舞一曲！$"

SootopolisCity_Gym_1F_Text_JuanRematchDefeat:
    .string "啊哈哈哈，你是赢家！\n你又一次打败我了！$"

SootopolisCity_Gym_1F_Text_JuanPostRematch:
    .string "亚当：如果我说要收你做徒弟，\n我想你绝对会拒绝。\p我想要把我的外衣\n作礼物送给你，\p但如果我没想错的话，\n你肯定也会拒绝。\p我的朋友，\n这正是你的高贵的表现啊！$"

SootopolisCity_Gym_1F_Text_JuanRematchNeedTwoMons:
    .string "亚当：啊，这间道馆终于恢复了\n它往日的风和日丽……\p但我们年轻的台风又再度袭来\n考验我们了！\p好的，我的朋友，\n当然！\p只要你想，\n我随时愿意与你共舞一曲！\p啊，不不不，\n你只带了1只宝可梦。\p我希望你能至少\n带2只宝可梦来。$"

