#include "global.h"
#include "battle_main.h"
#include "battle_util.h"
#include "bg.h"
#include "contest_effect.h"
#include "data.h"
#include "daycare.h"
#include "decompress.h"
#include "event_data.h"
#include "gpu_regs.h"
#include "graphics.h"
#include "international_string_util.h"
#include "item.h"
#include "item_icon.h"
#include "main.h"
#include "malloc.h"
#include "menu.h"
#include "m4a.h"
#include "overworld.h"
#include "palette.h"
#include "party_menu.h"
#include "pokedex.h"
#include "pokedex_plus_hgss.h"
#include "pokedex_area_screen.h"
#include "pokedex_cry_screen.h"
#include "pokemon_icon.h"
#include "pokemon_summary_screen.h"
#include "region_map.h"
#include "pokemon.h"
#include "malloc.h"
#include "scanline_effect.h"
#include "shop.h"
#include "sound.h"
#include "sprite.h"
#include "string_util.h"
#include "strings.h"
#include "task.h"
#include "text_window.h"
#include "trainer_pokemon_sprites.h"
#include "trig.h"
#include "rtc.h"
#include "window.h"
#include "random.h"
#include "siirtc.h"
#include "dig_fossil.h"
#include "script.h"
#include "constants/abilities.h"
#include "constants/vars.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/flags.h"
#include "constants/rgb.h"
#include "constants/songs.h"

#define _PARTS_NUM_MAX   (8)
#define _PARTS_TREASURE_NUM_MAX (4)
#define DIG_FOSSIL_DEBUG 1

struct FossilParts
{
    const u8* attribute; // アトリビュートデータへのポインタ  無い時はNULL
    u16 random;
    u16 random1;
    u16 random2;
    u16 random3;
    u8 width;
    u8 height;
    u8 partsType; // パーツ種類
    const u8* ncg;
    const u16* ncl;
};

typedef struct
{
    const struct FossilParts* pParts;  // 元データ参照ポインタ
    u8 partsType;           // パーツ種類
    u8 x;
    u8 y;
    u8 dir;
    u8 bGetItem;
} FossilPartsData;

enum
{
    _SEQ_FIELD_FADEOUT,
    _SEQ_GAME_INIT1,
    _SEQ_GAME_INIT2,
    _SEQ_GAME_FADE_IN,
    _SEQ_GAME_FADE_IN_WAIT,
    _SEQ_RADAR,
    _SEQ_MESSAGE,
    _SEQ_MESSAGE_WAIT,
    _SEQ_MESSAGE_FIRST,
    _SEQ_MESSAGE_FIRST_WAIT,
    _SEQ_GAME,
    _SEQ_SUCCESS_WAIT,
    _SEQ_KEY_WAIT,
    _SEQ_RESULT_MSG,
    _SEQ_KEY_WAIT2,
    _SEQ_FAINALIZE,
    _SEQ_UG_REBOOT,
    _SEQ_UG_REBOOT_WAIT,
    _SEQ_END,
    _SEQ_QUAKE,
    _SEQ_WIPE,
    _SEQ_WIPE_CHANGE,
    _SEQ_WIPE_CHANGE2,
    _SEQ_WIPE_MES,
    _SEQ_KEY_WAIT_FAILED,    
};

#define B1MAX 8
#define B2MAX 5

#define FOSSIL_MAP_WIDTH (12)
#define FOSSIL_MAP_HEIGHT (8)
#define _DIGMAP_INVALID (0xFF)
#define _DIG_GAUGE_START (200 - 4)

#define COMM_CHILD_MAX (7)
#define COMM_INVALID_ID (0xff)
#define COMM_MACHINE_MAX (COMM_CHILD_MAX + 1)

#define _PUSH_START (2)

enum
{
    _CLACT_HUMMER,
    _CLACT_EFFECT, // 切换按钮的特效
    _CLACT_HIT_HARD, //

    _CLACT_HIT_BIG_0, //
    _CLACT_HIT_BIG_1, //
    _CLACT_HIT_BIG_2, //
    _CLACT_HIT_BIG_3, //

    _CLACT_KIRA_SINGLE,  //

    _CLACT_KIRA_P1,  //
    _CLACT_KIRA_P2,  //
    _CLACT_KIRA_P3,  //

    _CLACT_MAX,
};

static EWRAM_DATA struct FossilEventTask
{
    bool8 bPic;
    u8 touchPanelRelease;
    u8 digGauge;
    u8 bSuccess;
    u8 seq;
    u8 shakeCount;
    s8 shakeX;
    s8 shakeZ;
    u8 touchButton;
    u8 touchX;
    u8 touchY;
    u8 timer;
    u8 delay;
    u8 digCarat;
    u8 kiraTimer;
    u8 _PARTS_TREASURE_NUM;
    int digTimer[_PARTS_TREASURE_NUM_MAX];
    MATHRandContext32 sRand;
    FossilPartsData aDeposit[_PARTS_NUM_MAX];
    u8 logMsgFossil[COMM_MACHINE_MAX];
    u8 friendDigPointX[COMM_MACHINE_MAX];
    u8 friendDigPointZ[COMM_MACHINE_MAX];
    u8 depositMap[FOSSIL_MAP_HEIGHT][FOSSIL_MAP_WIDTH];
    u8 buildupMap[FOSSIL_MAP_HEIGHT][FOSSIL_MAP_WIDTH];
    u16 bgTilemapBuff[3][0x400];
    const u16* palData[_PARTS_TREASURE_NUM_MAX];
    struct Sprite* spriteWork[_CLACT_MAX];
    
} *sFossilGameData = NULL;

static void Task_DigFossil(u8 taskId);
static void CommRandSeedInitialize(MATHRandContext32 *pRand);
static void _touchButtonInitialize(void);
static bool8 _gameProcess(void);
static void _shakeProcess(void);
static void _shakeProcessVBlank(void);
static void _touchButtonProcess(int level);
static void _setCellActor(void);
static void _gaugeDisp(void);
static void SpriteCB_HummerAnim(struct Sprite *sprite);
static void SpriteCB_CursorPos(struct Sprite *sprite);
static void _partsDigColor(void);
static bool8 _fossilGetMessage(void);
static void FossilGame_AddTextPrinterForMessage(const u8* message);

#include "data/dig_fossil.h"

static const u32 sDigFossil_BackGround_Gfx[] = INCBIN_U32("graphics/dig_fossil/ug_fossil.4bpp.lz");
static const u32 sDigFossil_BackGround_Map[] = INCBIN_U32("graphics/dig_fossil/ug_fossil.bin.lz");
static const u16 sDigFossil_BackGround_Pal[] = INCBIN_U16("graphics/dig_fossil/ug_fossil.gbapal");

static const u32 sDigFossil_Effect_Gfx[] = INCBIN_U32("graphics/dig_fossil/ug_anim_effect.4bpp.lz");
static const u16 sDigFossil_Effect_Pal[] = INCBIN_U16("graphics/dig_fossil/ug_anim_effect.gbapal");

static const u32 sDigFossil_Gauge_Gfx[] = INCBIN_U32("graphics/dig_fossil/gauge_head.4bpp");
static const u16 sDigFossil_Gauge_Pal[] = INCBIN_U16("graphics/dig_fossil/gauge_head.gbapal");

static const u8 gText_FossilStartMessage[] = _("确认到墙壁中有\n{STR_VAR_1}个大型反应!{PAUSE_UNTIL_PRESS}");
static const u8 gText_FossilFirstMessage[] = _("……………………\n……………………\p咦？探险套装里\n夹着一张便条：\p“挖化石指南！\p我把榔头和鹤嘴锄放进\n探险套装里了！\p用这些道具就可以把\n墙壁里的宝物挖出来。\p在墙壁崩塌前挖出来的话，\n就肯定能得到好东西。\p你一定能行的！\n祝你好运！”{PAUSE_UNTIL_PRESS}");
static const u8 gText_FossilFoundAll[] = _("挖出了所有化石！{PAUSE_UNTIL_PRESS}");
static const u8 gText_FossilFail[] = _("墙壁崩塌了！{PAUSE_UNTIL_PRESS}");
static const u8 gText_GetTreasure[] = _("你收集到了{STR_VAR_1} {STR_VAR_2}！{PAUSE_UNTIL_PRESS}");
static const u8 gText_GameGetItem[] = _("找到了{STR_VAR_1}！{PAUSE_UNTIL_PRESS}");

