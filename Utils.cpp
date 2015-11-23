#include "Utils.h"

USING_NS_CC;

bool boxBoxCheck(const Vec2& aPos, const Size& aSize, const Vec2& bPos, const Size& bSize)
{
    // calculating distance from centers
    const Vec2 offset = bPos - aPos; // vector from A to B
    
    return mabs(offset.x) <= (aSize.width + bSize.width) / 2.0f &&
        mabs(offset.y) <= (aSize.height + bSize.height) / 2.0f;
}

bool circleBoxCheck(const Vec2& circle, float circleRadius, const Vec2& rectPos, const Size& rectSize)
{
    Vec2 circleDistance;
    circleDistance.x = mabs(circle.x - rectPos.x);
    circleDistance.y = mabs(circle.y - rectPos.y);
    
    if (circleDistance.x > (rectSize.width / 2.0f + circleRadius)) { return false; }
    if (circleDistance.y > (rectSize.height / 2.0f + circleRadius)) { return false; }
    
    if (circleDistance.x <= (rectSize.width / 2.0f)) { return true; }
    if (circleDistance.y <= (rectSize.height / 2.0f)) { return true; }
    
    float a = circleDistance.x - rectSize.width / 2.0f;
    float b = circleDistance.y - rectSize.height / 2.0f;
    
    float cornerDistanceSQ = (a * a) + (b * b);
    
    return (cornerDistanceSQ <= circleRadius * circleRadius);
}
