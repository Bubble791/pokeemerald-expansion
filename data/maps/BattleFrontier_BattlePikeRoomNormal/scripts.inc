BattleFrontier_BattlePikeRoomNormal_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, BattleFrontier_BattlePikeRoom_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_BattlePikeRoom_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, BattleFrontier_BattlePikeRoomNormal_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, BattleFrontier_BattlePikeRoom_OnWarp
	.byte 0

BattleFrontier_BattlePikeRoomNormal_OnFrame:
	map_script_2 VAR_TEMP_0, 0, BattleFrontier_BattlePikeRoomNormal_EventScript_EnterRoom
	.2byte 0

BattleFrontier_BattlePikeRoomNormal_EventScript_EnterRoom::
	setvar VAR_TEMP_0, 1
	pike_getroomtype
	switch VAR_RESULT
	case PIKE_ROOM_SINGLE_BATTLE, BattleFrontier_BattlePikeRoomNormal_EventScript_EnterSingleBattleRoom
	case PIKE_ROOM_HEAL_FULL, BattleFrontier_BattlePikeRoomNormal_EventScript_EnterFullHealRoom
	case PIKE_ROOM_STATUS, BattleFrontier_BattlePikeRoomNormal_EventScript_EnterStatusRoom
	case PIKE_ROOM_HARD_BATTLE, BattleFrontier_BattlePikeRoomNormal_EventScript_EnterHardBattleRoom
	case PIKE_ROOM_DOUBLE_BATTLE, BattleFrontier_BattlePikeRoomNormal_EventScript_EnterDoubleBattleRoom
	case PIKE_ROOM_BRAIN, BattleFrontier_BattlePikeRoomNormal_EventScript_EnterBrainRoom
	end

BattleFrontier_BattlePikeRoomNormal_EventScript_EnterSingleBattleRoom::
	lockall
	delay 16
	applymovement LOCALID_PIKE_ROOM_NPC_1, BattleFrontier_BattlePikeRoomNormal_Movement_ApproachPlayer
	waitmovement 0
	pike_gettrainerintro 0
	msgbox gStringVar4, MSGBOX_DEFAULT
	waitmessage
	closemessage
	releaseall
	setvar VAR_0x8004, SPECIAL_BATTLE_PIKE_SINGLE
	setvar VAR_0x8005, 0
	special DoSpecialTrainerBattle
	waitstate
	switch VAR_RESULT
	case 1, BattleFrontier_BattlePikeRoomNormal_EventScript_WonSingleBattle
BattleFrontier_BattlePikeRoomNormal_EventScript_WarpToLobbyLost::
	frontier_set FRONTIER_DATA_CHALLENGE_STATUS, CHALLENGE_STATUS_LOST
	warp MAP_BATTLE_FRONTIER_BATTLE_PIKE_LOBBY, 5, 6
	waitstate
	end

BattleFrontier_BattlePikeRoomNormal_EventScript_WonSingleBattle::
	applymovement LOCALID_PIKE_ROOM_NPC_1, BattleFrontier_BattlePikeRoomNormal_Movement_NPCExit
	waitmovement 0
	end

BattleFrontier_BattlePikeRoomNormal_EventScript_EnterHardBattleRoom::
	lockall
	delay 16
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_BattleSomewhatToughTrainer, MSGBOX_DEFAULT
	waitmessage
	closemessage
	applymovement LOCALID_PIKE_ROOM_NPC_1, BattleFrontier_BattlePikeRoomNormal_Movement_ApproachPlayer
	waitmovement 0
	pike_gettrainerintro 0
	msgbox gStringVar4, MSGBOX_DEFAULT
	waitmessage
	closemessage
	releaseall
	setvar VAR_0x8004, SPECIAL_BATTLE_PIKE_SINGLE
	setvar VAR_0x8005, 0
	special DoSpecialTrainerBattle
	waitstate
	switch VAR_RESULT
	case 1, BattleFrontier_BattlePikeRoomNormal_EventScript_WonHardBattle
	goto BattleFrontier_BattlePikeRoomNormal_EventScript_WarpToLobbyLost
	end

BattleFrontier_BattlePikeRoomNormal_EventScript_WonHardBattle::
	applymovement LOCALID_PIKE_ROOM_NPC_1, BattleFrontier_BattlePikeRoomNormal_Movement_NPCExit
	waitmovement 0
	applymovement LOCALID_PIKE_ROOM_NPC_2, BattleFrontier_BattlePikeRoomNormal_Movement_HealNPCApproachPlayer
	waitmovement 0
	lock
	faceplayer
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_RestoreToFullHealth, MSGBOX_DEFAULT
	playfanfare MUS_HEAL
	waitfanfare
	special HealPlayerParty
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_EnjoyRestOfChallenge2, MSGBOX_DEFAULT
	closemessage
	release
	applymovement LOCALID_PIKE_ROOM_NPC_2, BattleFrontier_BattlePikeRoomNormal_Movement_NPCExit
	waitmovement 0
	end