extern const u32 sRegionMapCursorSmallGfxLZ[];
extern const u16 sRegionMapCursorPal[];

static const struct CompressedSpriteSheet gDigFossil_InterFaceSheet[] = 
{
    {
        .data = sDigFossil_Effect_Gfx,
        .size = 256 * 136 / 2,
        .tag = 0x5780
    },
    {
        .data = sRegionMapCursorSmallGfxLZ,
        .size = 256,
        .tag = 0x5781
    }
};

static const struct SpritePalette gDigFossil_InterFacePalette[] = 
{
    {
        .data = sDigFossil_Effect_Pal,
        .tag = 0x5780,
    },
    {
        .data = sRegionMapCursorPal,
        .tag = 0x5781,
    },
    {}
};

static const struct BgTemplate sDigFossil_BgTemplate[] =
{
    {
        .bg = 0,
        .charBaseIndex = 2,
        .mapBaseIndex = 28,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0
    },
    {
        .bg = 1,
        .charBaseIndex = 1,
        .mapBaseIndex = 29,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 1,
        .baseTile = 0
    },
    {
        .bg = 2,
        .charBaseIndex = 0,
        .mapBaseIndex = 30,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 2,
        .baseTile = 0
    },
    {
        .bg = 3,
        .charBaseIndex = 0,
        .mapBaseIndex = 31,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 3,
        .baseTile = 0
    }
};

static const struct WindowTemplate sDigFossil_WindowTemplates[] =
{
    {
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 15,
        .width = 27,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x194
    },
    DUMMY_WIN_TEMPLATE
};

static void ResetOtherVideoRegisters(void)
{
    DmaClearLarge16(3, (void *)(VRAM), VRAM_SIZE, 0x1000);

    {
        ClearGpuRegBits(0, DISPCNT_BG0_ON);
        SetGpuReg(REG_OFFSET_BG0CNT, 0);
        SetGpuReg(REG_OFFSET_BG0HOFS, 0);
        SetGpuReg(REG_OFFSET_BG0VOFS, 0);
    }

    {
        ClearGpuRegBits(0, DISPCNT_BG1_ON);
        SetGpuReg(REG_OFFSET_BG1CNT, 0);
        SetGpuReg(REG_OFFSET_BG1HOFS, 0);
        SetGpuReg(REG_OFFSET_BG1VOFS, 0);
    }

    {
        ClearGpuRegBits(0, DISPCNT_BG2_ON);
        SetGpuReg(REG_OFFSET_BG2CNT, 0);
        SetGpuReg(REG_OFFSET_BG2HOFS, 0);
        SetGpuReg(REG_OFFSET_BG2VOFS, 0);
    }

    {
        ClearGpuRegBits(0, DISPCNT_BG3_ON);
        SetGpuReg(REG_OFFSET_BG3CNT, 0);
        SetGpuReg(REG_OFFSET_BG3HOFS, 0);
        SetGpuReg(REG_OFFSET_BG3VOFS, 0);
    }

    {
        ClearGpuRegBits(0, DISPCNT_OBJ_ON);
        ResetSpriteData();
        FreeAllSpritePalettes();
        gReservedSpritePaletteCount = 8;
    }
}

void CB2_OnlyRunTask(void)
{
    RunTasks();
    UpdatePaletteFade();
}

void CB2_StartDigFossilGame(void)
{
    ResetTasks();

    CreateTask(Task_DigFossil, 0);
    SetMainCallback2(CB2_OnlyRunTask);
    BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
    sFossilGameData = AllocZeroed(sizeof(struct FossilEventTask));
}

void Special_StartDigFossilGame(void)
{
    gMain.savedCallback = CB2_ReturnToField;
    SetMainCallback2(CB2_StartDigFossilGame);
    LockPlayerFieldControls();
}

static void FossilGame_InitializeData(void)
{
    int i;

    for (i = 0; i < COMM_MACHINE_MAX; i++)
    {
        sFossilGameData->friendDigPointX[i] = _DIGMAP_INVALID;
        sFossilGameData->friendDigPointZ[i] = _DIGMAP_INVALID;
    }
    sFossilGameData->bPic = TRUE;
    sFossilGameData->digGauge = _DIG_GAUGE_START;
    sFossilGameData->touchX = 0;
    sFossilGameData->touchY = 0;

    for (i = 0; i < _PARTS_NUM_MAX; i++)
    {
        sFossilGameData->aDeposit[i].pParts = NULL;
        sFossilGameData->aDeposit[i].bGetItem = FALSE;
    }
    for (i = 0; i < FOSSIL_MAP_WIDTH * FOSSIL_MAP_HEIGHT; i++)
    {
        sFossilGameData->depositMap[i / FOSSIL_MAP_WIDTH][i % FOSSIL_MAP_WIDTH] = 0;
        sFossilGameData->buildupMap[i / FOSSIL_MAP_WIDTH][i % FOSSIL_MAP_WIDTH] = 2;
    }
}

static int _fossilRandGet(const struct FossilParts* pParts)
{
    u32 value = gSaveBlock2Ptr->playerTrainerId[0]
              | (gSaveBlock2Ptr->playerTrainerId[1] << 8)
              | (gSaveBlock2Ptr->playerTrainerId[2] << 16)
              | (gSaveBlock2Ptr->playerTrainerId[3] << 24);
    bool8 bEvent = value % 2;
    int treasureRand = 0;

    if (IsNationalPokedexEnabled()) // 全国图鉴获得
    {
        if (bEvent) // 根据玩家Id决定哪一组化石容易获得
        {
            treasureRand += pParts->random2;
        }
        else
        {
            treasureRand += pParts->random3;
        }
    }
    else
    {
        if (bEvent)
        {
            treasureRand += pParts->random;
        }
        else
        {
            treasureRand += pParts->random1;
        }
    }
    return treasureRand;
}

static int _getTreasurePartsRandomMax(void)
{
    int i, treasureRand = 0;

    for (i = 0; i < NELEMS(gFossilGamePartsData); i++)
    {
        if (DIG_PARTS_NODIG1 == gFossilGamePartsData[i].partsType)
        {
            break;
        }
        treasureRand += _fossilRandGet(&gFossilGamePartsData[i]);
    }
    return treasureRand;
}

static int _getTreasurePartsRandom(int random)
{
    int i, treasureRand = random;

    for(i = 0; i < NELEMS(gFossilGamePartsData) ; i++)
    {
        if(DIG_PARTS_NODIG1 == gFossilGamePartsData[i].partsType)
            break;

        treasureRand -= _fossilRandGet(&gFossilGamePartsData[i]);
        if(treasureRand < 0)
        {
            return i;
        }
    }

    return 0;
}

static int _getTreasurePartsNoDigNum(void)
{
    int i, j = 0;

    for(i = 0; i < NELEMS(gFossilGamePartsData); i++)
    {
        if(gFossilGamePartsData[i].partsType >= DIG_PARTS_NODIG1){
            j++;
        }
    }
    return j;
}

void UnderGroundSetFossilDig(int type)
{
    if((DIG_PARTS_PLATE_FIRE > type) || (type > DIG_PARTS_PLATE_IRON))
        return;

    FossilSetPlateBit(type);
}

// 检查是否挖到了稀有石板
bool8 UnderGroundIsFossilAdvent(int type)
{
    if ((DIG_PARTS_PLATE_FIRE > type) || (type > DIG_PARTS_PLATE_IRON))
    {
        return TRUE;
    }
    if (FossilGetPlateBit(type))
    {
        return FALSE;
    }
    return TRUE;
}

