//
//  Created by Rohan Kuruvilla
//  Copyright (c) 2012 Zynga Inc. All rights reserved.
//
#ifndef __JS_BINDINGS_CHIPMUNK_FUNCTIONS_HPP__
#define __JS_BINDINGS_CHIPMUNK_FUNCTIONS_HPP__

JSBool JSPROXY_cpArbiterGetCount(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpArbiterGetDepth(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpArbiterGetElasticity(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpArbiterGetFriction(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpArbiterGetNormal(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpArbiterGetPoint(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpArbiterGetSurfaceVelocity(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpArbiterIgnore(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpArbiterIsFirstContact(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpArbiterSetElasticity(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpArbiterSetFriction(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpArbiterSetSurfaceVelocity(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpArbiterTotalImpulse(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpArbiterTotalImpulseWithFriction(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpArbiterTotalKE(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpAreaForCircle(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpAreaForSegment(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBBArea(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBBClampVect(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBBContainsBB(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBBContainsVect(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBBExpand(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBBIntersects(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBBIntersectsSegment(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBBMerge(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBBMergedArea(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBBNew(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBBNewForCircle(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBBSegmentQuery(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBBWrapVect(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBodyActivate(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBodyActivateStatic(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBodyAlloc(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBodyApplyForce(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBodyApplyImpulse(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBodyDestroy(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBodyFree(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBodyGetAngVel(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBodyGetAngVelLimit(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBodyGetAngle(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBodyGetForce(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBodyGetMass(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBodyGetMoment(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBodyGetPos(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBodyGetRot(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBodyGetSpace(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBodyGetTorque(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBodyGetVel(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBodyGetVelAtLocalPoint(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBodyGetVelAtWorldPoint(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBodyGetVelLimit(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBodyInit(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBodyInitStatic(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBodyIsRogue(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBodyIsSleeping(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBodyIsStatic(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBodyKineticEnergy(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBodyLocal2World(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBodyNew(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBodyNewStatic(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBodyResetForces(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBodySetAngVel(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBodySetAngVelLimit(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBodySetAngle(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBodySetForce(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBodySetMass(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBodySetMoment(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBodySetPos(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBodySetTorque(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBodySetVel(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBodySetVelLimit(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBodySleep(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBodySleepWithGroup(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBodyUpdatePosition(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBodyUpdateVelocity(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBodyWorld2Local(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBoxShapeNew(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpBoxShapeNew2(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpCircleShapeGetOffset(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpCircleShapeGetRadius(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpCircleShapeNew(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpConstraintActivateBodies(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpConstraintDestroy(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpConstraintFree(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpConstraintGetA(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpConstraintGetB(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpConstraintGetErrorBias(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpConstraintGetImpulse(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpConstraintGetMaxBias(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpConstraintGetMaxForce(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpConstraintGetSpace(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpConstraintSetErrorBias(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpConstraintSetMaxBias(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpConstraintSetMaxForce(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpDampedRotarySpringGetDamping(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpDampedRotarySpringGetRestAngle(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpDampedRotarySpringGetStiffness(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpDampedRotarySpringNew(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpDampedRotarySpringSetDamping(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpDampedRotarySpringSetRestAngle(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpDampedRotarySpringSetStiffness(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpDampedSpringGetAnchr1(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpDampedSpringGetAnchr2(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpDampedSpringGetDamping(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpDampedSpringGetRestLength(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpDampedSpringGetStiffness(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpDampedSpringNew(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpDampedSpringSetAnchr1(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpDampedSpringSetAnchr2(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpDampedSpringSetDamping(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpDampedSpringSetRestLength(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpDampedSpringSetStiffness(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpGearJointGetPhase(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpGearJointGetRatio(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpGearJointNew(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpGearJointSetPhase(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpGearJointSetRatio(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpGrooveJointGetAnchr2(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpGrooveJointGetGrooveA(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpGrooveJointGetGrooveB(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpGrooveJointNew(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpGrooveJointSetAnchr2(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpGrooveJointSetGrooveA(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpGrooveJointSetGrooveB(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpInitChipmunk(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpMomentForBox(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpMomentForBox2(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpMomentForCircle(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpMomentForSegment(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpPinJointGetAnchr1(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpPinJointGetAnchr2(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpPinJointGetDist(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpPinJointNew(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpPinJointSetAnchr1(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpPinJointSetAnchr2(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpPinJointSetDist(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpPivotJointGetAnchr1(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpPivotJointGetAnchr2(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpPivotJointNew(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpPivotJointNew2(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpPivotJointSetAnchr1(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpPivotJointSetAnchr2(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpPolyShapeGetNumVerts(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpPolyShapeGetVert(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpRatchetJointGetAngle(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpRatchetJointGetPhase(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpRatchetJointGetRatchet(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpRatchetJointNew(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpRatchetJointSetAngle(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpRatchetJointSetPhase(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpRatchetJointSetRatchet(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpResetShapeIdCounter(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpRotaryLimitJointGetMax(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpRotaryLimitJointGetMin(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpRotaryLimitJointNew(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpRotaryLimitJointSetMax(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpRotaryLimitJointSetMin(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSegmentShapeGetA(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSegmentShapeGetB(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSegmentShapeGetNormal(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSegmentShapeGetRadius(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSegmentShapeNew(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSegmentShapeSetNeighbors(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpShapeCacheBB(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpShapeDestroy(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpShapeFree(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpShapeGetBB(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpShapeGetBody(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpShapeGetCollisionType(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpShapeGetElasticity(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpShapeGetFriction(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpShapeGetGroup(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpShapeGetLayers(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpShapeGetSensor(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpShapeGetSpace(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpShapeGetSurfaceVelocity(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpShapePointQuery(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpShapeSetBody(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpShapeSetCollisionType(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpShapeSetElasticity(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpShapeSetFriction(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpShapeSetGroup(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpShapeSetLayers(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpShapeSetSensor(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpShapeSetSurfaceVelocity(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpShapeUpdate(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSimpleMotorGetRate(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSimpleMotorNew(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSimpleMotorSetRate(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSlideJointGetAnchr1(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSlideJointGetAnchr2(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSlideJointGetMax(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSlideJointGetMin(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSlideJointNew(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSlideJointSetAnchr1(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSlideJointSetAnchr2(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSlideJointSetMax(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSlideJointSetMin(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSpaceActivateShapesTouchingShape(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSpaceAddBody(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSpaceAddConstraint(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSpaceAddShape(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSpaceAddStaticShape(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSpaceAlloc(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSpaceContainsBody(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSpaceContainsConstraint(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSpaceContainsShape(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSpaceDestroy(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSpaceFree(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSpaceGetCollisionBias(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSpaceGetCollisionPersistence(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSpaceGetCollisionSlop(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSpaceGetCurrentTimeStep(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSpaceGetDamping(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSpaceGetEnableContactGraph(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSpaceGetGravity(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSpaceGetIdleSpeedThreshold(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSpaceGetIterations(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSpaceGetSleepTimeThreshold(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSpaceGetStaticBody(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSpaceInit(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSpaceIsLocked(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSpaceNew(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSpacePointQueryFirst(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSpaceReindexShape(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSpaceReindexShapesForBody(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSpaceReindexStatic(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSpaceRemoveBody(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSpaceRemoveConstraint(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSpaceRemoveShape(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSpaceRemoveStaticShape(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSpaceSetCollisionBias(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSpaceSetCollisionPersistence(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSpaceSetCollisionSlop(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSpaceSetDamping(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSpaceSetEnableContactGraph(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSpaceSetGravity(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSpaceSetIdleSpeedThreshold(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSpaceSetIterations(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSpaceSetSleepTimeThreshold(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSpaceStep(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpSpaceUseSpatialHash(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpfabs(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpfclamp(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpfclamp01(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpflerp(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpflerpconst(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpfmax(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpfmin(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpv(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpvadd(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpvclamp(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpvcross(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpvdist(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpvdistsq(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpvdot(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpveql(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpvforangle(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpvlength(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpvlengthsq(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpvlerp(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpvlerpconst(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpvmult(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpvnear(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpvneg(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpvnormalize(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpvnormalize_safe(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpvperp(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpvproject(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpvrotate(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpvrperp(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpvslerp(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpvslerpconst(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpvsub(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpvtoangle(JSContext *cx, uint32_t argc, jsval *vp);
JSBool JSPROXY_cpvunrotate(JSContext *cx, uint32_t argc, jsval *vp);

#endif /* __JS_BINDINGS_CHIPMUNK_FUNCTIONS_HPP__ */

