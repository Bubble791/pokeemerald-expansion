for i in range(173):
    strings = str(i).zfill(4)
    print(f"static const u32 sTestGfx{i}[] = INCBIN_U32(\"graphics/mp4/test_frames/indexed/frame_{strings}.8bpp.smol\");")
    print(f"static const u16 sTestPal{i}[] = INCBIN_U16(\"graphics/mp4/test_frames/indexed/frame_{strings}.gbapal\");")

for i in range(173):
    print(f"sTestGfx{i},")

for i in range(173):
    print(f"sTestPal{i},")