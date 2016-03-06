//
//  EmojicodeAPI.h
//  Emojicode
//
//  Created by Theo Weidmann on 12.01.15.
//  Copyright (c) 2015 Theo Weidmann. All rights reserved.
//

/*
 * Welcome to Emojicode!
 * This API file is the point to get started if you want to write a package (or something else interfacing or using Emojicode).
 * You might need to also include `EmojicodeString.h`, `EmojicodeList.h` and `EmojicodeDictionary.h`. 
 * Follow the Emojicode style guide.
 */

#ifndef Emojicode_EmojicodeAPI_h
#define Emojicode_EmojicodeAPI_h

#include "EmojicodeShared.h"

typedef struct Class Class;
typedef struct Method Method;
typedef struct ClassMethod ClassMethod;
typedef struct Initializer Initializer;
typedef struct List List;
typedef struct Thread Thread;
typedef struct StackFrame StackFrame;

extern Class *CL_STRING;
extern Class *CL_LIST;
extern Class *CL_ERROR;
extern Class *CL_DATA;
extern Class *CL_DICTIONARY;
extern Class *CL_ENUMERATOR;
extern Class *CL_CAPTURED_METHOD_CALL;
extern Class *CL_CLOSURE;

typedef struct Object {
    /** The object’s class. */
    Class *class;
    /** The size of this object: the size of the Object struct and the value area. */
    size_t size;
    /** The objects garabage collection state */
    struct Object *newLocation;
    /**
     * A pointer to the allocated @c value area. This area is as large as specified in the class.
     * @warning Never change the content of this variable as the Garbage Collector updates this field
     * in each cycle.
     */
    void *value;
} Object;


#define T_OBJECT 0
#define T_INTEGER 1
#define T_BOOLEAN 2
#define T_SYMBOL 3
#define T_DOUBLE 4

typedef uint_fast8_t Type;
typedef unsigned char Byte;

/** Either a object reference or a primitive value. */
typedef struct {
    /** The type of the primitive or whether it contains an object reference. */
    Type type;
    union {
        EmojicodeInteger raw;
        double doubl;
        Object *object;
    };
} Something;

#if __SIZEOF_DOUBLE__ != 8
#warning Double does not match the size of an 64-bit integer
#endif

#define somethingObject(o) ((Something){T_OBJECT, .object = (o)})
#define somethingInteger(o) ((Something){T_INTEGER, (o)})
#define somethingSymbol(o) ((Something){T_SYMBOL, (o)})
#define somethingBoolean(o) ((Something){T_BOOLEAN, (o)})
#define somethingDouble(o) ((Something){T_DOUBLE, .doubl = (o)})
#define EMOJICODE_TRUE ((Something){T_BOOLEAN, 1})
#define EMOJICODE_FALSE ((Something){T_BOOLEAN, 0})
#define NOTHINGNESS ((Something){T_OBJECT, .object = NULL})

#define unwrapInteger(o) ((o).raw)
#define unwrapLong(o) (*(EmojicodeLong *)((o)->value))
#define unwrapBool(o) ((o).raw > 0)
#define unwrapSymbol(o) ((EmojicodeChar)(o).raw)

extern bool isNothingness(Something sth);

/** Whether this thing is a reference to a valid object. */
extern bool isRealObject(Something sth);

//MARK: Built In Classes

typedef struct String {
    /** The number of code points in @c characters. Strings are not null terminated! */
    EmojicodeInteger length;
    /** The characters of this string. Strings are not null terminated! */
    Object *characters;
} String;

typedef struct {
    EmojicodeInteger length;
    char *bytes;
} Data;

typedef struct {
    const char *message;
    EmojicodeInteger code;
} EmojicodeError;

extern Object* newError(const char *message, int code);


//MARK: Callables

/** You can use this function to call a callable object. It’s internally Garbage-Collector safe. */
extern Something executeCallableExtern(Object *callable, Something *args, Thread *thread);


//MARK: Primitive Objects

/**
 * Allocates a new object for the given class.
 * The @c value field will point to a value area as large as specified for the given class.
 * @param class The class of the object.
 * @warning GC-invoking
 */
extern Object* newObject(Class *class);

/** 
 * Allocates an object with an value area with the size given.
 * @param size The size of the value area.
 * @warning GC-invoking
 */
extern Object* newArray(size_t size);

/**
 * Trys to enlarge the given array object to the given size.
 * @param array An array object created by @c newArray.
 * @param size The new size.
 * @warning Do not use this method to shrink an array.
 * @warning GC-invoking
 */
extern Object* enlargeArray(Object *array, size_t size);


//MARK: Object-orientation

/** Returns true if @c cl or a superclass of @c cl conforms to the protocol. */
extern bool conformsTo(Class *cl, EmojicodeCoin index);

/** Returns true if @c a inherits from class @c from */
extern bool inheritsFrom(Class *a, Class *from);

/** Returns true if @c object is an instance of @c cl (or of a subclass of @c cl) */
extern bool instanceof(Object *object, Class *cl);


//MARK: Garbage Collection

/**
 * Marks the object @c O pointed to by the pointer @c P to which @c of points.
 * @warning This function will modify @c P to point to an exact copy of @c O after the function call.
 */
extern void mark(Object **of);


//MARK: Stack

/**
 * Pushes a new stack frame with the given values.
 * @c this The object/class context.
 * @c variable The number of variables to store in the stack frame.
 */
void stackPush(void *this, uint8_t variableCount, uint8_t argCount, Thread *thread);

/** Pops the current stack frame from the stack. */
void stackPop(Thread *thread);

/** Get the variable at the given index. */
Something stackGetVariable(uint8_t index, Thread *thread);

/** Set the variable at the given index. */
void stackSetVariable(uint8_t index, Something value, Thread *thread);

/** Decrements the variable at the given index. */
void stackDecrementVariable(uint8_t index, Thread *thread);
/** Increments the variable at the given index. */
void stackIncrementVariable(uint8_t index, Thread *thread);

Something* stackReserveFrame(void *t, uint8_t variableCount, Thread *thread);

void stackPushReservedFrame(Thread *thread);

/** Returns the object on which the method was called. */
Object* stackGetThis(Thread *);

/** Returns the class on which the method was called. */
Class* stackGetThisClass(Thread *thread);


//MARK: Packages

typedef Something (*MethodHandler)(Thread *thread);
typedef Something (*ClassMethodHandler)(Thread *thread);
typedef void (*InitializerHandler)(Thread *thread);
typedef void (*Marker)(Object *self);
typedef void (*Deinitializer)(void *value);

/**
 * Generates a secure random number. The integer is either generated using arc4random_uniform if available
 * or by reading from @c /dev/urandmon.
 * @param min The minimal integer (inclusive).
 * @param max The maximal integer (inclusive).
 */
extern EmojicodeInteger secureRandomNumber(EmojicodeInteger min, EmojicodeInteger max);

#endif
