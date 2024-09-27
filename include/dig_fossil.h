#ifndef GUARD_DIG_FOSSIL_H
#define GUARD_DIG_FOSSIL_H

// ほれる石の種類

#define STONE_TYPE_NONE (0)
#define STONE_TYPE_DIAMOND (1) //  こんごうだま
#define STONE_TYPE_PEARL (2)   //  ましろだま
#define STONE_TYPE_RED (3)     //  あかいいし
#define STONE_TYPE_BLUE (4)    //  あおいいし
#define STONE_TYPE_GREEN (5)   //  みどりのいし
#define STONE_TYPE_MAX (6)

// 埋める種類
#define DIG_PARTS_NONE (STONE_TYPE_NONE)
#define DIG_PARTS_KONGOU_S (STONE_TYPE_DIAMOND) // こんごうだま	KASEKI_KONGOU_S
#define DIG_PARTS_SIRATAMA_S (STONE_TYPE_PEARL) // しらたま	KASEKI_SIRATAMA_S
#define DIG_PARTS_RED_S (STONE_TYPE_RED)        // 赤いタマ
#define DIG_PARTS_BLUE_S (STONE_TYPE_BLUE)      // 青いタマ
#define DIG_PARTS_GREEN_S (STONE_TYPE_GREEN)    // 緑のタマ
#define DIG_PARTS_KONGOU_L (6)                  // だいこんごうだま	KASEKI_KONGOU_L
#define DIG_PARTS_SIRATAMA_L (7)                // だいしらたま	KASEKI_SIRATAMA_L
#define DIG_PARTS_RED_L (8)                     // だいこんごうだま	KASEKI_KONGOU_L
#define DIG_PARTS_BLUE_L (9)                    // だいこんごうだま	KASEKI_KONGOU_L
#define DIG_PARTS_GREEN_L (10)                  // だいしらたま	KASEKI_SIRATAMA_L
#define DIG_PARTS_TREASURE_MIN (11)
#define DIG_PARTS_CIRCLE (DIG_PARTS_TREASURE_MIN) // まんまる	KASEKI_
#define DIG_PARTS_KEYSTONE (12)                   // かなめ	KASEKI_
#define DIG_PARTS_SUN (13)                        // たいようのいし	KASEKI_SUN
#define DIG_PARTS_STAR (14)                       // ほしのかけら	KASEKI_STAR
#define DIG_PARTS_MOON (15)                       // つきのいし	KASEKI_MOON
#define DIG_PARTS_HARD (16)                       // かたいいし	KASEKI_HARD
#define DIG_PARTS_KAMINARI (17)                   // かみなりのいし	KASEKI_KAMINARI
#define DIG_PARTS_KAWARAZU (18)                   // かわらずのいし	KASEKI_KAWARAZU
#define DIG_PARTS_HONOO (19)                      // ほのおのいし	KASEKI_HONOO
#define DIG_PARTS_MIZU (20)                       // みずのいし	KASEKI_MIZU
#define DIG_PARTS_REAF (21)                       // リーフのいし	KASEKI_REAF
#define DIG_PARTS_GOLD (22)                       // きんのたま	KASEKI_GOLD
#define DIG_PARTS_KAI (23)                        // かいのカセキ	KASEKI_KAI
#define DIG_PARTS_KOURA (24)                      // こうらのカセキ	KASEKI_KOURA
#define DIG_PARTS_TSUME (25)                      // ツメのカセキ	KASEKI_TSUME
#define DIG_PARTS_NEKKO (26)                      // ねっこのカセキ	KASEKI_NEKKO
#define DIG_PARTS_KOHAKU (27)                     // ひみつのコハク	KASEKI_KOHAKU
#define DIG_PARTS_BONE (28)                       // ふといほね	KASEKI_BONE
#define DIG_PARTS_GENKI_S (29)                    // 元気のかけら
#define DIG_PARTS_GENKI_L (30)                    // げんきのかたまり
#define DIG_PARTS_PLA_RED (31)                    // あかいかけら
#define DIG_PARTS_PLA_BLUE (32)                   // あおいかけら
#define DIG_PARTS_PLA_YELLOW (33)                 // きいろいかけら
#define DIG_PARTS_PLA_GREEN (34)                  // みどりのかけら
#define DIG_PARTS_HEART (35)                      // ハートのウロコ
#define DIG_PARTS_SHIELD (36)                     // たてのカセキ
#define DIG_PARTS_ZUGAI (37)                      // ずがいのカセキ
#define DIG_PARTS_CRAY (38)                       // ひかりのねんど
#define DIG_PARTS_IRONBALL (39)                   // くろいてっきゅう
#define DIG_PARTS_COLD (40)                       // つめたいいわ
#define DIG_PARTS_SARA (41)                       // さらさらいわ
#define DIG_PARTS_HEAT (42)                       // あついいわ
#define DIG_PARTS_WET (43)                        // しめったいわ
#define DIG_PARTS_PLATE_FIRE (44)                 // ひのたまプレート
#define DIG_PARTS_PLATE_WATER (45)                // しずくプレート
#define DIG_PARTS_PLATE_THUNDER (46)              // いかづちプレート
#define DIG_PARTS_PLATE_GREEN (47)                // みどりのプレート
#define DIG_PARTS_PLATE_ICICLE (48)               // つららのプレート
#define DIG_PARTS_PLATE_KNUCKLE (49)              // こぶしのプレート
#define DIG_PARTS_PLATE_POISON (50)               // もうどくプレート
#define DIG_PARTS_PLATE_GROUND (51)               // だいちのプレート
#define DIG_PARTS_PLATE_SKY (52)                  // あおぞらプレート
#define DIG_PARTS_PLATE_WONDER (53)               // ふしぎのプレート
#define DIG_PARTS_PLATE_IRIDESCENCE (54)          // たまむしプレート
#define DIG_PARTS_PLATE_ROCK (55)                 // がんせきプレート
#define DIG_PARTS_PLATE_GHOST (56)                // もののけプレート
#define DIG_PARTS_PLATE_DRAGON (57)               // りゅうのプレート
#define DIG_PARTS_PLATE_DARK (58)                 // こわもてプレート
#define DIG_PARTS_PLATE_IRON (59)                 // こうてつプレート