BattleFrontier_BattlePikeRoomNormal_EventScript_EnterBrainRoom::
	delay 22
	lockall
	applymovement LOCALID_PIKE_ROOM_NPC_2, BattleFrontier_BattlePikeRoomNormal_Movement_PreQueenHealNPCApproachPlayer
	waitmovement 0
	pike_prequeenheal
	switch VAR_RESULT
	case 0, BattleFrontier_BattlePikeRoomNormal_EventScript_PreQueenNoHeal
	case 1, BattleFrontier_BattlePikeRoomNormal_EventScript_PreQueenHealOneMon
	case 2, BattleFrontier_BattlePikeRoomNormal_EventScript_PreQueenHealTwoMons

BattleFrontier_BattlePikeRoomNormal_EventScript_LucyEnter::
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_ShallFetchOurMaster, MSGBOX_DEFAULT
	closemessage
	special SpawnCameraObject
	applymovement LOCALID_CAMERA, BattleFrontier_BattlePikeRoomNormal_Movement_CameraPanUp
	applymovement LOCALID_PIKE_ROOM_NPC_2, BattleFrontier_BattlePikeRoomNormal_Movement_HealNPCExitForLucy
	waitmovement 0
	playse SE_PIKE_CURTAIN_CLOSE
	call BattleFrontier_BattlePikeRoomNormal_EventScript_SetCurtainTilesLittleClosed
	delay 4
	call BattleFrontier_BattlePikeRoomNormal_EventScript_SetCurtainTilesMostlyClosed
	delay 4
	call BattleFrontier_BattlePikeRoomNormal_EventScript_SetCurtainTilesClosed
	delay 4
	waitse
	delay 60
	playse SE_PIKE_CURTAIN_OPEN
	delay 65
	call BattleFrontier_BattlePikeRoomNormal_EventScript_SetCurtainTilesMostlyClosed
	showobjectat LOCALID_PIKE_ROOM_NPC_1, MAP_BATTLE_FRONTIER_BATTLE_PIKE_ROOM_NORMAL
	delay 4
	call BattleFrontier_BattlePikeRoomNormal_EventScript_SetCurtainTilesLittleClosed
	delay 4
	call BattleFrontier_BattlePikeRoomNormal_EventScript_SetCurtainTilesOpen
	waitse
	applymovement LOCALID_PIKE_ROOM_NPC_1, BattleFrontier_BattlePikeRoomNormal_Movement_LucyEnter
	waitmovement 0
	pike_getbrainstatus
	switch VAR_RESULT
	case FRONTIER_BRAIN_GOLD, BattleFrontier_BattlePikeRoomNormal_EventScript_IntroLucyGold
	case FRONTIER_BRAIN_STREAK, BattleFrontier_BattlePikeRoomNormal_EventScript_BattleLucySilver
	case FRONTIER_BRAIN_STREAK_LONG, BattleFrontier_BattlePikeRoomNormal_EventScript_BattleLucyGold
	frontier_get FRONTIER_DATA_HEARD_BRAIN_SPEECH
	goto_if_ne VAR_RESULT, FALSE, BattleFrontier_BattlePikeRoomNormal_EventScript_BattleLucySilver
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_ImThePikeQueen, MSGBOX_DEFAULT
	frontier_set FRONTIER_DATA_HEARD_BRAIN_SPEECH
BattleFrontier_BattlePikeRoomNormal_EventScript_BattleLucySilver::
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_HopeYouDidntUseUpLuck, MSGBOX_DEFAULT
	call BattleFrontier_BattlePikeRoomNormal_EventScript_DoPikeQueenBattle
	goto_if_eq VAR_RESULT, 1, BattleFrontier_BattlePikeRoomNormal_EventScript_DefeatedLucySilver
	goto BattleFrontier_BattlePikeRoomNormal_EventScript_WarpToLobbyLost

BattleFrontier_BattlePikeRoomNormal_EventScript_DefeatedLucySilver::
	frontier_getsymbols
	goto_if_ne VAR_RESULT, 0, BattleFrontier_BattlePikeRoomNormal_EventScript_DefeatedLucy
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_LucyShowMeFrontierPass, MSGBOX_DEFAULT
	waitmessage
	playfanfare MUS_OBTAIN_SYMBOL
	message BattleFrontier_BattlePikeRoomNormal_Text_ReceivedLuckSymbol
	waitmessage
	waitfanfare
	frontier_givesymbol
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_AllThereIsDisappear, MSGBOX_DEFAULT
	closemessage
	goto BattleFrontier_BattlePikeRoomNormal_EventScript_DefeatedLucy

BattleFrontier_BattlePikeRoomNormal_EventScript_IntroLucyGold::
	frontier_get FRONTIER_DATA_HEARD_BRAIN_SPEECH
	goto_if_ne VAR_RESULT, FALSE, BattleFrontier_BattlePikeRoomNormal_EventScript_BattleLucyGold
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_LucyYouAgain, MSGBOX_DEFAULT
	frontier_set FRONTIER_DATA_HEARD_BRAIN_SPEECH
