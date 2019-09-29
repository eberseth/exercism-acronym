#include "acronym.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

char* abbreviate(const char* phrase)
{
   if (NULL == phrase)
      return NULL;

   size_t len = strlen(phrase);
   if (0 == len)
      return NULL;

   // The resultant abbreviation will not be more that half the characters in the phrase due to
   // the ratio between the acronym character and other characters (whitespace and non-acronym)
   len = len / 2 + 1;

   // Create return string with space for null termination
   char* acronym = (char*)malloc(len + 1);
   if (NULL == acronym)
      return NULL;

   char* cur_acronym = acronym;
   bool last_ignore = true;

   while (*phrase)
   {
      if (isalpha(*phrase) || ('\'' == *phrase))
      {
         if (last_ignore)
         {
            *(cur_acronym++) = toupper(*phrase);
         }
         last_ignore = false;
      }
      else if (isspace(*phrase) || ispunct(*phrase))
      {
         last_ignore = true;
      }

      phrase++;
   }

   *cur_acronym = '\0';

   // If there is no acronym then there is nothing to return
   if (cur_acronym == acronym)
   {
      free(acronym);
      acronym = NULL;
   }

   return acronym;
}
