const u8 gEasyChatWord_Chores[] = _("家务");
const u8 gEasyChatWord_Home[] = _("家");
const u8 gEasyChatWord_Money[] = _("金钱");
const u8 gEasyChatWord_Allowance[] = _("零用钱");
const u8 gEasyChatWord_Bath[] = _("洗澡");
const u8 gEasyChatWord_Conversation[] = _("对话");
const u8 gEasyChatWord_School[] = _("学校");
const u8 gEasyChatWord_Commemorate[] = _("纪念");
const u8 gEasyChatWord_Habit[] = _("习惯");
const u8 gEasyChatWord_Group[] = _("团体");
const u8 gEasyChatWord_Word[] = _("组词");
const u8 gEasyChatWord_Store[] = _("商店");
const u8 gEasyChatWord_Service[] = _("服务");
const u8 gEasyChatWord_Work[] = _("造型");
const u8 gEasyChatWord_System[] = _("系统");
const u8 gEasyChatWord_Train[] = _("起床");
const u8 gEasyChatWord_Class[] = _("班级");
const u8 gEasyChatWord_Lessons[] = _("课程");
const u8 gEasyChatWord_Information[] = _("信息");
const u8 gEasyChatWord_Living[] = _("生活");
const u8 gEasyChatWord_Teacher[] = _("老师");
const u8 gEasyChatWord_Tournament[] = _("锦标赛");
const u8 gEasyChatWord_Letter[] = _("信件");
const u8 gEasyChatWord_Event[] = _("事件");
const u8 gEasyChatWord_Digital[] = _("数字");
const u8 gEasyChatWord_Test[] = _("测试");
const u8 gEasyChatWord_DeptStore[] = _("百货商店");
const u8 gEasyChatWord_Television[] = _("电视");
const u8 gEasyChatWord_Phone[] = _("电话");
const u8 gEasyChatWord_Item[] = _("物品");
const u8 gEasyChatWord_Name[] = _("名字");
const u8 gEasyChatWord_News[] = _("新闻");
const u8 gEasyChatWord_Popular[] = _("流行");
const u8 gEasyChatWord_Party[] = _("派对");
const u8 gEasyChatWord_Study[] = _("学习");
const u8 gEasyChatWord_Machine[] = _("作业");
const u8 gEasyChatWord_Mail[] = _("邮件");
const u8 gEasyChatWord_Message[] = _("保证");
const u8 gEasyChatWord_Promise[] = _("约定");
const u8 gEasyChatWord_Dream[] = _("梦想");
const u8 gEasyChatWord_Kindergarten[] = _("幼儿园");
const u8 gEasyChatWord_Life[] = _("梦");
const u8 gEasyChatWord_Radio[] = _("电台");
const u8 gEasyChatWord_Rental[] = _("租借");
const u8 gEasyChatWord_World[] = _("世界");

