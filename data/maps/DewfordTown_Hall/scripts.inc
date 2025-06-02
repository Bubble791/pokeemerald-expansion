DewfordTown_Hall_MapScripts::
	.byte 0

DewfordTown_Hall_EventScript_Girl::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	special IsTrendyPhraseBoring
	goto_if_eq VAR_RESULT, TRUE, DewfordTown_Hall_EventScript_GirlBoredOfTrend
	msgbox DewfordTown_Hall_Text_CantImagineLifeWithoutTrend, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_EventScript_GirlBoredOfTrend::
	msgbox DewfordTown_Hall_Text_GettingBoredOfTrend, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_EventScript_Woman::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	msgbox DewfordTown_Hall_Text_TeachingMonAboutTrend, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_EventScript_Man::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	special BufferDeepLinkPhrase
	msgbox DewfordTown_Hall_Text_DeepLinkBetweenXAndY, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, DewfordTown_Hall_EventScript_ConfirmTrendLink
	goto_if_eq VAR_RESULT, NO, DewfordTown_Hall_EventScript_RejectTrendLink
	end

DewfordTown_Hall_EventScript_ConfirmTrendLink::
	msgbox DewfordTown_Hall_Text_MyHunchWasRight, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_EventScript_RejectTrendLink::
	msgbox DewfordTown_Hall_Text_NotEasyToKeepUp, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_EventScript_ExpertM::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	msgbox DewfordTown_Hall_Text_TVShowAboutTrend, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DEWFORD_HALL_EXPERT_M, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	release
	end

DewfordTown_Hall_EventScript_Twin::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	msgbox DewfordTown_Hall_Text_IsTrendMorePopularAcrossSea, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DEWFORD_HALL_TWIN, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	release
	end

DewfordTown_Hall_EventScript_LittleBoy::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	msgbox DewfordTown_Hall_Text_CollectTrendMerchandise, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_EventScript_Bookshelf::
	lockall
	call Common_EventScript_BufferTrendyPhrase
	msgbox DewfordTown_Hall_Text_BooksAboutTrend, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_Painting::
	lockall
	call Common_EventScript_BufferTrendyPhrase
	special GetDewfordHallPaintingNameIndex
	switch VAR_RESULT
	case 0, DewfordTown_Hall_EventScript_ScreamTitle
	case 4, DewfordTown_Hall_EventScript_ScreamTitle
	case 1, DewfordTown_Hall_EventScript_SmileTitle
	case 5, DewfordTown_Hall_EventScript_ScreamTitle
	case 2, DewfordTown_Hall_EventScript_LastTitle
	case 6, DewfordTown_Hall_EventScript_LastTitle
	case 3, DewfordTown_Hall_EventScript_BirthTitle
	case 7, DewfordTown_Hall_EventScript_LastTitle
	end

DewfordTown_Hall_EventScript_ScreamTitle::
	msgbox DewfordTown_Hall_Text_TrendsScream, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_SmileTitle::
	msgbox DewfordTown_Hall_Text_TrendsSmile, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_LastTitle::
	msgbox DewfordTown_Hall_Text_LastTrend, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_BirthTitle::
	msgbox DewfordTown_Hall_Text_BirthOfTrend, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_SchoolKidM::
	lockall
	setvar VAR_0x8008, 0
	goto DewfordTown_Hall_EventScript_DoTrendDebate
	end

DewfordTown_Hall_EventScript_PsychicM::
	lockall
	setvar VAR_0x8008, 1
	goto DewfordTown_Hall_EventScript_DoTrendDebate
	end

DewfordTown_Hall_EventScript_DoTrendDebate::
	call Common_EventScript_BufferTrendyPhrase
	special GetDewfordHallPaintingNameIndex
	switch VAR_RESULT
	case 0, DewfordTown_Hall_EventScript_TrendDebate1
	case 1, DewfordTown_Hall_EventScript_TrendDebate1
	case 2, DewfordTown_Hall_EventScript_TrendDebate2
	case 3, DewfordTown_Hall_EventScript_TrendDebate2
	case 4, DewfordTown_Hall_EventScript_TrendDebate3
	case 5, DewfordTown_Hall_EventScript_TrendDebate3
	case 6, DewfordTown_Hall_EventScript_TrendDebate4
	case 7, DewfordTown_Hall_EventScript_TrendDebate5
	end

