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
 * $Id: Dictionary.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <Dictionary.h>

/** Create an empty dictionary on the heap
 * @return a new dictionary
 * @warning the dictionary should be destroyed using Dictionary_destroy()
 */
Dictionary * IMPLEMENT(Dictionary_create)(void)
{
    Dictionary * dictionary = (Dictionary*)malloc(sizeof(Dictionary));
    if(dictionary == NULL)
    {
        fatalError("dictionary allocation fail at function Dictionary_create in file Dictionary.c");
    }
    dictionary->count = 0;
    dictionary->entries = NULL;

    return dictionary;

  /*return provided_Dictionary_create();*/
}

/** Destroy a dictionary
 * @param dictionary the dictionary
 */
void IMPLEMENT(Dictionary_destroy)(Dictionary * dictionary)
{
    int i = 0;
    DictionaryEntry * entry = dictionary->entries;

    while(i < dictionary->count)
    {
        free(entry->name);
        if(entry->type == STRING_ENTRY)
        {
            free(entry->value.stringValue);
        }
        entry++;
        i++;
    }
    free(dictionary->entries);
    free(dictionary);

 /*provided_Dictionary_destroy(dictionary);*/
}

/** Get a pointer on the entry associated with the given entry name
 * @param dictionary the dictionary
 * @param name the name of the entry
 * @return a pointer on the entry or NULL if the entry was not found
 */
DictionaryEntry * IMPLEMENT(Dictionary_getEntry)(Dictionary * dictionary, const char * name)
{
    int i = 0;
    for(i = 0; i < dictionary->count; i++)
    {
        if(icaseCompareString(((dictionary->entries[i]).name), name) == 0)
        {
            return &(dictionary->entries[i]);/*if entry is already in dictionary->entries, return pointer on that name*/
        }
    }
    return NULL;

  /*return provided_Dictionary_getEntry(dictionary, name);*/
}

/** Define or change a dictionary entry as a string
 * @param dictionary the dictionary
 * @param name the entry name
 * @param value the value
 */
void IMPLEMENT(Dictionary_setStringEntry)(Dictionary * dictionary, const char * name, const char * value)
{
    size_t numberEntry = 0;
    DictionaryEntry * entry = Dictionary_getEntry(dictionary, name);

    if(entry == NULL)
    {
        numberEntry = (size_t)((dictionary->count)+1);/* set number of entry */
        (dictionary->count)++;
        dictionary->entries = realloc(dictionary->entries, sizeof(DictionaryEntry) * numberEntry);
        if(dictionary->entries == NULL)
        {
            fatalError("Realloc failed of dictionary->entries in function Dictionary_setStringEntry, file Dictionary.c");
        }
        entry = dictionary->entries + numberEntry - 1;/* the pointer entry goes to the position of the new entry */

        /* set entry with name */
        entry->name = duplicateString(name);
        entry->type = STRING_ENTRY;
        entry->value.stringValue = NULL;
    }

    if(entry->type == STRING_ENTRY)
    {
        free(entry->value.stringValue);
    }
    entry->type = STRING_ENTRY;
    entry->value.stringValue = duplicateString(value);

  /*provided_Dictionary_setStringEntry(dictionary, name, value);*/
}

/** Define or change a dictionary entry as a number
 * @param dictionary the dictionary
 * @param name the entry name
 * @param value the value
 */
void IMPLEMENT(Dictionary_setNumberEntry)(Dictionary * dictionary, const char * name, double value)
{
    size_t numberEntry = 0;
    DictionaryEntry * entry = Dictionary_getEntry(dictionary, name);

    if(entry == NULL)
    {
        numberEntry = (size_t)((dictionary->count)+1);
        (dictionary->count)++;
        dictionary->entries = realloc(dictionary->entries, sizeof(DictionaryEntry) * numberEntry);
        if(dictionary->entries == NULL)
        {
            fatalError("Realloc failure of dictionary->entries in function Dictionary_setNumberEntry, file Dictionary.c");
        }
        entry = dictionary->entries + numberEntry - 1;
        entry->name=duplicateString(name);
    }

    entry->type=NUMBER_ENTRY;
    entry->value.numberValue=value;

  /*provided_Dictionary_setNumberEntry(dictionary, name, value);*/
}

/** Create a new string on the heap which is the result of the formatting of format according to the dictionary content
 * @param dictionary the dictionary
 * @param format the string to format
 * @return a new string created on the heap
 * @warning the user is responsible for freeing the returned string
 */
char * IMPLEMENT(Dictionary_format)(Dictionary * dictionary, const char * format)
{
  return provided_Dictionary_format(dictionary, format);
}
