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
 * $Id: OperatorTable.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <OperatorTable.h>
#include <EncryptDecrypt.h>

#define KEY "thisIsMyKey"

/**
 * Create an empty table of operators.
 * @return the new table
 * @relates OperatorTable
 */
OperatorTable * IMPLEMENT(OperatorTable_create)(void) {

    /*char *** newTable = (char *)malloc(sizeof(int) + (OPERATORTABLE_MAXNAMESIZE + OPERATORTABLE_MAXPASSWORDSIZE) * sizeof(char));*/
    /*OperatorTable * newTable = (OperatorTable *)malloc(sizeof(OperatorTable));
    newTable->recordCount = 0;
    newTable->records = NULL;*/

    OperatorTable * newTable;
    newTable = (OperatorTable*)malloc(sizeof(OperatorTable));
    if(newTable == NULL)
    {
        fatalError("Memory allocation failure at function OperatorTable_create in OperatorTable.c.");
    }
    newTable->recordCount = 0;
    newTable->records = NULL;

    return newTable;

    /*return provided_OperatorTable_create();*/
}

/** Free a table of operators.
 * @param table a pointer to the table to free
 * @relates OperatorTable
 */
void IMPLEMENT(OperatorTable_destroy)(OperatorTable * table) {

    int i;
    for(i = 0; i < table->recordCount; i++)
    {
        free(table->records[i][0]);
        free(table->records[i][1]);
        free(table->records[i]);
    }
    free(table->records);
    free(table);

    /*provided_OperatorTable_destroy(table);*/
}

/** Load a table of operators from a file.
 * @param filename the file name
 * @return the new table
 * @relates OperatorTable
 */
OperatorTable * IMPLEMENT(OperatorTable_loadFromFile)(const char * filename) {
    return provided_OperatorTable_loadFromFile(filename);
}

/** Save a table of operators to a file.
 * @param table the table of operators
 * @param filename the file name
 * @relates OperatorTable
 */
void IMPLEMENT(OperatorTable_saveToFile)(OperatorTable * table, const char * filename) {
    provided_OperatorTable_saveToFile(table, filename);
}

/** Get the number of records of a table of operators
 * @param table the table of operators
 * @return the number of records
 * @relates OperatorTable
 */
int IMPLEMENT(OperatorTable_getRecordCount)(OperatorTable * table) {
    return table->recordCount;

    /*return provided_OperatorTable_getRecordCount(table);*/
}

/** Get the name of a record of a table of operators.
 * @param table the table of operators
 * @param recordIndex the record number
 * @return the name of the operator
 * @relates OperatorTable
 */
const char * IMPLEMENT(OperatorTable_getName)(OperatorTable * table, int recordIndex) {

   if(recordIndex >= 0 || recordIndex <= table->recordCount)
   {
       return (table->records[recordIndex][0]);
   }
    else
    {
        return NULL;
    }

    /*return provided_OperatorTable_getName(table, recordNum);*/
}

/** Get the password of a record of a table of operators.
 * @param table the table of operators
 * @param recordIndex the record index
 * @return the paswword of the operator
 * @relates OperatorTable
 */
const char * IMPLEMENT(OperatorTable_getPassword)(OperatorTable * table, int recordIndex) {
    if(recordIndex >= 0 || recordIndex <= table->recordCount)
    {
        return (table->records[recordIndex][1]);
    }
    else
    {
        return NULL;
    }

    /*return provided_OperatorTable_getPassword(table, recordIndex);*/
}

/** Get the record index associated with an operator name.
 * @param table the table of operators
 * @param name the name of the operator
 * @return the index of the operator or -1 if the operator is not in the table
 * @relates OperatorTable
 */
int IMPLEMENT(OperatorTable_findOperator)(OperatorTable * table, const char * name) {

    /*int i;
    for (i = 0; i < OperatorTable.recordCount; i++)
    {
        if(icaseCompareString)(table, name) == 0)
            return i;
    }

    return -1;*/

    int i;
    for (i = 0; i < table->recordCount; i++)
    {
        if(icaseCompareString(table->records[i][0], name) == 0)
            return i;
    }
    return -1;


    /*return provided_OperatorTable_findOperator(table, name);*/
}

/** Define or change the password of an operator
 * @param table the table of operators
 * @param name the name of the operator
 * @param password the password of the operator
 * @return the index of the operator in the table
 * @relates OperatorTable
 */
int IMPLEMENT(OperatorTable_setOperator)(OperatorTable * table, const char * name, const char * password) {

    /*table.records.table[0] = name;
    table.records.table[sizeof(name)][sizeof(name)] = password;

    return * table;*/

    int i;
    i = OperatorTable_findOperator(table, name);
    if(i != -1)
    {
        free(table->records[i][1]);
        table->records[i][1] = duplicateString(password);
    }
    else
    {
        i = table->recordCount++;
        table->records = (char ***)realloc(table->records, (size_t)table->recordCount * sizeof(char**));
        if(table->records == NULL)
        {
            fatalError("Memory allocation failure - realloc - at function OperatorTable_setOperator in OperatorTable.c.");
        }
        table->records[i] = (char**)malloc(2 * sizeof(char*));
        if(table->records[i] == NULL)
        {
            fatalError("Memory allocation failure - malloc - at function OperatorTable_setOperator in OperatorTable.c.");
        }
        table->records[i][0] = duplicateString(name);
        table->records[i][1] = duplicateString(password);
    }
    return i;

    /*return provided_OperatorTable_setOperator(table, name, password);*/
}

/** Remove an operator from the table.
 * @param table the table of operators
 * @param recordIndex the index of the record to remove
 * @relates OperatorTable
 */
void IMPLEMENT(OperatorTable_removeRecord)(OperatorTable * table, int recordIndex) {

    int i;

    free(table->records[recordIndex][0]);
    free(table->records[recordIndex][1]);
    free(table->records[recordIndex]);

    for(i = recordIndex; i < table->recordCount - 1; i++)
        table->records[i] = table->records[i + 1];

    table->records = realloc(table->records, (size_t)(table->recordCount - 1) * sizeof(char * *));
    table->recordCount--;

    /*provided_OperatorTable_removeRecord(table, recordIndex);*/
}

