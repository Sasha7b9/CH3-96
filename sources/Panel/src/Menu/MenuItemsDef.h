// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Menu/MenuItems.h"


#define DEF_SWITCH_UGO_2(name, titleRu, titleEn, hintRu, hintEn,                                                    \
    nameRu1, nameRu2, nameEn1, nameEn2, ugo1, ugo2, state, func)                                                    \
static char *n##name##Ru[] = { nameRu1, nameRu2, nullptr };                                                         \
static char *n##name##En[] = { nameEn2, nameEn2, nullptr };                                                         \
static char *ugo##name[] = { ugo1, ugo2, nullptr };                                                                 \
static Switch name(titleRu, titleEn, hintRu, hintEn, n##name##Ru, n##name##En, ugo##name, &state, func);

#define DEF_SWITCH_2(name, titleRu, titleEn, hintRu, hintEn,                                                        \
    nameRu1, nameRu2, nameEn1, nameEn2, state, func)                                                                \
static char *n##name##Ru[] = { nameRu1, nameRu2, nullptr };                                                         \
static char *n##name##En[] = { nameEn1, nameEn2, nullptr };                                                         \
static Switch name(titleRu, titleEn, hintRu, hintEn, n##name##Ru, n##name##En, nullptr, &state, func);

#define DEF_SWITCH_3(name, titleRu, titleEn, hintRu, hintEn,                                                        \
    nameRu1, nameRu2, nameRu3, nameEn1, nameEn2, nameEn3, state, func)                                              \
static char *n##name##Ru[] = { nameRu1, nameRu2, nameRu3, nullptr };                                                \
static char *n##name##En[] = { nameEn1, nameEn2, nameEn3, nullptr };                                                \
static Switch name(titleRu, titleEn, hintRu, hintEn, n##name##Ru, n##name##En, nullptr, &state, func);

#define DEF_SWITCH_4(name, titleRu, titleEn, hintRu, hintEn,                                                        \
    nameRu1, nameRu2, nameRu3, nameRu4, nameEn1, nameEn2, nameEn3, nameEn4, state, func)                            \
static char *n##name##Ru[] = { nameRu1, nameRu2, nameRu3, nameRu4, nullptr };                                       \
static char *n##name##En[] = { nameEn1, nameEn2, nameEn3, nameEn4, nullptr };                                       \
static Switch name(titleRu, titleEn, hintRu, hintEn, n##name##Ru, n##name##En, nullptr, &state, func);

#define DEF_SWITCH_5(name, titleRu, titleEn, hintRu, hintEn,                                                        \
    nameRu1, nameRu2, nameRu3, nameRu4, nameRu5, nameEn1, nameEn2, nameEn3, nameEn4, nameEn5, state, func)          \
static char *n##name##Ru[] = { nameRu1, nameRu2, nameRu3, nameRu4, nameRu5, nullptr };                              \
static char *n##name##En[] = { nameEn1, nameEn2, nameEn3, nameEn4, nameEn5, nullptr };                              \
static Switch name(titleRu, titleEn, hintRu, hintEn, n##name##Ru, n##name##En, nullptr, &state, func);

#define DEF_SWITCH_6(name, titleRu, titleEn, hintRu, hintEn,                                                        \
    nameRu1, nameRu2, nameRu3, nameRu4, nameRu5, nameRu6, nameEn1, nameEn2, nameEn3, nameEn4, nameEn5, nameEn6,     \
    state, func)                                                                                                    \
static char *n##name##Ru[] = { nameRu1, nameRu2, nameRu3, nameRu4, nameRu5, nameRu6, nullptr };                     \
static char *n##name##En[] = { nameEn1, nameEn2, nameEn3, nameEn4, nameEn5, nameEn6, nullptr };                     \
static Switch name(titleRu, titleEn, hintRu, hintEn, n##name##Ru, n##name##En, nullptr, &state, func);

#define DEF_BUTTON(name, titleRu, titleEn, hintRu, hintEn, funcPress)                                               \
static Button name(titleRu, titleEn, hintRu, hintEn, funcPress)