const struct EasyChatWordInfo gEasyChatGroup_Lifestyle[] = {
    [EC_INDEX(EC_WORD_CHORES)] =
    {
        .text = gEasyChatWord_Chores,
        .alphabeticalOrder = EC_INDEX(EC_WORD_ALLOWANCE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_HOME)] =
    {
        .text = gEasyChatWord_Home,
        .alphabeticalOrder = EC_INDEX(EC_WORD_BATH),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_MONEY)] =
    {
        .text = gEasyChatWord_Money,
        .alphabeticalOrder = EC_INDEX(EC_WORD_CHORES),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_ALLOWANCE)] =
    {
        .text = gEasyChatWord_Allowance,
        .alphabeticalOrder = EC_INDEX(EC_WORD_CLASS),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_BATH)] =
    {
        .text = gEasyChatWord_Bath,
        .alphabeticalOrder = EC_INDEX(EC_WORD_COMMEMORATE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_CONVERSATION)] =
    {
        .text = gEasyChatWord_Conversation,
        .alphabeticalOrder = EC_INDEX(EC_WORD_CONVERSATION),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_SCHOOL)] =
    {
        .text = gEasyChatWord_School,
        .alphabeticalOrder = EC_INDEX(EC_WORD_DEPT_STORE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_COMMEMORATE)] =
    {
        .text = gEasyChatWord_Commemorate,
        .alphabeticalOrder = EC_INDEX(EC_WORD_DIGITAL),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_HABIT)] =
    {
        .text = gEasyChatWord_Habit,
        .alphabeticalOrder = EC_INDEX(EC_WORD_DREAM),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_GROUP)] =
    {
        .text = gEasyChatWord_Group,
        .alphabeticalOrder = EC_INDEX(EC_WORD_EVENT),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_WORD)] =
    {
        .text = gEasyChatWord_Word,
        .alphabeticalOrder = EC_INDEX(EC_WORD_GROUP),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_STORE)] =
    {
        .text = gEasyChatWord_Store,
        .alphabeticalOrder = EC_INDEX(EC_WORD_HABIT),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_SERVICE)] =
    {
        .text = gEasyChatWord_Service,
        .alphabeticalOrder = EC_INDEX(EC_WORD_HOME),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_WORK)] =
    {
        .text = gEasyChatWord_Work,
        .alphabeticalOrder = EC_INDEX(EC_WORD_INFORMATION),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_SYSTEM)] =
    {
        .text = gEasyChatWord_System,
        .alphabeticalOrder = EC_INDEX(EC_WORD_ITEM),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_TRAIN)] =
    {
        .text = gEasyChatWord_Train,
        .alphabeticalOrder = EC_INDEX(EC_WORD_KINDERGARTEN),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_CLASS)] =
    {
        .text = gEasyChatWord_Class,
        .alphabeticalOrder = EC_INDEX(EC_WORD_LESSONS),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_LESSONS)] =
    {
        .text = gEasyChatWord_Lessons,
        .alphabeticalOrder = EC_INDEX(EC_WORD_LETTER),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_INFORMATION)] =
    {
        .text = gEasyChatWord_Information,
        .alphabeticalOrder = EC_INDEX(EC_WORD_LIFE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_LIVING)] =
    {
        .text = gEasyChatWord_Living,
        .alphabeticalOrder = EC_INDEX(EC_WORD_LIVING),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_TEACHER)] =
    {
        .text = gEasyChatWord_Teacher,
        .alphabeticalOrder = EC_INDEX(EC_WORD_MACHINE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_TOURNAMENT)] =
    {
        .text = gEasyChatWord_Tournament,
        .alphabeticalOrder = EC_INDEX(EC_WORD_MAIL),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_LETTER)] =
    {
        .text = gEasyChatWord_Letter,
        .alphabeticalOrder = EC_INDEX(EC_WORD_MESSAGE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_EVENT)] =
    {
        .text = gEasyChatWord_Event,
        .alphabeticalOrder = EC_INDEX(EC_WORD_MONEY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_DIGITAL)] =
    {
        .text = gEasyChatWord_Digital,
        .alphabeticalOrder = EC_INDEX(EC_WORD_NAME),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_TEST)] =
    {
        .text = gEasyChatWord_Test,
        .alphabeticalOrder = EC_INDEX(EC_WORD_NEWS),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_DEPT_STORE)] =
    {
        .text = gEasyChatWord_DeptStore,
        .alphabeticalOrder = EC_INDEX(EC_WORD_PARTY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_TELEVISION)] =
    {
        .text = gEasyChatWord_Television,
        .alphabeticalOrder = EC_INDEX(EC_WORD_PHONE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_PHONE)] =
    {
        .text = gEasyChatWord_Phone,
        .alphabeticalOrder = EC_INDEX(EC_WORD_POPULAR),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_ITEM)] =
    {
        .text = gEasyChatWord_Item,
        .alphabeticalOrder = EC_INDEX(EC_WORD_PROMISE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_NAME)] =
    {
        .text = gEasyChatWord_Name,
        .alphabeticalOrder = EC_INDEX(EC_WORD_RADIO),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_NEWS)] =
    {
        .text = gEasyChatWord_News,
        .alphabeticalOrder = EC_INDEX(EC_WORD_RENTAL),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_POPULAR)] =
    {
        .text = gEasyChatWord_Popular,
        .alphabeticalOrder = EC_INDEX(EC_WORD_SCHOOL),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_PARTY)] =
    {
        .text = gEasyChatWord_Party,
        .alphabeticalOrder = EC_INDEX(EC_WORD_SERVICE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_STUDY)] =
    {
        .text = gEasyChatWord_Study,
        .alphabeticalOrder = EC_INDEX(EC_WORD_STORE),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_MACHINE)] =
    {
        .text = gEasyChatWord_Machine,
        .alphabeticalOrder = EC_INDEX(EC_WORD_STUDY),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_MAIL)] =
    {
        .text = gEasyChatWord_Mail,
        .alphabeticalOrder = EC_INDEX(EC_WORD_SYSTEM),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_MESSAGE)] =
    {
        .text = gEasyChatWord_Message,
        .alphabeticalOrder = EC_INDEX(EC_WORD_TEACHER),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_PROMISE)] =
    {
        .text = gEasyChatWord_Promise,
        .alphabeticalOrder = EC_INDEX(EC_WORD_TELEVISION),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_DREAM)] =
    {
        .text = gEasyChatWord_Dream,
        .alphabeticalOrder = EC_INDEX(EC_WORD_TEST),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_KINDERGARTEN)] =
    {
        .text = gEasyChatWord_Kindergarten,
        .alphabeticalOrder = EC_INDEX(EC_WORD_TOURNAMENT),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_LIFE)] =
    {
        .text = gEasyChatWord_Life,
        .alphabeticalOrder = EC_INDEX(EC_WORD_TRAIN),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_RADIO)] =
    {
        .text = gEasyChatWord_Radio,
        .alphabeticalOrder = EC_INDEX(EC_WORD_WORD),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_RENTAL)] =
    {
        .text = gEasyChatWord_Rental,
        .alphabeticalOrder = EC_INDEX(EC_WORD_WORK),
        .enabled = TRUE,
    },
    [EC_INDEX(EC_WORD_WORLD)] =
    {
        .text = gEasyChatWord_World,
        .alphabeticalOrder = EC_INDEX(EC_WORD_WORLD),
        .enabled = TRUE,
    },
};
