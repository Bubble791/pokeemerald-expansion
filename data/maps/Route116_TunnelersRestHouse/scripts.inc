Route116_TunnelersRestHouse_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route116_TunnelersRestHouse_OnTransition
	.byte 0

Route116_TunnelersRestHouse_OnTransition:
	setflag FLAG_LANDMARK_TUNNELERS_REST_HOUSE
	end

Route116_TunnelersRestHouse_EventScript_Tunneler1::
	msgbox Route116_TunnelersRestHouse_Text_WeHadToStopBoring, MSGBOX_NPC
	end

Route116_TunnelersRestHouse_EventScript_Tunneler2::
	msgbox Route116_TunnelersRestHouse_Text_ManDiggingHisWayToVerdanturf, MSGBOX_NPC
	end

Route116_TunnelersRestHouse_EventScript_Tunneler3::
	lock
	faceplayer
	goto_if_set FLAG_RUSTURF_TUNNEL_OPENED, Route116_TunnelersRestHouse_EventScript_TunnelOpened
	msgbox Route116_TunnelersRestHouse_Text_GetToVerdanturfWithoutTunnel, MSGBOX_DEFAULT
	release
	end

Route116_TunnelersRestHouse_EventScript_TunnelOpened::
	msgbox Route116_TunnelersRestHouse_Text_TunnelHasGoneThrough, MSGBOX_DEFAULT
	release
	end

Route116_TunnelersRestHouse_Text_WeHadToStopBoring:
    .string "那边的卡绿隧道啊……\p起初我们动用大型机械组织了\n庞大的施工队开凿岩层。\l但后来不得不停工了。\p因为发现这样会严重影响到\n野生宝可梦的栖息环境。\p所以现在我们只能\n无所事事地闲逛了。$"

Route116_TunnelersRestHouse_Text_ManDiggingHisWayToVerdanturf:
    .string "有个男人正独自向\n绿茵镇方向挖掘。\l他急着想打通隧道。\p说是只要不用机械慢慢挖\n就不会惊扰宝可梦\l也能保护自然环境。\p不知道他现在挖通了没有？$"

Route116_TunnelersRestHouse_Text_GetToVerdanturfWithoutTunnel:
    .string "要绕开隧道去绿茵镇的话，\n得先渡海到武斗镇，\l再坐船到凯那市，\l最后穿过紫堇市才行。$"

Route116_TunnelersRestHouse_Text_TunnelHasGoneThrough:
    .string "听到了吗？到绿茵镇的隧道\n已经打通了！\p看来只要怀抱足够强烈的愿望，\n梦想就真的能实现呢。$"

