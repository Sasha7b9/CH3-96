// 2022/01/13 13:50:48 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class Page;


struct PageColors
{
    static Page *self;

    static void Init();
};


struct PageInfo
{
    static Page *self;
};


class PageService
{
public:
    static void UseReset();
    static Page *self;
};


class PageStatistics
{
public:

    static Page *self;

    static void Clear();
};
