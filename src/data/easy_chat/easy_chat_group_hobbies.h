const u8 gEasyChatWord_Idol[] = _("偶像");
const u8 gEasyChatWord_Anime[] = _("动漫");
const u8 gEasyChatWord_Song[] = _("歌曲");
const u8 gEasyChatWord_Movie[] = _("电影");
const u8 gEasyChatWord_Sweets[] = _("糖果");
const u8 gEasyChatWord_Chat[] = _("聊天");
const u8 gEasyChatWord_ChildsPlay[] = _("儿童游戏");
const u8 gEasyChatWord_Toys[] = _("玩具");
const u8 gEasyChatWord_Music[] = _("音乐");
const u8 gEasyChatWord_Cards[] = _("卡片");
const u8 gEasyChatWord_Shopping[] = _("购物");
const u8 gEasyChatWord_Camera[] = _("相机");
const u8 gEasyChatWord_Viewing[] = _("专注");
const u8 gEasyChatWord_Spectator[] = _("观众");
const u8 gEasyChatWord_Gourmet[] = _("美食");
const u8 gEasyChatWord_Game[] = _("游戏");
const u8 gEasyChatWord_Rpg[] = _("角色扮演");
const u8 gEasyChatWord_Collection[] = _("收藏");
const u8 gEasyChatWord_Complete[] = _("完整");
const u8 gEasyChatWord_Magazine[] = _("杂志");
const u8 gEasyChatWord_Walk[] = _("散步");
const u8 gEasyChatWord_Bike[] = _("自行车");
const u8 gEasyChatWord_Hobby[] = _("爱好");
const u8 gEasyChatWord_Sports[] = _("运动");
const u8 gEasyChatWord_Software[] = _("软件");
const u8 gEasyChatWord_Songs[] = _("摇滚");
const u8 gEasyChatWord_Diet[] = _("饮食");
const u8 gEasyChatWord_Treasure[] = _("宝藏");
const u8 gEasyChatWord_Travel[] = _("旅行");
const u8 gEasyChatWord_Dance[] = _("舞蹈");
const u8 gEasyChatWord_Channel[] = _("频道");
const u8 gEasyChatWord_Making[] = _("味道");
const u8 gEasyChatWord_Fishing[] = _("钓鱼");
const u8 gEasyChatWord_Date[] = _("约会");
const u8 gEasyChatWord_Design[] = _("设计");
const u8 gEasyChatWord_Locomotive[] = _("机车");
const u8 gEasyChatWord_PlushDoll[] = _("毛绒娃娃");
const u8 gEasyChatWord_Pc[] = _("电脑");
const u8 gEasyChatWord_Flowers[] = _("鲜花");
const u8 gEasyChatWord_Hero[] = _("英雄");
const u8 gEasyChatWord_Nap[] = _("小睡");
const u8 gEasyChatWord_Heroine[] = _("女主角");
const u8 gEasyChatWord_Fashion[] = _("时尚");
const u8 gEasyChatWord_Adventure[] = _("冒险");
const u8 gEasyChatWord_Board[] = _("板");
const u8 gEasyChatWord_Ball[] = _("球");
const u8 gEasyChatWord_Book[] = _("书");
const u8 gEasyChatWord_Festival[] = _("节日");
const u8 gEasyChatWord_Comics[] = _("漫画");
const u8 gEasyChatWord_Holiday[] = _("假期");
const u8 gEasyChatWord_Plans[] = _("度假");
const u8 gEasyChatWord_Trendy[] = _("潮流");
const u8 gEasyChatWord_Vacation[] = _("昆虫");
const u8 gEasyChatWord_Look[] = _("适合");

