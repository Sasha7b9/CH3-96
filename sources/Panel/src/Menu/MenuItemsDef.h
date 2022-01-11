// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Menu/MenuItems.h"


#define DEF_SWITCH_2(name, titleRu, titleEn, hintRu, hintEn, name1, name2, state, func)                             \
static char *n##name[] = { name1, name2, nullptr };                                                                 \
static Switch name(titleRu, titleEn, hintRu, hintEn, n##name, nullptr, &state, func);

#define DEF_SWITCH_UGO_2(name, titleRu, titleEn, hintRu, hintEn, name1, name2, ugo1, ugo2, state, func)             \
static char *n##name[] = { name1, name2, nullptr };                                                                 \
static char *ugo##name[] = { ugo1, ugo2, nullptr };                                                                 \
static Switch name(titleRu, titleEn, hintRu, hintEn, n##name, ugo##name, &state, func);

#define DEF_SWITCH_3(name, titleRu, titleEn, hintRu, hintEn, name1, name2, name3, state, func)                      \
static char *n##name[] = { name1, name2, name3, nullptr };                                                          \
static Switch name(titleRu, titleEn, hintRu, hintEn, n##name, nullptr, &state, func);

#define DEF_SWITCH_4(name, titleRu, titleEn, hintRu, hintEn, name1, name2, name3, name4, state, func)               \
static char *n##name[] = { name1, name2, name3, name4, nullptr };                                                   \
static Switch name(titleRu, titleEn, hintRu, hintEn, n##name, nullptr, &state, func);

#define DEF_SWITCH_5(name, titleRu, titleEn, hintRu, hintEn, name1, name2, name3, name4, name5, state, func)        \
static char *n##name[] = { name1, name2, name3, name4, name5, nullptr };                                            \
static Switch name(titleRu, titleEn, hintRu, hintEn, n##name, nullptr, &state, func);

#define DEF_SWITCH_6(name, titleRu, titleEn, hintRu, hintEn, name1, name2, name3, name4, name5, name6, state, func) \
static char *n##name[] = { name1, name2, name3, name4, name5, name6, nullptr };                                     \
static Switch name(titleRu, titleEn, hintRu, hintEn, n##name, nullptr, &state, func);

#define DEF_BUTTON(name, titleRu, titleEn, hintRu, hintEn, funcPress)                                               \
static Button name(titleRu, titleEn, hintRu, hintEn, funcPress)
