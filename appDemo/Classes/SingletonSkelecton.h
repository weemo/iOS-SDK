/*
 *  SingletonSkelecton.h
 *  dbRadio
 *
 *  Created by hongbo yang on 10-7-22.
 *  Copyright 2010 Douban Inc. All rights reserved.
 *
 */
//this skelecton is from Apple Mac OSX reference Library: Cocoa Fundamentals Guide: http://developer.apple.com/mac/library/documentation/Cocoa/Conceptual/CocoaFundamentals/CocoaObjects/CocoaObjects.html#//apple_ref/doc/uid/TP40002974-CH4-97333-CJBDDIBI
#define DEFINE_SHARED_INSTANCE_USING_BLOCK(block) \
static dispatch_once_t pred = 0; \
__strong static id _sharedObject = nil; \
dispatch_once(&pred, ^{ \
_sharedObject = block(); \
}); \
return _sharedObject;

#define DECLARE_INTERFACE_SINGLETON_CLASS_BEGIN(classname, superclassname) \
@interface classname : superclassname

#define DECLARE_INTERFACE_SINGLETON_CLASS_END(classname) \
+ (classname *)shared##classname; \
@end

#define SYNTHESIZE_SINGLETON_FOR_CLASS(classname) \
\
static classname *shared##classname = nil; \
\
+ (classname *)shared##classname \
{ \
@synchronized(self) \
{ \
if (shared##classname == nil) \
{ \
shared##classname = [[self alloc] init]; \
} \
} \
\
return shared##classname; \
} \
\
+ (id)allocWithZone:(NSZone *)zone \
{ \
@synchronized(self) \
{ \
if (shared##classname == nil) \
{ \
shared##classname = [super allocWithZone:zone]; \
return shared##classname; \
} \
} \
\
return nil; \
} \
\
- (id)copyWithZone:(NSZone *)zone \
{ \
return self; \
} \
\
- (id)retain \
{ \
return self; \
} \
\
- (NSUInteger)retainCount \
{ \
return NSUIntegerMax; \
} \
\
- (void)release \
{ \
} \
\
- (id)autorelease \
{ \
return self; \
}


#define IMPLEMENT_SINGLETON_CLASS_BEGIN(classname) \
\
static classname * __shared##classname##Manager = nil; \
\
@implementation classname \
+ (classname *)shared##classname \
{ \
if (nil == __shared##classname##Manager) { \
__shared##classname##Manager = [[super allocWithZone:NULL] init]; \
} \
return __shared##classname##Manager; \
} \
\
+ (id)allocWithZone:(NSZone *)zone \
{ \
return [[self shared##classname] retain]; \
} \
\
- (id)copyWithZone:(NSZone *)zone \
{ \
return self; \
} \
\
- (id)retain \
{ \
return self; \
} \
\
- (NSUInteger)retainCount \
{ \
return NSUIntegerMax;\
} \
\
- (oneway void)release \
{ \
\
} \
\
- (id)autorelease \
{ \
return self; \
}



#define IMPLEMENT_SINGLETON_CLASS_END() \
@end