BattleFrontier_BattlePikeRoomNormal_EventScript_BattleLucyGold::
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_NowComeOn, MSGBOX_DEFAULT
	call BattleFrontier_BattlePikeRoomNormal_EventScript_DoPikeQueenBattle
	goto_if_eq VAR_RESULT, 1, BattleFrontier_BattlePikeRoomNormal_EventScript_DefeatedLucyGold
	goto BattleFrontier_BattlePikeRoomNormal_EventScript_WarpToLobbyLost

BattleFrontier_BattlePikeRoomNormal_EventScript_DefeatedLucyGold::
	frontier_getsymbols
	goto_if_eq VAR_RESULT, 2, BattleFrontier_BattlePikeRoomNormal_EventScript_DefeatedLucy
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_LucyFrontierPass, MSGBOX_DEFAULT
	waitmessage
	playfanfare MUS_OBTAIN_SYMBOL
	message BattleFrontier_BattlePikeRoomNormal_Text_LuckSymbolTookGoldenShine
	waitmessage
	waitfanfare
	frontier_givesymbol
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_IWontForget, MSGBOX_DEFAULT
	closemessage
	goto BattleFrontier_BattlePikeRoomNormal_EventScript_DefeatedLucy
	end

BattleFrontier_BattlePikeRoomNormal_EventScript_DefeatedLucy::
	applymovement LOCALID_PIKE_ROOM_NPC_1, BattleFrontier_BattlePikeRoomNormal_Movement_LucyMoveAside
	waitmovement 0
	applymovement LOCALID_PLAYER, BattleFrontier_BattlePikeRoomNormal_Movement_PlayerWalkUp2
	waitmovement 0
	pike_get PIKE_DATA_WIN_STREAK
	addvar VAR_RESULT, 1
	pike_set PIKE_DATA_WIN_STREAK, VAR_RESULT
	call BattleFrontier_BattlePikeRoom_EventScript_WarpToFinalRoom
	waitstate
	end

BattleFrontier_BattlePikeRoomNormal_EventScript_PreQueenNoHeal::
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_ChoseRoomNoHeal, MSGBOX_DEFAULT
	goto BattleFrontier_BattlePikeRoomNormal_EventScript_LucyEnter
	end

BattleFrontier_BattlePikeRoomNormal_EventScript_PreQueenHealOneMon::
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_ChoseRoomHealOne, MSGBOX_DEFAULT
	playfanfare MUS_HEAL
	waitfanfare
	goto BattleFrontier_BattlePikeRoomNormal_EventScript_LucyEnter
	end

BattleFrontier_BattlePikeRoomNormal_EventScript_PreQueenHealTwoMons::
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_ChoseRoomHealTwo, MSGBOX_DEFAULT
	playfanfare MUS_HEAL
	waitfanfare
	goto BattleFrontier_BattlePikeRoomNormal_EventScript_LucyEnter
	end

BattleFrontier_BattlePikeRoomNormal_EventScript_EnterFullHealRoom::
	lockall
	delay 16
	applymovement LOCALID_PIKE_ROOM_NPC_1, BattleFrontier_BattlePikeRoomNormal_Movement_ApproachPlayer
	waitmovement 0
	message BattleFrontier_BattlePikeRoomNormal_Text_WillRestoreToFullHealth
	waitmessage
	playfanfare MUS_HEAL
	waitfanfare
	special HealPlayerParty
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_EnjoyRestOfChallenge, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PIKE_ROOM_NPC_1, BattleFrontier_BattlePikeRoomNormal_Movement_NPCExit
	waitmovement 0
	releaseall
	end

BattleFrontier_BattlePikeRoomNormal_EventScript_EnterDoubleBattleRoom::
	lockall
	delay 16
	applymovement LOCALID_PIKE_ROOM_NPC_1, BattleFrontier_BattlePikeRoomNormal_Movement_Trainer1WalkRight
	applymovement LOCALID_PIKE_ROOM_NPC_2, BattleFrontier_BattlePikeRoomNormal_Movement_Trainer2WalkLeft
	waitmovement 0
	applymovement LOCALID_PIKE_ROOM_NPC_1, BattleFrontier_BattlePikeRoomNormal_Movement_DoubleTrainersWalkDown
	applymovement LOCALID_PIKE_ROOM_NPC_2, BattleFrontier_BattlePikeRoomNormal_Movement_DoubleTrainersWalkDown
	waitmovement 0
	applymovement LOCALID_PIKE_ROOM_NPC_1, BattleFrontier_BattlePikeRoomNormal_Movement_Trainer1FacePlayer
	applymovement LOCALID_PIKE_ROOM_NPC_2, BattleFrontier_BattlePikeRoomNormal_Movement_Trainer2FacePlayer
	waitmovement 0
	applymovement LOCALID_PLAYER, BattleFrontier_BattlePikeRoomNormal_Movement_PlayerFaceTrainer1
	waitmovement 0
	pike_gettrainerintro 0
	msgbox gStringVar4, MSGBOX_DEFAULT
	closemessage
	delay 16
	applymovement LOCALID_PLAYER, BattleFrontier_BattlePikeRoomNormal_Movement_PlayerFaceTrainer2
	waitmovement 0
	pike_gettrainerintro 1
	msgbox gStringVar4, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, SPECIAL_BATTLE_PIKE_DOUBLE
	setvar VAR_0x8005, 0
	special DoSpecialTrainerBattle
	waitstate
	switch VAR_RESULT
	case 1, BattleFrontier_BattlePikeRoomNormal_EventScript_WonDoubleBattle
	goto BattleFrontier_BattlePikeRoomNormal_EventScript_WarpToLobbyLost
	end

