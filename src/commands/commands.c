
//
// commands.c
//

#include "EmojicodeAPI.h"
#include "EmojicodeString.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

PackageVersion getVersion(){
  return (PackageVersion){0, 1};
}

Something runCommand(Thread *thread) {
  FILE *fp;
  // char *output;
  char *command = stringToChar(stackGetVariable(0, thread).object->value);
  char buffer[1024];
  char stdout[8388608]; // 2^23 bytes

  /* Open the command for reading. */
  fp = popen(command, "r");
  if (fp == NULL) {
    printf("Failed to run command\n" );
    exit(1);
  }

  /* Read the output a line at a time */
  while (fgets(buffer, sizeof(buffer), fp) != NULL) {
    strcat(stdout, buffer);
  }

  pclose(fp);

  Object *string = stringFromChar(stdout);

  return somethingObject(string);
}

ClassMethodHandler handlerPointerForClassMethod(EmojicodeChar cl, EmojicodeChar symbol) {

  if(cl == 0x1F916) { // 🤖
    switch (symbol) {
      case 0x2328: // ⌨
        return runCommand;
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
