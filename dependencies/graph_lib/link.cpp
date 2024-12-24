#include "link.h"

bool operator< (const Link& a, const Link& b)
{
    return a.from < b.from;
}

bool operator== (const Link& a, const Link& b)
{
    float res = (a.length - b.length);
    if (res < 0) { res = -res; }
    return (a.from == b.from) && (a.to == b.to) && (res < 0.1f);
}
