// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "defines.h"
#include "Display/Colors.h"
#include "Keyboard/Keyboard.h"
#include "Utils/Observer.h"


struct TypeMeasure;
class Switch;


struct Enumeration
{
    uint8  value;           // Текущее состояние перечисления
    pchar *namesRu;
    pchar *namesEn;
    char **ugo;
    const bool *correct;    // Если указатель на этот массив не равен nullptr, то его элементы используются следующим
                            // образом : value не может значения индексов, соответствующих false
    explicit Enumeration(uint8 v, const bool *_correct = nullptr, int states = 0);
    operator int()         { return (int)value; }
    String ToString() const;
    char *UGO() const;
    int NumStates() const;
    // Возвращает индекс из массива names, соотвествующий текущему value
    int IndexName() const;
    bool Is(uint8 v) const { return value == v; }
    Switch *sw;
    bool SetValue(uint8 v);
    bool ValidValue(uint8 v) const;
    int numStates;
};



class Item
{
    friend class Hint;
public:
    Item(pchar hintRu, pchar hintEn);
    virtual ~Item() {};

    static const int HEIGHT = 35;

    // Функция отрисовки
    virtual void Draw(int x, int y, int width, bool selected = false) = 0;
    // Функция обработки нажатия кнопки/поворота ручки
    virtual bool OnControl(const Control &) { return false; };

    static Color ColorBackground(bool selected);

    static Color ColorDraw(bool selected);

    pchar GetHint() const;

protected:
    // Общая часть подсказки для данного итема
    pchar hint[2];

private:
    // Создать подсказку для итема
    virtual void CreateHint(String &hint) const = 0;
};



class Button : public Item
{
public:
    Button(pchar text_ru, pchar text_en, pchar hintRu, pchar hintEn, void (*funcPress)()) :
        Item(hintRu, hintEn), funcOnPress(funcPress)
    {
        text[0] = text_ru;
        text[1] = text_en;
    };

    virtual void Draw(int x, int y, int width, bool selected = false);
    virtual bool OnControl(const Control &control);

    pchar Title() const;

private:
    pchar text[2];
    void (*funcOnPress)();

    virtual void CreateHint(String &hint) const;
};



class Switch : public Item
{
    friend class Page;
    friend class PageModes;
public:

    Switch(pchar textRu, pchar textEn, pchar hintRu, pchar hintEn, pchar *_namesRu, pchar *_namesEn, char **_ugo,
        Enumeration *_state, void(*_onClick)()) :
        Item(hintRu, hintEn), funcOnPress(_onClick), state(_state)
    {
        text[0] = textRu;
        text[1] = textEn;

        state->namesRu = _namesRu;
        state->namesEn = _namesEn;

        state->ugo = _ugo;
        state->sw = this;
    };
    virtual void Draw(int x, int y, int width, bool selected = false);
    virtual bool OnControl(const Control &control);

    void FuncOnPress() const { if (funcOnPress) { funcOnPress(); }; }

    uint8 Value() const { return state->value; }

    // Для управления по SCPI
    void FuncForSCPI(int i);

    pchar Title() const;

    bool SetValue(uint8 v);

private:
    pchar       text[2];            // Надпись на переключателе
    void        (*funcOnPress)();   // Эта функция вызывается после изменения состояния переключателя
    Enumeration *state;             // Адрес переменной с состоянием переключателя
    virtual void CreateHint(String &hint) const;
    // Переключить в следующее состояние
    void  NextChoice();
};



class Page : public Item, public Observer
{
    friend struct Channel;

public:
    Page(Item **_items, void (*_onEvent)(EventType::E)) :
        Item("", ""), selectedItem(0), items(_items), onEvent(_onEvent)
    {};

    virtual void Draw(int x, int y, int width, bool selected = false);
    virtual bool OnControl(const Control &) { return false; };

    // Возвращает указатель на выделенный пункт меню
    Item *SelectedItem() { return items[selectedItem]; };

    // Возвращает true, если это страница режимов
    bool IsPageModes() const;

    // Возвращает true, если это страница настроек
    bool IsPageSettings() const;

    // Делает текущим следующий элемент
    void SelectNextItem();

    // Делает текущим предыдущий элемент
    void SelectPrevItem();

    // Проверить на корректность номер выделенного итема. Если он больше, чем количество итемов - скорректировать
    void VerifySelectedItem();

    virtual void OnEvent(EventType::E);

    // Номер выбранного итема
    int selectedItem;

protected:

    // Возвращает количество итемов на странице
    int NumItems() const;

    virtual void CreateHint(String &_hint) const { _hint.Free(); };

    // Возвращает ширину элемента меню с номером num
    int WidthItem(int num) const;

    // Указатель на массив элементов меню. Заканчивается нулём.
    Item **items;

    void (*onEvent)(EventType::E);
};


class PageModes : public Page
{
public:
    PageModes(Item **items, void (*onEvent)(EventType::E)) : Page(items, onEvent) {}

    // Функции действительны для страниц режимов каналов
    TypeMeasure *GetTypeMeasure() const;
    int GetModeMeasure() const;
    bool ExistTypeMeasure(uint8 type) const;
    void ResetTypeAndModeMeasure();
    bool ExistModeMeasure(int mode) const;
    void ResetModeMeasure();
};