static bool8 _isFreeDiposit(void)
{
    int i;

    for(i = 0; i < _PARTS_NUM_MAX; i++)
    {
        if(sFossilGameData->aDeposit[i].pParts == NULL)
        {
            return TRUE;
        }
    }
    return FALSE;
}

static bool8 FossilGame_isAttribute(const struct FossilParts *pParts, int x, int y)
{
    const u8 *attr = pParts->attribute;
    int xpos, ypos, width;

    if (attr == NULL)
    {
        return TRUE; // 全面あたりのみ
    }
    ypos = y / 2;
    xpos = x / 2;
    width = pParts->width / 2;
    if (attr[ypos * width + xpos] == 'o')
    {
        return FALSE;
    }
    return TRUE;
}

static int _setDiposit(int partsIndex, int x, int y)
{
    int i;

    for (i = 0; i < _PARTS_NUM_MAX; i++)
    {
        if (sFossilGameData->aDeposit[i].pParts == NULL)
        {
            sFossilGameData->aDeposit[i].pParts = &gFossilGamePartsData[partsIndex];
            sFossilGameData->aDeposit[i].partsType = gFossilGamePartsData[partsIndex].partsType;
            sFossilGameData->aDeposit[i].x = x;
            sFossilGameData->aDeposit[i].y = y;
            sFossilGameData->aDeposit[i].bGetItem = FALSE;
            return i + 1;
        }
    }
    return 0;
}

static bool8 _partsDeposit(int partsIndex, int x, int y)
{
    int i, j, xParts, yParts, idx;

    if (!_isFreeDiposit()) // 检查存在空的数据内存
    {
        return FALSE;
    }

    xParts = gFossilGamePartsData[partsIndex].width / 2 + x;
    yParts = gFossilGamePartsData[partsIndex].height / 2 + y;

    if (xParts > FOSSIL_MAP_WIDTH) // 超出范围
    {
        return FALSE;
    }
    if (yParts > FOSSIL_MAP_HEIGHT) // 超出范围
    {
        return FALSE;
    }

    for (i = x; i < xParts; i++)
    {
        for (j = y; j < yParts; j++)
        {
            if (FossilGame_isAttribute(&gFossilGamePartsData[partsIndex], (i - x) * 2, (j - y) * 2)) // 检查对应格子中是否存在别的道具
            {
                if (sFossilGameData->depositMap[j][i] != 0)
                {
                    return FALSE;
                }
            }
        }
    }
    idx = _setDiposit(partsIndex, x, y);
    for (i = x; i < xParts; i++)
    {
        for (j = y; j < yParts; j++)
        {
            if (FossilGame_isAttribute(&gFossilGamePartsData[partsIndex], (i - x) * 2, (j - y) * 2))
            {
                sFossilGameData->depositMap[j][i] = idx;
            }
        }
    }

    return TRUE;
}

#define _PALLET_INDEX (3)

static int _depositBGInitParts(int idx, int charOffset)
{
    FossilPartsData* pFPD = &sFossilGameData->aDeposit[idx];
    u16* pScrAddr = GetBgTilemapBuffer(2);
    int xini = pFPD->x * 2;
    int yini = pFPD->y * 2;
    int xend = xini + pFPD->pParts->width;
    int yend = yini + pFPD->pParts->height;
    int y, x, scr, i = charOffset;
    int pidx = idx;
    u32 size = pFPD->pParts->width * pFPD->pParts->height * 32;

    if(idx >= sFossilGameData->_PARTS_TREASURE_NUM)
    {
        pidx = _PARTS_TREASURE_NUM_MAX;  // 硬い石のパレット位置がここになる
    }

    LoadBgTiles(2, pFPD->pParts->ncg, size, charOffset);
    LoadPalette(pFPD->pParts->ncl, PLTT_ID(pidx + _PALLET_INDEX), PLTT_SIZE_4BPP);

    if (idx < sFossilGameData->_PARTS_TREASURE_NUM)
    {
        sFossilGameData->palData[idx] = pFPD->pParts->ncl;
    }
    for (y = yini; y < yend; y++)
    {
        for (x = xini; x < xend; x++)
        {
            i++;
            if (!FossilGame_isAttribute(pFPD->pParts, x - xini, y - yini))
            {
                continue;
            }
            scr = x + ((y + 4) * 32);
            pScrAddr[scr] = ((pidx + _PALLET_INDEX) * 0x1000) + i - 1;
        }
    }
    return size;
}

static void _depositBGInit(int partsMax)
{
    int sendByte;
    int i, charOffset = 512 + 24 * 4 + 32 + 1; // 1 + charByte/32;

    for (i = 0; i < partsMax; i++)
    {
        sendByte = _depositBGInitParts(i, charOffset);
        charOffset += sendByte / 32;
    }
}

static void FossilGame_RandomDeposit(void)
{
    int i, j, treasureRand = _getTreasurePartsRandomMax();
    int rand, parts, x, y, limit = 0, partsIndex, type;
    int noDigNum = _getTreasurePartsNoDigNum();
    int plate[_PARTS_TREASURE_NUM_MAX];

    sFossilGameData->_PARTS_TREASURE_NUM = MATH_Rand32(&sFossilGameData->sRand, (_PARTS_TREASURE_NUM_MAX - 1)) + 2;

    if (UnderGroundIsFirstFossil()) // 初次挖掘时必定3个
    {
        sFossilGameData->_PARTS_TREASURE_NUM = 3;
    }
    for (i = 0; i < sFossilGameData->_PARTS_TREASURE_NUM;)
    {
        rand = MATH_Rand32(&sFossilGameData->sRand, treasureRand); // お宝の何を埋めるか決める
        partsIndex = _getTreasurePartsRandom(rand);
        type = gFossilGamePartsData[partsIndex].partsType;
        if (!UnderGroundIsFossilAdvent(gFossilGamePartsData[partsIndex].partsType)) // 检查是否可以设置石板类
        {
            continue;
        }
        if ((DIG_PARTS_PLATE_FIRE <= type) && (type <= DIG_PARTS_PLATE_IRON)) // 石板类道具不会重复设置，当存在相同石板时跳过
        {
            bool8 dbl = FALSE;
            plate[i] = type;
            for (j = 0; j < i; j++)
            {
                if (plate[j] == type)
                {
                    dbl = TRUE;
                }
            }
            if (dbl)
            {
                continue;
            }
        }
        else
        {
            plate[i] = DIG_PARTS_BONE; // 
        }

        x = MATH_Rand32(&sFossilGameData->sRand, FOSSIL_MAP_WIDTH);
        y = MATH_Rand32(&sFossilGameData->sRand, FOSSIL_MAP_HEIGHT);
        if (_partsDeposit(partsIndex, x, y))
        {
            i++;
        }
    }
    if (!UnderGroundIsFirstFossil()) // 初次挖掘不会生成铁块
    {
        for (limit = 0; limit < 100; limit++)
        {
            partsIndex = MATH_Rand32(&sFossilGameData->sRand, noDigNum); // 邪魔する硬い石を埋める
            partsIndex += NELEMS(gFossilGamePartsData) - noDigNum;
            x = MATH_Rand32(&sFossilGameData->sRand, FOSSIL_MAP_WIDTH);
            y = MATH_Rand32(&sFossilGameData->sRand, FOSSIL_MAP_HEIGHT);
            if (_partsDeposit(partsIndex, x, y))
            {
                i++;
            }
            if (i > 12)
            {
                break;
            }
        }
    }
    _depositBGInit(i); // 将道具打印至bg
}

