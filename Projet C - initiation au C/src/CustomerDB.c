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
 * $Id: CustomerDB.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <CustomerDB.h>
#include <CustomerRecord.h>
#include <CustomerRecordEditor.h>

const char * CUSTOMERDB_FILENAME = BASEPATH "/data/Customer.db";

CustomerDB * IMPLEMENT(CustomerDB_create)(const char * filename) {

    FILE * customerFile;
    CustomerDB * dataBase;

    customerFile = fopen(filename, "w+");
    if(customerFile == NULL)
    {
        return NULL;
    }
    dataBase = (CustomerDB *)malloc(sizeof(CustomerDB));

    if(dataBase == NULL)
    {
        fatalError("Error memory allocation - dataBase - in function CustomerDB_create, file CustomerDB.c");
    }

    dataBase->recordCount = 0;
    dataBase->file = customerFile;

    if(fwrite(&dataBase->recordCount, sizeof(int), 1, dataBase->file) < 1)
    {
        fatalError("Error at writing at function CustomerDB_create, file CustomerDB.c");
    }
    return dataBase;

    /*return provided_CustomerDB_create(filename);*/
}

CustomerDB * IMPLEMENT(CustomerDB_open)(const char * filename) {

    CustomerDB * CustomerFile=malloc(sizeof(CustomerDB));
    if(CustomerFile==NULL)fatalError("Error malloc CustomerFile");

    CustomerFile->recordCount=0;
    /*We make CustomerFile->file point on the file designed by filename,
     and it's open in read and write mode*/
    CustomerFile->file = fopen(filename,"r+");
    if(CustomerFile->file==NULL){
        free(CustomerFile);
        return NULL;
    }
    /*read the number of record in the file and put it in the CustomerFile->recordCount*/
    if(fread(&CustomerFile->recordCount, sizeof(int),1,CustomerFile->file)!=1){
       fclose(CustomerFile->file);
       fatalError("Error fwread from recordCount into file");
    }
    return CustomerFile;

    /*return provided_CustomerDB_open(filename);*/
}

CustomerDB * IMPLEMENT(CustomerDB_openOrCreate)(const char * filename) {

    CustomerDB * customerDB;
    customerDB=CustomerDB_open(filename);

    /*if the file doesn't exist we create a new file*/
    if(customerDB==NULL){
        return CustomerDB_create(filename);
    }
    else{
        return customerDB;
    }

    /*return provided_CustomerDB_openOrCreate(filename);*/
}

void IMPLEMENT(CustomerDB_close)(CustomerDB * customerDB) {

    /* put the pointer at the begining of the file */
    rewind(customerDB->file);
    /* write the current customerDB->recordCount at the begining of the file */
    if(fwrite(&customerDB->recordCount, sizeof(int),1,customerDB->file) < 1)
    {
       fclose(customerDB->file);
       fatalError("Error fwread at function CustomerDB_openOrCreate into file CustomerDB.c");
    }
    /*close the file*/
    fclose(customerDB->file);/* no need to test "fclose(customerDB->file) != 0" */
    free(customerDB);

    /*provided_CustomerDB_close(customerDB);*/
}

int IMPLEMENT(CustomerDB_getRecordCount)(CustomerDB * customerDB) {
    return customerDB->recordCount;

    /*return provided_CustomerDB_getRecordCount(customerDB);*/
}

char * CustomerDB_getFieldValueAsString(CustomerDB * customerDB, int recordIndex, int field) {
    char * content = NULL;
    if (customerDB != NULL) {
        CustomerRecord_FieldProperties properties = CustomerRecord_getFieldProperties(field);
        CustomerRecord record;
        CustomerRecord_init(&record);
        CustomerDB_readRecord(customerDB, recordIndex, &record);
        content = (*properties.getValue)(&record);
        CustomerRecord_finalize(&record);
    }
    return content;
}

void IMPLEMENT(CustomerDB_appendRecord)(CustomerDB * customerDB, CustomerRecord *record) {
    CustomerDB_writeRecord( customerDB, customerDB->recordCount, record );
    /*provided_CustomerDB_appendRecord(customerDB, record);*/
}

