/*
 * Copyright 2010 Sébastien Aupetit <sebastien.aupetit@univ-tours.fr>
 *
 * This source code is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option) any
 * later version.
 *
 * This source code is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this source code. If not, see <http://www.gnu.org/licenses/>.
 *
 * $Id: MyString.c 293 2011-10-02 15:05:44Z sebtic $
 */

#include <MyString.h>
#include <limits.h>

/** Like the tolower() function. It converts the letter c to lower case, if possible.
 * @param c the letter to convert
 * @return the lower case letter associated to c if c is a letter, or c otherwise
 */
char IMPLEMENT(toLowerChar)(char c) {
     if('A' <= c && c <= 'Z')
    {
        c = (char)(c+('a'-'A'));
    }
    return c;
}

/** Like the toupper() function. It converts the letter c to upper case, if possible.
 * @param c the letter to convert
 * @return the upper case letter associated to c if c is a letter, or c otherwise
 */
char IMPLEMENT(toUpperChar)(char c) {
    if('a' <= c && c <= 'z')
    {
        c = (char)(c-('a'-'A'));
    }
    return c;
}

/** Like the strcmp() function. It compares the two strings str1 and str2.
 * It returns an integer less than, equal to, or greater than zero if str1 is found, respectively, to be less than, to match, or be greater
 * than str2.
 * @param str1 the first string
 * @param str2 the second string
 * @return an integer less than, equal to, or greater than zero if str1 is found, respectively, to be less than, to match, or be greater
 * than str2
 */
int IMPLEMENT(compareString)(const char * str1, const char * str2) {
    int i = 0;
    int compare = 0;
    while(compare == 0)
    {
        if(str1[i] == '\0' && str2[i] == '\0')
            break;
        if(str1[i] < str2[i] || (str1[i] == '\0' && str2[i] != '\0'))
            compare = -1;
        if(str1[i] > str2[i] || (str2[i] == '\0' && str1[i] != '\0'))
            compare = 1;
        i++;
    }

    return compare;
}

/** Like the strcasecmp() function. It compares the two strings str1 and str2, ignoring the case of the characters.
 * It returns an integer less than, equal to, or greater than zero if str1 is found, respectively, to be less than, to match, or be greater
 * than str2.
 * @param str1 the first string
 * @param str2 the second string
 * @return an integer less than, equal to, or greater than zero if str1 is found, respectively, to be less than, to match, or be greater
 * than str2
 */
int IMPLEMENT(icaseCompareString)(const char * str1, const char * str2) {

    size_t i = 0;
    int compare = 0;
    while(compare == 0)
    {
        if(str1[i] == '\0' && str2[i] == '\0')
            break;
        else if(str1[i] < str2[i] || (str1[i] == '\0' && str2[i] != '\0')) /* si on str1 est avant ou si on est a la fin de str1 */
            {
                if(('A' <= str1[i] && str1[i] <= 'Z') && ((int)str1[i] == (int)str2[i]-('a'-'A'))) /* Si str1 et str2 sont identiques a la majuscule pres */
                    compare = 0;
                else
                {
                    compare = -1;
                    break;
                }
            }
        else if(str1[i] > str2[i] || (str2[i] == '\0' && str1[i] != '\0'))
           {
               if(('A' <= str2[i] && str2[i] <= 'Z') && ((int)str1[i] == (int)str2[i]+('a'-'A'))) /* Si str1 et str2 sont identiques a la majuscule pres */
                    compare = 0;
                else
                {
                    compare = 1;
                    break;
                }
           }
        i++;
    }
    return compare;

    /*return provided_icaseCompareString(str1, str2);*/
}

/** Like the strlen() function. It calculates the length of the string str, not including the terminating '\\0' character.
 * @param str the string
 * @return the number of characters in str.
 */
size_t IMPLEMENT(stringLength)(const char * str) {
    const char * last = str;
    while(* last != '\0') /* *last est identique a ecrire : *last != '\0'  */
        last++;
    return (size_t)(last-str);
}

/** Copy the string pointed to by src, including the terminating null byte ('\\0'), to the buffer pointed to by dest.
 * @warning The strings may not overlap, and the destination string dest must be large enough to receive the copy.
 *
 * @param dest the destination string
 * @param src the source string
 */