BattleFrontier_BattlePikeRoomNormal_EventScript_WonDoubleBattle::
	applymovement LOCALID_PLAYER, BattleFrontier_BattlePikeRoomNormal_Movement_PlayerFaceTrainer2
	waitmovement 0
	applymovement LOCALID_PIKE_ROOM_NPC_1, BattleFrontier_BattlePikeRoomNormal_Movement_Trainer1Exit
	waitmovement 0
	applymovement LOCALID_PIKE_ROOM_NPC_2, BattleFrontier_BattlePikeRoomNormal_Movement_Trainer2Exit
	waitmovement 0
	applymovement LOCALID_PLAYER, BattleFrontier_BattlePikeRoomNormal_Movement_PlayerFaceUp
	waitmovement 0
	end

BattleFrontier_BattlePikeRoomNormal_EventScript_EnterStatusRoom::
	lockall
	message BattleFrontier_BattlePikeRoomNormal_Text_WatchOut
	applymovement LOCALID_PIKE_ROOM_NPC_2, BattleFrontier_BattlePikeRoomNormal_Movement_MonApproachPlayer
	waitmovement 0
	pike_getstatusmon
	copyvar VAR_0x8004, VAR_RESULT
	call_if_eq VAR_0x8004, PIKE_STATUSMON_KIRLIA, BattleFrontier_BattlePikeRoomNormal_EventScript_KirliaAttack
	call_if_eq VAR_0x8004, PIKE_STATUSMON_DUSCLOPS, BattleFrontier_BattlePikeRoomNormal_EventScript_DusclopsAttack
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_AttacksWhenStartled, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

BattleFrontier_BattlePikeRoomNormal_EventScript_KirliaAttack::
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_KirliaStop, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_KIRLIA, CRY_MODE_NORMAL
	waitmoncry
	pike_getstatus
	call_if_eq VAR_RESULT, PIKE_STATUS_TOXIC, BattleFrontier_BattlePikeRoomNormal_EventScript_KirliaUsedToxic
	call_if_eq VAR_RESULT, PIKE_STATUS_BURN, BattleFrontier_BattlePikeRoomNormal_EventScript_KirliaUsedWillOWisp
	call_if_eq VAR_RESULT, PIKE_STATUS_PARALYSIS, BattleFrontier_BattlePikeRoomNormal_EventScript_KirliaUsedThunderWave
	call_if_eq VAR_RESULT, PIKE_STATUS_SLEEP, BattleFrontier_BattlePikeRoomNormal_EventScript_KirliaUsedHypnosis
	pike_flashscreen
	waitstate
	applymovement LOCALID_PIKE_ROOM_NPC_1, BattleFrontier_BattlePikeRoomNormal_Movement_NPCApproachMon
	waitmovement 0
	applymovement LOCALID_PIKE_ROOM_NPC_2, BattleFrontier_BattlePikeRoomNormal_Movement_MonFaceNPC
	waitmovement 0
	waitse
	playmoncry SPECIES_KIRLIA, CRY_MODE_NORMAL
	waitmoncry
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_ThatsEnough, MSGBOX_DEFAULT
	waitse
	playmoncry SPECIES_KIRLIA, CRY_MODE_NORMAL
	waitmoncry
	closemessage
	applymovement LOCALID_PIKE_ROOM_NPC_2, BattleFrontier_BattlePikeRoomNormal_Movement_MonMoveAside
	applymovement LOCALID_PIKE_ROOM_NPC_1, BattleFrontier_BattlePikeRoomNormal_Movement_StatusNPCApproachPlayer
	waitmovement 0
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_ApologizeForKirlia, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePikeRoomNormal_EventScript_DusclopsAttack::
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_DusclopsStop, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_DUSCLOPS, CRY_MODE_NORMAL
	waitmoncry
	pike_getstatus
	call_if_eq VAR_RESULT, PIKE_STATUS_FREEZE, BattleFrontier_BattlePikeRoomNormal_EventScript_DusclopsUsedIceBeam
	call_if_eq VAR_RESULT, PIKE_STATUS_BURN, BattleFrontier_BattlePikeRoomNormal_EventScript_DusclopsUsedWillOWisp
	pike_flashscreen
	waitstate
	applymovement LOCALID_PIKE_ROOM_NPC_1, BattleFrontier_BattlePikeRoomNormal_Movement_NPCApproachMon
	waitmovement 0
	applymovement LOCALID_PIKE_ROOM_NPC_2, BattleFrontier_BattlePikeRoomNormal_Movement_MonFaceNPC
	waitmovement 0
	waitse
	playmoncry SPECIES_DUSCLOPS, CRY_MODE_NORMAL
	waitmoncry
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_ThatsEnough, MSGBOX_DEFAULT
	waitse
	playmoncry SPECIES_DUSCLOPS, CRY_MODE_NORMAL
	waitmoncry
	closemessage
	applymovement LOCALID_PIKE_ROOM_NPC_2, BattleFrontier_BattlePikeRoomNormal_Movement_MonMoveAside
	applymovement LOCALID_PIKE_ROOM_NPC_1, BattleFrontier_BattlePikeRoomNormal_Movement_StatusNPCApproachPlayer
	waitmovement 0
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_ApologizeForDusclops, MSGBOX_DEFAULT
	return

