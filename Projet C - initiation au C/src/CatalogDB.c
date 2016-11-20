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
 * $Id: CatalogDB.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <CatalogDB.h>
#include <CatalogRecord.h>
#include <CatalogRecordEditor.h>

/** The catalog file name */
const char * CATALOGDB_FILENAME = BASEPATH "/data/Catalog.db";

/** Create a database of products
 * @param filename the file name of the database
 * @return a pointer on a CatalogDB representing the opened database, NULL otherwise
 */
CatalogDB * IMPLEMENT(CatalogDB_create)(const char * filename) {

    CatalogDB * catalogFile = malloc(sizeof(CatalogDB));
    if(catalogFile == NULL)
    {
        fatalError("Error malloc for catalogFile, function CatalogDB_create from file CatalogDB.c");
    }

    catalogFile->recordCount = 0;
    catalogFile->file = fopen(filename,"w+b");
    if(catalogFile->file == NULL)
    {
        free(catalogFile);
        return NULL;
    }
    /* we write the number of record (recordCount) in the catalogFile->file*/
    if(fwrite(&catalogFile->recordCount, sizeof(int), 1, catalogFile->file) != 1)
    {
       fclose(catalogFile->file);/* we close the file here in case of buffer not empty that could make a corrupted file.*/
       fatalError("Error fwrite from recordCount into file CatalogDB.c");
    }
    return catalogFile;

    /*return provided_CatalogDB_create(filename);*/
}

/** Open an existing database of products
 * @param filename the file name of the database
 * @return a pointer on a CatalogDB representing the opened database, NULL otherwise
 */
CatalogDB * IMPLEMENT(CatalogDB_open)(const char * filename) {

    CatalogDB * catalogFile = malloc(sizeof(CatalogDB));
    if(catalogFile == NULL)
    {
        fatalError("Error malloc for catalogFile, function CatalogDB_open from file CatalogDB.c");
    }
    catalogFile->recordCount = 0;

    /*We make catalogFile->file point on the file designed by filename, and it's open in read and write mode*/
    catalogFile->file = fopen(filename,"r+");
    if(catalogFile->file == NULL)
    {
        free(catalogFile);
        return NULL;
    }
    /*read the number of record in the file and put it in the catalogFile->recordCount*/
    if(fread(&catalogFile->recordCount, sizeof(int),1,catalogFile->file) != 1)
    {
       fclose(catalogFile->file);
       fatalError("Error fwread from file CatalogDB.c");
    }
    return catalogFile;

    /*return provided_CatalogDB_open(filename);*/
}

/** Open if exists or create otherwise a database of products
 * @param filename the file name of the database
 * @return a pointer on a CatalogDB representing the opened database, NULL otherwise
 */
CatalogDB * IMPLEMENT(CatalogDB_openOrCreate)(const char * filename) {

    CatalogDB * catalogDB;
    catalogDB=CatalogDB_open(filename);

    /*if the file doesn't exist we create a new file*/
    if(catalogDB==NULL)
    {
        return CatalogDB_create(filename);
    }
    else
    {
        return catalogDB;
    }

    /*return provided_CatalogDB_openOrCreate(filename);*/
}

/** Flush cached data, close a database and free the structure representing the opened database
 * @param catalogDB a pointer on a CatalogDB representing the opened database
 */
void IMPLEMENT(CatalogDB_close)(CatalogDB * catalogDB) {

    /*put the pointer at the begining of the file*/
    fseek(catalogDB->file,0,SEEK_SET);
    /*write the current catalogDB->recordCount at the begining of the file*/
     if(fwrite(&catalogDB->recordCount, sizeof(int),1,catalogDB->file) != 1)
    {
       fclose(catalogDB->file);
       fatalError("Error fwread from recordCount, function CatalogDB_close, file CatalogDB.c");
    }
    /*close the file*/
    fclose(catalogDB->file);
    free(catalogDB);

    /*provided_CatalogDB_close(catalogDB);*/
}

/** Get the number of records of the database
 * @param catalogDB the database
 * @return the number of records
 */
int IMPLEMENT(CatalogDB_getRecordCount)(CatalogDB * catalogDB) {
    return catalogDB->recordCount;

    /*return provided_CatalogDB_getRecordCount(catalogDB);*/
}

/** Create a new string on the heap containing the value of the specified field for the specified record of a database
 * @param catalogDB the database
 * @param recordIndex the record index
 * @param field the field to query
 * @return a new string
 * @note The string is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * CatalogDB_getFieldValueAsString(CatalogDB * catalogDB, int recordIndex, int field) {
    char * content = NULL;
    if (catalogDB != NULL) {
        CatalogRecord_FieldProperties properties = CatalogRecord_getFieldProperties(field);
        CatalogRecord record;
        CatalogRecord_init(&record);
        CatalogDB_readRecord(catalogDB, recordIndex, &record);
        content = (*properties.getValue)(&record);
        CatalogRecord_finalize(&record);
    }
    return content;
}

/** Append the specified record at the end of the database
 * @param catalogDB the database
 * @param record the record
 */
void IMPLEMENT(CatalogDB_appendRecord)(CatalogDB * catalogDB, CatalogRecord *record) {

    CatalogDB_writeRecord(catalogDB, catalogDB->recordCount , record);

    /*provided_CatalogDB_appendRecord(catalogDB, record);*/
}

