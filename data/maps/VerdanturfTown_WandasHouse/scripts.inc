VerdanturfTown_WandasHouse_MapScripts::
	.byte 0

VerdanturfTown_WandasHouse_EventScript_Wally::
	lock
	faceplayer
	goto_if_set FLAG_WALLY_SPEECH, VerdanturfTown_WandasHouse_EventScript_WallyShortSpeech
	msgbox VerdanturfTown_WandasHouse_Text_StrongerSpeech, MSGBOX_DEFAULT
	setflag FLAG_WALLY_SPEECH
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallyShortSpeech::
	msgbox VerdanturfTown_WandasHouse_Text_StrongerSpeechShort, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysUncle::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_WALLY_VICTORY_ROAD, VerdanturfTown_WandasHouse_EventScript_WallysUncleEverGrande
	goto_if_set FLAG_DEFEATED_LAVARIDGE_GYM, VerdanturfTown_WandasHouse_EventScript_WallysUncleSlippedOff
	msgbox VerdanturfTown_WandasHouse_Text_WallysNextDoor, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysUncleSlippedOff::
	msgbox VerdanturfTown_WandasHouse_Text_WallySlippedOff, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysUncleEverGrande::
	msgbox VerdanturfTown_WandasHouse_Text_WallyGoneThatFar, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WandasBoyfriend::
	msgbox VerdanturfTown_WandasHouse_Text_CanSeeGirlfriendEveryDay, MSGBOX_NPC
	end

VerdanturfTown_WandasHouse_EventScript_Wanda::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_LAVARIDGE_GYM, VerdanturfTown_WandasHouse_EventScript_WandaDontWorry
	goto_if_set FLAG_DEFEATED_WALLY_MAUVILLE, VerdanturfTown_WandasHouse_EventScript_MeetWanda
	msgbox VerdanturfTown_WandasHouse_Text_DontWorryAboutWally, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_MeetWanda::
	msgbox VerdanturfTown_WandasHouse_Text_MeetWanda, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WandaDontWorry::
	msgbox VerdanturfTown_WandasHouse_Text_DontWorryAboutWally, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysAunt::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_WALLY_VICTORY_ROAD, VerdanturfTown_WandasHouse_EventScript_WallysAuntEverGrande
	goto_if_set FLAG_DEFEATED_LAVARIDGE_GYM, VerdanturfTown_WandasHouse_EventScript_WallysAuntAnythingHappened
	goto_if_set FLAG_RUSTURF_TUNNEL_OPENED, VerdanturfTown_WandasHouse_EventScript_WallysAuntTunnelOpen
	msgbox VerdanturfTown_WandasHouse_Text_DaughtersBoyfriendDriven, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysAuntTunnelOpen::
	msgbox VerdanturfTown_WandasHouse_Text_DaughtersBoyfriendWasDigging, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysAuntAnythingHappened::
	msgbox VerdanturfTown_WandasHouse_Text_IfAnythingHappenedToWally, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysAuntEverGrande::
	msgbox VerdanturfTown_WandasHouse_Text_WallyWasInEverGrande, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_Text_StrongerSpeech:
    .string "满充：虽然我输给了你，{PLAYER}，\n但我不再消沉了，\p因为我有了新的目标——\n和拉鲁拉丝一起挑战宝可梦道馆，\l成为一名厉害的训练家！\p请看着我，{PLAYER}。\n总有一天我会比你更强！\p到那时，\n我会再次向你挑战！$"

VerdanturfTown_WandasHouse_Text_StrongerSpeechShort:
    .string "满充：请看着我，{PLAYER}。\n总有一天我会比你更强！\p到那时，\n我会再次向你挑战！$"

VerdanturfTown_WandasHouse_Text_WallysNextDoor:
    .string "叔叔：哦，{PLAYER}{KUN}！\n满充就在隔壁。\p但是，孩子，\n有些事我想告诉你，\p这里的自然环境\n对满充的身体有好处，\p但让他打起精神来的\n并不只是环境，\l是宝可梦给了那孩子希望。$"

VerdanturfTown_WandasHouse_Text_WallySlippedOff:
    .string "满充不在……\n他一个人溜了出去……$"

VerdanturfTown_WandasHouse_Text_WallyGoneThatFar:
    .string "叔叔：真的吗？\n满充自己一个人\l去了那么远的地方……\p我想我该称赞他一下——\n不愧是我弟弟的儿子。$"

VerdanturfTown_WandasHouse_Text_MeetWanda:
    .string "满盈：你是？\n哦，我知道了！\p你就是满充常说的\n{PLAYER}。\p我是满充的堂姐，\n很高兴认识你！\p自从满充来这儿以后，\n他变得活泼开朗多了。$"

VerdanturfTown_WandasHouse_Text_DontWorryAboutWally:
    .string "满盈：别担心满充，\n他没事。\p我了解我的堂弟，\n而且还有宝可梦在他的身边。$"

VerdanturfTown_WandasHouse_Text_CanSeeGirlfriendEveryDay:
    .string "多亏了你，我可以天天\n跟我的女朋友相聚了。\l开心吗？当然！那还用说！$"

VerdanturfTown_WandasHouse_Text_DaughtersBoyfriendDriven:
    .string "我女儿的男友是个\n充满热情和决心的人，\p他为了见我女儿\n每天都不停地挖隧道。\p女儿有些担心，\n所以经常跑到隧道去。$"

VerdanturfTown_WandasHouse_Text_DaughtersBoyfriendWasDigging:
    .string "太令人吃惊了，女儿的男友\n徒手挖开了隧道！\p难以置信！$"

VerdanturfTown_WandasHouse_Text_IfAnythingHappenedToWally:
    .string "要是满充出了什么事，\n我怎么该和他住在\l橙华市的父母交代……$"

VerdanturfTown_WandasHouse_Text_WallyWasInEverGrande:
    .string "满充去过彩悠市？\p他那住在橙华市的父母\n一定会大吃一惊的！$"

