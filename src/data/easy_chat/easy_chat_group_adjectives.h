const u8 gEasyChatWord_Wandering[] = _("徘徊");
const u8 gEasyChatWord_Rickety[] = _("过时");
const u8 gEasyChatWord_RockSolid[] = _("坚如磐石");
const u8 gEasyChatWord_Hungry[] = _("饥饿");
const u8 gEasyChatWord_Tight[] = _("紧张");
const u8 gEasyChatWord_Ticklish[] = _("狂野");
const u8 gEasyChatWord_Twirling[] = _("旋转");
const u8 gEasyChatWord_Spiraling[] = _("刻薄");
const u8 gEasyChatWord_Thirsty[] = _("口渴");
const u8 gEasyChatWord_Lolling[] = _("懒洋洋");
const u8 gEasyChatWord_Silky[] = _("柔滑");
const u8 gEasyChatWord_Sadly[] = _("悲伤");
const u8 gEasyChatWord_Hopeless[] = _("绝望");
const u8 gEasyChatWord_Useless[] = _("没用的");
const u8 gEasyChatWord_Drooling[] = _("普通");
const u8 gEasyChatWord_Exciting[] = _("令人兴奋");
const u8 gEasyChatWord_Thick[] = _("厚");
const u8 gEasyChatWord_Smooth[] = _("光滑");
const u8 gEasyChatWord_Slimy[] = _("黏糊糊");
const u8 gEasyChatWord_Thin[] = _("薄");
const u8 gEasyChatWord_Break[] = _("打破");
const u8 gEasyChatWord_Voracious[] = _("贪婪");
const u8 gEasyChatWord_Scatter[] = _("散落");
const u8 gEasyChatWord_Awesome[] = _("棒极了");
const u8 gEasyChatWord_Wimpy[] = _("软弱");
const u8 gEasyChatWord_Wobbly[] = _("摇摇晃晃");
const u8 gEasyChatWord_Shaky[] = _("摇晃");
const u8 gEasyChatWord_Ripped[] = _("撕裂");
const u8 gEasyChatWord_Shredded[] = _("碎裂");
const u8 gEasyChatWord_Increasing[] = _("增加");
const u8 gEasyChatWord_Yet[] = _("然而");
const u8 gEasyChatWord_Destroyed[] = _("被摧毁");
const u8 gEasyChatWord_Fiery[] = _("火热");
const u8 gEasyChatWord_LoveyDovey[] = _("甜蜜");
const u8 gEasyChatWord_Happily[] = _("幸福");
const u8 gEasyChatWord_Anticipation[] = _("期待");