static void FossilGame_Initialize1(void)
{
    CommRandSeedInitialize(&sFossilGameData->sRand);
    InitBgsFromTemplates(0, sDigFossil_BgTemplate, ARRAY_COUNT(sDigFossil_BgTemplate));
    SetBgTilemapBuffer(1, &sFossilGameData->bgTilemapBuff[0]);
    SetBgTilemapBuffer(2, &sFossilGameData->bgTilemapBuff[1]);
    SetBgTilemapBuffer(3, &sFossilGameData->bgTilemapBuff[2]);

    LoadCompressedSpriteSheet(&gDigFossil_InterFaceSheet[0]);
    LoadCompressedSpriteSheet(&gDigFossil_InterFaceSheet[1]);
    LoadSpritePalettes(gDigFossil_InterFacePalette);

    LoadBgTiles(1, NARC_ug_parts_kaseki_board_wall_NCGR, sizeof(NARC_ug_parts_kaseki_board_wall_NCGR), 1);

    LoadMessageBoxAndFrameGfx(0, TRUE);

    FossilGame_InitializeData(); 
    FossilGame_RandomDeposit();

    InitWindows(sDigFossil_WindowTemplates);
    DeactivateAllTextPrinters();
}

static void _randomBuildup(void)
{
    static const u8 buildup1[B1MAX][B1MAX] = 
    {
        {0, 0, 4, 4, 4, 4, 0, 0}, 
        {0, 4, 4, 4, 4, 4, 4, 0}, 
        {4, 4, 4, 4, 4, 4}, 
        {4, 4, 4, 4, 4, 4}, 
        {4, 4, 4, 4, 4, 4}, 
        {4, 4, 4, 4, 4, 4}, 
        {0, 4, 4, 4, 4, 4, 4, 0}, 
        {0, 0, 4, 4, 4, 4, 0, 0}
    };

    static const u8 buildup2[B2MAX][B2MAX] = 
    {
        {0, 6, 6, 6, 0}, 
        {6, 6, 6, 6, 6}, 
        {6, 6, 6, 6, 6}, 
        {6, 6, 6, 6, 6}, 
        {0, 6, 6, 6, 0}
    };
    int rand, x, y, xini, yini, i;
    bool8 bBuildup = TRUE;

    for (i = 0; i < 10; i++)
    {
        xini = MATH_Rand32(&sFossilGameData->sRand, FOSSIL_MAP_WIDTH + B1MAX) - B1MAX;
        yini = MATH_Rand32(&sFossilGameData->sRand, FOSSIL_MAP_HEIGHT + B1MAX) - B2MAX;
        for (y = yini; y < yini + B1MAX; y++)
        {
            if ((y >= FOSSIL_MAP_HEIGHT) || (y < 0))
            {
                continue;
            }
            for (x = xini; x < xini + B1MAX; x++)
            {
                if ((x >= FOSSIL_MAP_WIDTH) || (x < 0))
                {
                    continue;
                }
                if (buildup1[y - yini][x - xini] == 0)
                {
                    continue;
                }
                sFossilGameData->buildupMap[y][x] = buildup1[y - yini][x - xini];
            }
        }
    }
    for (i = 0; i < 15; i++)
    {
        xini = MATH_Rand32(&sFossilGameData->sRand, FOSSIL_MAP_WIDTH + B2MAX) - B2MAX;
        yini = MATH_Rand32(&sFossilGameData->sRand, FOSSIL_MAP_HEIGHT + B2MAX) - B2MAX;
        bBuildup = TRUE;
        for (y = yini; y < yini + B2MAX; y++)
        {
            if ((y >= FOSSIL_MAP_HEIGHT) || (y < 0))
            {
                continue;
            }
            for (x = xini; x < xini + B2MAX; x++)
            {
                if ((x >= FOSSIL_MAP_WIDTH) || (x < 0))
                {
                    continue;
                }
                if (buildup1[y - yini][x - xini] == 0)
                {
                    continue;
                }
                if (sFossilGameData->buildupMap[y][x] < 4)
                {
                    bBuildup = FALSE;
                    break;
                }
            }
            if (bBuildup == FALSE)
            {
                break;
            }
        }
        if (!bBuildup)
        {
            continue;
        }
        for (y = yini; y < yini + B2MAX; y++)
        {
            if ((y >= FOSSIL_MAP_HEIGHT) || (y < 0))
            {
                continue;
            }
            for (x = xini; x < xini + B2MAX; x++)
            {
                if ((x >= FOSSIL_MAP_WIDTH) || (x < 0))
                {
                    continue;
                }
                if (buildup2[y - yini][x - xini] == 0)
                {
                    continue;
                }
                sFossilGameData->buildupMap[y][x] = buildup2[y - yini][x - xini];
            }
        }
    }
}

static void _buildupBGDraw(void)
{
    u8 lv0[] = {0xe, 0xf, 0x1e, 0x1f};
    u8 lv1[] = {0xa, 0xb, 0x1a, 0x1b};
    u8 lv2[] = {0x8, 0x9, 0x18, 0x19};
    u8 lv3[] = {0x6, 0x7, 0x16, 0x17};
    u8 lv4[] = {0x4, 0x5, 0x14, 0x15};
    u8 lv5[] = {0x2, 0x3, 0x12, 0x13};
    u8 lv6[] = {0x0, 0x1, 0x10, 0x11};
    u8 *lvlTbl[] = {lv0, lv1, lv2, lv3, lv4, lv5, lv6};

    u16 *pScrAddr = GetBgTilemapBuffer(1);
    int y, x, scr;

    for (y = 0; y < FOSSIL_MAP_HEIGHT; y++)
    {
        for (x = 0; x < FOSSIL_MAP_WIDTH; x++)
        {
            u8 *pTbl = lvlTbl[sFossilGameData->buildupMap[y][x]];
            scr = x * 2 + ((y * 2 + 4) * 32);
            pScrAddr[scr] = pTbl[0] + 0x2001;
            pScrAddr[scr + 1] = pTbl[1] + 0x2001;
            pScrAddr[scr + 32] = pTbl[2] + 0x2001;
            pScrAddr[scr + 33] = pTbl[3] + 0x2001;
        }
    }
    CopyBgTilemapBufferToVram(1);
}

static bool8 IsHitEffectSprite(u8 id)
{
    if (id == _CLACT_HIT_BIG_1 
    || id == _CLACT_HIT_BIG_2 
    || id == _CLACT_HIT_BIG_3)
        return TRUE;
    return FALSE;
}

static void SpriteCB_HummerAnim(struct Sprite *sprite)
{
    if (sprite->data[0] == _CLACT_HUMMER)
    {
        static const s16 posTbl[][2] = 
        {
            {0, -32},
            {-8, -24},
            {8, -32},
            {11, -32},
            {8, -32},
            {11, -32},
            {0, 0}
        };
        sprite->x2 = posTbl[sprite->animCmdIndex][0] + 16;
        sprite->y2 = posTbl[sprite->animCmdIndex][1] + 16;
    }

    if (IsHitEffectSprite(sprite->data[0]))
    {
        sprite->x = sFossilGameData->spriteWork[_CLACT_HIT_BIG_0]->x;
        sprite->y = sFossilGameData->spriteWork[_CLACT_HIT_BIG_0]->y;
    }
    sprite->invisible = FALSE;
    if (sprite->animEnded)
        sprite->invisible = TRUE;
}

static void SpriteCB_CursorPos(struct Sprite *sprite)
{
    sprite->x = sFossilGameData->touchX * 16 + 8;
    sprite->y = (sFossilGameData->touchY + 2) * 16 + 8;
}

static void SpriteAnimStop(struct Sprite *sprite)
{
    sprite->animBeginning = FALSE;
    sprite->animEnded = TRUE;
}

