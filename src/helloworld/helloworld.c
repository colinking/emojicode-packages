
//
// helloworld.c
//

#include "EmojicodeAPI.h"
#include "EmojicodeString.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

PackageVersion getVersion(){
  return (PackageVersion){0, 1};
}

Something helloWorld(Thread *thread) {
  char stringBuffer[] = "Hello World!";
  Object *string = stringFromChar(stringBuffer);

  return somethingObject(string);
}

Something helloPerson(Thread *thread) {
  char *name = stringToChar(stackGetVariable(0, thread).object->value);

  char greeting[strlen(name)+7];
  sprintf(greeting, "Hello %s!", name);

  Object *string = stringFromChar(greeting);

  return somethingObject(string);
}

ClassMethodHandler handlerPointerForClassMethod(EmojicodeChar cl, EmojicodeChar symbol) {

  if(cl == 0x1F44B) { // 👋
    switch (symbol) {
      case 0x1F30D: // 🌍
        return helloWorld;
      case 0x1F64B: // 🙋
        return helloPerson;
    }
  }

  return NULL;
}

MethodHandler handlerPointerForMethod(EmojicodeChar cl, EmojicodeChar symbol){
  return NULL;
}

InitializerHandler handlerPointerForInitializer(EmojicodeChar cl, EmojicodeChar symbol){
  return NULL;
}

Marker markerPointerForClass(EmojicodeChar cl){
  return NULL;
}

uint_fast32_t sizeForClass(Class *cl, EmojicodeChar name) {
  return 0;
}

Deinitializer deinitializerPointerForClass(EmojicodeChar cl){
  return NULL;
}