void IMPLEMENT(copyString)(char * dest, const char * src) {
    fprintf(stderr,
            "You should avoid strcpy and copyString. Use strncpy or copyStringWithLength instead\n");
    copyStringWithLength(dest, src, INT_MAX);
}

/** Copy the first destSize characters of the string pointed to by src, including the terminating null byte ('\\0'), to the buffer pointed to by dest.
 * @warning The strings may not overlap, and the destination string dest must be large enough to receive the copy.
 * @warning If src is longer than destSize characters, the string is truncated and the terminating null byte ('\\0') is added.
 *
 * @param dest the destination string
 * @param src the source string
 * @param destSize the maximal number of characters to copy
 */
void IMPLEMENT(copyStringWithLength)(char * dest, const char * src, size_t destSize) {

    size_t  i;
    for(i = 0; i < (destSize - 1) && src[i] != '\0'; i++)
        dest[i] = src[i];
    dest[i] = '\0';

     /*provided_copyStringWithLength(dest, src, destSize);*/
}

/** Like the strdup() function. It creates a copy of the string on the heap.
 * @note The copy is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 * @param str the string to duplicate
 */
char * IMPLEMENT(duplicateString)(const char * str) {
    char * copy;
    size_t i;
    size_t size = stringLength(str);
    copy = (char *)malloc((size+1)*sizeof(char));
    if(copy == NULL)
        fatalError("Memory allocation failure at function duplicateString in MyString.c.");
    else
    {
         for(i = 0; i <= size; i++)
        {
            *(copy+i) = *(str+i);
        }
    }
    return copy;
    /*return provided_duplicateString(str);*/
}

/** Test if the string str begins by the string start, ignoring the case of the characters.
 * @param start the string which should be at the beginning of str
 * @param str the string to test
 * @return a non null number (true) if the str begins with the string start, false otherwise
 */
int IMPLEMENT(icaseStartWith)(const char * start, const char * str) {
    int i;
    for(i = 0 ; start[i] != '\0'; i++)
    {
        if(toLowerChar(start[i]) != toLowerChar(str[i]))
            return 0;
    }
    return 1;
}

/** Test if the string str ends by the string start, ignoring the case of the characters.
 * @param end the string which should be at the end of str
 * @param str the string to test
 * @return a non null number (true) if the str ends with the string end, false otherwise
 */
int IMPLEMENT(icaseEndWith)(const char * end, const char * str) {

    size_t sizeEnd = stringLength(end);
    size_t sizeStr = stringLength(str);
    if(sizeEnd <= sizeStr)
    {
        int testEnd = icaseCompareString(str+sizeStr-sizeEnd, end);
        if(testEnd == 0)
            return -1;
    }
    return 0;

    /*return provided_icaseEndWith(end, str);*/
}

/** Create a new string on the heap which is the result of the concatenation of the two strings.
 * @note The new string is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 * @param str1 the first string
 * @param str2 the second string
 * @return the new string
 */
char * IMPLEMENT(concatenateString)(const char * str1, const char * str2) {

    size_t i;
    size_t str1Length = stringLength(str1),
            str2Length = stringLength(str2);
    char * concat = (char*)malloc((str1Length + str2Length + 1) * sizeof(char));

    if(concat == NULL)
        fatalError("Memory allocation failure at function concatenateString in MyString.c.");

    /* Copy first string. */
    for(i = 0; i < str1Length; ++i)
        concat[i] = str1[i];
    /* Copy second string. */
    for(i = 0; i < str2Length; ++i)
        concat[str1Length + i] = str2[i];
    concat[str1Length + i] = '\0';

    return concat;

   /*return provided_concatenateString(str1, str2);*/
}

/** Like the index() function. It returns a pointer to the first occurrence of the character c in the string str.
 * @param str the string to search in
 * @param c the character to find
 * @return a pointer to the first occurrence of the character c in the string str if c is in str, NULL otherwise
 */
const char * IMPLEMENT(indexOfChar)(const char *str, char c) {
    for(; * str; str++)/* while * str != c keep going : * str != '\0' */
    {
        if(* str == c)
            return str;
    }

    return NULL;
    /*return provided_indexOfChar(str, c);*/
}

