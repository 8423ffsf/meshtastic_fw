#pragma once
#include <Arduino.h>

namespace graphics
{

// ============================================================================
// 彩色 Emote Font 数据结构
// ============================================================================

#define EMOTE_COLOR_WIDTH 16
#define EMOTE_COLOR_HEIGHT 16
#define EMOTE_COLOR_SIZE (EMOTE_COLOR_WIDTH * EMOTE_COLOR_HEIGHT * 2)  // 512 bytes per emote, RGB565

// EmoteFont 结构 (简化版，偏移量可通过索引计算)
struct ColorEmoteFont {
    const uint16_t *map;            // 压缩码点映射表
    const uint8_t *bitmap_data;     // RGB565 位图数据
    uint16_t count;                 // 条目数量
};

// 全局实例
extern const ColorEmoteFont colorEmoteFont;

// 获取 Color Emote 位图数据
inline const uint16_t* getColorEmoteBitmap(size_t index) {
    return (const uint16_t*)(colorEmoteFont.bitmap_data + index * EMOTE_COLOR_SIZE);
}

// 二分查找彩色 Emote 索引
int findColorEmoteIndex(uint16_t compressedCodePoint);

// ============================================================================
// 预设宏定义
// ============================================================================
// 控制包含哪些分类的 emote，支持细粒度控制
//
// 使用示例:
// #define EMOTE_COLOR_TINY       // 仅基础集 (默认)
// #define EMOTE_COLOR_MINIMAL    // 基础 + 常用表情
// #define EMOTE_COLOR_COMPACT    // MINIMAL + 天气自然
// #define EMOTE_COLOR_STANDARD   // COMPACT + 动物食物
// #define EMOTE_COLOR_EXTENDED   // STANDARD + 活动旅行
// #define EMOTE_COLOR_LARGE      // EXTENDED + 物品符号
// #define EMOTE_COLOR_FULL       // 所有分类

// ============================================================================
// 预设宏展开
// ============================================================================

// EMOTE_COLOR_TINY: 默认配置，仅基础集
#ifdef EMOTE_COLOR_TINY
  // 不定义任何扩展分类
#endif

// EMOTE_COLOR_MINIMAL: 基础 + 常用表情
#ifdef EMOTE_COLOR_MINIMAL
  #define EMOTE_COLOR_INCLUDE_SMILEYS_EMOTION
  #define EMOTE_COLOR_INCLUDE_HAND_FINGERS
#endif

// EMOTE_COLOR_COMPACT: MINIMAL + 天气自然
#ifdef EMOTE_COLOR_COMPACT
  #define EMOTE_COLOR_INCLUDE_SMILEYS_EMOTION
  #define EMOTE_COLOR_INCLUDE_HAND_FINGERS
  #define EMOTE_COLOR_INCLUDE_WEATHER
  #define EMOTE_COLOR_INCLUDE_NATURE
#endif

// EMOTE_COLOR_STANDARD: COMPACT + 动物食物
#ifdef EMOTE_COLOR_STANDARD
  #define EMOTE_COLOR_INCLUDE_SMILEYS_EMOTION
  #define EMOTE_COLOR_INCLUDE_HAND_FINGERS
  #define EMOTE_COLOR_INCLUDE_WEATHER
  #define EMOTE_COLOR_INCLUDE_NATURE
  #define EMOTE_COLOR_INCLUDE_ANIMALS
  #define EMOTE_COLOR_INCLUDE_FOOD_DRINK
#endif

// EMOTE_COLOR_EXTENDED: STANDARD + 活动旅行
#ifdef EMOTE_COLOR_EXTENDED
  #define EMOTE_COLOR_INCLUDE_SMILEYS_EMOTION
  #define EMOTE_COLOR_INCLUDE_HAND_FINGERS
  #define EMOTE_COLOR_INCLUDE_WEATHER
  #define EMOTE_COLOR_INCLUDE_NATURE
  #define EMOTE_COLOR_INCLUDE_ANIMALS
  #define EMOTE_COLOR_INCLUDE_FOOD_DRINK
  #define EMOTE_COLOR_INCLUDE_ACTIVITIES
  #define EMOTE_COLOR_INCLUDE_SPORTS
  #define EMOTE_COLOR_INCLUDE_TRAVEL_PLACES
#endif

// EMOTE_COLOR_LARGE: EXTENDED + 物品符号
#ifdef EMOTE_COLOR_LARGE
  #define EMOTE_COLOR_INCLUDE_SMILEYS_EMOTION
  #define EMOTE_COLOR_INCLUDE_HAND_FINGERS
  #define EMOTE_COLOR_INCLUDE_WEATHER
  #define EMOTE_COLOR_INCLUDE_NATURE
  #define EMOTE_COLOR_INCLUDE_ANIMALS
  #define EMOTE_COLOR_INCLUDE_FOOD_DRINK
  #define EMOTE_COLOR_INCLUDE_ACTIVITIES
  #define EMOTE_COLOR_INCLUDE_SPORTS
  #define EMOTE_COLOR_INCLUDE_TRAVEL_PLACES
  #define EMOTE_COLOR_INCLUDE_OBJECTS
  #define EMOTE_COLOR_INCLUDE_SYMBOLS
  #define EMOTE_COLOR_INCLUDE_ARROWS
#endif

// EMOTE_COLOR_FULL: 所有分类
#ifdef EMOTE_COLOR_FULL
  #define EMOTE_COLOR_INCLUDE_SMILEYS_EMOTION
  #define EMOTE_COLOR_INCLUDE_HAND_FINGERS
  #define EMOTE_COLOR_INCLUDE_WEATHER
  #define EMOTE_COLOR_INCLUDE_NATURE
  #define EMOTE_COLOR_INCLUDE_ANIMALS
  #define EMOTE_COLOR_INCLUDE_FOOD_DRINK
  #define EMOTE_COLOR_INCLUDE_ACTIVITIES
  #define EMOTE_COLOR_INCLUDE_SPORTS
  #define EMOTE_COLOR_INCLUDE_TRAVEL_PLACES
  #define EMOTE_COLOR_INCLUDE_OBJECTS
  #define EMOTE_COLOR_INCLUDE_SYMBOLS
  #define EMOTE_COLOR_INCLUDE_ARROWS
  #define EMOTE_COLOR_INCLUDE_GEOMETRIC_SHAPES
  #define EMOTE_COLOR_INCLUDE_MATH_SYMBOLS
  #define EMOTE_COLOR_INCLUDE_TECHNICAL
  #define EMOTE_COLOR_INCLUDE_CURRENCY
  #define EMOTE_COLOR_INCLUDE_NUMBER_FORMS
  #define EMOTE_COLOR_INCLUDE_SUPPLEMENTAL_SYMBOLS
  #define EMOTE_COLOR_INCLUDE_PLAYING_CARDS
  #define EMOTE_COLOR_INCLUDE_GAME_SYMBOLS
  #define EMOTE_COLOR_INCLUDE_MUSIC
  #define EMOTE_COLOR_INCLUDE_ALPHANUMERIC
  #define EMOTE_COLOR_INCLUDE_ENCLOSED_CJK
  #define EMOTE_COLOR_INCLUDE_FULLWIDTH
#endif

} // namespace graphics
