//
//  Utils.h
//  Bursch
//
//  Created by Elviss Strazdins on 09.07.2014.
//
//

#pragma once

template <typename T> int sgn(T val)
{
    return (T(0) < val) - (val < T(0));
}

inline float lerp(float v0, float v1, float t)
{
	return v0 + t * (v1 - v0);
}

bool boxBoxCheck(const cocos2d::Vec2& aPos, const cocos2d::Size& aSize, const cocos2d::Vec2& bPos, const cocos2d::Size& bSize);

inline bool circleCircleCheck(const cocos2d::Vec2& aPos, float aRadius, const cocos2d::Vec2& bPos, float bRadius)
{
    return aPos.distanceSquared(bPos) <= (aRadius * aRadius) + (bRadius * bRadius);
}

bool circleBoxCheck(const cocos2d::Vec2& aPos, float aRadius, const cocos2d::Vec2& bPos, const cocos2d::Size& bSize);

inline float mabs(float i)
{
    (*reinterpret_cast<uint32_t*>(&i)) &= 0x7fffffff;
    return i;
}