DewfordTown_Hall_EventScript_TrendDebate1::
	call DewfordTown_Hall_EventScript_DebateReact1
	msgbox DewfordTown_Hall_Text_SawTrendCoolestThing, MSGBOX_DEFAULT
	call DewfordTown_Hall_EventScript_DebateReact2
	msgbox DewfordTown_Hall_Text_AllegedTrendNotAuthentic, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_TrendDebate2::
	call DewfordTown_Hall_EventScript_DebateReact1
	msgbox DewfordTown_Hall_Text_ComposedTrendThemeSong, MSGBOX_DEFAULT
	call DewfordTown_Hall_EventScript_DebateReact2
	msgbox DewfordTown_Hall_Text_WorkOnYourSinging, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_TrendDebate3::
	call DewfordTown_Hall_EventScript_DebateReact1
	msgbox DewfordTown_Hall_Text_OrganizeTrendParty, MSGBOX_DEFAULT
	call DewfordTown_Hall_EventScript_DebateReact2
	msgbox DewfordTown_Hall_Text_BrilliantIndeed, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_TrendDebate4::
	call DewfordTown_Hall_EventScript_DebateReact1
	msgbox DewfordTown_Hall_Text_TrendHasBecomePartOfLife, MSGBOX_DEFAULT
	call DewfordTown_Hall_EventScript_DebateReact2
	msgbox DewfordTown_Hall_Text_TrendWeighsHeavilyOnMind, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_TrendDebate5::
	call DewfordTown_Hall_EventScript_DebateReact1
	msgbox DewfordTown_Hall_Text_IfWeTeamUpWellBeInvincible, MSGBOX_DEFAULT
	call DewfordTown_Hall_EventScript_DebateReact2
	msgbox DewfordTown_Hall_Text_WellBeTrendDuo, MSGBOX_DEFAULT
	releaseall
	end

DewfordTown_Hall_EventScript_DontMovePlayer1::
	return

DewfordTown_Hall_EventScript_DebateReact1::
	applymovement LOCALID_DEWFORD_HALL_PSYCHIC_M, DewfordTown_Hall_Movement_PsychicWalkInPlaceLeft
	waitmovement 0
	goto_if_eq VAR_0x8008, 0, DewfordTown_Hall_EventScript_PlayerReactWest
	goto_if_eq VAR_0x8008, 1, DewfordTown_Hall_EventScript_DontMovePlayer2
	end

DewfordTown_Hall_EventScript_PlayerReactWest::
	goto_if_eq VAR_FACING, DIR_EAST, DewfordTown_Hall_EventScript_DontMovePlayer1
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

DewfordTown_Hall_EventScript_DontMovePlayer2::
	return

DewfordTown_Hall_EventScript_DebateReact2::
	applymovement LOCALID_DEWFORD_HALL_SCHOOL_KID_M, DewfordTown_Hall_Movement_SchoolKidWalkInPlaceRight
	waitmovement 0
	goto_if_eq VAR_0x8008, 0, DewfordTown_Hall_EventScript_PlayerReactNorthSouth
	goto_if_eq VAR_0x8008, 1, DewfordTown_Hall_EventScript_PlayerReactEast
	end

DewfordTown_Hall_EventScript_PlayerReactNorthSouth::
	call_if_eq VAR_FACING, DIR_NORTH, DewfordTown_Hall_EventScript_PlayerWalkInPlaceUp
	call_if_eq VAR_FACING, DIR_SOUTH, DewfordTown_Hall_EventScript_PlayerWalkInPlaceDown
	return

DewfordTown_Hall_EventScript_PlayerWalkInPlaceUp::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	return

DewfordTown_Hall_EventScript_PlayerWalkInPlaceDown::
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	return

DewfordTown_Hall_EventScript_PlayerReactEast::
	goto_if_eq VAR_FACING, DIR_WEST, DewfordTown_Hall_EventScript_DontMovePlayer1
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

DewfordTown_Hall_Movement_PsychicWalkInPlaceLeft:
	walk_in_place_left
	step_end

DewfordTown_Hall_Movement_SchoolKidWalkInPlaceRight:
	walk_in_place_right
	step_end

DewfordTown_Hall_EventScript_SludgeBombMan::
	lock
	faceplayer
	call Common_EventScript_BufferTrendyPhrase
	goto_if_set FLAG_RECEIVED_TM_SLUDGE_BOMB, DewfordTown_Hall_EventScript_ReceivedSludgeBomb
	msgbox DewfordTown_Hall_Text_GiveYouSludgeBomb, MSGBOX_DEFAULT
	giveitem ITEM_TM_SLUDGE_BOMB
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM_SLUDGE_BOMB
	release
	end

DewfordTown_Hall_EventScript_ReceivedSludgeBomb::
	msgbox DewfordTown_Hall_Text_LoveSludgeBombButTrendInToo, MSGBOX_DEFAULT
	release
	end

DewfordTown_Hall_Text_CantImagineLifeWithoutTrend:
    .string "现在流行什么？哎，当然是\n“{STR_VAR_1}”！\p不敢相信生活中没有\n“{STR_VAR_1}”会怎么样！$"

DewfordTown_Hall_Text_GettingBoredOfTrend:
    .string "现在流行什么？哎，当然是\n“{STR_VAR_1}”！\p但我对它已经有些腻了。\p说不定该找点\n新玩意儿了。$"

DewfordTown_Hall_Text_TeachingMonAboutTrend:
    .string "我想把“{STR_VAR_1}”\n的事教给我的宝可梦，\l但好像不太顺利。\p我想这对它来说太困难了。$"

DewfordTown_Hall_Text_DeepLinkBetweenXAndY:
    .string "我正在研究现今十分流行的\n“{STR_VAR_1}”。\p“{STR_VAR_1}”和\n“{STR_VAR_2}”之间\l是不是有很深的联系呢？$"

