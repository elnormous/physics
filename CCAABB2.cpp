/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "CCAABB2.h"

NS_CC_BEGIN

AABB2::AABB2()
{
    reset();
}

AABB2::AABB2(const Vec2& min, const Vec2& max)
{
    set(min, max);
}

AABB2::AABB2(const AABB2& box)
{
    set(box._min,box._max);
}

Vec2 AABB2::getCenter()
{
    Vec2 center;
    center.x = 0.5f*(_min.x+_max.x);
    center.y = 0.5f*(_min.y+_max.y);
    
    return center;
}

void AABB2::getCorners(Vec2 *dst) const
{
    assert(dst);
    
    // Near face, specified counter-clockwise looking towards the origin from the positive z-axis.
    // Left-top.
    dst[0].set(_min.x, _max.y);
    // Left-bottom.
    dst[1].set(_min.x, _min.y);
    // Right-bottom.
    dst[2].set(_max.x, _min.y);
    // Right-top.
    dst[3].set(_max.x, _max.y);
}

bool AABB2::intersects(const AABB2& aabb) const
{
    return ((_min.x >= aabb._min.x && _min.x <= aabb._max.x) || (aabb._min.x >= _min.x && aabb._min.x <= _max.x)) &&
           ((_min.y >= aabb._min.y && _min.y <= aabb._max.y) || (aabb._min.y >= _min.y && aabb._min.y <= _max.y));
}

bool AABB2::containPoint(const Vec2& point) const
{
    if (point.x < _min.x) return false;
    if (point.y < _min.y) return false;
    if (point.x > _max.x) return false;
    if (point.y > _max.y) return false;
    return true;
}

void AABB2::merge(const AABB2& box)
{
    // Calculate the new minimum point.
    _min.x = std::min(_min.x, box._min.x);
    _min.y = std::min(_min.y, box._min.y);
    
    // Calculate the new maximum point.
    _max.x = std::max(_max.x, box._max.x);
    _max.y = std::max(_max.y, box._max.y);
}

void AABB2::set(const Vec2& min, const Vec2& max)
{
    this->_min = min;
    this->_max = max;
}

void AABB2::reset()
{
    _min.set(99999.0f, 99999.0f);
    _max.set(-99999.0f, -99999.0f);
}

bool AABB2::isEmpty() const
{
    return _min.x > _max.x || _min.y > _max.y;
}

void AABB2::updateMinMax(const Vec2* point, ssize_t num)
{
    for (ssize_t i = 0; i < num; i++)
    {
        // Leftmost point.
        if (point[i].x < _min.x)
            _min.x = point[i].x;
        
        // Lowest point.
        if (point[i].y < _min.y)
            _min.y = point[i].y;
        
        // Rightmost point.
        if (point[i].x > _max.x)
            _max.x = point[i].x;
        
        // Highest point.
        if (point[i].y > _max.y)
            _max.y = point[i].y;
    }
}

NS_CC_END
