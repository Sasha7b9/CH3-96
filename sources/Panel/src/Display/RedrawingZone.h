// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


/*
* �������� ������, ������������� �������������� �� ������
*/
class RedrawingZone
{
public:

    struct ModeDraw
    {
        enum E
        {
            ToBuffer,       // ��������� ����������� �������� - ����� �����
            ToHardware      // ������� ����� � ���������� �������
        };
    };

    RedrawingZone(int x, int y, int width, int height) :
        x0(0), y0(0), modeDraw(ModeDraw::ToBuffer), left(x), top(y), width(width), height(height), needUpdate(false) {}
    virtual ~RedrawingZone() {};

    void Update(ModeDraw::E mode);
   
    // ���������� ���� ������������� �����������
    void Refresh();

protected:

    virtual bool Draw() = 0;

    int x0;
    int y0;
    ModeDraw::E modeDraw;

    int Width() { return width; }

    // ������� ���������� ����� ����������
    virtual void BeforeDraw() {};

    // ������� ���������� ����� ���������
    virtual void AfterDraw() {};

private:

    void FillBackground();

    const int left;
    const int top;
    const int width;
    const int height;
    bool needUpdate;
};


class DataZone : public RedrawingZone
{
public:
    DataZone() : RedrawingZone(10, 140, Display::PHYSICAL_WIDTH - 50, 60) {}

protected:

    virtual bool Draw();
};


class ProgressBarTimeMeasureZone : public RedrawingZone
{
public:
    ProgressBarTimeMeasureZone() : RedrawingZone(273, 90, 55, 5) {};

    static void Reset();

protected:

    virtual bool Draw();

    static uint timeStart;      // ����� �������� ����� ���������� ������. ������������ ��� ������� ���������
};


class SynchroZone : public RedrawingZone
{
public:

    SynchroZone() : RedrawingZone(390, 120, 20, 20), oldColor(0) {}

    static void Fire();

protected:

    virtual bool Draw();

    int CalculateSize();

    uint CalculateColor();

    // ���������� 0 � ������ ��������� � 1.0 � ������ ��������� � �����
    float CalculateRelativeTime();

    virtual void BeforeDraw();

    virtual void AfterDraw();

    static uint timeStart;

    static const int MAX_SIZE = 12;

    uint oldColor;
};
