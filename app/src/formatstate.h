#ifndef FORMATSTATE_H
#define FORMATSTATE_H

#include <QColor>

class FormatState
{
public:
    FormatState();

    void setTextBold(bool b)
    {
        tb = b;
    }

    bool isTextBold() const
    {
        return tb;
    }

    void setTextItalic(bool i)
    {
        ti = i;
    }

    bool isTextItalic() const
    {
        return ti;
    }

    void setTextUnderline(bool u)
    {
        tu = u;
    }

    bool isTextUnderline() const
    {
        return tu;
    }

    void setTextStrikeOut(bool s)
    {
        ts = s;
    }

    bool isTextStrikeOut() const
    {
        return ts;
    }

    void setTextColor(const QColor &c)
    {
        tc = c;
    }

    QColor textColor() const
    {
        return tc;
    }

    void setTextBackgroundColor(const QColor &c)
    {
        tbc = c;
    }

    QColor textBackgroundColor() const
    {
        return tbc;
    }

private:
    bool tb;
    bool ti;
    bool tu;
    bool ts;
    QColor tc;
    QColor tbc;
};

#endif // FORMATSTATE_H