BattleFrontier_BattlePikeRoomNormal_EventScript_KirliaUsedToxic::
	message BattleFrontier_BattlePikeRoomNormal_Text_KirliaUsedToxic
	waitmessage
	return

BattleFrontier_BattlePikeRoomNormal_EventScript_KirliaUsedWillOWisp::
	message BattleFrontier_BattlePikeRoomNormal_Text_KirliaUsedWillOWisp
	waitmessage
	return

BattleFrontier_BattlePikeRoomNormal_EventScript_KirliaUsedThunderWave::
	message BattleFrontier_BattlePikeRoomNormal_Text_KirliaUsedThunderWave
	waitmessage
	return

BattleFrontier_BattlePikeRoomNormal_EventScript_KirliaUsedHypnosis::
	message BattleFrontier_BattlePikeRoomNormal_Text_KirliaUsedHypnosis
	waitmessage
	return

BattleFrontier_BattlePikeRoomNormal_EventScript_DusclopsUsedIceBeam::
	message BattleFrontier_BattlePikeRoomNormal_Text_DusclopsUsedIceBeam
	waitmessage
	return

BattleFrontier_BattlePikeRoomNormal_EventScript_DusclopsUsedWillOWisp::
	message BattleFrontier_BattlePikeRoomNormal_Text_DusclopsUsedWillOWisp
	waitmessage
	return

BattleFrontier_BattlePikeRoomNormal_EventScript_DoPikeQueenBattle::
	closemessage
	applymovement LOCALID_PLAYER, BattleFrontier_BattlePikeRoomNormal_Movement_PlayerWalkUp2
	waitmovement 0
	setvar VAR_0x8004, SPECIAL_BATTLE_PIKE_SINGLE
	setvar VAR_0x8005, 0
	special DoSpecialTrainerBattle
	waitstate
	return

BattleFrontier_BattlePikeRoomNormal_Movement_ApproachPlayer:
	walk_down
	walk_down
	step_end

BattleFrontier_BattlePikeRoomNormal_Movement_NPCExit:
	walk_up
	walk_up
	walk_up
	set_invisible
	walk_up
	step_end

BattleFrontier_BattlePikeRoomNormal_Movement_HealNPCExit:
	walk_up
	set_invisible
	walk_up
	step_end

BattleFrontier_BattlePikeRoomNormal_Movement_NPCApproachMon:
	walk_down
	step_end

BattleFrontier_BattlePikeRoomNormal_Movement_StatusNPCApproachPlayer:
	walk_down
	face_left
	delay_16
	delay_16
	face_down
	step_end

BattleFrontier_BattlePikeRoomNormal_Movement_MonApproachPlayer:
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_down
	walk_fast_left
	face_down
	step_end

BattleFrontier_BattlePikeRoomNormal_Movement_MonFaceNPC:
	face_up
	step_end

BattleFrontier_BattlePikeRoomNormal_Movement_MonMoveAside:
	walk_left
BattleFrontier_BattlePikeRoomNormal_Movement_MonFaceRight:
	face_right
	step_end

BattleFrontier_BattlePikeRoomNormal_Movement_HealNPCApproachPlayer:
	walk_down
	walk_down
	walk_right
	face_down
	step_end

BattleFrontier_BattlePikeRoomNormal_Movement_PlayerFaceTrainer1:
	face_left
	step_end

BattleFrontier_BattlePikeRoomNormal_Movement_PlayerFaceTrainer2:
	face_right
	step_end

BattleFrontier_BattlePikeRoomNormal_Movement_PlayerFaceUp:
	face_up
	step_end

BattleFrontier_BattlePikeRoomNormal_Movement_Trainer1WalkRight:
	walk_right
	step_end

BattleFrontier_BattlePikeRoomNormal_Movement_Trainer2WalkLeft:
	walk_left
	step_end

BattleFrontier_BattlePikeRoomNormal_Movement_DoubleTrainersWalkDown:
	walk_down
	walk_down
	step_end

BattleFrontier_BattlePikeRoomNormal_Movement_Trainer1FacePlayer:
	face_right
	step_end

BattleFrontier_BattlePikeRoomNormal_Movement_Trainer2FacePlayer:
	face_left
	step_end

BattleFrontier_BattlePikeRoomNormal_Movement_Trainer1Exit:
	walk_up
	walk_up
	walk_up
	walk_right
	walk_up
	set_invisible
	walk_up
	step_end

