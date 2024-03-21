#include "prelude.h"
#include "msg.h"
#include "text.h"
#include "decoding.h"

#define CHAR_NEWLINE 0x01

extern struct Glyph const * const GlyphType_GlyS[];
extern struct Glyph const * const GlyphType_GlyT[];

/* LynJump */
void SetTextFontGlyphs(int glyphset)
{
    if (glyphset == TEXT_GLYPHS_SYSTEM)
    {
        gActiveFont->glyphs = GlyphType_GlyS;
    }
    else
    {
        gActiveFont->glyphs = GlyphType_GlyT;
    }
}

static const struct Glyph * GetCharGlyphUnicode(u32 unicode_ch, struct Font * font)
{
    const struct Glyph * glyph;
    int hi = (unicode_ch >> 0x8) & 0xFF;
    int lo = unicode_ch & 0xFF;

    /* For now, we can only support for group 1 of unicode (U_0000 ~ U_FFFF) */
    if (unicode_ch >= 0x10000)
    {
        return NULL;
    }

    for(glyph = font->glyphs[lo]; glyph != NULL; glyph = glyph->next)
    {
        if (glyph->sjis_byte_1 == hi)
            return glyph;
    }

    return NULL;
}

/* LynJump! */
const char * GetCharTextLen(const char * str, i32 * width)
{
    const struct Glyph * glyph;
    u32 unicod;
    int ret, decode_len;

    ret = DecodeUtf8(str, &unicod, &decode_len);
    if (ret)
        return GetCharTextLen("?", width);

    glyph = GetCharGlyphUnicode(unicod, gActiveFont);
    if (glyph == NULL)
        return GetCharTextLen("?", width);

    *width = glyph->width;
    return str + decode_len;
}

/* LynJump! */
int GetStringTextLen(const char * str)
{
    i32 _wid;
    int width = 0;
    while (*str != 0 && *str != CHAR_NEWLINE)
    {
        str = GetCharTextLen(str, &_wid);
        width += _wid;
    }
    return width;
}

/* LynJump */
char const * GetStringLineEnd(char const * str)
{
    i32 _wid;
    int width = 0;
    while (*str != 0 && *str != CHAR_NEWLINE)
    {
        str = GetCharTextLen(str, &_wid);
        width += _wid;
    }
    return str;
}

/* LynJump */
const char * Text_DrawCharacter(struct Text * text, const char * str)
{
    const struct Glyph * glyph;
    u32 unicod;
    int ret, decode_len;

    ret = DecodeUtf8(str, &unicod, &decode_len);
    if (ret)
    {
        unicod = '?';
        decode_len = 1;
    }

    glyph = GetCharGlyphUnicode(unicod, gActiveFont);
    if (glyph == NULL)
        glyph = GetCharGlyphUnicode('?', gActiveFont);

    gActiveFont->draw_glyph(text, glyph);
    return str + decode_len;
}

/* LynJump */
void Text_DrawString(struct Text * text, char const * str)
{
    while (*str > 1)
        str = Text_DrawCharacter(text, str);
}

/* LynJump */
void Text_DrawNumber(struct Text * text, int number)
{
    if (number == 0)
    {
        Text_DrawCharacter(text, "0");
        return;
    }

    while (number != 0)
    {
        u16 chr = '0' + ((number % 10) << 8);
        number /= 10;

        Text_DrawCharacter(text, (char const *) &chr);

        text->x -= 16;
    }
}

/* LynJump */
void Text_DrawNumberOrBlank(struct Text * text, int number)
{
    if (number == 0xFF || number == -1) {
        Text_Skip(text, -8);
        Text_DrawString(text, "ーー");

        return;
    }

    Text_DrawNumber(text, number);
}

static u32 my_log10(u32 number)
{
    if (number >= 100000000) return 9;
    if (number >= 10000000) return 8;
    if (number >= 1000000) return 7;
    if (number >= 100000) return 6;
    if (number >= 10000) return 5;
    if (number >= 1000) return 4;
    if (number >= 100) return 3;
    if (number >= 10) return 2;
    if (number >= 1) return 1;
    return 0;
}

/* LynJump */
int NumberToString(int number, char * buf)
{
    u32 off, beg;

    off = 0;

    if (number == 0) {
        *buf++ = '0';
        *buf++ = '\0';
        return 1;
    }

    if (number < 0) {
        buf[off++] = '-';
        number = -number;
    }

    off += my_log10(number);
    beg = off;

    while (number > 0) {
        buf[off--] = '0' + DivRem(number, 10);
        number = Div(number, 10);
    }

    buf[beg + 1] = '\0';
    return beg + 1;
}
