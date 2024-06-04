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

  strContent = malloc(DYNSTR_EXTRA_CAPACITY);

  if (strContent == NULL) {
    retVal = -1;
    goto end;
  }

  (*dStr)->content = strContent;
  (*dStr)->capacity = DYNSTR_EXTRA_CAPACITY;

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

int DynStr_fromCStr (DynStr_t ** dStr, char * srcCStr) {
  int retVal = 0;
  int resVal;

  resVal = DynStr_init(dStr);

  if (resVal != 0) {
    retVal = -1;
    goto end;
  }

  size_t srcSize = strlen(srcCStr);
  size_t requiredCapacity = srcSize;

  resVal = DynStr_reserve(*dStr, requiredCapacity);
  
  if (resVal != 0) {
    retVal = -1;
    goto end;
  }

  char * dest = (*dStr)->content;
  char * src = srcCStr;

  memmove(dest, src, srcSize);
  
  (*dStr)->count += srcSize;

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

  size_t srcSize = srcDStr->count;
  size_t requiredCapacity = (*dStr)->count + srcSize;

  resVal = DynStr_reserve(*dStr, requiredCapacity);
  
  if (resVal != 0) {
    retVal = -1;
    goto end;
  }

  char * dest = (*dStr)->content + (*dStr)->count;
  char * src = srcDStr->content;

  memmove(dest, src, srcSize);
  
  (*dStr)->count += srcSize;

  end:

  if (retVal != 0) {
    DynStr_end(dStr);
  }

  return retVal;
}

int DynStr_fromDynStrOpt (DynStr_t ** dStr, DynStr_t * srcDStr, DynStrOptions_t opt) {
  int retVal = 0;
  int resVal;

  if (opt.offset + opt.count > srcDStr->count) {
    retVal = -1;
    goto end;
  }

  resVal = DynStr_init(dStr);

  if (resVal != 0) {
    retVal = -1;
    goto end;
  }

  resVal = DynStr_reserve(*dStr, opt.count);

  if (resVal != 0) {
    retVal = -1;
    goto end;
  }

  char * dest = (*dStr)->content;
  char * src = srcDStr->content + opt.offset;  

  memmove(dest, src, opt.count);
  
  (*dStr)->count = opt.count;

  end:

  return retVal;
}

int DynStr_concatCStr (DynStr_t * dStr, char * srcCStr) {
  int retVal = 0;
  int resVal;

  size_t srcSize = strlen(srcCStr);
  size_t requiredCapacity = dStr->count + srcSize;

  resVal = DynStr_reserve(dStr, requiredCapacity);
  
  if (resVal != 0) {
    retVal = -1;
    goto end;
  }

  char * dest = dStr->content + dStr->count;
  char * src = srcCStr;

  memmove(dest, src, srcSize);
  
  dStr->count += srcSize;

  end:

  return retVal;
}

int DynStr_concatDynStr (DynStr_t * dStr, DynStr_t * srcDStr) {
  int retVal = 0;
  int resVal;

  size_t srcSize = srcDStr->count;
  size_t requiredCapacity = dStr->count + srcSize;

  resVal = DynStr_reserve(dStr, requiredCapacity);
  
  if (resVal != 0) {
    retVal = -1;
    goto end;
  }

  char * dest = dStr->content + dStr->count;
  char * src = srcDStr->content;

  memmove(dest, src, srcSize);
  
  dStr->count += srcSize;

  end:

  return retVal;
}

int DynStr_concatDynStrOpt (DynStr_t * dStr, DynStr_t * srcDStr, DynStrOptions_t opt) {
  int retVal = 0;
  int resVal;

  if (opt.offset + opt.count > srcDStr->count) {
    retVal = -1;
    goto end;
  }

  size_t srcSize = opt.count;
  size_t requiredCapacity = dStr->count + srcSize;

  resVal = DynStr_reserve(dStr, requiredCapacity);

  if (resVal != 0) {
    retVal = -1;
    goto end;
  }

  char * dest = dStr->content + dStr->count;
  char * src = srcDStr->content + opt.offset;  

  memmove(dest, src, srcSize);
  
  dStr->count += srcSize;

  end:

  return retVal;
}

int DynStr_reserve (DynStr_t * dStr, size_t requiredCapacity) {
  int retVal = 0;

  if (requiredCapacity > dStr->capacity) {
    char * newContent = realloc(dStr->content, requiredCapacity + DYNSTR_EXTRA_CAPACITY);
    
    if (newContent == NULL) {
      retVal = -1;
      goto end; 
    }

    dStr->content = newContent;
    dStr->capacity = requiredCapacity + DYNSTR_EXTRA_CAPACITY;
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

int DynStr_toCStr (DynStr_t * dStr, char ** destCStr) {
  int retVal = 0;

  *destCStr = malloc(dStr->count + 1);

  if (*destCStr == NULL) {
    retVal = -1;
    goto end;
  }

  char * dest = *destCStr;
  char * src = dStr->content;

  memmove(dest, src, dStr->count);

  (*destCStr)[dStr->count] = '\0';

  end:

  return retVal;
}