BattleFrontier_BattlePikeRoomNormal_Movement_Trainer2Exit:
	walk_up
	walk_up
	walk_up
	walk_left
	walk_up
	set_invisible
	walk_up
	step_end

@ For approaching Lucy and exiting room after defeating Lucy
BattleFrontier_BattlePikeRoomNormal_Movement_PlayerWalkUp2:
	walk_up
	walk_up
	step_end

BattleFrontier_BattlePikeRoomNormal_Movement_PreQueenHealNPCApproachPlayer:
	walk_down
	walk_down
	step_end

BattleFrontier_BattlePikeRoomNormal_Movement_HealNPCExitForLucy:
	walk_up
	walk_up
	walk_up
	set_invisible
	step_end

BattleFrontier_BattlePikeRoomNormal_Movement_LucyEnter:
	set_visible
	walk_down
	step_end

BattleFrontier_BattlePikeRoomNormal_Movement_LucyMoveAside:
	walk_left
	face_right
	step_end

BattleFrontier_BattlePikeRoomNormal_EventScript_NPC::
	pike_getroomtype
	switch VAR_RESULT
	case PIKE_ROOM_NPC, BattleFrontier_BattlePikeRoomNormal_EventScript_NormalNPC
	case PIKE_ROOM_STATUS, BattleFrontier_BattlePikeRoomNormal_EventScript_StatusNPC
	case PIKE_ROOM_HEAL_PART, BattleFrontier_BattlePikeRoomNormal_EventScript_HealNPC
BattleFrontier_BattlePikeRoomNormal_EventScript_NormalNPC::
	lock
	faceplayer
	pike_getnpcmsg
	msgbox gStringVar4, MSGBOX_DEFAULT
	waitmessage
	closemessage
	release
	end

BattleFrontier_BattlePikeRoomNormal_EventScript_StatusNPC::
	lock
	faceplayer
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_ApologizeHopeMonsAreFine, MSGBOX_DEFAULT
	closemessage
	release
	end

BattleFrontier_BattlePikeRoomNormal_EventScript_HealNPC::
	pike_healonetwomons
	call_if_eq VAR_RESULT, 2, BattleFrontier_BattlePikeRoomNormal_EventScript_WillRestoreTwoMons
	call_if_eq VAR_RESULT, 1, BattleFrontier_BattlePikeRoomNormal_EventScript_WillRestoreOneMon
	playfanfare MUS_HEAL
	waitfanfare
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_BestOfLuckFarewell, MSGBOX_DEFAULT
	closemessage
	release
	applymovement LOCALID_PIKE_ROOM_NPC_1, BattleFrontier_BattlePikeRoomNormal_Movement_HealNPCExit
	waitmovement 0
	end

BattleFrontier_BattlePikeRoomNormal_EventScript_WillRestoreOneMon::
	lock
	faceplayer
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_WillRestoreOneMon, MSGBOX_DEFAULT
	closemessage
	return

BattleFrontier_BattlePikeRoomNormal_EventScript_WillRestoreTwoMons::
	lock
	faceplayer
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_WillRestoreTwoMons, MSGBOX_DEFAULT
	closemessage
	return

@ Dusclops or Kirlia
BattleFrontier_BattlePikeRoomNormal_EventScript_StatusMon::
	lock
	faceplayer
	msgbox BattleFrontier_BattlePikeRoomNormal_Text_Silence, MSGBOX_DEFAULT
	closemessage
	release
	applymovement LOCALID_PIKE_ROOM_NPC_2, BattleFrontier_BattlePikeRoomNormal_Movement_MonFaceRight
	waitmovement 0
	end

BattleFrontier_BattlePikeRoomNormal_EventScript_SetCurtainTilesMostlyClosed::
	setmetatile 4, 1, METATILE_BattlePike_Curtain_Stage1_Tile0, TRUE
	setmetatile 3, 2, METATILE_BattlePike_Curtain_Stage1_Tile1, TRUE
	setmetatile 4, 2, METATILE_BattlePike_Curtain_Stage1_Tile2, TRUE
	setmetatile 5, 2, METATILE_BattlePike_Curtain_Stage1_Tile3, TRUE
	setmetatile 3, 3, METATILE_BattlePike_Curtain_Stage1_Tile4, TRUE
	setmetatile 4, 3, METATILE_BattlePike_Curtain_Stage1_Tile5, FALSE
	setmetatile 5, 3, METATILE_BattlePike_Curtain_Stage1_Tile6, TRUE
	special DrawWholeMapView
	return

BattleFrontier_BattlePikeRoomNormal_EventScript_SetCurtainTilesLittleClosed::
	setmetatile 4, 1, METATILE_BattlePike_Curtain_Stage2_Tile0, TRUE
	setmetatile 3, 2, METATILE_BattlePike_Curtain_Stage2_Tile1, TRUE
	setmetatile 4, 2, METATILE_BattlePike_Curtain_Stage2_Tile2, TRUE
	setmetatile 5, 2, METATILE_BattlePike_Curtain_Stage2_Tile3, TRUE
	setmetatile 3, 3, METATILE_BattlePike_Curtain_Stage2_Tile4, TRUE
	setmetatile 4, 3, METATILE_BattlePike_Curtain_Stage2_Tile5, FALSE
	setmetatile 5, 3, METATILE_BattlePike_Curtain_Stage2_Tile6, TRUE
	special DrawWholeMapView
	return

