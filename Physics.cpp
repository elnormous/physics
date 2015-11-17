//
//  Physics.cpp
//  Bursch
//
//  Created by Elviss Strazdins on 20.06.2014.
//  Copyright (c) 2014 Bool Games. All rights reserved.
//
#include "Physics.h"
#include "Body.h"
#include "Utils.h"
#include "Space.h"

USING_NS_CC;

namespace BearSlayer
{
    Physics::Physics(const cocos2d::AABB2& worldSize):
        _worldSize(worldSize)
	{
        cocos2d::Vec2 size = cocos2d::Vec2(_worldSize._max - _worldSize._min);
        
        _spacesX = ceilf(size.x / SPACE_SIZE);
        _spacesY = ceilf(size.y / SPACE_SIZE);
	}

	Physics::~Physics()
	{

	}
    
    bool Physics::checkCollision(Body* body1, Body* body2, const Vec2& change)
    {
        if (body1->_shape == Body::Shape::Box &&
            body2->_shape == Body::Shape::Box)
        {
            return boxBoxCheck(body1->_position + change, body1->_size, body2->_position, body2->_size);
        }
        else if (body1->_shape == Body::Shape::Circle &&
                 body2->_shape == Body::Shape::Circle)
        {
            return circleCircleCheck(body1->_position + change, body1->_radius, body2->_position, body2->_radius);
        }
        else if (body1->_shape == Body::Shape::Circle &&
                 body2->_shape == Body::Shape::Box)
        {
            return circleBoxCheck(body1->_position + change, body1->_radius, body2->_position, body2->_size);
        }
        else if (body1->_shape == Body::Shape::Box &&
                 body2->_shape == Body::Shape::Circle)
        {
            return circleBoxCheck(body2->_position, body2->_radius, body1->_position + change, body1->_size);
        }
        
        return false;
    }
    
	void Physics::update(float delta, uint32_t iterations)
	{
        _locked = true;
        
        for (Body* body : _bodies)
        {
            body->_debugCollided = false;
            //std::vector<Contact> oldContacts = body->_contacts;
            body->clearContacts();
        }
        
        for (uint32_t i = 0; i < iterations; i++)
        {
            for (Body* body : _bodies)
            {
                // if body is enabled and is sensor or moving
                if (body->_enabled &&
                    (!body->_velocity.isZero() || body->_sensor))
                {
                    Vec2 change = (body->_velocity * delta) / (float)iterations;
                    
                    AABB2 bodyAABB = body->_aabb;
                    bodyAABB._min += (change + body->_position);
                    bodyAABB._max += (change + body->_position);
                    
                    std::vector<Body*> possibleBodies;
                    
                    for (const Space* space : body->getSpaces())
                    {
                        for (Body* otherBody : space->_bodies)
                        {
                            if (body != otherBody &&
                                otherBody->_enabled &&
                                (body->_mask & otherBody->_category) != 0)
                            {
                                // TODO: try to use distance instead of aabb check
                                AABB2 otherBodyAABB = body->_aabb;
                                otherBodyAABB._min += (otherBody->_position);
                                otherBodyAABB._max += (otherBody->_position);
                                
                                if (bodyAABB.intersects(otherBodyAABB))
                                {
                                    possibleBodies.push_back(otherBody);
                                }
                            }
                        }
                    }
                    
                    Vec2 bodyPosition = body->getPosition();
                    
                    std::sort(possibleBodies.begin(), possibleBodies.end(), [&bodyPosition](Body* body1, Body* body2) {
                        //return bodyPosition.distanceSquared(body1->getPosition()) < bodyPosition.distanceSquared(body2->getPosition());
                        Vec2 diff1 = bodyPosition - body1->getPosition();
                        Vec2 diff2 = bodyPosition - body2->getPosition();
                        
                        return mabs(diff1.x) + mabs(diff1.y) < mabs(diff2.x) + mabs(diff2.y);
                    });
                    
                    for (Body* otherBody : possibleBodies)
                    {
                        if (checkCollision(body, otherBody, change))
                        {
                            Vec2 newNormal = body->_position - otherBody->_position;
                            
                            /*Vec2 sizeSum = Vec2(body->_size.width / 2.0f + otherBody->_size.width / 2.0f,
                                                body->_size.height / 2.0f + otherBody->_size.height / 2.0f);
                            
                            newNormal.x = newNormal.x / sizeSum.x;
                            newNormal.y = newNormal.y / sizeSum.y;*/
                            
                            if (mabs(newNormal.x) > mabs(newNormal.y))
                            {
                                if (newNormal.x != 0.0f) newNormal.x /= mabs(newNormal.x);
                                newNormal.y = 0.0f;
                            }
                            else
                            {
                                newNormal.x = 0.0f;
                                if (newNormal.y != 0.0f) newNormal.y /= mabs(newNormal.y);
                            }
                            
                            if (!otherBody->isSensor())
                            {
                                //normal
                                if (!newNormal.isZero())
                                {
                                    if (newNormal.x != 0.0f)
                                    {
                                        change.x = 0.0f;
                                    }
                                    
                                    if (newNormal.y != 0.0f)
                                    {
                                        change.y = 0.0f;
                                    }
                                }
                            }
                            
                            /*if (newNormal.x != 0.0f)
                            {
                                log("GOT");
                            }*/
                            
                            Contact contact;
                            contact.bodyA = body;
                            contact.bodyB = otherBody;
                            contact.normal = newNormal;
                            body->addContact(contact);
                            
                            body->_debugCollided = true;
                            
                            Contact contact2;
                            contact2.bodyA = otherBody;
                            contact2.bodyB = body;
                            contact2.normal = -newNormal;
                            otherBody->addContact(contact2);
                            
                            otherBody->_debugCollided = true;
                        }
                    }
                    
                    body->_velocity = (change / delta) * (float)iterations;
                    body->_position += change;
                    body->updateSpace();
                }
            }
		}
        
        _locked = false;
	}

    Body* Physics::createBody(const Body::Def& bodyDef)
	{
        assert(!_locked && "World is locked");
        
        Body* body = nullptr;
        
        if (bodyDef.shape == Body::Shape::Box ||
            bodyDef.shape == Body::Shape::Circle)
        {
            body = new Body(bodyDef, this);
            
            _bodies.pushBack(body);
            body->release();
        }
		
		return body;
	}

	void Physics::removeBody(Body* body)
    {
        assert(!_locked && "World is locked");
        
		auto i = _bodies.find(body);
		
		if (i != _bodies.end())
		{
			_bodies.erase(i);
		}
	}
    
    Body* Physics::getClosestBody(const cocos2d::Vec2& position, uint32_t mask) const
    {
        Body* result = nullptr;
        float closestDistance;
        
        for (Body* body : _bodies)
        {
            if (mask == 0 || body->_category & mask)
            {
                float distance = position.distanceSquared(body->_position);
                
                if (!result ||
                    distance < closestDistance)
                {
                    closestDistance = distance;
                    result = body;
                }
            }
        }
        
        return result;
    }
    
    void Physics::reset()
    {
        for (Body* body : _bodies)
        {
            body->_contacts.clear();
            body->_velocity.x = 0.0f;
            body->_velocity.y = 0.0f;
        }
    }
    
    Space* Physics::getSpace(int32_t spaceId)
    {
        Spaces::iterator i = _spaces.find(spaceId);
        
        if (i != _spaces.end())
        {
            return i->second;
        }
        else
        {
            Space* space = new Space(spaceId);
            _spaces.insert(spaceId, space);
            space->release();
            return space;
        }
    }
}