const struct EasyChatWordInfo gEasyChatGroup_Hobbies[] = {
    [EC_INDEX(EC_WORD_IDOL)] =
    {
        .text = gEasyChatWord_Idol,
        .alphabeticalOrder = EC_INDEX(EC_WORD_ADVENTURE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_ANIME)] =
    {
        .text = gEasyChatWord_Anime,
        .alphabeticalOrder = EC_INDEX(EC_WORD_ANIME),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_SONG)] =
    {
        .text = gEasyChatWord_Song,
        .alphabeticalOrder = EC_INDEX(EC_WORD_BALL),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_MOVIE)] =
    {
        .text = gEasyChatWord_Movie,
        .alphabeticalOrder = EC_INDEX(EC_WORD_BIKE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_SWEETS)] =
    {
        .text = gEasyChatWord_Sweets,
        .alphabeticalOrder = EC_INDEX(EC_WORD_BOARD),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_CHAT)] =
    {
        .text = gEasyChatWord_Chat,
        .alphabeticalOrder = EC_INDEX(EC_WORD_BOOK),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_CHILD_S_PLAY)] =
    {
        .text = gEasyChatWord_ChildsPlay,
        .alphabeticalOrder = EC_INDEX(EC_WORD_CAMERA),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_TOYS)] =
    {
        .text = gEasyChatWord_Toys,
        .alphabeticalOrder = EC_INDEX(EC_WORD_CARDS),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_MUSIC)] =
    {
        .text = gEasyChatWord_Music,
        .alphabeticalOrder = EC_INDEX(EC_WORD_CHANNEL),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_CARDS)] =
    {
        .text = gEasyChatWord_Cards,
        .alphabeticalOrder = EC_INDEX(EC_WORD_CHAT),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_SHOPPING)] =
    {
        .text = gEasyChatWord_Shopping,
        .alphabeticalOrder = EC_INDEX(EC_WORD_CHILD_S_PLAY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_CAMERA)] =
    {
        .text = gEasyChatWord_Camera,
        .alphabeticalOrder = EC_INDEX(EC_WORD_COLLECTION),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_VIEWING)] =
    {
        .text = gEasyChatWord_Viewing,
        .alphabeticalOrder = EC_INDEX(EC_WORD_COMICS),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_SPECTATOR)] =
    {
        .text = gEasyChatWord_Spectator,
        .alphabeticalOrder = EC_INDEX(EC_WORD_COMPLETE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_GOURMET)] =
    {
        .text = gEasyChatWord_Gourmet,
        .alphabeticalOrder = EC_INDEX(EC_WORD_DANCE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_GAME)] =
    {
        .text = gEasyChatWord_Game,
        .alphabeticalOrder = EC_INDEX(EC_WORD_DATE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_RPG)] =
    {
        .text = gEasyChatWord_Rpg,
        .alphabeticalOrder = EC_INDEX(EC_WORD_DESIGN),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_COLLECTION)] =
    {
        .text = gEasyChatWord_Collection,
        .alphabeticalOrder = EC_INDEX(EC_WORD_DIET),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_COMPLETE)] =
    {
        .text = gEasyChatWord_Complete,
        .alphabeticalOrder = EC_INDEX(EC_WORD_FASHION),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_MAGAZINE)] =
    {
        .text = gEasyChatWord_Magazine,
        .alphabeticalOrder = EC_INDEX(EC_WORD_FESTIVAL),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_WALK)] =
    {
        .text = gEasyChatWord_Walk,
        .alphabeticalOrder = EC_INDEX(EC_WORD_FISHING),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_BIKE)] =
    {
        .text = gEasyChatWord_Bike,
        .alphabeticalOrder = EC_INDEX(EC_WORD_FLOWERS),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_HOBBY)] =
    {
        .text = gEasyChatWord_Hobby,
        .alphabeticalOrder = EC_INDEX(EC_WORD_GAME),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_SPORTS)] =
    {
        .text = gEasyChatWord_Sports,
        .alphabeticalOrder = EC_INDEX(EC_WORD_GOURMET),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_SOFTWARE)] =
    {
        .text = gEasyChatWord_Software,
        .alphabeticalOrder = EC_INDEX(EC_WORD_HERO),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_SONGS)] =
    {
        .text = gEasyChatWord_Songs,
        .alphabeticalOrder = EC_INDEX(EC_WORD_HEROINE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_DIET)] =
    {
        .text = gEasyChatWord_Diet,
        .alphabeticalOrder = EC_INDEX(EC_WORD_HOBBY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_TREASURE)] =
    {
        .text = gEasyChatWord_Treasure,
        .alphabeticalOrder = EC_INDEX(EC_WORD_HOLIDAY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_TRAVEL)] =
    {
        .text = gEasyChatWord_Travel,
        .alphabeticalOrder = EC_INDEX(EC_WORD_IDOL),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_DANCE)] =
    {
        .text = gEasyChatWord_Dance,
        .alphabeticalOrder = EC_INDEX(EC_WORD_LOCOMOTIVE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_CHANNEL)] =
    {
        .text = gEasyChatWord_Channel,
        .alphabeticalOrder = EC_INDEX(EC_WORD_LOOK),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_MAKING)] =
    {
        .text = gEasyChatWord_Making,
        .alphabeticalOrder = EC_INDEX(EC_WORD_MAGAZINE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_FISHING)] =
    {
        .text = gEasyChatWord_Fishing,
        .alphabeticalOrder = EC_INDEX(EC_WORD_MAKING),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_DATE)] =
    {
        .text = gEasyChatWord_Date,
        .alphabeticalOrder = EC_INDEX(EC_WORD_MOVIE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_DESIGN)] =
    {
        .text = gEasyChatWord_Design,
        .alphabeticalOrder = EC_INDEX(EC_WORD_MUSIC),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_LOCOMOTIVE)] =
    {
        .text = gEasyChatWord_Locomotive,
        .alphabeticalOrder = EC_INDEX(EC_WORD_NAP),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_PLUSH_DOLL)] =
    {
        .text = gEasyChatWord_PlushDoll,
        .alphabeticalOrder = EC_INDEX(EC_WORD_PC),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_PC)] =
    {
        .text = gEasyChatWord_Pc,
        .alphabeticalOrder = EC_INDEX(EC_WORD_PLANS),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_FLOWERS)] =
    {
        .text = gEasyChatWord_Flowers,
        .alphabeticalOrder = EC_INDEX(EC_WORD_PLUSH_DOLL),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_HERO)] =
    {
        .text = gEasyChatWord_Hero,
        .alphabeticalOrder = EC_INDEX(EC_WORD_RPG),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_NAP)] =
    {
        .text = gEasyChatWord_Nap,
        .alphabeticalOrder = EC_INDEX(EC_WORD_SHOPPING),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_HEROINE)] =
    {
        .text = gEasyChatWord_Heroine,
        .alphabeticalOrder = EC_INDEX(EC_WORD_SOFTWARE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_FASHION)] =
    {
        .text = gEasyChatWord_Fashion,
        .alphabeticalOrder = EC_INDEX(EC_WORD_SONG),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_ADVENTURE)] =
    {
        .text = gEasyChatWord_Adventure,
        .alphabeticalOrder = EC_INDEX(EC_WORD_SONGS),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_BOARD)] =
    {
        .text = gEasyChatWord_Board,
        .alphabeticalOrder = EC_INDEX(EC_WORD_SPECTATOR),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_BALL)] =
    {
        .text = gEasyChatWord_Ball,
        .alphabeticalOrder = EC_INDEX(EC_WORD_SPORTS),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_BOOK)] =
    {
        .text = gEasyChatWord_Book,
        .alphabeticalOrder = EC_INDEX(EC_WORD_SWEETS),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_FESTIVAL)] =
    {
        .text = gEasyChatWord_Festival,
        .alphabeticalOrder = EC_INDEX(EC_WORD_TOYS),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_COMICS)] =
    {
        .text = gEasyChatWord_Comics,
        .alphabeticalOrder = EC_INDEX(EC_WORD_TRAVEL),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_HOLIDAY)] =
    {
        .text = gEasyChatWord_Holiday,
        .alphabeticalOrder = EC_INDEX(EC_WORD_TREASURE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_PLANS)] =
    {
        .text = gEasyChatWord_Plans,
        .alphabeticalOrder = EC_INDEX(EC_WORD_TRENDY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_TRENDY)] =
    {
        .text = gEasyChatWord_Trendy,
        .alphabeticalOrder = EC_INDEX(EC_WORD_VACATION),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_VACATION)] =
    {
        .text = gEasyChatWord_Vacation,
        .alphabeticalOrder = EC_INDEX(EC_WORD_VIEWING),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_LOOK)] =
    {
        .text = gEasyChatWord_Look,
        .alphabeticalOrder = EC_INDEX(EC_WORD_WALK),
        .enabled = TRUE,
    },
};
