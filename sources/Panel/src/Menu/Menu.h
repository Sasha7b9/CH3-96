// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


class Page;


namespace Menu
{
    void Init();

    void Draw();

    Page* OpenedPage();

    void SetOpenedPage(Page *page);

    namespace Input
    {
        void Update();
    };
};
