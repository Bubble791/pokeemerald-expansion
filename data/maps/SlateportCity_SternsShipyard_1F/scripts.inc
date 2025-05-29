.set LOCALID_DOCK, 1

SlateportCity_SternsShipyard_1F_MapScripts::
	.byte 0

SlateportCity_SternsShipyard_1F_EventScript_Dock::
	lockall
	goto_if_set FLAG_SYS_GAME_CLEAR, SlateportCity_SternsShipyard_1F_EventScript_FerryReady
	goto_if_set FLAG_BADGE07_GET, SlateportCity_SternsShipyard_1F_EventScript_BrineyJoined
	goto_if_set FLAG_DELIVERED_DEVON_GOODS, SlateportCity_SternsShipyard_1F_EventScript_NeedVeteran
	goto_if_set FLAG_DOCK_REJECTED_DEVON_GOODS, SlateportCity_SternsShipyard_1F_EventScript_GoFindStern
	msgbox SlateportCity_SternsShipyard_1F_Text_CantMakeHeadsOrTails, MSGBOX_DEFAULT
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_MeetDockDeliverToStern, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DOCK, Common_Movement_FaceOriginalDirection
	waitmovement 0
	setflag FLAG_DOCK_REJECTED_DEVON_GOODS
	setflag FLAG_HIDE_SLATEPORT_CITY_TEAM_AQUA
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_FerryReady::
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_FerryIsReady, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_BrineyJoined::
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_BrineyJoinedUs, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_GoFindStern::
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_CouldYouFindStern, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DOCK, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_NeedVeteran::
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_CouldUseAdviceFromVeteran, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_Scientist1::
	msgbox SlateportCity_SternsShipyard_1F_Text_SeaIsLikeLivingThing, MSGBOX_NPC
	end

SlateportCity_SternsShipyard_1F_EventScript_Scientist2::
	msgbox SlateportCity_SternsShipyard_1F_Text_GetSeasickEasily, MSGBOX_NPC
	end

SlateportCity_SternsShipyard_1F_EventScript_Briney::
	msgbox SlateportCity_SternsShipyard_1F_Text_DecidedToHelpDock, MSGBOX_NPC
	end

SlateportCity_SternsShipyard_1F_Text_CantMakeHeadsOrTails:
    .string "唔……如果这个放这里，\n那个放那里……\p那么这个东西放哪里？\n那个装置又该怎么办？\p啊啊啊！\n完全理不清头绪！$"

SlateportCity_SternsShipyard_1F_Text_MeetDockDeliverToStern:
    .string "嗯？\n你好，我是津贺。\p楠木馆长雇我来\n设计一艘游船。\p啊！那个……\n那是得文的物品吗？\p但是，呃……\n这样不行……\p楠木馆长出去了，\n他说有些事要处理。\p可以请你帮忙找找楠木馆长，\n把包裹交给他吗？$"

SlateportCity_SternsShipyard_1F_Text_CouldYouFindStern:
    .string "津贺：楠木馆长\n去哪儿了呢？\p可以请你帮忙找找楠木馆长，\n把包裹交给他吗？$"

SlateportCity_SternsShipyard_1F_Text_CouldUseAdviceFromVeteran:
    .string "津贺：造船是一门艺术。\p很多东西并不是\n只靠计算就能够知道的。\p真希望能向哪位熟悉大海的\n资深老水手请教一下……$"

SlateportCity_SternsShipyard_1F_Text_BrineyJoinedUs:
    .string "津贺：嗨！哈奇老人\n也来帮我们的忙了。\p多亏了这位资深老水手，\n游船的组装正在顺利进行中。$"

SlateportCity_SternsShipyard_1F_Text_FerryIsReady:
    .string "津贺：游船终于造好了！\p这崭新的破浪号是\n工业技术的奇迹！\p但我觉得我们\n甚至还能做得更好。\p要知道，技术的进步\n永无止境。$"

SlateportCity_SternsShipyard_1F_Text_DecidedToHelpDock:
    .string "哈奇：啊，{PLAYER}{KUN}！\n好久不见！\p自从我遇见了你，\n我这个老水手又焕发青春啦！\p所以我决定来\n帮津贺造游船。\p毕竟你看，\n游船上可以载很多人呢。\p那个津贺\n也真不简单。\p有他的技术和我的经验，\n我敢肯定我们一定\l能造出一了不起的船！$"

SlateportCity_SternsShipyard_1F_Text_SeaIsLikeLivingThing:
    .string "季节，天气，\n月亮在天空中的位置……\p这些，还有其他很多东西\n都会对大海产生影响。\p是的！\n大海就好像生物一样！$"

SlateportCity_SternsShipyard_1F_Text_GetSeasickEasily:
    .string "我很容易晕船，\n所以我只能到这儿来帮忙。$"

