#pragma once

#include "emotes.h"
#include <stdint.h>
#include <string.h>

namespace graphics
{

/**
 * Helper functions for working with emotes using the optimized EmoteFont structure
 */

/**
 * Convert UTF-8 string to Unicode code point
 * Only handles the first character in the string
 * 
 * @param utf8 UTF-8 encoded string
 * @param len Length of the UTF-8 sequence (output parameter)
 * @return Unicode code point, or 0 if invalid
 */
inline uint32_t utf8ToCodePoint(const char* utf8, size_t* len = nullptr) {
    if (!utf8 || !*utf8) {
        if (len) *len = 0;
        return 0;
    }
    
    uint8_t c = (uint8_t)utf8[0];
    uint32_t codePoint = 0;
    size_t seqLen = 0;
    
    if (c < 0x80) {
        // 1-byte sequence (ASCII)
        codePoint = c;
        seqLen = 1;
    } else if ((c & 0xE0) == 0xC0) {
        // 2-byte sequence
        codePoint = ((c & 0x1F) << 6) | ((uint8_t)utf8[1] & 0x3F);
        seqLen = 2;
    } else if ((c & 0xF0) == 0xE0) {
        // 3-byte sequence
        codePoint = ((c & 0x0F) << 12) | 
                    (((uint8_t)utf8[1] & 0x3F) << 6) | 
                    ((uint8_t)utf8[2] & 0x3F);
        seqLen = 3;
    } else if ((c & 0xF8) == 0xF0) {
        // 4-byte sequence
        codePoint = ((c & 0x07) << 18) | 
                    (((uint8_t)utf8[1] & 0x3F) << 12) | 
                    (((uint8_t)utf8[2] & 0x3F) << 6) | 
                    ((uint8_t)utf8[3] & 0x3F);
        seqLen = 4;
    }
    
    if (len) *len = seqLen;
    return codePoint;
}

/**
 * Find emote glyph by UTF-8 string
 * This is a convenience wrapper around findEmoteGlyph()
 * 
 * @param utf8Label UTF-8 encoded emote label
 * @return Pointer to EmoteGlyph, or nullptr if not found
 */
inline const EmoteGlyph* findEmoteByLabel(const char* utf8Label) {
    if (!utf8Label) return nullptr;
    
    uint32_t codePoint = utf8ToCodePoint(utf8Label);
    if (codePoint == 0) return nullptr;
    
    return findEmoteGlyph(codePoint);
}

/**
 * Get emote bitmap data from glyph
 * 
 * @param glyph Pointer to EmoteGlyph
 * @return Pointer to bitmap data in PROGMEM
 */
inline const uint8_t* getEmoteBitmap(const EmoteGlyph* glyph) {
    if (!glyph || !emoteFont.data) return nullptr;
    
    uint16_t offset = pgm_read_word(&glyph->dataOffset);
    return &emoteFont.data[offset];
}

/**
 * Get emote width from glyph
 * 
 * @param glyph Pointer to EmoteGlyph
 * @return Width in pixels
 */
inline uint8_t getEmoteWidth(const EmoteGlyph* glyph) {
    if (!glyph) return 0;
    return pgm_read_byte(&glyph->width);
}

/**
 * Get emote height from glyph
 * 
 * @param glyph Pointer to EmoteGlyph
 * @return Height in pixels
 */
inline uint8_t getEmoteHeight(const EmoteGlyph* glyph) {
    if (!glyph) return 0;
    return pgm_read_byte(&glyph->height);
}

/**
 * Example: Optimized emote rendering function
 * This replaces the linear search in drawStringWithEmotes()
 * 
 * Usage:
 *   const char* emoji = "👍";
 *   const EmoteGlyph* glyph = findEmoteByLabel(emoji);
 *   if (glyph) {
 *       renderEmoteGlyph(display, x, y, glyph);
 *   }
 */
inline void renderEmoteGlyph(OLEDDisplay* display, int x, int y, const EmoteGlyph* glyph) {
    if (!glyph) return;
    
    uint8_t w = getEmoteWidth(glyph);
    uint8_t h = getEmoteHeight(glyph);
    const uint8_t* bitmap = getEmoteBitmap(glyph);
    
    if (bitmap) {
        display->drawXbm(x, y, w, h, bitmap);
    }
}

/**
 * Check if EmoteFont is initialized and ready to use
 * 
 * @return true if EmoteFont is available, false if using legacy emotes array
 */
inline bool isEmoteFontAvailable() {
    return emoteFont.count > 0 && emoteFont.map != nullptr && emoteFont.glyphs != nullptr;
}

} // namespace graphics

