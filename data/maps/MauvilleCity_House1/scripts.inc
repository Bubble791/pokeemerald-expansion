MauvilleCity_House1_MapScripts::
	.byte 0

MauvilleCity_House1_EventScript_RockSmashDude::
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM_ROCK_SMASH, MauvilleCity_House1_EventScript_ReceivedRockSmash
	msgbox MauvilleCity_House1_Text_ImRockSmashDudeTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_HM_ROCK_SMASH
	setflag FLAG_RECEIVED_HM_ROCK_SMASH
	setflag FLAG_HIDE_ROUTE_111_ROCK_SMASH_TIP_GUY
	msgbox MauvilleCity_House1_Text_ExplainRockSmash, MSGBOX_DEFAULT
	release
	end

MauvilleCity_House1_EventScript_ReceivedRockSmash::
	msgbox MauvilleCity_House1_Text_MonCanFlyOutOfSmashedRock, MSGBOX_DEFAULT
	release
	end

MauvilleCity_House1_Text_ImRockSmashDudeTakeThis:
    .string "呀嗬！\p人们叫我碎岩大叔，\n但我不喜欢被这么叫，\p我应该有个更棒的称呼，\n比如碎岩小哥什么的。\p呀嗬！\p不管怎样，\n你的宝可梦似乎很强。\p我喜欢！\n那，这个秘传学习器给你！$"

MauvilleCity_House1_Text_ExplainRockSmash:
    .string "那个秘传学习器的内容是\n碎岩，\p如果你碰到有巨石\n挡了你的路……\p那么，就用这秘传\n学习器把它们打得粉碎！\p是的！我说，把巨岩打碎！\n呀嗬！$"

MauvilleCity_House1_Text_MonCanFlyOutOfSmashedRock:
    .string "哦，对了，如果你打碎了岩石，\n藏在里面的宝可梦可能会跳出来。\p呀嗬！$"