const struct EasyChatWordInfo gEasyChatGroup_Adjectives[] = {
    [EC_INDEX(EC_WORD_WANDERING)] =
    {
        .text = gEasyChatWord_Wandering,
        .alphabeticalOrder = EC_INDEX(EC_WORD_ANTICIPATION),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_RICKETY)] =
    {
        .text = gEasyChatWord_Rickety,
        .alphabeticalOrder = EC_INDEX(EC_WORD_AWESOME),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_ROCK_SOLID)] =
    {
        .text = gEasyChatWord_RockSolid,
        .alphabeticalOrder = EC_INDEX(EC_WORD_BREAK),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_HUNGRY)] =
    {
        .text = gEasyChatWord_Hungry,
        .alphabeticalOrder = EC_INDEX(EC_WORD_DESTROYED),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_TIGHT)] =
    {
        .text = gEasyChatWord_Tight,
        .alphabeticalOrder = EC_INDEX(EC_WORD_DROOLING),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_TICKLISH)] =
    {
        .text = gEasyChatWord_Ticklish,
        .alphabeticalOrder = EC_INDEX(EC_WORD_EXCITING),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_TWIRLING)] =
    {
        .text = gEasyChatWord_Twirling,
        .alphabeticalOrder = EC_INDEX(EC_WORD_FIERY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_SPIRALING)] =
    {
        .text = gEasyChatWord_Spiraling,
        .alphabeticalOrder = EC_INDEX(EC_WORD_HAPPILY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_THIRSTY)] =
    {
        .text = gEasyChatWord_Thirsty,
        .alphabeticalOrder = EC_INDEX(EC_WORD_HOPELESS),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_LOLLING)] =
    {
        .text = gEasyChatWord_Lolling,
        .alphabeticalOrder = EC_INDEX(EC_WORD_HUNGRY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_SILKY)] =
    {
        .text = gEasyChatWord_Silky,
        .alphabeticalOrder = EC_INDEX(EC_WORD_INCREASING),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_SADLY)] =
    {
        .text = gEasyChatWord_Sadly,
        .alphabeticalOrder = EC_INDEX(EC_WORD_LOLLING),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_HOPELESS)] =
    {
        .text = gEasyChatWord_Hopeless,
        .alphabeticalOrder = EC_INDEX(EC_WORD_LOVEY_DOVEY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_USELESS)] =
    {
        .text = gEasyChatWord_Useless,
        .alphabeticalOrder = EC_INDEX(EC_WORD_RICKETY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_DROOLING)] =
    {
        .text = gEasyChatWord_Drooling,
        .alphabeticalOrder = EC_INDEX(EC_WORD_RIPPED),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_EXCITING)] =
    {
        .text = gEasyChatWord_Exciting,
        .alphabeticalOrder = EC_INDEX(EC_WORD_ROCK_SOLID),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_THICK)] =
    {
        .text = gEasyChatWord_Thick,
        .alphabeticalOrder = EC_INDEX(EC_WORD_SADLY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_SMOOTH)] =
    {
        .text = gEasyChatWord_Smooth,
        .alphabeticalOrder = EC_INDEX(EC_WORD_SCATTER),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_SLIMY)] =
    {
        .text = gEasyChatWord_Slimy,
        .alphabeticalOrder = EC_INDEX(EC_WORD_SHAKY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_THIN)] =
    {
        .text = gEasyChatWord_Thin,
        .alphabeticalOrder = EC_INDEX(EC_WORD_SHREDDED),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_BREAK)] =
    {
        .text = gEasyChatWord_Break,
        .alphabeticalOrder = EC_INDEX(EC_WORD_SILKY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_VORACIOUS)] =
    {
        .text = gEasyChatWord_Voracious,
        .alphabeticalOrder = EC_INDEX(EC_WORD_SLIMY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_SCATTER)] =
    {
        .text = gEasyChatWord_Scatter,
        .alphabeticalOrder = EC_INDEX(EC_WORD_SMOOTH),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_AWESOME)] =
    {
        .text = gEasyChatWord_Awesome,
        .alphabeticalOrder = EC_INDEX(EC_WORD_SPIRALING),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_WIMPY)] =
    {
        .text = gEasyChatWord_Wimpy,
        .alphabeticalOrder = EC_INDEX(EC_WORD_THICK),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_WOBBLY)] =
    {
        .text = gEasyChatWord_Wobbly,
        .alphabeticalOrder = EC_INDEX(EC_WORD_THIN),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_SHAKY)] =
    {
        .text = gEasyChatWord_Shaky,
        .alphabeticalOrder = EC_INDEX(EC_WORD_THIRSTY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_RIPPED)] =
    {
        .text = gEasyChatWord_Ripped,
        .alphabeticalOrder = EC_INDEX(EC_WORD_TICKLISH),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_SHREDDED)] =
    {
        .text = gEasyChatWord_Shredded,
        .alphabeticalOrder = EC_INDEX(EC_WORD_TIGHT),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_INCREASING)] =
    {
        .text = gEasyChatWord_Increasing,
        .alphabeticalOrder = EC_INDEX(EC_WORD_TWIRLING),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_YET)] =
    {
        .text = gEasyChatWord_Yet,
        .alphabeticalOrder = EC_INDEX(EC_WORD_USELESS),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_DESTROYED)] =
    {
        .text = gEasyChatWord_Destroyed,
        .alphabeticalOrder = EC_INDEX(EC_WORD_VORACIOUS),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_FIERY)] =
    {
        .text = gEasyChatWord_Fiery,
        .alphabeticalOrder = EC_INDEX(EC_WORD_WANDERING),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_LOVEY_DOVEY)] =
    {
        .text = gEasyChatWord_LoveyDovey,
        .alphabeticalOrder = EC_INDEX(EC_WORD_WIMPY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_HAPPILY)] =
    {
        .text = gEasyChatWord_Happily,
        .alphabeticalOrder = EC_INDEX(EC_WORD_WOBBLY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_ANTICIPATION)] =
    {
        .text = gEasyChatWord_Anticipation,
        .alphabeticalOrder = EC_INDEX(EC_WORD_YET),
        .enabled = TRUE,
    },
};
