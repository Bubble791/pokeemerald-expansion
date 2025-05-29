const u8 gEasyChatWord_Fall[] = _("秋天");
const u8 gEasyChatWord_Morning[] = _("早晨");
const u8 gEasyChatWord_Tomorrow[] = _("明天");
const u8 gEasyChatWord_Last[] = _("最后");
const u8 gEasyChatWord_Day[] = _("马上");
const u8 gEasyChatWord_Sometime[] = _("有时");
const u8 gEasyChatWord_Always[] = _("总是");
const u8 gEasyChatWord_Current[] = _("时");
const u8 gEasyChatWord_Forever[] = _("永远");
const u8 gEasyChatWord_Days[] = _("天");
const u8 gEasyChatWord_End[] = _("一天");
const u8 gEasyChatWord_Tuesday[] = _("星期二");
const u8 gEasyChatWord_Yesterday[] = _("昨天");
const u8 gEasyChatWord_Today[] = _("今天");
const u8 gEasyChatWord_Friday[] = _("星期五");
const u8 gEasyChatWord_Monday[] = _("星期一");
const u8 gEasyChatWord_Later[] = _("稍后");
const u8 gEasyChatWord_Earlier[] = _("早点");
const u8 gEasyChatWord_Another[] = _("每天");
const u8 gEasyChatWord_Time[] = _("时间");
const u8 gEasyChatWord_Finish[] = _("结束");
const u8 gEasyChatWord_Wednesday[] = _("星期三");
const u8 gEasyChatWord_Soon[] = _("很快");
const u8 gEasyChatWord_Start[] = _("比起");
const u8 gEasyChatWord_Month[] = _("月");
const u8 gEasyChatWord_Stop[] = _("停止");
const u8 gEasyChatWord_Now[] = _("现在");
const u8 gEasyChatWord_Final[] = _("最初");
const u8 gEasyChatWord_Next[] = _("下一个");
const u8 gEasyChatWord_Age[] = _("年龄");
const u8 gEasyChatWord_Saturday[] = _("星期六");
const u8 gEasyChatWord_Summer[] = _("夏天");
const u8 gEasyChatWord_Sunday[] = _("星期日");
const u8 gEasyChatWord_Beginning[] = _("开始");
const u8 gEasyChatWord_Spring[] = _("春天");
const u8 gEasyChatWord_Daytime[] = _("白天");
const u8 gEasyChatWord_Winter[] = _("冬天");
const u8 gEasyChatWord_Daily[] = _("再");
const u8 gEasyChatWord_Olden[] = _("回");
const u8 gEasyChatWord_Almost[] = _("几乎");
const u8 gEasyChatWord_Nearly[] = _("很久");
const u8 gEasyChatWord_Thursday[] = _("星期四");
const u8 gEasyChatWord_Nighttime[] = _("夜间");
const u8 gEasyChatWord_Night[] = _("夜晚");
const u8 gEasyChatWord_Week[] = _("周");

