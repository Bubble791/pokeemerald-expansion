MeteorFalls_StevensCave_MapScripts::
	.byte 0

MeteorFalls_StevensCave_EventScript_Steven::
	lock
	goto_if_set FLAG_DEFEATED_METEOR_FALLS_STEVEN, MeteorFalls_StevensCave_EventScript_Defeated
	waitse
	playse SE_PIN
	applymovement LOCALID_METEOR_FALLS_STEVEN, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_METEOR_FALLS_STEVEN, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_METEOR_FALLS_STEVEN, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MeteorFalls_StevensCave_Text_ShouldKnowHowGoodIAmExpectWorst, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_STEVEN, MeteorFalls_StevensCave_Text_StevenDefeat
	msgbox MeteorFalls_StevensCave_Text_MyPredictionCameTrue, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_METEOR_FALLS_STEVEN
	release
	end

MeteorFalls_StevensCave_EventScript_Defeated::
	applymovement LOCALID_METEOR_FALLS_STEVEN, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MeteorFalls_StevensCave_Text_MyPredictionCameTrue, MSGBOX_DEFAULT
	release
	end

MeteorFalls_StevensCave_Text_ShouldKnowHowGoodIAmExpectWorst:
    .string "大吾：咦，{PLAYER}{KUN}，\n你知道我在这里啊。\p你会不会……认为我只是\n个普通的石头狂人？\p……不。\p我们在绿岭市宇宙中心\n共同战斗过，\p我拥有怎样的实力\n你应该很清楚了吧。\p好吧，{PLAYER}{KUN}，\n如果你想和我对战的话，做好觉悟吧！$"

MeteorFalls_StevensCave_Text_StevenDefeat:
    .string "你……\n没想到你已经变得这么强了……$"

MeteorFalls_StevensCave_Text_MyPredictionCameTrue:
    .string "大吾：说起来……从在武斗镇的石之洞窟\n第一次遇到你，我就有种感觉，\p感觉你最终将会\n成为冠军。\p我的预感通常都\n很准确吧。\p那么……接下来你要去的地方是……\p…… …… ……\n…… …… ……\p呵呵呵，即使是我也不知道呀。$"