void IMPLEMENT(CustomerDB_insertRecord)(CustomerDB * customerDB, int recordIndex, CustomerRecord * record) {

    int i;
    CustomerRecord rec;
    CustomerRecord_init(&rec);

    if(customerDB->recordCount == 0)
    {
        CustomerDB_writeRecord( customerDB, 0, record);
    }
    else
    {
        for(i = customerDB->recordCount - 1; i >= recordIndex; i--)
        {
            CustomerDB_readRecord( customerDB, i, &rec);
            CustomerDB_writeRecord( customerDB, i + 1, &rec);
        }
    }

    CustomerRecord_finalize( &rec );
    CustomerDB_writeRecord( customerDB, recordIndex, record);

    /*provided_CustomerDB_insertRecord(customerDB, recordIndex, record);*/
}

void IMPLEMENT(CustomerDB_removeRecord)(CustomerDB * customerDB, int recordIndex) {

    int i;
    CustomerRecord rec;
    CustomerRecord_init(&rec);

    if(recordIndex == customerDB->recordCount)
    {
        customerDB->recordCount--;
    }
    else
    {
        for(i = recordIndex + 1; i < customerDB->recordCount; i++)
        {
            CustomerDB_readRecord(customerDB, i, &rec);
            CustomerDB_writeRecord(customerDB, i - 1, &rec);
        }
    }

    CustomerRecord_finalize(&rec);
    customerDB->recordCount--;

    /*provided_CustomerDB_removeRecord(customerDB, recordIndex);*/
}

void IMPLEMENT(CustomerDB_readRecord)(CustomerDB * customerDB, int recordIndex, CustomerRecord * record) {

    long offset;
    if(recordIndex < 0 || customerDB->recordCount <= recordIndex)
    {
        fatalError("recordIndex < 0 at function CustomerDB_readRecord in CustomerDB.c");
    }
    /*offset is the interval use to read the recordIndex-th record, it's composed of :
    - sizeof(int) because before each record there is the recordCount of type int
    - recordIndex*sizeof(CustomerRecord) because there is recordIndex records before,
     and the sizeof(CustomerRecord) contain the size of each field in CustomerRecord (recordCount, file) */
    offset = (long)(sizeof(int)+(unsigned long)recordIndex*CUSTOMERRECORD_SIZE);

    /* we put the pointer customerDB->file where begin the recordIndex-th record , and we read the file*/
    if(fseek(customerDB->file, offset, SEEK_SET) != 0)
    {
        fatalError("Error at function CustomerDB_readRecord in file CustomerDB.c");
    }
    CustomerRecord_read(record, customerDB->file);

    /*provided_CustomerDB_readRecord(customerDB, recordIndex, record);*/
}

void IMPLEMENT(CustomerDB_writeRecord)(CustomerDB * customerDB, int recordIndex, CustomerRecord * record) {
    long offset;

    if(recordIndex < 0)fatalError("Error record index negative");

    /*if we write at the end of the file we set the new number of record*/
    if(recordIndex==customerDB->recordCount)customerDB->recordCount++;
    if(recordIndex>customerDB->recordCount)fatalError("Error recordIndex > customerDB->recordCount");

    /*offset is the interval use to read the recordIndex-th record, it's composed of :
    - sizeof(int) because before each record there is the recordCount of type int
    - recordIndex*sizeof(CustomerRecord) because there is recordIndex records before,
     and the sizeof(CustomerRecord) contain the size of each field in CustomerRecord (recordCount, file) */
     offset = (long)(sizeof(int)+(unsigned long)recordIndex*CUSTOMERRECORD_SIZE);

    /* we put the pointer customerDB->file where begin the recordIndex-th record , and we read the file*/
    fseek(customerDB->file,offset,SEEK_SET);
    CustomerRecord_write(record,customerDB->file);

    /*provided_CustomerDB_writeRecord(customerDB, recordIndex, record);*/
}