DewfordTown_Hall_Text_MyHunchWasRight:
    .string "啊！\n我的直觉是对的！\p我离流行达人又近了一步，\n万岁！$"

DewfordTown_Hall_Text_NotEasyToKeepUp:
    .string "什么？！\n真的？！\p对我这样的老人来说，\n跟上潮流可不容易！$"

DewfordTown_Hall_Text_TVShowAboutTrend:
    .string "说到关于\n“{STR_VAR_1}”的事……\l是不是有相关的电视节目？$"

DewfordTown_Hall_Text_IsTrendMorePopularAcrossSea:
    .string "在海的另一侧……\p“{STR_VAR_1}”\n是不是更加流行吗？$"

DewfordTown_Hall_Text_CollectTrendMerchandise:
    .string "我收集正版授权的\n“{STR_VAR_1}”周边。\p我有正版\n“{STR_VAR_1}”玩偶……\p正版“{STR_VAR_1}”\n品牌服装……\p还有正版授权的\n“{STR_VAR_1}”\l图书。\p嘿嘿，都是我的！\n才不给你看呢！$"

DewfordTown_Hall_Text_BooksAboutTrend:
    .string "辨别好的\n“{STR_VAR_1}”&\l坏的“{STR_VAR_1}”……\p“{STR_VAR_1}”和\n宝可梦之间的关系……\p实用的\n“{STR_VAR_1}”……\p书架上塞满了关于\n“{STR_VAR_1}”的书。$"

DewfordTown_Hall_Text_TrendsScream:
    .string "标题是“{STR_VAR_1}的\n尖叫”。$"

DewfordTown_Hall_Text_TrendsSmile:
    .string "标题是“{STR_VAR_1}的\n微笑”。$"

DewfordTown_Hall_Text_LastTrend:
    .string "标题是“最后的\n{STR_VAR_1}”。$"

DewfordTown_Hall_Text_BirthOfTrend:
    .string "标题是“{STR_VAR_1}\n的诞生”。$"

DewfordTown_Hall_Text_SawTrendCoolestThing:
    .string "我看过“{STR_VAR_1}”！\n超酷对吧？\p这绝对是当下\n最火的东西！\p太惊艳了！\n这才是真正的潮流啊！$"

DewfordTown_Hall_Text_AllegedTrendNotAuthentic:
    .string "啊，不不不。\p你说你看到过\n“{STR_VAR_1}”\l——那不可能。\p真正的版本更加……\n怎么说呢，\l更犀利也更柔和！\p总之简直\n不可思议！$"

DewfordTown_Hall_Text_ComposedTrendThemeSong:
    .string "嘿，听好，我为\n“{STR_VAR_1}”作了曲。\p“{STR_VAR_1}”\n现在真的非常流行。\p好了，听着！\n……\p哦！\n{STR_VAR_1}！\p美丽的\n{STR_VAR_1}！$"

DewfordTown_Hall_Text_WorkOnYourSinging:
    .string "……\p我说，伙计，\n你沉迷“{STR_VAR_1}”前\l能不能先学会怎么唱歌？$"

DewfordTown_Hall_Text_OrganizeTrendParty:
    .string "无论如何，\n就像我之前说的，\l我们该在岛上组织个\l“{STR_VAR_1}”派对了。$"

DewfordTown_Hall_Text_BrilliantIndeed:
    .string "啊，绝妙的主意！\p这样就能决出谁才是最擅长\n“{STR_VAR_1}”的人。\l真是绝妙的主意！\p从今天起，我们的生活就围绕\n“{STR_VAR_1}”了！$"

DewfordTown_Hall_Text_TrendHasBecomePartOfLife:
    .string "其实我在想……\p你不觉得\n“{STR_VAR_1}”\l已经从潮流变成我们\l日常生活的一部分了吗？$"

DewfordTown_Hall_Text_TrendWeighsHeavilyOnMind:
    .string "什么？\n有那么夸张？\p不过“{STR_VAR_1}”\n确实让你魂牵梦萦，\l醒着睡着都在想。\p你简直就是\n“{STR_VAR_1}”教授！$"

DewfordTown_Hall_Text_IfWeTeamUpWellBeInvincible:
    .string "只要我们组队，\n在“{STR_VAR_1}”\l领域就所向无敌！$"

DewfordTown_Hall_Text_WellBeTrendDuo:
    .string "说得好，朋友！\p我们就是\n“{STR_VAR_1}”2人组！\p这形象太完美了！\n哈哈哈！$"

DewfordTown_Hall_Text_GiveYouSludgeBomb:
    .string "对我来说，污泥炸弹才是\n最为流行的。\p嗯？你说你不知道\n污泥炸弹？\p这也太可怜了。\n我给你一个吧。$"

DewfordTown_Hall_Text_LoveSludgeBombButTrendInToo:
    .string "我超爱污泥炸弹。\p但现在会\n“{STR_VAR_1}”的\l宝可梦也很流行呢。$"