/** Insert the specified record at the given position in the database
 * @param catalogDB the database
 * @param recordIndex the insertion position
 * @param record the record
 */
void IMPLEMENT(CatalogDB_insertRecord)(CatalogDB * catalogDB, int recordIndex, CatalogRecord * record) {

    int position;/*current index of record who are readin the while below*/
    int count;/*will be the number of record in the catalogDB*/

     /* initialisation of a temporary variable who will have the value of record*/
    CatalogRecord tmp;
    CatalogRecord_init(&tmp);

    if(catalogDB->recordCount < 0)
    {
        fatalError("Error : catalogDB->recordCount can not be negative");
    }
    count = catalogDB->recordCount;

    /*move the record (position) to the place of the next one (position+1) until the end, to make place for the new record*/
    for(position = count - 1; position >= recordIndex ; position--)
    {
        CatalogDB_readRecord(catalogDB, position , &tmp);
        CatalogDB_writeRecord(catalogDB, position+1, &tmp);
    }

    /*set the record at his respected index*/
    CatalogDB_writeRecord(catalogDB, recordIndex,record);
    CatalogRecord_finalize(&tmp);

    /*provided_CatalogDB_insertRecord(catalogDB, recordIndex, record);*/
}

/** Remove a record at a given position from the database
 * @param catalogDB the database
 * @param recordIndex the removal position
 */
void IMPLEMENT(CatalogDB_removeRecord)(CatalogDB * catalogDB, int recordIndex) {

    int position;/*current index of record who are readin the while below*/
    int count;/*will be the number of record in the customerDB*/

    /* initialisation of a temporary variable who will have the value of record*/
    CatalogRecord tmp;
    CatalogRecord_init(&tmp);

    if(catalogDB->recordCount < 0)
    {
        fatalError("Error : catalogDB->recordCount can not be negative");
    }
    count = catalogDB->recordCount;
/*move the record (position+1) to the place of the precedent one (position) until the end, to replace the removed value*/
    position = recordIndex;
    while(position < count - 1)
    {
        CatalogDB_readRecord(catalogDB, position+1 , &tmp);
        CatalogDB_writeRecord(catalogDB, position, &tmp);
        position++;
    }
    /*set null value to the last record who is now unused */
    CatalogRecord_finalize(&tmp);
    CatalogRecord_init(&tmp);
    CatalogDB_writeRecord(catalogDB, position, &tmp);
    /*free the unused memory*/
    CatalogRecord_finalize(&tmp);

    /*provided_CatalogDB_removeRecord(catalogDB, recordIndex);*/
}

/** Read a record from the database
 * @param catalogDB the database
 * @param recordIndex the position of the record to read
 * @param record the record to fill with data
 */
void IMPLEMENT(CatalogDB_readRecord)(CatalogDB * catalogDB, int recordIndex, CatalogRecord * record) {

    long offset;

    if(recordIndex < 0)
    {
        fatalError("Error : recordIndex can not be negative");
    }
    if(recordIndex >= catalogDB->recordCount)
    {
        fatalError("Error : recordIndex >= catalogDB->recordCount, not correct");
    }
    /*offset is the interval use to read the recordIndex-th record, it's composed of :
    - sizeof(int) because before each record there is the recordCount of type int
    - recordIndex*sizeof(CatalogRecord) because there is recordIndex records before,
     and the sizeof(CatalogRecord) contain the size of each field in CatalogRecord (recordCount, file) */
    offset = (long) (sizeof(int) + (unsigned long) recordIndex * CATALOGRECORD_SIZE);

    /* we put the pointer catalogDB->file where begin the recordIndex-th record , and we read the file*/
    fseek(catalogDB->file,offset,SEEK_SET);
    CatalogRecord_read(record,catalogDB->file);

    /*provided_CatalogDB_readRecord(catalogDB, recordIndex, record);*/
}

/** Write a record from the database
 * @param catalogDB the database
 * @param recordIndex the position of the record to write
 * @param record the record containing the data
 */
void IMPLEMENT(CatalogDB_writeRecord)(CatalogDB * catalogDB, int recordIndex, CatalogRecord * record) {

    long offset;

    if(recordIndex < 0)
    {
        fatalError("Error : recordIndex can not be negative");
    }
    /*if we write at the end of the file we set the new number of record*/
    if(recordIndex==catalogDB->recordCount)
    {
        catalogDB->recordCount++;
    }
    if(recordIndex>catalogDB->recordCount)
    {
        fatalError("Error : recordIndex > customerDB->recordCount, doesn't make sens");
    }
    /*offset is the interval use to read the recordIndex-th record, it's composed of :
    - sizeof(int) because before each record there is the recordCount of type int
    - recordIndex*sizeof(CustomerRecord) because there is recordIndex records before,
     and the sizeof(CustomerRecord) contain the size of each field in CustomerRecord (recordCount, file) */
    offset = (long)(sizeof(int) + (unsigned long)recordIndex * CATALOGRECORD_SIZE);

    /* we put the pointer customerDB->file where begin the recordIndex-th record , and we read the file*/
    fseek(catalogDB->file,offset,SEEK_SET);
    CatalogRecord_write(record,catalogDB->file);

    /*provided_CatalogDB_writeRecord(catalogDB, recordIndex, record);*/
}