#define DIG_PARTS_TREASURE_MAX (60)

#define DIG_PARTS_NODIG1 (DIG_PARTS_TREASURE_MAX)                         // 掘れない岩	kaseki_iwa01	面積が４マス	棒形の真っ黒の石
#define DIG_PARTS_NODIG2 (DIG_PARTS_TREASURE_MAX + 1)                     // 掘れない岩	kaseki_iwa02	面積が４マス	四角型の真っ黒の石
#define DIG_PARTS_NODIG3 (DIG_PARTS_TREASURE_MAX + 2)                     // 掘れない岩	kaseki_iwa03	面積が４マス	T型の真っ黒の石
#define DIG_PARTS_NODIG4 (DIG_PARTS_TREASURE_MAX + 3)                     // 掘れない岩	kaseki_iwa04	面積が４マス	Z型の真っ黒の石
#define DIG_PARTS_NODIG5 (DIG_PARTS_TREASURE_MAX + 4)                     // 掘れない岩	kaseki_iwa05	面積が４マス	S型の真っ黒の石
#define DIG_PARTS_NODIG6 (DIG_PARTS_TREASURE_MAX + 5)                     // 掘れない岩	kaseki_iwa06	面積が９マス	四角型の真っ黒の石
#define DIG_PARTS_NODIG7 (DIG_PARTS_TREASURE_MAX + 6)                     // 掘れない岩	kaseki_iwa07	面積が８マス	棒形の真っ黒の石

#define DIG_PARTS_MAX (DIG_PARTS_TREASURE_MAX + 7)

#define DIG_PARTS_TYPE_FOSSIL_MIN (DIG_PARTS_KAI)
#define DIG_PARTS_TYPE_FOSSIL_MAX (DIG_PARTS_BONE + 1)

typedef struct
{
    u64 x;
    u64 mul;
    u64 add;
} MATHRandContext32;

typedef struct
{
    u8 lt_x;
    u8 lt_y;
    u8 rb_x;
    u8 rb_y;
} _SCR_RECT;

enum
{
    _HUMMER_BUTTON,
    _PIC_BUTTON,
    _END_BUTTON,
};

#define _COST_DIG_HUMMER (8) /// 大锤损耗8
#define _COST_DIG_PIC (4)    /// 小锤损耗4

static inline bool8 UnderGroundIsFirstFossil(void)
{    
    return !FlagGet(FLAG_UNUSED_0x055);
}

static inline void UnderGroundSetFirstFossil(void)
{    
    FlagSet(FLAG_UNUSED_0x055);
}

static inline void MATH_InitRand32(MATHRandContext32 *context, u64 seed)
{
    context->x = seed;
    context->mul = (1566083941LL << 32) + 1812433253LL;
    context->add = 2531011;
}

static inline u32 MATH_Rand32(MATHRandContext32 *context, u32 max)
{
    context->x = context->mul * context->x + context->add;

    if (max == 0)
    {
        return (u32)(context->x >> 32);
    }
    else
    {
        return (u32)(((context->x >> 32) * max) >> 32);
    }
}

// 检查石板时候已经获得
static inline u32 FossilGetPlateBit(u8 type)
{
    return VarGet(VAR_UNUSED_0x404E) & (0x0001 << (type - DIG_PARTS_PLATE_FIRE));
}

// 设置已经获取石板的flag
static inline void FossilSetPlateBit(u8 type)
{
    u32 digBit = VarGet(VAR_UNUSED_0x404E);

    digBit |= (0x0001 << (type - DIG_PARTS_PLATE_FIRE));

    VarSet(VAR_UNUSED_0x404E, digBit);
}

void CB2_StartDigFossilGame(void);

#endif // GUARD_DIG_FOSSIL_H