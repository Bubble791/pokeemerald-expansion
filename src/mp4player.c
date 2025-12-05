#include "global.h"
#include "battle.h"
#include "title_screen.h"
#include "sprite.h"
#include "gba/m4a_internal.h"
#include "clear_save_data_menu.h"
#include "decompress.h"
#include "event_data.h"
#include "intro.h"
#include "m4a.h"
#include "main.h"
#include "main_menu.h"
#include "palette.h"
#include "reset_rtc_screen.h"
#include "berry_fix_program.h"
#include "sound.h"
#include "sprite.h"
#include "task.h"
#include "scanline_effect.h"
#include "gpu_regs.h"
#include "trig.h"
#include "graphics.h"
#include "constants/rgb.h"
#include "constants/songs.h"

static void Task_PrintMp4(u8 taskID);

static const u32 sTestGfx0[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0000.8bpp.lz");
static const u16 sTestPal0[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0000.gbapal");
static const u32 sTestGfx1[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0001.8bpp.lz");
static const u16 sTestPal1[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0001.gbapal");
static const u32 sTestGfx2[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0002.8bpp.lz");
static const u16 sTestPal2[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0002.gbapal");
static const u32 sTestGfx3[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0003.8bpp.lz");
static const u16 sTestPal3[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0003.gbapal");
static const u32 sTestGfx4[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0004.8bpp.lz");
static const u16 sTestPal4[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0004.gbapal");
static const u32 sTestGfx5[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0005.8bpp.lz");
static const u16 sTestPal5[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0005.gbapal");
static const u32 sTestGfx6[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0006.8bpp.lz");
static const u16 sTestPal6[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0006.gbapal");
static const u32 sTestGfx7[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0007.8bpp.lz");
static const u16 sTestPal7[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0007.gbapal");
static const u32 sTestGfx8[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0008.8bpp.lz");
static const u16 sTestPal8[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0008.gbapal");
static const u32 sTestGfx9[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0009.8bpp.lz");
static const u16 sTestPal9[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0009.gbapal");
static const u32 sTestGfx10[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0010.8bpp.lz");
static const u16 sTestPal10[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0010.gbapal");
static const u32 sTestGfx11[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0011.8bpp.lz");
static const u16 sTestPal11[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0011.gbapal");
static const u32 sTestGfx12[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0012.8bpp.lz");
static const u16 sTestPal12[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0012.gbapal");
static const u32 sTestGfx13[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0013.8bpp.lz");
static const u16 sTestPal13[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0013.gbapal");
static const u32 sTestGfx14[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0014.8bpp.lz");
static const u16 sTestPal14[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0014.gbapal");
static const u32 sTestGfx15[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0015.8bpp.lz");
static const u16 sTestPal15[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0015.gbapal");
static const u32 sTestGfx16[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0016.8bpp.lz");
static const u16 sTestPal16[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0016.gbapal");
static const u32 sTestGfx17[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0017.8bpp.lz");
static const u16 sTestPal17[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0017.gbapal");
static const u32 sTestGfx18[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0018.8bpp.lz");
static const u16 sTestPal18[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0018.gbapal");
static const u32 sTestGfx19[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0019.8bpp.lz");
static const u16 sTestPal19[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0019.gbapal");
static const u32 sTestGfx20[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0020.8bpp.lz");
static const u16 sTestPal20[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0020.gbapal");
static const u32 sTestGfx21[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0021.8bpp.lz");
static const u16 sTestPal21[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0021.gbapal");
static const u32 sTestGfx22[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0022.8bpp.lz");
static const u16 sTestPal22[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0022.gbapal");
static const u32 sTestGfx23[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0023.8bpp.lz");
static const u16 sTestPal23[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0023.gbapal");
static const u32 sTestGfx24[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0024.8bpp.lz");
static const u16 sTestPal24[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0024.gbapal");
static const u32 sTestGfx25[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0025.8bpp.lz");
static const u16 sTestPal25[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0025.gbapal");
static const u32 sTestGfx26[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0026.8bpp.lz");
static const u16 sTestPal26[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0026.gbapal");
static const u32 sTestGfx27[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0027.8bpp.lz");
static const u16 sTestPal27[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0027.gbapal");
static const u32 sTestGfx28[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0028.8bpp.lz");
static const u16 sTestPal28[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0028.gbapal");
static const u32 sTestGfx29[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0029.8bpp.lz");
static const u16 sTestPal29[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0029.gbapal");
static const u32 sTestGfx30[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0030.8bpp.lz");
static const u16 sTestPal30[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0030.gbapal");
static const u32 sTestGfx31[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0031.8bpp.lz");
static const u16 sTestPal31[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0031.gbapal");
static const u32 sTestGfx32[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0032.8bpp.lz");
static const u16 sTestPal32[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0032.gbapal");
static const u32 sTestGfx33[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0033.8bpp.lz");
static const u16 sTestPal33[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0033.gbapal");
static const u32 sTestGfx34[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0034.8bpp.lz");
static const u16 sTestPal34[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0034.gbapal");
static const u32 sTestGfx35[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0035.8bpp.lz");
static const u16 sTestPal35[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0035.gbapal");
static const u32 sTestGfx36[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0036.8bpp.lz");
static const u16 sTestPal36[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0036.gbapal");
static const u32 sTestGfx37[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0037.8bpp.lz");
static const u16 sTestPal37[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0037.gbapal");
static const u32 sTestGfx38[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0038.8bpp.lz");
static const u16 sTestPal38[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0038.gbapal");
static const u32 sTestGfx39[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0039.8bpp.lz");
static const u16 sTestPal39[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0039.gbapal");
static const u32 sTestGfx40[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0040.8bpp.lz");
static const u16 sTestPal40[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0040.gbapal");
static const u32 sTestGfx41[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0041.8bpp.lz");
static const u16 sTestPal41[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0041.gbapal");
static const u32 sTestGfx42[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0042.8bpp.lz");
static const u16 sTestPal42[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0042.gbapal");
static const u32 sTestGfx43[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0043.8bpp.lz");
static const u16 sTestPal43[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0043.gbapal");
static const u32 sTestGfx44[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0044.8bpp.lz");
static const u16 sTestPal44[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0044.gbapal");
static const u32 sTestGfx45[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0045.8bpp.lz");
static const u16 sTestPal45[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0045.gbapal");
static const u32 sTestGfx46[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0046.8bpp.lz");
static const u16 sTestPal46[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0046.gbapal");
static const u32 sTestGfx47[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0047.8bpp.lz");
static const u16 sTestPal47[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0047.gbapal");
static const u32 sTestGfx48[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0048.8bpp.lz");
static const u16 sTestPal48[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0048.gbapal");
static const u32 sTestGfx49[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0049.8bpp.lz");
static const u16 sTestPal49[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0049.gbapal");
static const u32 sTestGfx50[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0050.8bpp.lz");
static const u16 sTestPal50[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0050.gbapal");
static const u32 sTestGfx51[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0051.8bpp.lz");
static const u16 sTestPal51[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0051.gbapal");
static const u32 sTestGfx52[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0052.8bpp.lz");
static const u16 sTestPal52[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0052.gbapal");
static const u32 sTestGfx53[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0053.8bpp.lz");
static const u16 sTestPal53[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0053.gbapal");
static const u32 sTestGfx54[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0054.8bpp.lz");
static const u16 sTestPal54[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0054.gbapal");
static const u32 sTestGfx55[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0055.8bpp.lz");
static const u16 sTestPal55[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0055.gbapal");
static const u32 sTestGfx56[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0056.8bpp.lz");
static const u16 sTestPal56[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0056.gbapal");
static const u32 sTestGfx57[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0057.8bpp.lz");
static const u16 sTestPal57[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0057.gbapal");
static const u32 sTestGfx58[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0058.8bpp.lz");
static const u16 sTestPal58[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0058.gbapal");
static const u32 sTestGfx59[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0059.8bpp.lz");
static const u16 sTestPal59[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0059.gbapal");
static const u32 sTestGfx60[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0060.8bpp.lz");
static const u16 sTestPal60[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0060.gbapal");
static const u32 sTestGfx61[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0061.8bpp.lz");
static const u16 sTestPal61[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0061.gbapal");
static const u32 sTestGfx62[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0062.8bpp.lz");
static const u16 sTestPal62[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0062.gbapal");
static const u32 sTestGfx63[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0063.8bpp.lz");
static const u16 sTestPal63[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0063.gbapal");
static const u32 sTestGfx64[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0064.8bpp.lz");
static const u16 sTestPal64[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0064.gbapal");
static const u32 sTestGfx65[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0065.8bpp.lz");
static const u16 sTestPal65[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0065.gbapal");
static const u32 sTestGfx66[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0066.8bpp.lz");
static const u16 sTestPal66[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0066.gbapal");
static const u32 sTestGfx67[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0067.8bpp.lz");
static const u16 sTestPal67[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0067.gbapal");
static const u32 sTestGfx68[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0068.8bpp.lz");
static const u16 sTestPal68[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0068.gbapal");
static const u32 sTestGfx69[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0069.8bpp.lz");
static const u16 sTestPal69[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0069.gbapal");
static const u32 sTestGfx70[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0070.8bpp.lz");
static const u16 sTestPal70[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0070.gbapal");
static const u32 sTestGfx71[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0071.8bpp.lz");
static const u16 sTestPal71[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0071.gbapal");
static const u32 sTestGfx72[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0072.8bpp.lz");
static const u16 sTestPal72[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0072.gbapal");
static const u32 sTestGfx73[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0073.8bpp.lz");
static const u16 sTestPal73[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0073.gbapal");
static const u32 sTestGfx74[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0074.8bpp.lz");
static const u16 sTestPal74[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0074.gbapal");
static const u32 sTestGfx75[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0075.8bpp.lz");
static const u16 sTestPal75[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0075.gbapal");
static const u32 sTestGfx76[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0076.8bpp.lz");
static const u16 sTestPal76[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0076.gbapal");
static const u32 sTestGfx77[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0077.8bpp.lz");
static const u16 sTestPal77[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0077.gbapal");
static const u32 sTestGfx78[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0078.8bpp.lz");
static const u16 sTestPal78[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0078.gbapal");
static const u32 sTestGfx79[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0079.8bpp.lz");
static const u16 sTestPal79[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0079.gbapal");
static const u32 sTestGfx80[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0080.8bpp.lz");
static const u16 sTestPal80[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0080.gbapal");
static const u32 sTestGfx81[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0081.8bpp.lz");
static const u16 sTestPal81[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0081.gbapal");
static const u32 sTestGfx82[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0082.8bpp.lz");
static const u16 sTestPal82[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0082.gbapal");
static const u32 sTestGfx83[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0083.8bpp.lz");
static const u16 sTestPal83[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0083.gbapal");
static const u32 sTestGfx84[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0084.8bpp.lz");
static const u16 sTestPal84[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0084.gbapal");
static const u32 sTestGfx85[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0085.8bpp.lz");
static const u16 sTestPal85[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0085.gbapal");
static const u32 sTestGfx86[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0086.8bpp.lz");
static const u16 sTestPal86[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0086.gbapal");
static const u32 sTestGfx87[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0087.8bpp.lz");
static const u16 sTestPal87[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0087.gbapal");
static const u32 sTestGfx88[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0088.8bpp.lz");
static const u16 sTestPal88[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0088.gbapal");
static const u32 sTestGfx89[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0089.8bpp.lz");
static const u16 sTestPal89[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0089.gbapal");
static const u32 sTestGfx90[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0090.8bpp.lz");
static const u16 sTestPal90[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0090.gbapal");
static const u32 sTestGfx91[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0091.8bpp.lz");
static const u16 sTestPal91[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0091.gbapal");
static const u32 sTestGfx92[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0092.8bpp.lz");
static const u16 sTestPal92[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0092.gbapal");
static const u32 sTestGfx93[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0093.8bpp.lz");
static const u16 sTestPal93[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0093.gbapal");
static const u32 sTestGfx94[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0094.8bpp.lz");
static const u16 sTestPal94[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0094.gbapal");
static const u32 sTestGfx95[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0095.8bpp.lz");
static const u16 sTestPal95[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0095.gbapal");
static const u32 sTestGfx96[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0096.8bpp.lz");
static const u16 sTestPal96[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0096.gbapal");
static const u32 sTestGfx97[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0097.8bpp.lz");
static const u16 sTestPal97[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0097.gbapal");
static const u32 sTestGfx98[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0098.8bpp.lz");
static const u16 sTestPal98[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0098.gbapal");
static const u32 sTestGfx99[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0099.8bpp.lz");
static const u16 sTestPal99[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0099.gbapal");
static const u32 sTestGfx100[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0100.8bpp.lz");
static const u16 sTestPal100[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0100.gbapal");
static const u32 sTestGfx101[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0101.8bpp.lz");
static const u16 sTestPal101[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0101.gbapal");
static const u32 sTestGfx102[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0102.8bpp.lz");
static const u16 sTestPal102[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0102.gbapal");
static const u32 sTestGfx103[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0103.8bpp.lz");
static const u16 sTestPal103[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0103.gbapal");
static const u32 sTestGfx104[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0104.8bpp.lz");
static const u16 sTestPal104[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0104.gbapal");
static const u32 sTestGfx105[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0105.8bpp.lz");
static const u16 sTestPal105[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0105.gbapal");
static const u32 sTestGfx106[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0106.8bpp.lz");
static const u16 sTestPal106[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0106.gbapal");
static const u32 sTestGfx107[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0107.8bpp.lz");
static const u16 sTestPal107[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0107.gbapal");
static const u32 sTestGfx108[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0108.8bpp.lz");
static const u16 sTestPal108[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0108.gbapal");
static const u32 sTestGfx109[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0109.8bpp.lz");
static const u16 sTestPal109[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0109.gbapal");
static const u32 sTestGfx110[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0110.8bpp.lz");
static const u16 sTestPal110[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0110.gbapal");
static const u32 sTestGfx111[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0111.8bpp.lz");
static const u16 sTestPal111[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0111.gbapal");
static const u32 sTestGfx112[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0112.8bpp.lz");
static const u16 sTestPal112[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0112.gbapal");
static const u32 sTestGfx113[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0113.8bpp.lz");
static const u16 sTestPal113[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0113.gbapal");
static const u32 sTestGfx114[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0114.8bpp.lz");
static const u16 sTestPal114[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0114.gbapal");
static const u32 sTestGfx115[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0115.8bpp.lz");
static const u16 sTestPal115[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0115.gbapal");
static const u32 sTestGfx116[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0116.8bpp.lz");
static const u16 sTestPal116[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0116.gbapal");
static const u32 sTestGfx117[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0117.8bpp.lz");
static const u16 sTestPal117[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0117.gbapal");
static const u32 sTestGfx118[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0118.8bpp.lz");
static const u16 sTestPal118[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0118.gbapal");
static const u32 sTestGfx119[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0119.8bpp.lz");
static const u16 sTestPal119[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0119.gbapal");
static const u32 sTestGfx120[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0120.8bpp.lz");
static const u16 sTestPal120[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0120.gbapal");
static const u32 sTestGfx121[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0121.8bpp.lz");
static const u16 sTestPal121[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0121.gbapal");
static const u32 sTestGfx122[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0122.8bpp.lz");
static const u16 sTestPal122[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0122.gbapal");
static const u32 sTestGfx123[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0123.8bpp.lz");
static const u16 sTestPal123[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0123.gbapal");
static const u32 sTestGfx124[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0124.8bpp.lz");
static const u16 sTestPal124[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0124.gbapal");
static const u32 sTestGfx125[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0125.8bpp.lz");
static const u16 sTestPal125[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0125.gbapal");
static const u32 sTestGfx126[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0126.8bpp.lz");
static const u16 sTestPal126[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0126.gbapal");
static const u32 sTestGfx127[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0127.8bpp.lz");
static const u16 sTestPal127[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0127.gbapal");
static const u32 sTestGfx128[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0128.8bpp.lz");
static const u16 sTestPal128[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0128.gbapal");
static const u32 sTestGfx129[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0129.8bpp.lz");
static const u16 sTestPal129[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0129.gbapal");
static const u32 sTestGfx130[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0130.8bpp.lz");
static const u16 sTestPal130[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0130.gbapal");
static const u32 sTestGfx131[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0131.8bpp.lz");
static const u16 sTestPal131[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0131.gbapal");
static const u32 sTestGfx132[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0132.8bpp.lz");
static const u16 sTestPal132[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0132.gbapal");
static const u32 sTestGfx133[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0133.8bpp.lz");
static const u16 sTestPal133[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0133.gbapal");
static const u32 sTestGfx134[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0134.8bpp.lz");
static const u16 sTestPal134[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0134.gbapal");
static const u32 sTestGfx135[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0135.8bpp.lz");
static const u16 sTestPal135[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0135.gbapal");
static const u32 sTestGfx136[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0136.8bpp.lz");
static const u16 sTestPal136[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0136.gbapal");
static const u32 sTestGfx137[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0137.8bpp.lz");
static const u16 sTestPal137[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0137.gbapal");
static const u32 sTestGfx138[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0138.8bpp.lz");
static const u16 sTestPal138[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0138.gbapal");
static const u32 sTestGfx139[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0139.8bpp.lz");
static const u16 sTestPal139[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0139.gbapal");
static const u32 sTestGfx140[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0140.8bpp.lz");
static const u16 sTestPal140[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0140.gbapal");
static const u32 sTestGfx141[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0141.8bpp.lz");
static const u16 sTestPal141[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0141.gbapal");
static const u32 sTestGfx142[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0142.8bpp.lz");
static const u16 sTestPal142[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0142.gbapal");
static const u32 sTestGfx143[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0143.8bpp.lz");
static const u16 sTestPal143[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0143.gbapal");
static const u32 sTestGfx144[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0144.8bpp.lz");
static const u16 sTestPal144[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0144.gbapal");
static const u32 sTestGfx145[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0145.8bpp.lz");
static const u16 sTestPal145[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0145.gbapal");
static const u32 sTestGfx146[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0146.8bpp.lz");
static const u16 sTestPal146[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0146.gbapal");
static const u32 sTestGfx147[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0147.8bpp.lz");
static const u16 sTestPal147[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0147.gbapal");
static const u32 sTestGfx148[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0148.8bpp.lz");
static const u16 sTestPal148[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0148.gbapal");
static const u32 sTestGfx149[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0149.8bpp.lz");
static const u16 sTestPal149[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0149.gbapal");
static const u32 sTestGfx150[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0150.8bpp.lz");
static const u16 sTestPal150[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0150.gbapal");
static const u32 sTestGfx151[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0151.8bpp.lz");
static const u16 sTestPal151[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0151.gbapal");
static const u32 sTestGfx152[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0152.8bpp.lz");
static const u16 sTestPal152[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0152.gbapal");
static const u32 sTestGfx153[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0153.8bpp.lz");
static const u16 sTestPal153[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0153.gbapal");
static const u32 sTestGfx154[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0154.8bpp.lz");
static const u16 sTestPal154[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0154.gbapal");
static const u32 sTestGfx155[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0155.8bpp.lz");
static const u16 sTestPal155[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0155.gbapal");
static const u32 sTestGfx156[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0156.8bpp.lz");
static const u16 sTestPal156[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0156.gbapal");
static const u32 sTestGfx157[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0157.8bpp.lz");
static const u16 sTestPal157[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0157.gbapal");
static const u32 sTestGfx158[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0158.8bpp.lz");
static const u16 sTestPal158[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0158.gbapal");
static const u32 sTestGfx159[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0159.8bpp.lz");
static const u16 sTestPal159[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0159.gbapal");
static const u32 sTestGfx160[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0160.8bpp.lz");
static const u16 sTestPal160[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0160.gbapal");
static const u32 sTestGfx161[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0161.8bpp.lz");
static const u16 sTestPal161[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0161.gbapal");
static const u32 sTestGfx162[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0162.8bpp.lz");
static const u16 sTestPal162[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0162.gbapal");
static const u32 sTestGfx163[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0163.8bpp.lz");
static const u16 sTestPal163[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0163.gbapal");
static const u32 sTestGfx164[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0164.8bpp.lz");
static const u16 sTestPal164[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0164.gbapal");
static const u32 sTestGfx165[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0165.8bpp.lz");
static const u16 sTestPal165[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0165.gbapal");
static const u32 sTestGfx166[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0166.8bpp.lz");
static const u16 sTestPal166[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0166.gbapal");
static const u32 sTestGfx167[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0167.8bpp.lz");
static const u16 sTestPal167[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0167.gbapal");
static const u32 sTestGfx168[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0168.8bpp.lz");
static const u16 sTestPal168[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0168.gbapal");
static const u32 sTestGfx169[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0169.8bpp.lz");
static const u16 sTestPal169[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0169.gbapal");
static const u32 sTestGfx170[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0170.8bpp.lz");
static const u16 sTestPal170[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0170.gbapal");
static const u32 sTestGfx171[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0171.8bpp.lz");
static const u16 sTestPal171[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0171.gbapal");
static const u32 sTestGfx172[] = INCBIN_U32("graphics/mp4/test_frames/indexed/frame_0172.8bpp.lz");
static const u16 sTestPal172[] = INCBIN_U16("graphics/mp4/test_frames/indexed/frame_0172.gbapal");

static const u32 *const sTitleScreenBackgroundGfxTable[] = 
{
    sTestGfx0,
    sTestGfx1,
    sTestGfx2,
    sTestGfx3,
    sTestGfx4,
    sTestGfx5,
    sTestGfx6,
    sTestGfx7,
    sTestGfx8,
    sTestGfx9,
    sTestGfx10,
    sTestGfx11,
    sTestGfx12,
    sTestGfx13,
    sTestGfx14,
    sTestGfx15,
    sTestGfx16,
    sTestGfx17,
    sTestGfx18,
    sTestGfx19,
    sTestGfx20,
    sTestGfx21,
    sTestGfx22,
    sTestGfx23,
    sTestGfx24,
    sTestGfx25,
    sTestGfx26,
    sTestGfx27,
    sTestGfx28,
    sTestGfx29,
    sTestGfx30,
    sTestGfx31,
    sTestGfx32,
    sTestGfx33,
    sTestGfx34,
    sTestGfx35,
    sTestGfx36,
    sTestGfx37,
    sTestGfx38,
    sTestGfx39,
    sTestGfx40,
    sTestGfx41,
    sTestGfx42,
    sTestGfx43,
    sTestGfx44,
    sTestGfx45,
    sTestGfx46,
    sTestGfx47,
    sTestGfx48,
    sTestGfx49,
    sTestGfx50,
    sTestGfx51,
    sTestGfx52,
    sTestGfx53,
    sTestGfx54,
    sTestGfx55,
    sTestGfx56,
    sTestGfx57,
    sTestGfx58,
    sTestGfx59,
    sTestGfx60,
    sTestGfx61,
    sTestGfx62,
    sTestGfx63,
    sTestGfx64,
    sTestGfx65,
    sTestGfx66,
    sTestGfx67,
    sTestGfx68,
    sTestGfx69,
    sTestGfx70,
    sTestGfx71,
    sTestGfx72,
    sTestGfx73,
    sTestGfx74,
    sTestGfx75,
    sTestGfx76,
    sTestGfx77,
    sTestGfx78,
    sTestGfx79,
    sTestGfx80,
    sTestGfx81,
    sTestGfx82,
    sTestGfx83,
    sTestGfx84,
    sTestGfx85,
    sTestGfx86,
    sTestGfx87,
    sTestGfx88,
    sTestGfx89,
    sTestGfx90,
    sTestGfx91,
    sTestGfx92,
    sTestGfx93,
    sTestGfx94,
    sTestGfx95,
    sTestGfx96,
    sTestGfx97,
    sTestGfx98,
    sTestGfx99,
    sTestGfx100,
    sTestGfx101,
    sTestGfx102,
    sTestGfx103,
    sTestGfx104,
    sTestGfx105,
    sTestGfx106,
    sTestGfx107,
    sTestGfx108,
    sTestGfx109,
    sTestGfx110,
    sTestGfx111,
    sTestGfx112,
    sTestGfx113,
    sTestGfx114,
    sTestGfx115,
    sTestGfx116,
    sTestGfx117,
    sTestGfx118,
    sTestGfx119,
    sTestGfx120,
    sTestGfx121,
    sTestGfx122,
    sTestGfx123,
    sTestGfx124,
    sTestGfx125,
    sTestGfx126,
    sTestGfx127,
    sTestGfx128,
    sTestGfx129,
    sTestGfx130,
    sTestGfx131,
    sTestGfx132,
    sTestGfx133,
    sTestGfx134,
    sTestGfx135,
    sTestGfx136,
    sTestGfx137,
    sTestGfx138,
    sTestGfx139,
    sTestGfx140,
    sTestGfx141,
    sTestGfx142,
    sTestGfx143,
    sTestGfx144,
    sTestGfx145,
    sTestGfx146,
    sTestGfx147,
    sTestGfx148,
    sTestGfx149,
    sTestGfx150,
    sTestGfx151,
    sTestGfx152,
    sTestGfx153,
    sTestGfx154,
    sTestGfx155,
    sTestGfx156,
    sTestGfx157,
    sTestGfx158,
    sTestGfx159,
    sTestGfx160,
    sTestGfx161,
    sTestGfx162,
    sTestGfx163,
    sTestGfx164,
    sTestGfx165,
    sTestGfx166,
    sTestGfx167,
    sTestGfx168,
    sTestGfx169,
    sTestGfx170,
    sTestGfx171,
    sTestGfx172
};

static const u16 *const sTitleScreenBackgroundPalTable[] = 
{
    sTestPal0,
    sTestPal1,
    sTestPal2,
    sTestPal3,
    sTestPal4,
    sTestPal5,
    sTestPal6,
    sTestPal7,
    sTestPal8,
    sTestPal9,
    sTestPal10,
    sTestPal11,
    sTestPal12,
    sTestPal13,
    sTestPal14,
    sTestPal15,
    sTestPal16,
    sTestPal17,
    sTestPal18,
    sTestPal19,
    sTestPal20,
    sTestPal21,
    sTestPal22,
    sTestPal23,
    sTestPal24,
    sTestPal25,
    sTestPal26,
    sTestPal27,
    sTestPal28,
    sTestPal29,
    sTestPal30,
    sTestPal31,
    sTestPal32,
    sTestPal33,
    sTestPal34,
    sTestPal35,
    sTestPal36,
    sTestPal37,
    sTestPal38,
    sTestPal39,
    sTestPal40,
    sTestPal41,
    sTestPal42,
    sTestPal43,
    sTestPal44,
    sTestPal45,
    sTestPal46,
    sTestPal47,
    sTestPal48,
    sTestPal49,
    sTestPal50,
    sTestPal51,
    sTestPal52,
    sTestPal53,
    sTestPal54,
    sTestPal55,
    sTestPal56,
    sTestPal57,
    sTestPal58,
    sTestPal59,
    sTestPal60,
    sTestPal61,
    sTestPal62,
    sTestPal63,
    sTestPal64,
    sTestPal65,
    sTestPal66,
    sTestPal67,
    sTestPal68,
    sTestPal69,
    sTestPal70,
    sTestPal71,
    sTestPal72,
    sTestPal73,
    sTestPal74,
    sTestPal75,
    sTestPal76,
    sTestPal77,
    sTestPal78,
    sTestPal79,
    sTestPal80,
    sTestPal81,
    sTestPal82,
    sTestPal83,
    sTestPal84,
    sTestPal85,
    sTestPal86,
    sTestPal87,
    sTestPal88,
    sTestPal89,
    sTestPal90,
    sTestPal91,
    sTestPal92,
    sTestPal93,
    sTestPal94,
    sTestPal95,
    sTestPal96,
    sTestPal97,
    sTestPal98,
    sTestPal99,
    sTestPal100,
    sTestPal101,
    sTestPal102,
    sTestPal103,
    sTestPal104,
    sTestPal105,
    sTestPal106,
    sTestPal107,
    sTestPal108,
    sTestPal109,
    sTestPal110,
    sTestPal111,
    sTestPal112,
    sTestPal113,
    sTestPal114,
    sTestPal115,
    sTestPal116,
    sTestPal117,
    sTestPal118,
    sTestPal119,
    sTestPal120,
    sTestPal121,
    sTestPal122,
    sTestPal123,
    sTestPal124,
    sTestPal125,
    sTestPal126,
    sTestPal127,
    sTestPal128,
    sTestPal129,
    sTestPal130,
    sTestPal131,
    sTestPal132,
    sTestPal133,
    sTestPal134,
    sTestPal135,
    sTestPal136,
    sTestPal137,
    sTestPal138,
    sTestPal139,
    sTestPal140,
    sTestPal141,
    sTestPal142,
    sTestPal143,
    sTestPal144,
    sTestPal145,
    sTestPal146,
    sTestPal147,
    sTestPal148,
    sTestPal149,
    sTestPal150,
    sTestPal151,
    sTestPal152,
    sTestPal153,
    sTestPal154,
    sTestPal155,
    sTestPal156,
    sTestPal157,
    sTestPal158,
    sTestPal159,
    sTestPal160,
    sTestPal161,
    sTestPal162,
    sTestPal163,
    sTestPal164,
    sTestPal165,
    sTestPal166,
    sTestPal167,
    sTestPal168,
    sTestPal169,
    sTestPal170,
    sTestPal171,
    sTestPal172
};

static const u32 sTitleScreenBackgroundTilemap[] = INCBIN_U32("graphics/title_screen/bg/full.bin.lz");

static void MainCB2(void)
{
    RunTasks();
    UpdatePaletteFade();
}

static void VBlankCB(void)
{

}

void RunTestAnim(void)
{
    switch (gMain.state)
    {
    default:
    case 0:
        SetVBlankCallback(NULL);
        SetGpuReg(REG_OFFSET_BLDCNT, 0);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        SetGpuReg(REG_OFFSET_BLDY, 0);
        SetGpuReg(REG_OFFSET_DISPCNT, 0);
        SetGpuReg(REG_OFFSET_BG2CNT, 0);
        SetGpuReg(REG_OFFSET_BG1CNT, 0);
        SetGpuReg(REG_OFFSET_BG0CNT, 0);
        SetGpuReg(REG_OFFSET_BG2HOFS, 0);
        SetGpuReg(REG_OFFSET_BG2VOFS, 0);
        SetGpuReg(REG_OFFSET_BG1HOFS, 0);
        SetGpuReg(REG_OFFSET_BG1VOFS, 0);
        SetGpuReg(REG_OFFSET_BG0HOFS, 0);
        SetGpuReg(REG_OFFSET_BG0VOFS, 0);
        DmaFill16(3, 0, (void *)VRAM, VRAM_SIZE);
        DmaFill32(3, 0, (void *)OAM, OAM_SIZE);
        DmaFill16(3, 0, (void *)(PLTT + 2), PLTT_SIZE - 2);
        ResetPaletteFade();
        gMain.state = 1;
        break;
    case 1:
        ScanlineEffect_Stop();
        ResetTasks();
        ResetSpriteData();
        FreeAllSpritePalettes();
        LoadPalette(sTitleScreenBackgroundPalTable[0], 0, 256 * 2);
        LZ77UnCompVram(sTitleScreenBackgroundGfxTable[0], (void *)(BG_CHAR_ADDR(0)));
        LZ77UnCompVram(sTitleScreenBackgroundTilemap, (void *)(BG_SCREEN_ADDR(20))); 
        gMain.state = 2;
        break;
    case 2:
    {
        u8 taskId = CreateTask(Task_PrintMp4, 0);
        gMain.state = 3;
        break;
    }
    case 3:
        gMain.state = 4;
        break;
    case 4:
        SetGpuReg(REG_OFFSET_WIN0H, 0);
        SetGpuReg(REG_OFFSET_WIN0V, 0);
        SetGpuReg(REG_OFFSET_WIN1H, 0);
        SetGpuReg(REG_OFFSET_WIN1V, 0);
        SetGpuReg(REG_OFFSET_WININ, WININ_WIN0_BG_ALL | WININ_WIN0_OBJ | WININ_WIN1_BG_ALL | WININ_WIN1_OBJ);
        SetGpuReg(REG_OFFSET_WINOUT, WINOUT_WIN01_BG_ALL | WINOUT_WIN01_OBJ | WINOUT_WINOBJ_ALL);
        SetGpuReg(REG_OFFSET_BLDCNT, 0);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        SetGpuReg(REG_OFFSET_BLDY, 0);
        SetGpuReg(REG_OFFSET_BG0CNT, BGCNT_PRIORITY(3) | BGCNT_CHARBASE(0) | BGCNT_SCREENBASE(20) | BGCNT_256COLOR | BGCNT_TXT256x256);
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_MODE_1
                                        | DISPCNT_OBJ_1D_MAP
                                        | DISPCNT_BG0_ON
                                        | DISPCNT_OBJ_ON
                                        | DISPCNT_WIN0_ON
                                        | DISPCNT_OBJWIN_ON);

        gMain.state = 5;
        break;
    case 5:
        SetMainCallback2(MainCB2);
        SetVBlankCallback(VBlankCB);
        break;
    }
}

static void Task_PrintMp4(u8 taskId)
{
    if (gTasks[taskId].data[1]++ % 6 == 0)
    {
        DmaCopy16(3, sTitleScreenBackgroundPalTable[gTasks[taskId].data[0] % NELEMS(sTitleScreenBackgroundPalTable)], (void *)PLTT, BG_PLTT_SIZE);
        LZ77UnCompVram(sTitleScreenBackgroundGfxTable[gTasks[taskId].data[0] % NELEMS(sTitleScreenBackgroundGfxTable)], (void *)(BG_CHAR_ADDR(0)));
        gTasks[taskId].data[0]++;
    }
}


void CB2_RunTestAnim(void)
{
    SetMainCallback2(RunTestAnim);
}