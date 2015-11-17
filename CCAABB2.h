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

#ifndef __CC_AABB2_H__
#define __CC_AABB2_H__

#include "base/ccMacros.h"
#include "math/CCMath.h"

NS_CC_BEGIN

/**
 * @addtogroup _3d
 * @{
 */

/**
 * Axis Aligned Bounding Box (AABB), usually calculate some rough but fast collision detection.
 */
class AABB2
{
    
public:
    /**
     * Constructor.
     * @lua new
     */
    AABB2();
    
    /**
     * Constructor.
     * @lua new
     */
    AABB2(const Vec2& min, const Vec2& max);
    
    /**
     * Constructor.
     */
    AABB2(const AABB2& box);
    
    /**
     * Gets the center point of the bounding box.
     */
    Vec2 getCenter();
    
    /* Near face, specified counter-clockwise looking towards the origin from the positive z-axis.
     * verts[0] : left top
     * verts[1] : left bottom
     * verts[2] : right bottom
     * verts[3] : right top
     */
    void getCorners(Vec2 *dst) const;
    
    /**
     * Tests whether this bounding box intersects the specified bounding object.
     */
    bool intersects(const AABB2& aabb) const;
    
    /**
     * check whether the point is in.
     */
    bool containPoint(const Vec2& point) const;
    
    /**
     * Sets this bounding box to the smallest bounding box
     * that contains both this bounding object and the specified bounding box.
     */
    void merge(const AABB2& box);
    
    /**
     * Sets this bounding box to the specified values.
     */
    void set(const Vec2& min, const Vec2& max);
    
    /**
     * Reset min and max value.If you invoke this method, isEmpty() shall return true.
     */
    void reset();
    
    /**
     * check the AABB object is empty(reset).
     */
    bool isEmpty() const;
    
    /**
     * update the _min and _max from the given point.
     */
    void updateMinMax(const Vec2* point, ssize_t num);
    
public:
    Vec2 _min;
    Vec2 _max;
};

// end of 3d group
/// @}

NS_CC_END

#endif
