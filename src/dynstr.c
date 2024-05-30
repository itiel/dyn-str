// dynstr.c

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "dynstr.h"

int DynStr_init (DynStr_t ** dStr) {
  int retVal = 0;

  char * strContent = NULL;

  *dStr = calloc(1, sizeof(DynStr_t));

  if (*dStr == NULL) {
    retVal = -1;
    goto end;
  }

  strContent = calloc(0, sizeof(char));

  if (strContent == NULL) {
    retVal = -1;
    goto end;
  }

  (*dStr)->content = strContent;

  end:

  if (retVal != 0) {
    if (strContent != NULL) {
      free((*dStr)->content);
    }

    if (*dStr != NULL) {
      free(*dStr);
      *dStr = NULL;
    }
  }

  return retVal;
}

int DynStr_end (DynStr_t ** dStr) {
  int retVal = 0;

  if (*dStr != NULL) {
    if ((*dStr)->content != NULL) {
      free((*dStr)->content);
    }

    free(*dStr);
    *dStr = NULL;
  }

  return retVal;
}

int DynStr_fromLiteral (DynStr_t ** dStr, char * srcLit) {
  int retVal = 0;
  int resVal;

  resVal = DynStr_init(dStr);

  if (resVal != 0) {
    retVal = -1;
    goto end;
  }

  resVal = DynStr_concatLiteral(*dStr, srcLit);

  if (resVal != 0) {
    retVal = -1;
    goto end;
  }

  end:

  if (retVal != 0) {
    DynStr_end(dStr);
  }

  return retVal;
}

int DynStr_fromDynStr (DynStr_t ** dStr, DynStr_t * srcDStr) {
  int retVal = 0;
  int resVal;

  resVal = DynStr_init(dStr);

  if (resVal != 0) {
    retVal = -1;
    goto end;
  }

  resVal = DynStr_concatDynStr(*dStr, srcDStr);

  if (resVal != 0) {
    retVal = -1;
    goto end;
  }

  end:

  if (retVal != 0) {
    DynStr_end(dStr);
  }

  return retVal;
}

int DynStr_concatLiteral (DynStr_t * dStr, char * srcLit) {
  int retVal = 0;
  int resVal;

  size_t srcSize = strlen(srcLit);

  resVal = DynStr_concat(dStr, srcLit, srcSize);

  if (resVal != 0) {
    retVal = -1;
    goto end;
  }

  end:

  return retVal;
}

int DynStr_concatDynStr (DynStr_t * dStr, DynStr_t * srcDStr) {
  int retVal = 0;
  int resVal;

  resVal = DynStr_concat(dStr, srcDStr->content, srcDStr->count);

  if (resVal != 0) {
    retVal = -1;
    goto end;
  }

  end:

  return retVal;
}

int DynStr_concat (DynStr_t * dStr, char * src, size_t srcSize) {
  int retVal = 0;
  int resVal;

  size_t requiredCapacity = dStr->count + srcSize;

  resVal = DynStr_reserve(dStr, requiredCapacity);

  if (resVal != 0) {
    retVal = -1;
    goto end;
  }

  memmove(dStr->content + dStr->count, src, srcSize);
  dStr->count += srcSize;

  end:

  return retVal;
}

int DynStr_reserve (DynStr_t * dStr, size_t requiredCapacity) {
  int retVal = 0;

  if (requiredCapacity > dStr->capacity) {
    char * newContent = realloc(dStr->content, requiredCapacity);
    
    if (newContent == NULL) {
      retVal = -1;
      goto end; 
    }

    dStr->content = newContent;
    dStr->capacity = requiredCapacity;
  }

  end:
  
  return retVal;
}

int DynStr_compare (DynStr_t * dStr1, DynStr_t * dStr2, int * result) {
  int retVal = 0;

  *result = dStr1->count == dStr2->count;

  if (!(*result)) {
    goto end;
  }
  
  *result = (memcmp(dStr1->content, dStr2->content, dStr1->count) == 0);

  end:

  return retVal;
}

int DynStr_ensureNullTermination(DynStr_t *dStr) {
  int retVal = 0;
  int resVal;

  resVal = DynStr_reserve(dStr, dStr->count + 1);

  if (resVal != 0) {
    retVal = -1;
    goto end;
  }

  dStr->content[dStr->count] = '\0';

  end:

  return retVal;
}