BattleFrontier_BattlePikeRoomNormal_EventScript_SetCurtainTilesOpen::
	setmetatile 4, 1, METATILE_BattlePike_Curtain_Stage3_Tile0, TRUE
	setmetatile 3, 2, METATILE_BattlePike_Curtain_Stage3_Tile1, TRUE
	setmetatile 4, 2, METATILE_BattlePike_Curtain_Stage3_Tile2, TRUE
	setmetatile 5, 2, METATILE_BattlePike_Curtain_Stage3_Tile3, TRUE
	setmetatile 3, 3, METATILE_BattlePike_Curtain_Stage3_Tile4, TRUE
	setmetatile 4, 3, METATILE_BattlePike_Curtain_Stage3_Tile5, FALSE
	setmetatile 5, 3, METATILE_BattlePike_Curtain_Stage3_Tile6, TRUE
	special DrawWholeMapView
	return

BattleFrontier_BattlePikeRoomNormal_EventScript_SetCurtainTilesClosed::
	setmetatile 4, 1, METATILE_BattlePike_Curtain_Stage0_Tile0, TRUE
	setmetatile 3, 2, METATILE_BattlePike_Curtain_Stage0_Tile1, TRUE
	setmetatile 4, 2, METATILE_BattlePike_Curtain_Stage0_Tile2, TRUE
	setmetatile 5, 2, METATILE_BattlePike_Curtain_Stage0_Tile3, TRUE
	setmetatile 3, 3, METATILE_BattlePike_Curtain_Stage0_Tile4, TRUE
	setmetatile 4, 3, METATILE_BattlePike_Curtain_Stage0_Tile5, FALSE
	setmetatile 5, 3, METATILE_BattlePike_Curtain_Stage0_Tile6, TRUE
	special DrawWholeMapView
	return

BattleFrontier_BattlePikeRoomNormal_Movement_CameraPanUp:
	walk_up
	walk_up
	step_end

@ Unused
BattleFrontier_BattlePikeRoomNormal_Movement_CameraPanDown:
	walk_down
	walk_down
	step_end

BattleFrontier_BattlePikeRoomNormal_Text_WillRestoreToFullHealth:
    .string "欢迎……\n您的运气值得赞扬……\p我来帮您的宝可梦回复体力……$"

BattleFrontier_BattlePikeRoomNormal_Text_EnjoyRestOfChallenge:
    .string "愿您享受接下来的\n选择式对战的挑战……$"

BattleFrontier_BattlePikeRoomNormal_Text_WillRestoreOneMon:
    .string "哦，您是个幸运的人。\n我现在心情还不错。\p我会帮您的1只宝可梦\n回复体力。$"

BattleFrontier_BattlePikeRoomNormal_Text_BestOfLuckFarewell:
    .string "祝您好运。\n再见。$"

@ Seems there was a planned room type where the player could choose to battle and would be healed if they won
@ Possibly replaced/superseded by the hard battle room, which is the same but the battle isnt optional
@ Unused
BattleFrontier_BattlePikeRoomNormal_Text_CareForBattleWillRestoreMons:
    .string "不好意思……\p要不要来场对战？\n如果你赢了就帮你治疗宝可梦。$"

@ Unused
BattleFrontier_BattlePikeRoomNormal_Text_NowShallWe:
    .string "好……\n现在，可以吗？$"

@ Unused
BattleFrontier_BattlePikeRoomNormal_Text_HowUnsportingOfYou:
    .string "我知道了……\n你好卑鄙……$"

@ Unused
BattleFrontier_BattlePikeRoomNormal_Text_WillRestoreMonsAsPromised:
    .string "太漂亮了……\p就像承诺好的，\n我来让你的宝可梦恢复健康。$"

@ Unused
BattleFrontier_BattlePikeRoomNormal_Text_BestOfLuckFarewell2:
    .string "祝你好运。\n再会。$"

BattleFrontier_BattlePikeRoomNormal_Text_WatchOut:
    .string "哦，天哪！\n小心！$"

BattleFrontier_BattlePikeRoomNormal_Text_KirliaStop:
    .string "奇鲁莉安！\n不得无礼！$"

BattleFrontier_BattlePikeRoomNormal_Text_DusclopsStop:
    .string "彷徨夜灵！\n快停下来！$"

BattleFrontier_BattlePikeRoomNormal_Text_KirliaUsedToxic:
    .string "奇鲁莉安使用了剧毒！$"

BattleFrontier_BattlePikeRoomNormal_Text_KirliaUsedHypnosis:
    .string "奇鲁莉安使用了催眠术！$"

BattleFrontier_BattlePikeRoomNormal_Text_KirliaUsedThunderWave:
    .string "奇鲁莉安使用了电击波！$"

BattleFrontier_BattlePikeRoomNormal_Text_KirliaUsedWillOWisp:
    .string "奇鲁莉安使用了磷火！$"