static void _setCellActor(void)
{
    int j;
    u32 spriteId;

    for (j = _CLACT_HUMMER; j <= _CLACT_KIRA_P3; j++)
    {
        spriteId = CreateSprite(&gDigFossilObjData, 0, 0, 0);
        sFossilGameData->spriteWork[j] = &gSprites[spriteId];
        sFossilGameData->spriteWork[j]->data[0] = j;
        // 各种效果的处理
        switch (j)
        {
            case _CLACT_HIT_BIG_0:
                sFossilGameData->spriteWork[j]->x2 = -16;
                sFossilGameData->spriteWork[j]->y2 = -16;
                break;
            case _CLACT_HIT_BIG_1:
                sFossilGameData->spriteWork[j]->hFlip = 1;
                sFossilGameData->spriteWork[j]->x2 = 16;
                sFossilGameData->spriteWork[j]->y2 = -16;
                break;
            case _CLACT_HIT_BIG_2:
                sFossilGameData->spriteWork[j]->vFlip = 1;
                sFossilGameData->spriteWork[j]->x2 = -16;
                sFossilGameData->spriteWork[j]->y2 = 16;
                break;
            case _CLACT_HIT_BIG_3:
                sFossilGameData->spriteWork[j]->hFlip = 1;
                sFossilGameData->spriteWork[j]->vFlip = 1;
                sFossilGameData->spriteWork[j]->x2 = 16;
                sFossilGameData->spriteWork[j]->y2 = 16;
                break;
            case _CLACT_KIRA_SINGLE:    // 布灵布灵效果
            case _CLACT_KIRA_P1:
            case _CLACT_KIRA_P2:
            case _CLACT_KIRA_P3:
                sFossilGameData->spriteWork[j]->oam.shape = SPRITE_SHAPE(16x16);
                sFossilGameData->spriteWork[j]->oam.size = SPRITE_SIZE(16x16);
                break;
            case _CLACT_EFFECT:
                sFossilGameData->spriteWork[j]->oam.shape = SPRITE_SHAPE(64x64);
                sFossilGameData->spriteWork[j]->oam.size = SPRITE_SIZE(64x64);
                break;
            default:
                break;
        }
        SpriteAnimStop(sFossilGameData->spriteWork[j]);
    }
    CreateSprite(&gSpriteCursor, 0, 0, 10);
}

static void FossilGame_Initialize2(void)
{
    LZ77UnCompVram(sDigFossil_BackGround_Gfx, (void*)(BG_CHAR_ADDR(0)));
    LZ77UnCompWram(sDigFossil_BackGround_Map, GetBgTilemapBuffer(3));
    LoadBgTiles(3, sDigFossil_Gauge_Gfx, sizeof(sDigFossil_Gauge_Gfx), 544);

    LoadPalette(sDigFossil_BackGround_Pal, BG_PLTT_ID(0), PLTT_SIZE_4BPP * 3);
    LoadPalette(sDigFossil_Gauge_Pal, BG_PLTT_ID(13), PLTT_SIZE_4BPP);

    _touchButtonInitialize();
    _randomBuildup();
    _buildupBGDraw();

    _setCellActor();
    // _gaugeDisp();

    CopyBgTilemapBufferToVram(2);
    CopyBgTilemapBufferToVram(1);
    CopyBgTilemapBufferToVram(3);
    SetGpuReg(REG_OFFSET_BLDY, 0);
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_1D_MAP | DISPCNT_OBJ_ON);
    ShowBg(0);
    ShowBg(1);
    ShowBg(2);
    ShowBg(3);
}

