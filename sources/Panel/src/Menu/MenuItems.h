#pragma once
#include "defines.h"
#include "Keyboard/Keyboard.h"


struct Enumeration
{
    /// ������� ��������� ������������
    uint8  value;
    char **names;
    char **ugo;
    Enumeration(uint8 v) : value(v) {};
    operator int() { return (int)value; };
    char *ToText() const { return names[value]; };
    int NumStates() const;
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Item
{
public:
    /// ������� ���������
    virtual void Draw(int x, int y) = 0;
    /// ������� ��������� ������� ������/�������� �����
    virtual bool OnControl(const Control &control) { return false; };

    static const int WIDTH = 35;
    static const int HEIGHT = 11;
    /// ����� �������� ������ ��������� ��� ���������� ��������������� �����
    static char hint[100];
    static char channelSettings[100];
protected:
    /// ����� ����� ���������
    char *commonHint;
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Button : public Item
{
public:
    Button(char *_text) : text(_text){};

    virtual void Draw(int x, int y);
    virtual bool OnControl(const Control &control);
    
private:
    char *text;
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Switch : public Item
{
public:

    Switch(char *_text, char *_comHint, char **_names, char **_ugo, Enumeration *_state, void(*_onClick)()) :
        text(_text), funcOnPress(_onClick), state(_state)
    {
        state->names = _names;
        
        commonHint = _comHint;
    };
    static void CreateChannelSettings();
    static char* ChannelSettings(){ return channelSettings; };
    virtual void Draw(int x, int y);
    virtual bool OnControl(const Control &control);

private:
    char        *text;              ///< ������� �� �������������
    void       (*funcOnPress)();    ///< ��� ������� ���������� ����� ��������� ��������� �������������
    Enumeration *state;             ///< ����� ���������� � ���������� �������������

    void CreateHint();
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Page : public Item
{
public:
    Page(Item **_items = nullptr) : items(_items), selectedItem(0) {};

    virtual void Draw(int x, int y);
    virtual bool OnControl(const Control &control);    
    /// ���������� ��������� �� ���������� ����� ����
    Item *SelectedItem() { return items[selectedItem]; };

    static Page empty;
    
private:
    /// ������ ������� ��������� �������
    void SelectNextItem();
    /// ������ ������� ���������� �������
    void SelectPrevItem();
    /// ���������� ���������� ������ �� ��������
    int NumItems();
    /// ��������� �� ������ ��������� ����. ������������� ����.
    Item **items;

    int selectedItem;
};