BattleFrontier_BattlePikeRoomNormal_Text_DusclopsUsedWillOWisp:
    .string "彷徨夜灵使用了磷火！$"

BattleFrontier_BattlePikeRoomNormal_Text_DusclopsUsedIceBeam:
    .string "彷徨夜灵使用了冰冻光束！$"

BattleFrontier_BattlePikeRoomNormal_Text_ThatsEnough:
    .string "适可而止吧！$"

BattleFrontier_BattlePikeRoomNormal_Text_ApologizeForKirlia:
    .string "我必须向您道歉……\n我的奇鲁莉安性格胆小……$"

BattleFrontier_BattlePikeRoomNormal_Text_ApologizeForDusclops:
    .string "我必须向您道歉……\n我的彷徨夜灵性格胆小……$"

BattleFrontier_BattlePikeRoomNormal_Text_AttacksWhenStartled:
    .string "一旦受到了惊吓就会\n无视警告胡乱攻击……\p您和您的宝可梦还好吗？$"

BattleFrontier_BattlePikeRoomNormal_Text_ApologizeHopeMonsAreFine:
    .string "我为所发生的一切道歉……\n我希望您的宝可梦没事。$"

BattleFrontier_BattlePikeRoomNormal_Text_Silence:
    .string "…… …… ……\n…… …… ……$"

BattleFrontier_BattlePikeRoomNormal_Text_BattleSomewhatToughTrainer:
    .string "欢迎……\p在此您将会迎战一名\n颇具实力的训练家……$"

BattleFrontier_BattlePikeRoomNormal_Text_RestoreToFullHealth:
    .string "精彩绝伦……\p为了表彰您的胜利，\n我将为您的宝可梦回复体力…………$"

BattleFrontier_BattlePikeRoomNormal_Text_EnjoyRestOfChallenge2:
    .string "愿您享受接下来的\n选择式对战的挑战……$"

BattleFrontier_BattlePikeRoomNormal_Text_ImThePikeQueen:
    .string "我叫小蓟……\n我就是这里的法则……\l因为我就是管道皇后……\p你已经知道了吧，想要前进，\n你必须击败我……\p……我可不是个喜欢闲聊的人。\n快点，来吧……$"

BattleFrontier_BattlePikeRoomNormal_Text_HopeYouDidntUseUpLuck:
    .string "你的运气……\n我希望你没有在这里把它用尽……$"

BattleFrontier_BattlePikeRoomNormal_Text_LucyShowMeFrontierPass:
    .string "小蓟：…… …… ……\n让我看看你的开拓通行证……$"

BattleFrontier_BattlePikeRoomNormal_Text_ReceivedLuckSymbol:
    .string "运气象征被刻在了\n开拓通行证上！$"

BattleFrontier_BattlePikeRoomNormal_Text_AllThereIsDisappear:
    .string "……仅此而已……\n快消失吧……$"

BattleFrontier_BattlePikeRoomNormal_Text_LucyYouAgain:
    .string "小蓟：……你又一次……\p…… …… ……\p……我脚踏花朵，\n历经暴雨才抵达了我现在的位置……\p我对我再次输给同样的对手\n可没什么特殊兴致……\p…… …… ……\n好……我来吧……$"

BattleFrontier_BattlePikeRoomNormal_Text_NowComeOn:
    .string "那么！\n来吧！$"

BattleFrontier_BattlePikeRoomNormal_Text_LucyFrontierPass:
    .string "小蓟：…… …… ……\p……开拓通行证……$"

BattleFrontier_BattlePikeRoomNormal_Text_LuckSymbolTookGoldenShine:
    .string "运气象征闪耀着\n金色的光芒！$"

BattleFrontier_BattlePikeRoomNormal_Text_IWontForget:
    .string "……你，我不会忘记的……\n……永远……$"

BattleFrontier_BattlePikeRoomNormal_Text_ChoseRoomNoHeal:
    .string "欢迎您……\p咯咯……\n看来您运气不佳……\p如果您没有选择这个房间，\n您的宝可梦本可以得到回复……$"

BattleFrontier_BattlePikeRoomNormal_Text_ChoseRoomHealOne:
    .string "欢迎您……\p既然您选择了这个房间，\n我会帮您的1只宝可梦回复体力……$"

BattleFrontier_BattlePikeRoomNormal_Text_ChoseRoomHealTwo:
    .string "欢迎您……\p既然您选择了这个房间，\n我会帮您的2只宝可梦回复体力……$"

@ Unused
BattleFrontier_BattlePikeRoomNormal_Text_WillRestoreAllMons:
    .string "欢迎您……\p呵呵……\n您应该感谢您的幸运星……\p因为您抽中了这间房间\n您的宝可梦将会接收治疗……$"

BattleFrontier_BattlePikeRoomNormal_Text_ShallFetchOurMaster:
    .string "我这就去请我们的主人……$"

BattleFrontier_BattlePikeRoomNormal_Text_WillRestoreTwoMons:
    .string "哦，您是一个幸运的人！\n我现在心情不错。\p我会帮您的2只宝可梦\n回复体力。$"