static void VBlankCB_DigFossil(void)
{
    LoadOam();
    _shakeProcessVBlank();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void CB2_DigFossilGame(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

static void Task_CloseDigFossil(u8 taskId)
{
    SetMainCallback2(gMain.savedCallback);
    FreeAllWindowBuffers();
    FREE_AND_SET_NULL(sFossilGameData);
    DestroyTask(taskId);
}

static void Task_DigFossil(u8 taskId)
{
    switch (sFossilGameData->seq)
    {
        case _SEQ_FIELD_FADEOUT:
            if (gPaletteFade.active)
                return;

            SetVBlankCallback(NULL);
            FreeAllWindowBuffers();
            ResetOtherVideoRegisters();
            ResetBgsAndClearDma3BusyFlags(0);
            ResetPaletteFade();
            sFossilGameData->seq++;
            break;
        case _SEQ_GAME_INIT1:
            FossilGame_Initialize1();
            sFossilGameData->seq++;
            break;
        case _SEQ_GAME_INIT2:
            FossilGame_Initialize2();
            sFossilGameData->seq++;
            break;
        case _SEQ_GAME_FADE_IN:
            BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
            SetMainCallback2(CB2_DigFossilGame);
            SetVBlankCallback(VBlankCB_DigFossil);
            sFossilGameData->seq++;
            break;
        case _SEQ_GAME_FADE_IN_WAIT:
            if (!gPaletteFade.active)
                sFossilGameData->seq = _SEQ_MESSAGE;
            break;
        case _SEQ_MESSAGE:
            ConvertIntToDecimalStringN(gStringVar1, sFossilGameData->_PARTS_TREASURE_NUM, STR_CONV_MODE_LEFT_ALIGN, 1);
            StringExpandPlaceholders(gStringVar4, gText_FossilStartMessage);
            FossilGame_AddTextPrinterForMessage(gStringVar4);
            sFossilGameData->seq++;
            break;
        case _SEQ_MESSAGE_WAIT:
            if (RunTextPrintersAndIsPrinter0Active() != TRUE)
            {
                ClearDialogWindowAndFrame(0, TRUE);
                if (UnderGroundIsFirstFossil())
                    sFossilGameData->seq++;
                else
                    sFossilGameData->seq = _SEQ_GAME;
            }
            break;
        case _SEQ_MESSAGE_FIRST:
            FossilGame_AddTextPrinterForMessage(gText_FossilFirstMessage);
            sFossilGameData->seq++;
            break;
        case _SEQ_MESSAGE_FIRST_WAIT:
            if (RunTextPrintersAndIsPrinter0Active())
                return;
            ClearDialogWindowAndFrame(0, TRUE);
            sFossilGameData->seq = _SEQ_GAME;
            break;
        case _SEQ_GAME:
            #if DIG_FOSSIL_DEBUG == 1
            if (JOY_HELD(B_BUTTON))
            {
                HideBg(1);
            }
            else
                ShowBg(1);
            #endif
            _gameProcess();
            _shakeProcess();
            _partsDigColor();
            break;
        case _SEQ_SUCCESS_WAIT:
            _partsDigColor();
            sFossilGameData->timer--;
            if(sFossilGameData->timer==0)
            {
                // Snd_SePlay(UG_SE_FOSSIL_CLEAR);
                FossilGame_AddTextPrinterForMessage(gText_FossilFoundAll);
                sFossilGameData->seq = _SEQ_KEY_WAIT;
            }
            break;
        case _SEQ_KEY_WAIT:
            if (RunTextPrintersAndIsPrinter0Active())
                return;
            sFossilGameData->seq = _SEQ_RESULT_MSG;
            break;
        case _SEQ_RESULT_MSG:
            if (_fossilGetMessage())
                sFossilGameData->seq = _SEQ_KEY_WAIT2;
            else
            {
                BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
                sFossilGameData->seq = _SEQ_FAINALIZE;
            }
            break;
        case _SEQ_KEY_WAIT2:
            if (RunTextPrintersAndIsPrinter0Active())
                return;
            sFossilGameData->seq = _SEQ_RESULT_MSG;
            break;
        case _SEQ_QUAKE:
            sFossilGameData->shakeCount = 1;
            sFossilGameData->timer--;
            if (sFossilGameData->timer == 0)
            {
                sFossilGameData->shakeCount = 100;
                BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
                sFossilGameData->seq = _SEQ_WIPE;
            }
            _shakeProcess();
            break;
        case _SEQ_WIPE:
            if (!gPaletteFade.active)
            {
                PlaySE(SE_M_ROCK_THROW);
                CpuFill16(0, GetBgTilemapBuffer(1), BG_SCREEN_SIZE);
                CpuFill16(0, GetBgTilemapBuffer(2), BG_SCREEN_SIZE);
                CpuFill16(0, GetBgTilemapBuffer(3), BG_SCREEN_SIZE);
                CopyBgTilemapBufferToVram(1);
                CopyBgTilemapBufferToVram(2);
                CopyBgTilemapBufferToVram(3);
                ResetSpriteData();
                sFossilGameData->seq = _SEQ_WIPE_CHANGE;
            }
            break;
        case _SEQ_WIPE_CHANGE:
            BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
            sFossilGameData->seq++;
            break;
        case _SEQ_WIPE_CHANGE2:
            if (!gPaletteFade.active)
            {
                FossilGame_AddTextPrinterForMessage(gText_FossilFail);
                sFossilGameData->seq = _SEQ_KEY_WAIT;
            }
            break;
        case _SEQ_FAINALIZE:
            if (!gPaletteFade.active)
                gTasks[taskId].func = Task_CloseDigFossil;
            break;
        default:
            break;
    }
}

static void _gaugeDisp(void)
{
    int gauge = sFossilGameData->digGauge;
    int changeBlock, i;
    u16 *pScrAddr = GetBgTilemapBuffer(2);
    u16 *pScrAddr2 = GetBgTilemapBuffer(3);
    int pattern;

    gauge = (gauge / 4) * 4; // gaugeは４の倍数
    pattern = 5 - (gauge % 24) / 4;

    gauge = gauge + 8;

    changeBlock = ((26 * 8) - gauge) / 8;

    for (i = 0; i < changeBlock; i++)
    {
        pScrAddr2[23 - i] = (2 << 12) + 0x0b - (i % 3);
        pScrAddr2[55 - i] = (2 << 12) + 0x41 - (i % 3);
        pScrAddr2[87 - i] = (2 << 12) + 0x77 - (i % 3);
        pScrAddr2[119 - i] = (2 << 12) + 0xad - (i % 3);

        pScrAddr[23 - i] = 0;
        pScrAddr[55 - i] = 0;
        pScrAddr[87 - i] = 0;
        pScrAddr[119 - i] = 0;
    }

    {
        i -= 1;
        for (int j = 0; j < 3; j++)
        {
            u16 toadd = j  + (pattern * 16) + 545;
            
            pScrAddr[21 + j - i] = (13 << 12) + toadd;
            pScrAddr[53 + j - i] = (13 << 12) + toadd + 4;
            pScrAddr[85 + j - i] = (13 << 12) + toadd + 8;
            pScrAddr[117 + j - i] = (13 << 12) + toadd + 12;
        }
    }
    
    CopyBgTilemapBufferToVram(3);
    CopyBgTilemapBufferToVram(2);
}

static bool8 _isFossil(int x, int y)
{
    int type;
    int idx = sFossilGameData->depositMap[y][x];
    if (idx == 0)
    {
        return FALSE;
    }
    type = sFossilGameData->aDeposit[idx - 1].partsType;
    if ((type != DIG_PARTS_NONE) && (type < DIG_PARTS_TREASURE_MAX))
    {
        return TRUE;
    }
    return FALSE;
}

static bool8 _isHardStone(int x, int y)
{
    int idx = sFossilGameData->depositMap[y][x];
    if (idx == 0)
    {
        return FALSE;
    }
    if (sFossilGameData->aDeposit[idx - 1].partsType >= DIG_PARTS_TREASURE_MAX) // 硬い石
    {
        return TRUE;
    }
    return FALSE;
}

static void _hammerStart(int x, int y, bool8 bPic, bool8 bHard, bool8 bFossil)
{
    if (bPic)
    {
        StartSpriteAnim(sFossilGameData->spriteWork[_CLACT_HUMMER], 0);
    }
    else
    {
        StartSpriteAnim(sFossilGameData->spriteWork[_CLACT_HUMMER], 1);
    }

    if (bHard)
    {
        StartSpriteAnim(sFossilGameData->spriteWork[_CLACT_HIT_HARD], 2);
        PlaySE(SE_PIN);
        sFossilGameData->spriteWork[_CLACT_HIT_HARD]->x = x + 8;
        sFossilGameData->spriteWork[_CLACT_HIT_HARD]->y = y + 8;
    }
    else if (bPic)
    {
        StartSpriteAnim(sFossilGameData->spriteWork[_CLACT_HIT_BIG_0], 3);
        StartSpriteAnim(sFossilGameData->spriteWork[_CLACT_HIT_BIG_1], 3);
        StartSpriteAnim(sFossilGameData->spriteWork[_CLACT_HIT_BIG_2], 3);
        StartSpriteAnim(sFossilGameData->spriteWork[_CLACT_HIT_BIG_3], 3);
        sFossilGameData->spriteWork[_CLACT_HIT_BIG_0]->x = x + 8;
        sFossilGameData->spriteWork[_CLACT_HIT_BIG_0]->y = y + 8;
        PlaySE(SE_CLICK);
    }
    else
    {
        StartSpriteAnim(sFossilGameData->spriteWork[_CLACT_HIT_BIG_0], 4);
        StartSpriteAnim(sFossilGameData->spriteWork[_CLACT_HIT_BIG_1], 4);
        StartSpriteAnim(sFossilGameData->spriteWork[_CLACT_HIT_BIG_2], 4);
        StartSpriteAnim(sFossilGameData->spriteWork[_CLACT_HIT_BIG_3], 4);
        sFossilGameData->spriteWork[_CLACT_HIT_BIG_0]->x = x + 8;
        sFossilGameData->spriteWork[_CLACT_HIT_BIG_0]->y = y + 8;
        PlaySE(SE_UNLOCK);
    }

    sFossilGameData->spriteWork[_CLACT_HUMMER]->x = x + 8;
    sFossilGameData->spriteWork[_CLACT_HUMMER]->y = y + 8;

    if (bFossil)
    {
        StartSpriteAnim(sFossilGameData->spriteWork[_CLACT_KIRA_SINGLE], 5);
        sFossilGameData->spriteWork[_CLACT_KIRA_SINGLE]->x = x + 16;
        sFossilGameData->spriteWork[_CLACT_KIRA_SINGLE]->y = y + 16;
    }
}

static void _digWall(int mapX, int mapY, bool8 bPic)
{
    static const s8 ham1X[] = {1, -1, -1, 1}; // ハンマー一回掘り
    static const s8 ham1Y[] = {1, -1, 1, -1};
    static const s8 picX[] = {0, 0, -1, 1}; // ハンマーなら２回ほれる
    static const s8 picY[] = {1, -1, 0, 0};
    int i;
    bool8 bHard = FALSE, bFossil = FALSE;

    if ((mapX < 0) || (mapX >= FOSSIL_MAP_WIDTH) || (mapY < 0) || (mapY >= FOSSIL_MAP_HEIGHT))
    {
        return;
    }
    if (sFossilGameData->buildupMap[mapY][mapX] != 0)
    {
        sFossilGameData->buildupMap[mapY][mapX] -= 1;
    }
    if (sFossilGameData->buildupMap[mapY][mapX] != 0)
    {
        sFossilGameData->buildupMap[mapY][mapX] -= 1;
    }
    if (_isHardStone(mapX, mapY) && (sFossilGameData->buildupMap[mapY][mapX] == 0))
    {
        bHard = TRUE;
    }
    if (_isFossil(mapX, mapY) && (sFossilGameData->buildupMap[mapY][mapX] == 0))
    {
        bFossil = TRUE;
        sFossilGameData->kiraTimer = 15;
    }
    _hammerStart(mapX * 16, (mapY + 2) * 16, bPic, bHard, bFossil);
    if (bHard)
    {
        return;
    }
    if (!bPic)
    {
        for (i = 0; i < 4; i++)
        {
            int cy = mapY + ham1Y[i];
            int cx = mapX + ham1X[i];
            if ((cy >= 0) && (cy < FOSSIL_MAP_HEIGHT))
            {
                if ((cx >= 0) && (cx < FOSSIL_MAP_WIDTH))
                {
                    if (sFossilGameData->buildupMap[cy][cx] != 0)
                    {
                        sFossilGameData->buildupMap[cy][cx] -= 1;
                    }
                }
            }
        }
    }
    for (i = 0; i < 4; i++)
    {
        int cy = mapY + picY[i];
        int cx = mapX + picX[i];
        if ((cy >= 0) && (cy < FOSSIL_MAP_HEIGHT))
        {
            if ((cx >= 0) && (cx < FOSSIL_MAP_WIDTH))
            {
                if (sFossilGameData->buildupMap[cy][cx] != 0)
                {
                    sFossilGameData->buildupMap[cy][cx] -= 1;
                }
                if (!bPic)
                {
                    if (sFossilGameData->buildupMap[cy][cx] != 0)
                    {
                        sFossilGameData->buildupMap[cy][cx] -= 1;
                    }
                }
            }
        }
    }
}

static bool8 _treasureCheck(void)
{
    int y, x, i;
    bool8 bTreasure[_PARTS_TREASURE_NUM_MAX];
    bool8 bRet = TRUE;

    for (i = 0; i < sFossilGameData->_PARTS_TREASURE_NUM; i++)
    {
        bTreasure[i] = TRUE;
    }
    for (y = 0; y < FOSSIL_MAP_HEIGHT; y++)
    {
        for (x = 0; x < FOSSIL_MAP_WIDTH; x++)
        {
            i = sFossilGameData->depositMap[y][x];
            if ((i <= sFossilGameData->_PARTS_TREASURE_NUM) && (i != 0))
            {
                if (sFossilGameData->buildupMap[y][x] != 0)
                {
                    bTreasure[i - 1] = FALSE;
                }
            }
        }
    }

    for (i = 0; i < sFossilGameData->_PARTS_TREASURE_NUM; i++)
    {
        if (!bTreasure[i])
        {
            bRet = FALSE;
        }
        else if (sFossilGameData->aDeposit[i].bGetItem == FALSE)
        {
            sFossilGameData->digTimer[i] = 1;
            sFossilGameData->aDeposit[i].bGetItem = TRUE;
        }
    }
    return bRet;
}

static bool8 _gameProcess(void)
{
    int cost;

    if(sFossilGameData->touchPanelRelease == 1)
        sFossilGameData->touchPanelRelease = 0;
    
    // A按键延迟
    if (sFossilGameData->delay)
    {
        sFossilGameData->delay--;
        return FALSE;
    }

    if (JOY_NEW(DPAD_LEFT))
    {
        if (sFossilGameData->touchX == 0)
            sFossilGameData->touchX = FOSSIL_MAP_WIDTH - 1;
        else
            sFossilGameData->touchX--;
    }
    else if(JOY_NEW(DPAD_RIGHT))
    {
        if (sFossilGameData->touchX == FOSSIL_MAP_WIDTH - 1)
            sFossilGameData->touchX = 0;
        else
            sFossilGameData->touchX++;
    }
    else if(JOY_NEW(DPAD_UP))
    {
        if (sFossilGameData->touchY == 0)
            sFossilGameData->touchY = FOSSIL_MAP_HEIGHT - 1;
        else
            sFossilGameData->touchY--;
    }
    else if(JOY_NEW(DPAD_DOWN))
    {
        if (sFossilGameData->touchY == FOSSIL_MAP_HEIGHT - 1)
            sFossilGameData->touchY = 0;
        else
            sFossilGameData->touchY++;
    }
    else if (JOY_NEW(A_BUTTON))
    {
        s16 tp_x = sFossilGameData->touchX;
        s16 tp_y = sFossilGameData->touchY;
        {
            _digWall(tp_x, tp_y, sFossilGameData->bPic);
            if (sFossilGameData->bPic)
            {
                cost = _COST_DIG_PIC;
            }
            else
            {
                cost = _COST_DIG_HUMMER;
            }
            if (sFossilGameData->digGauge > cost)
            {
                sFossilGameData->digGauge -= cost;
            }
            else
            {
                sFossilGameData->digGauge = 0;
            }
            _buildupBGDraw();
            _gaugeDisp();
            sFossilGameData->shakeCount = 1;
        }
        sFossilGameData->delay = 1;
    }
    else if (JOY_NEW(L_BUTTON) && sFossilGameData->touchButton != _HUMMER_BUTTON)
    {
        sFossilGameData->touchButton = _HUMMER_BUTTON;
        sFossilGameData->touchPanelRelease = 2;
        sFossilGameData->bPic = FALSE;
    }
    else if (JOY_NEW(R_BUTTON) && sFossilGameData->touchButton != _PIC_BUTTON)
    {
        sFossilGameData->touchButton = _PIC_BUTTON;
        sFossilGameData->touchPanelRelease = 2;
        sFossilGameData->bPic = TRUE;
    }

    if (sFossilGameData->kiraTimer)
    {
        sFossilGameData->kiraTimer--;
        if (sFossilGameData->kiraTimer == 0)
        {
            PlaySE(SE_EXP_MAX);
        }
    }

    _touchButtonProcess(sFossilGameData->touchPanelRelease);
    if(sFossilGameData->touchPanelRelease >= 2)
        sFossilGameData->touchPanelRelease++;
    
    if (_treasureCheck())
    {
        UnderGroundSetFirstFossil(); // 非第一次挖掘
        sFossilGameData->seq = _SEQ_SUCCESS_WAIT;
        sFossilGameData->timer = 25;
        sFossilGameData->bSuccess = TRUE;
        return TRUE;
    }
    else if ((sFossilGameData->digGauge <= 8)) // 墙壁坍塌
    {
        sFossilGameData->digGauge = 0;
        UnderGroundSetFirstFossil(); // 非第一次挖掘
        sFossilGameData->bSuccess = FALSE;
        sFossilGameData->timer = 45;
        sFossilGameData->seq = _SEQ_QUAKE;
        return TRUE;
    }
    return FALSE;
}

static void _shakeProcess(void)
{
    int num, wave;

    if (sFossilGameData->shakeCount == 0)
    {
        return;
    }
    // 震感随着挖掘次数增强
    num = ((_DIG_GAUGE_START - sFossilGameData->digGauge) / 10);
    wave = ((_DIG_GAUGE_START - sFossilGameData->digGauge) / 25);

    sFossilGameData->shakeCount++;
    if (sFossilGameData->shakeCount > num)
    {
        sFossilGameData->shakeX = sFossilGameData->shakeZ = 0;
    }
    else
    {
        sFossilGameData->shakeX = MATH_Rand32(&sFossilGameData->sRand, 3 + wave) - (3 + wave) / 2;
        sFossilGameData->shakeZ = MATH_Rand32(&sFossilGameData->sRand, 3 + wave) - (3 + wave) / 2;
    }
    
}

static void _shakeProcessVBlank(void)
{
    int i, num;

    if (sFossilGameData->shakeCount == 0)
    {
        return;
    }
    num = ((_DIG_GAUGE_START - sFossilGameData->digGauge) / 10);

    if (sFossilGameData->shakeCount > num)
    {
        sFossilGameData->shakeCount = 0;
    }
    for (i = 0; i < 3; i++)
    {
        ChangeBgX(i + 1, sFossilGameData->shakeX * 2, BG_COORD_SET);
        ChangeBgY(i + 1, sFossilGameData->shakeZ * 2, BG_COORD_SET);
    }
}

// 随机数生成
static void CommRandSeedInitialize(MATHRandContext32 *pRand)
{
    u64 randSeed = 0;
    struct SiiRtcInfo rtc;
    u8 year, month, day;

    RtcCalcLocalTime();
    RtcGetInfo(&rtc);

    year = ConvertBcdToBinary(rtc.year);
    month = ConvertBcdToBinary(rtc.month);
    day = ConvertBcdToBinary(rtc.day);

    randSeed = (((((((u64)year * 16ULL + month) * 32ULL) + day) * 32ULL + gLocalTime.hours) * 64ULL + gLocalTime.minutes) * 64ULL + (gLocalTime.seconds + gMain.vblankCounter1));
    MATH_InitRand32(pRand, randSeed);
}

//--------------------------------------------------------------
/**
 * 修改bg指定范围的tilemap
 */
//--------------------------------------------------------------
static void _scrDataChange(u16 *pScrTop, const u8 *data, int changeNum, int plusNum)
{
    int scr, y, x, pos, i;
    _SCR_RECT* pRect = (_SCR_RECT*)data;

    for (y = pRect->lt_y, i = 0; y < pRect->rb_y; y++, i++)
    {
        pos = plusNum * i + changeNum;
        for (x = pRect->lt_x; x < pRect->rb_x; x++)
        {
            scr = x + (y * 32);
            pScrTop[scr] = (pScrTop[scr] & 0xfc00) + pos;
            pos++;
        }
    }
}

static const u8 hummerPos[] = {24, 4, 30, 12};
static const u8 picPos[] = {24, 12, 30, 20};
static const u8 endPos[] = {24, 0, 30, 4};

static void _touchButtonInitialize(void)
{
    u16* pScrAddr;

    sFossilGameData->touchButton = _PIC_BUTTON;
    sFossilGameData->bPic = TRUE;
    pScrAddr = GetBgTilemapBuffer(2);
    _scrDataChange(pScrAddr, picPos, 48, 54);
}

static void _touchButtonProcess(int level)
{
    u16 *pScrAddr;

    if (level < _PUSH_START)
    {
        return;
    }

    pScrAddr = GetBgTilemapBuffer(2);
    switch (sFossilGameData->touchButton)
    {
    case _HUMMER_BUTTON:
        if (_PUSH_START == level)
        {
            _scrDataChange(pScrAddr, hummerPos, 24, 54); // level1
            _scrDataChange(pScrAddr, picPos, 36, 54);    // 戻す絵
            PlaySE(SE_SELECT);
        }
        else if (_PUSH_START + 1 == level)
        {
            _scrDataChange(pScrAddr, hummerPos, 30, 54); // 押した絵
        }
        if (_PUSH_START == level)
        {
            StartSpriteAnim(sFossilGameData->spriteWork[_CLACT_EFFECT], 6);
            sFossilGameData->spriteWork[_CLACT_EFFECT]->x = 199;
            sFossilGameData->spriteWork[_CLACT_EFFECT]->y = 48;
        }
        break;
    case _PIC_BUTTON:
        if (_PUSH_START == level)
        {
            _scrDataChange(pScrAddr, hummerPos, 18, 54); // 戻す絵
            _scrDataChange(pScrAddr, picPos, 42, 54);    // 押す絵
            PlaySE(SE_SELECT);
        }
        else if (_PUSH_START + 1 == level)
        {
            _scrDataChange(pScrAddr, picPos, 48, 54); // 押した絵
        }
        if (_PUSH_START == level)
        {
            StartSpriteAnim(sFossilGameData->spriteWork[_CLACT_EFFECT], 7);
            sFossilGameData->spriteWork[_CLACT_EFFECT]->x = 199;
            sFossilGameData->spriteWork[_CLACT_EFFECT]->y = 110;
        }
        break;
    }
    CopyBgTilemapBufferToVram(2);
}

static const u8 _palPattern[] = {32, 0xfe, 64, 0xfe, 32, 0xfe, 0, 0xfe, 32, 0xfe, 64, 0xfe, 32, 0xfe, 0, 0xff};

static void _partsDigColor(void)
{
    int i, x, y, j;

    // 掘りはじめにSEとアニメを設定
    for (i = 0; i < _PARTS_TREASURE_NUM_MAX; i++)
    {
        if (sFossilGameData->digTimer[i] == 1)
        {
            PlaySE(SE_SHINY);
            for (j = 0; j < 3; j++)
            {
                x = MATH_Rand32(&sFossilGameData->sRand, sFossilGameData->aDeposit[i].pParts->width * 8);
                y = MATH_Rand32(&sFossilGameData->sRand, sFossilGameData->aDeposit[i].pParts->height * 8);
                x += sFossilGameData->aDeposit[i].x * 2 * 8;
                y += sFossilGameData->aDeposit[i].y * 2 * 8;
                y += 8 * 4;

                StartSpriteAnim(sFossilGameData->spriteWork[_CLACT_KIRA_P1 + j], 8 + j);
                sFossilGameData->spriteWork[_CLACT_KIRA_P1 + j]->x = x + 8;
                sFossilGameData->spriteWork[_CLACT_KIRA_P1 + j]->y = y + 8;
            }
        }
    }

    for (i = 0; i < _PARTS_TREASURE_NUM_MAX; i++)
    {
        if (sFossilGameData->digTimer[i])
        {
            const u16 *pPal = sFossilGameData->palData[i];
            u8 pattern = _palPattern[sFossilGameData->digTimer[i] - 1];
            if (pattern == 0xff)
            {
                sFossilGameData->digTimer[i] = 0;
                continue;
            }
            sFossilGameData->digTimer[i]++;
            if (pattern == 0xfe)
            {
                continue;
            }
            LoadPalette(&pPal[pattern], BG_PLTT_ID(i + _PALLET_INDEX), 32);
        }
    }
}

static void FossilGame_AddTextPrinterForMessage(const u8* message)
{
    DrawDialogueFrame(0, TRUE);
    gTextFlags.canABSpeedUpPrint = TRUE;
    AddTextPrinterParameterized2(0, FONT_NORMAL, message, GetPlayerTextSpeedDelay(), NULL, TEXT_COLOR_DARK_GRAY, TEXT_COLOR_WHITE, TEXT_COLOR_LIGHT_GRAY);
}

bool8 CommDigIsStone(int type)
{
    if((type != STONE_TYPE_NONE) && (type < DIG_PARTS_TREASURE_MIN)){
        return TRUE;
    }
    return FALSE;
}

static int _calcDigStoneCarat(int no)
{
    int carat = 0;
    int stone = no;

    if (CommDigIsStone(stone))
    {
        if ((stone == DIG_PARTS_KONGOU_L) || (stone == DIG_PARTS_SIRATAMA_L) ||
            (stone == DIG_PARTS_KONGOU_S) || (stone == DIG_PARTS_SIRATAMA_S))
        {
            carat = MATH_Rand32(&sFossilGameData->sRand, 1) + 1;
        }
        else
        {
            carat = MATH_Rand32(&sFossilGameData->sRand, 4) + 1;
        }
        if ((stone == DIG_PARTS_KONGOU_L) || (stone == DIG_PARTS_SIRATAMA_L) ||
            (stone == DIG_PARTS_RED_L) || (stone == DIG_PARTS_BLUE_L) || (stone == DIG_PARTS_GREEN_L))
        {
            stone = stone - DIG_PARTS_KONGOU_L + STONE_TYPE_DIAMOND;
            carat += 10;
        }
        carat += sFossilGameData->digGauge / (_DIG_GAUGE_START / 5);
        if (sFossilGameData->digGauge != 0)
        {
            carat += 5;
        }
    }
    return carat;
}

static bool8 _fossilGetMessage(void)
{
    int i;

    for (i = 0; i < sFossilGameData->_PARTS_TREASURE_NUM; i++)
    {
        if (sFossilGameData->aDeposit[i].bGetItem == TRUE)
        {
            u16 item = gFossilTypeToItemIndex[sFossilGameData->aDeposit[i].partsType];
            int digCarat = _calcDigStoneCarat(sFossilGameData->aDeposit[i].partsType);

            sFossilGameData->aDeposit[i].bGetItem = FALSE;
            sFossilGameData->digCarat = digCarat;
            
            if (CommDigIsStone(sFossilGameData->aDeposit[i].partsType))
            {
                StringCopy(gStringVar1, gItemsInfo[item].name);
                ConvertIntToDecimalStringN(gStringVar2, sFossilGameData->digCarat, STR_CONV_MODE_LEFT_ALIGN, 2);
                StringExpandPlaceholders(gStringVar4, gText_GetTreasure);
                // 玉的获取代码
                // 
            }
            else
            {
                StringCopy(gStringVar1, gItemsInfo[item].name);
                StringExpandPlaceholders(gStringVar4, gText_GameGetItem);
                AddBagItem(item, 1);
            }
            FossilGame_AddTextPrinterForMessage(gStringVar4);
            return TRUE;
        }
    }
    return FALSE;
}