const struct EasyChatWordInfo gEasyChatGroup_Time[] = {
    [EC_INDEX(EC_WORD_FALL)] =
    {
        .text = gEasyChatWord_Fall,
        .alphabeticalOrder = EC_INDEX(EC_WORD_AGE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_MORNING)] =
    {
        .text = gEasyChatWord_Morning,
        .alphabeticalOrder = EC_INDEX(EC_WORD_ALMOST),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_TOMORROW)] =
    {
        .text = gEasyChatWord_Tomorrow,
        .alphabeticalOrder = EC_INDEX(EC_WORD_ALWAYS),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_LAST)] =
    {
        .text = gEasyChatWord_Last,
        .alphabeticalOrder = EC_INDEX(EC_WORD_ANOTHER),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_DAY)] =
    {
        .text = gEasyChatWord_Day,
        .alphabeticalOrder = EC_INDEX(EC_WORD_BEGINNING),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_SOMETIME)] =
    {
        .text = gEasyChatWord_Sometime,
        .alphabeticalOrder = EC_INDEX(EC_WORD_CURRENT),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_ALWAYS)] =
    {
        .text = gEasyChatWord_Always,
        .alphabeticalOrder = EC_INDEX(EC_WORD_DAILY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_CURRENT)] =
    {
        .text = gEasyChatWord_Current,
        .alphabeticalOrder = EC_INDEX(EC_WORD_DAY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_FOREVER)] =
    {
        .text = gEasyChatWord_Forever,
        .alphabeticalOrder = EC_INDEX(EC_WORD_DAYS),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_DAYS)] =
    {
        .text = gEasyChatWord_Days,
        .alphabeticalOrder = EC_INDEX(EC_WORD_DAYTIME),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_END)] =
    {
        .text = gEasyChatWord_End,
        .alphabeticalOrder = EC_INDEX(EC_WORD_EARLIER),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_TUESDAY)] =
    {
        .text = gEasyChatWord_Tuesday,
        .alphabeticalOrder = EC_INDEX(EC_WORD_END),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_YESTERDAY)] =
    {
        .text = gEasyChatWord_Yesterday,
        .alphabeticalOrder = EC_INDEX(EC_WORD_FALL),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_TODAY)] =
    {
        .text = gEasyChatWord_Today,
        .alphabeticalOrder = EC_INDEX(EC_WORD_FINAL),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_FRIDAY)] =
    {
        .text = gEasyChatWord_Friday,
        .alphabeticalOrder = EC_INDEX(EC_WORD_FINISH),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_MONDAY)] =
    {
        .text = gEasyChatWord_Monday,
        .alphabeticalOrder = EC_INDEX(EC_WORD_FOREVER),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_LATER)] =
    {
        .text = gEasyChatWord_Later,
        .alphabeticalOrder = EC_INDEX(EC_WORD_FRIDAY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_EARLIER)] =
    {
        .text = gEasyChatWord_Earlier,
        .alphabeticalOrder = EC_INDEX(EC_WORD_LAST),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_ANOTHER)] =
    {
        .text = gEasyChatWord_Another,
        .alphabeticalOrder = EC_INDEX(EC_WORD_LATER),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_TIME)] =
    {
        .text = gEasyChatWord_Time,
        .alphabeticalOrder = EC_INDEX(EC_WORD_MONDAY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_FINISH)] =
    {
        .text = gEasyChatWord_Finish,
        .alphabeticalOrder = EC_INDEX(EC_WORD_MONTH),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_WEDNESDAY)] =
    {
        .text = gEasyChatWord_Wednesday,
        .alphabeticalOrder = EC_INDEX(EC_WORD_MORNING),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_SOON)] =
    {
        .text = gEasyChatWord_Soon,
        .alphabeticalOrder = EC_INDEX(EC_WORD_NEARLY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_START)] =
    {
        .text = gEasyChatWord_Start,
        .alphabeticalOrder = EC_INDEX(EC_WORD_NEXT),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_MONTH)] =
    {
        .text = gEasyChatWord_Month,
        .alphabeticalOrder = EC_INDEX(EC_WORD_NIGHT),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_STOP)] =
    {
        .text = gEasyChatWord_Stop,
        .alphabeticalOrder = EC_INDEX(EC_WORD_NIGHTTIME),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_NOW)] =
    {
        .text = gEasyChatWord_Now,
        .alphabeticalOrder = EC_INDEX(EC_WORD_NOW),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_FINAL)] =
    {
        .text = gEasyChatWord_Final,
        .alphabeticalOrder = EC_INDEX(EC_WORD_OLDEN),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_NEXT)] =
    {
        .text = gEasyChatWord_Next,
        .alphabeticalOrder = EC_INDEX(EC_WORD_SATURDAY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_AGE)] =
    {
        .text = gEasyChatWord_Age,
        .alphabeticalOrder = EC_INDEX(EC_WORD_SOMETIME),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_SATURDAY)] =
    {
        .text = gEasyChatWord_Saturday,
        .alphabeticalOrder = EC_INDEX(EC_WORD_SOON),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_SUMMER)] =
    {
        .text = gEasyChatWord_Summer,
        .alphabeticalOrder = EC_INDEX(EC_WORD_SPRING),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_SUNDAY)] =
    {
        .text = gEasyChatWord_Sunday,
        .alphabeticalOrder = EC_INDEX(EC_WORD_START),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_BEGINNING)] =
    {
        .text = gEasyChatWord_Beginning,
        .alphabeticalOrder = EC_INDEX(EC_WORD_STOP),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_SPRING)] =
    {
        .text = gEasyChatWord_Spring,
        .alphabeticalOrder = EC_INDEX(EC_WORD_SUMMER),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_DAYTIME)] =
    {
        .text = gEasyChatWord_Daytime,
        .alphabeticalOrder = EC_INDEX(EC_WORD_SUNDAY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_WINTER)] =
    {
        .text = gEasyChatWord_Winter,
        .alphabeticalOrder = EC_INDEX(EC_WORD_THURSDAY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_DAILY)] =
    {
        .text = gEasyChatWord_Daily,
        .alphabeticalOrder = EC_INDEX(EC_WORD_TIME),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_OLDEN)] =
    {
        .text = gEasyChatWord_Olden,
        .alphabeticalOrder = EC_INDEX(EC_WORD_TODAY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_ALMOST)] =
    {
        .text = gEasyChatWord_Almost,
        .alphabeticalOrder = EC_INDEX(EC_WORD_TOMORROW),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_NEARLY)] =
    {
        .text = gEasyChatWord_Nearly,
        .alphabeticalOrder = EC_INDEX(EC_WORD_TUESDAY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_THURSDAY)] =
    {
        .text = gEasyChatWord_Thursday,
        .alphabeticalOrder = EC_INDEX(EC_WORD_WEDNESDAY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_NIGHTTIME)] =
    {
        .text = gEasyChatWord_Nighttime,
        .alphabeticalOrder = EC_INDEX(EC_WORD_WEEK),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_NIGHT)] =
    {
        .text = gEasyChatWord_Night,
        .alphabeticalOrder = EC_INDEX(EC_WORD_WINTER),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_WEEK)] =
    {
        .text = gEasyChatWord_Week,
        .alphabeticalOrder = EC_INDEX(EC_WORD_YESTERDAY),
        .enabled = TRUE,
    },
};
