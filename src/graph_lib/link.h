#pragma once

#ifndef LINK_H
#define LINK_H

#include "constants.h"

struct Link
{
    UINT from;
    UINT to;
    float length;
    Link(UINT _f, UINT _t, float _l) :from(_f), to(_t), length(_l) {}
};

bool operator< (const Link& a, const Link& b);
bool operator== (const Link& a, const Link& b);

#endif