/** Create a copy on the heap of part of a string. The new string contains the characters pointed from start (inclusive) to end (exclusive).
 * @note The new string is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 * @param start a pointer to the first character of the new string
 * @param end a pointer to the next character of the new string (the pointed character is not part of the new string)
 * @return the new string
 *
 * @code
 * char * str = "abcdef";
 * char * s1 = subString(str,str);
 * char * s2 = subString(str,str+strlen(str));
 * char * s3 = subString(str+1,str+2);
 *
 * We get:
 *    s1: "";
 *    s2: "abcdef";
 *    s3: "b";
 * @endcode
 */
char * IMPLEMENT(subString)(const char * start, const char * end) {

    char * subStr = (char*)malloc((size_t)((end - start) + 1) * sizeof(char));
    char * ptr = subStr;

    if(subStr == NULL)
        fatalError("Memory allocation failure at function subString in MyString.c.");

    for(; start != end; start++, subStr++)
        *subStr = *start;
    *subStr = '\0';

    return ptr;

    /*return provided_subString(start, end);*/
}

/** Like the strstr() function. It returns a pointer to the first occurrence of the string aiguille in the string meule_de_foin.
 * @param meule_de_foin the string to search in
 * @param aiguille the string to find
 * @return a pointer to the first occurrence of the string aiguille in the string meule_de_foin if aiguille is in meule_de_foin, NULL otherwise
 */
const char * IMPLEMENT(indexOfString)(const char *haystack, const char *needle) {

    char * tmp1,
            * tmp2;

    /* First check if needle is empty */
    if(*needle == '\0')
        return (char*)haystack;

    /* Run through the entire haystack string. */
    for(; *haystack != '\0'; haystack++)
    {
        /* First character of needle is matching the current haystack character */
        if(*haystack == *needle)
        {
            tmp1 = (char*)haystack;
            tmp2 = (char*)needle;
            /* Check for the rest of needle */
            while(*tmp1 == *tmp2)
            {
                tmp1++; tmp2++;

                /* Found needle in haystack. Return current haystack position. */
                if(*tmp2 == '\0')
                    return (char*)haystack;

                /* Reached haystack's end. No match. */
                if(*tmp1 == '\0')
                    return NULL;
            }
        }
    }
    return NULL;

    /*return provided_indexOfString(meule_de_foin, aiguille);*/
}

/** Convert a string to upper case.
 * @param str the string to convert
 */
void IMPLEMENT(makeUpperCaseString)(char * str) {
    int i;
    for(i = 0 ; str[i] != '\0' ; i++)
    {
        str[i] = toUpperChar(str[i]);
    }
}

/** Convert a string to lower case.
 * @param str the string to convert
 */
void IMPLEMENT(makeLowerCaseString)(char * str) {
    int i;
    for(i = 0 ; str[i] != '\0' ; i++)
    {
        str[i] = toLowerChar(str[i]);
    }
}

/** Create a new string on the heap which contents is the result of the insertion in src of insertLength characters from  toBeInserted at position insertPosition.
 * @note The new string is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 * @param src the string in which the insertion is done
 * @param insertPosition the position where the insertion is done
 * @param toBeInserted a pointer on the first character to insert
 * @param insertLength the number of character to insert
 * @return the new string
 */
char * IMPLEMENT(insertString)(const char * src, int insertPosition, const char * toBeInserted,
        int insertLength) {

    size_t len = stringLength(src) + (size_t)insertLength;
    char * insert = (char*)malloc((len + 1) * sizeof(char));
    int i,j;

    if(insert == NULL)
        fatalError("Memory allocation failure at function insertString in MyString.c.");

    /* Copy first part of src */
    for(i = 0; i < insertPosition; ++i)
        insert[i] = src[i];

    /* Copy toBeInserted part */
    for(j = 0; j < insertLength; ++j)
        insert[i+j] = toBeInserted[j];

    /* Copy last part of src */
    for(; src[i] != '\0'; ++i)
        insert[i+j] = src[i];
    insert[i+j] = '\0';

    return insert;

    /*return provided_insertString(src, insertPosition, toBeInserted, insertLength);*/
}
