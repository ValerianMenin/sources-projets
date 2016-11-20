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
 * $Id: CatalogRecord.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <CatalogRecord.h>

/** Static function which test if a code only contains numbers and letters
 * @param  value the value to test
 * @return true if the code is valid, false otherwise
 */
int IMPLEMENT(CatalogRecord_isValueValid_code)(const char * value)
{
    int valid = 1;
    size_t i = 0;

    while(value[i] != '\0' && valid != 0)
    {
        if((value[i] >= 'a' && value[i] <= 'z') || (value[i] >= 'A' && value[i] <= 'Z') || (value[i] >= '0' && value[i] <= '9'))
        {
            valid = 1;
        }
        else
        {
            valid = 0;
        }
        i++;
    }
    return valid;

  /*return provided_CatalogRecord_isValueValid_code(value);*/
}

/** Static function which test if the value is a positive number
 * @param  value the value to test
 * @return true if the valie is valid, false otherwise
 */
int IMPLEMENT(CatalogRecord_isValueValid_positiveNumber)(const char * value)
{
    int testValid = 1;
    int isEmptyString;
    char *endptr ;

    double convertedValue;
    convertedValue = strtod(value, &(endptr));

    isEmptyString = icaseCompareString(endptr, "");
    if(isEmptyString != 0)
    {
        testValid = 0;
    }
    else
    {
            /*if convertedValue : not valid */
        if(-convertedValue>convertedValue)
        {
            testValid = 0;
        }
        else
        {
            testValid = 1;
        }
    }
    return testValid;

  /*return provided_CatalogRecord_isValueValid_positiveNumber(value);*/
}

/** Static function to set the code field from a string
 * @param record a pointer to the record
 * @param value the value
 */
void IMPLEMENT(CatalogRecord_setValue_code)(CatalogRecord * record, const char * value)
{
    if(CatalogRecord_isValueValid_code(value) == 1)
    {
        free(record->code);
        record->code=duplicateString(value);
    }
    else
    {
        fatalError("Error in function CatalogRecord_setValue_code, file CatalogRecord.c");
    }

  /*provided_CatalogRecord_setValue_code(record, value);*/
  }

/** Static function to set the designation field from a string
 * @param record a pointer to the record
 * @param value the value
 */
void IMPLEMENT(CatalogRecord_setValue_designation)(CatalogRecord * record, const char * value)
{
    if(record->designation != NULL)
    {
        free(record->designation);
    }
    record->designation = duplicateString(value);

  /*provided_CatalogRecord_setValue_designation(record, value);*/
}

/** Static function to set the unity field from a string
 * @param record a pointer to the record
 * @param value the value
 */
void IMPLEMENT(CatalogRecord_setValue_unity)(CatalogRecord * record, const char * value)
{
    if(record->unity != NULL){
        free(record->unity);
    }
        record->unity = duplicateString(value);

  /*provided_CatalogRecord_setValue_unity(record, value);*/
}

/** Static function to set the basePrice field from a string
 * @param record a pointer to the record
 * @param value the value
 */
void IMPLEMENT(CatalogRecord_setValue_basePrice)(CatalogRecord * record, const char * value)
{
    char * endptr;
    double convertedValue;
    if(CatalogRecord_isValueValid_positiveNumber(value) == 1)
    {
        convertedValue = strtod(value, &(endptr));
        record->basePrice = convertedValue;
    }
    else
    {
        fatalError("Error basePrice invalid");
    }

  /*provided_CatalogRecord_setValue_basePrice(record, value);*/
}

/** Static function to set the sellingPrice field from a string
 * @param record a pointer to the record
 * @param value the value
 */
void IMPLEMENT(CatalogRecord_setValue_sellingPrice)(CatalogRecord * record, const char * value)
{
    char * endptr;
    double convertedValue;

    if(CatalogRecord_isValueValid_positiveNumber(value) == 1)
    {
		convertedValue = strtod(value, &(endptr));
        record->sellingPrice = convertedValue;
    }
    else
    {
        fatalError("Error sellingPrice invalid");
    }

  /*provided_CatalogRecord_setValue_sellingPrice(record, value);*/
}

/** Static function to set the rateOfVAT field from a string
 * @param record a pointer to the record
 * @param value the value
 */
void IMPLEMENT(CatalogRecord_setValue_rateOfVAT)(CatalogRecord * record, const char * value)
{
    char * endptr;
    double convertedValue;

    if(CatalogRecord_isValueValid_positiveNumber(value) == 1)
    {
        convertedValue = strtod(value, &(endptr));
        record->rateOfVAT = convertedValue;
    }
    else
    {
        fatalError("Error rateOfVAT invalid");
    }

  /*provided_CatalogRecord_setValue_rateOfVAT(record, value);*/
}


/** Static function which create a copy string on the head of the code field value
 * @param record a pointer to the record
 * @return the new string
 * @note The copy is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * IMPLEMENT(CatalogRecord_getValue_code)(CatalogRecord * record)
{
    return duplicateString(record->code);

    /*return provided_CatalogRecord_getValue_code(record);*/
}

/** Static function which create a copy string on the head of the designation field value
 * @param record a pointer to the record
 * @return the new string
 * @note The copy is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * IMPLEMENT(CatalogRecord_getValue_designation)(CatalogRecord * record)
{
    char * _designation = (char*)malloc(CATALOGRECORD_DESIGNATION_SIZE);
    if(_designation == NULL)
    {
        fatalError("Allocation error of designation");
    }
/*initialize every bit of the string "_designation" with '\0' */
    memset(_designation,'\0', CATALOGRECORD_DESIGNATION_SIZE);
/*copy the value inside the string "_designation" */
    copyStringWithLength(_designation,record->designation,CATALOGRECORD_DESIGNATION_SIZE);

    return _designation;

  /*return provided_CatalogRecord_getValue_designation(record);*/
}

/** Static function which create a copy string on the head of the unity field value
 * @param record a pointer to the record
 * @return the new string
 * @note The copy is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * IMPLEMENT(CatalogRecord_getValue_unity)(CatalogRecord * record)
{
    char * _unity = (char*)malloc(CATALOGRECORD_UNITY_SIZE);
    if(_unity == NULL)
    {
        fatalError("Allocation failed of unity, function CatalogRecord_getValue_unity, file CatalogRecord.c");
    }
    memset(_unity,'\0', CATALOGRECORD_UNITY_SIZE);
    copyStringWithLength(_unity,record->unity,CATALOGRECORD_UNITY_SIZE);

    return _unity;

  /*return provided_CatalogRecord_getValue_unity(record);*/
}

/** Static function which create a copy string on the head of the basePrice field value
 * @param record a pointer to the record
 * @return the new string
 * @note The copy is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * IMPLEMENT(CatalogRecord_getValue_basePrice)(CatalogRecord * record)
{
    /*
    char * _basePrice = (char*)malloc(CATALOGRECORD_BASEPRICE_SIZE * sizeof(char));
    if(_basePrice == NULL)
    {
        fatalError("Allocation failed of _basePrice, function CatalogRecord_getValue_basePrice, file CatalogRecord.c");
    }
    memset(_basePrice,'\0', CATALOGRECORD_BASEPRICE_SIZE);
    sprintf(_basePrice, "%.2f" ,record->basePrice);

    return _basePrice;
    */

    char buffer[CATALOGRECORD_MAXSTRING_SIZE];
    snprintf(buffer, CATALOGRECORD_MAXSTRING_SIZE, "%.2f", record->basePrice);
    return duplicateString(buffer);

  /*return provided_CatalogRecord_getValue_basePrice(record);*/
}

/** Static function which create a copy string on the head of the sellingPrice field value
 * @param record a pointer to the record
 * @return the new string
 * @note The copy is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * IMPLEMENT(CatalogRecord_getValue_sellingPrice)(CatalogRecord * record)
{
    char * _sellingPrice = (char*)malloc(CATALOGRECORD_SELLINGPRICE_SIZE*sizeof(char));
    if(_sellingPrice == NULL)
    {
        fatalError("Allocation failed of _sellingPrice, function CatalogRecord_getValue_sellingPrice, file CatalogRecord.c");
    }
    memset(_sellingPrice,'\0', CATALOGRECORD_SELLINGPRICE_SIZE);
    sprintf(_sellingPrice, "%.2f" ,record->sellingPrice);

    return _sellingPrice;

  /*return provided_CatalogRecord_getValue_sellingPrice(record);*/
}

/** Static function which create a copy string on the head of the rateOfVAT field value
 * @param record a pointer to the record
 * @return the new string
 * @note The copy is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * IMPLEMENT(CatalogRecord_getValue_rateOfVAT)(CatalogRecord * record)
{
    char * _rateOfVAT = (char*)malloc(CATALOGRECORD_RATEOFVAT_SIZE*sizeof(char));
    if(_rateOfVAT == NULL)
    {
        fatalError("Allocation failed of _rateOfVAT, function CatalogRecord_getValue_rateOfVAT, file CatalogRecord.c");
    }
    memset(_rateOfVAT,'\0', CATALOGRECORD_RATEOFVAT_SIZE);
    sprintf(_rateOfVAT, "%.2f" ,record->rateOfVAT);

    return _rateOfVAT;

  /*return provided_CatalogRecord_getValue_rateOfVAT(record);*/
}

/** Initialize a record
 * @param[in] record a pointer to a record to initialize
 * @warning every initialized record must be finalized with CatalogRecord_finalize()
 */
void IMPLEMENT(CatalogRecord_init)(CatalogRecord * record)
{
    record->code = duplicateString("");
    record->designation = duplicateString("");
    record->unity = duplicateString("");
    record->basePrice = 0;
    record->sellingPrice = 0;
    record->rateOfVAT = 0;

    /*provided_CatalogRecord_init(record);*/
}

/** Finalize a record.
 * @param[in] record a pointer to a record to finalize
 */
void IMPLEMENT(CatalogRecord_finalize)(CatalogRecord * record)
{
    free(record->code);
    free(record->designation);
    free(record->unity);

  /*provided_CatalogRecord_finalize(record);*/
}

/** Read a record from a file
 * @param record a pointer to an initialized record on which to store data
 * @param file the file from which the data are read
 */
void IMPLEMENT(CatalogRecord_read)(CatalogRecord * record, FILE * file)
{
#if 0
    /*malloc buffer with CATALOGRECORD_SIZE*/
   char * _valueCatalogRecord=(char*)malloc(CATALOGRECORD_SIZE);
        if(_valueCatalogRecord == NULL)
        {
            fatalError("Allocation failed of _valueCatalogRecord, function CatalogRecord_read, file CatalogRecord.c");
        }

/*read each value of the file and put it in the record*/
    if(fread(_valueCatalogRecord, sizeof(char) * CATALOGRECORD_CODE_SIZE, 1, file) == 0)
    {
        if(feof(file) == 0)fatalError("Error ! read in the file fail , end of file ");
        if(ferror(file) == 0)fatalError("Error ! read in the file fail , error");
        fatalError("Error ! read size in the file fail !");
    }
    CatalogRecord_setValue_code(record, _valueCatalogRecord);


    if(fread(_valueCatalogRecord,sizeof(char)*CATALOGRECORD_DESIGNATION_SIZE,1,file)==0){
        if(feof(file)==0)fatalError("Error ! read in the file fail , end of file ");
        if(ferror(file)==0)fatalError("Error ! read in the file fail , error");
        fatalError("Error ! read content in the file fail !");
    }
    CatalogRecord_setValue_designation(record, _valueCatalogRecord);


    if(fread(_valueCatalogRecord, sizeof(char)*CATALOGRECORD_UNITY_SIZE,1,file)==0){
	    if(feof(file)==0)fatalError("Error ! read in the file fail , end of file ");
        if(ferror(file)==0)fatalError("Error ! read in the file fail , error");
        fatalError("Error ! read size in the file fail !");
    }
    CatalogRecord_setValue_unity(record,_valueCatalogRecord);


    if(fread(_valueCatalogRecord,sizeof(char)*CATALOGRECORD_BASEPRICE_SIZE,1,file)==0){
	    if(feof(file)==0)fatalError("Error ! read in the file fail , end of file ");
        if(ferror(file)==0)fatalError("Error ! read in the file fail , error");
        fatalError("Error ! read content in the file fail !");
    }
    CatalogRecord_setValue_basePrice(record,_valueCatalogRecord);


    if(fread(_valueCatalogRecord,sizeof(char)*CATALOGRECORD_SELLINGPRICE_SIZE,1,file)==0){
	    if(feof(file)==0)fatalError("Error ! read in the file fail , end of file ");
        if(ferror(file)==0)fatalError("Error ! read in the file fail , error");
        fatalError("Error ! read content in the file fail !");
    }
    CatalogRecord_setValue_sellingPrice(record,_valueCatalogRecord);


    if(fread(_valueCatalogRecord,sizeof(char)*CATALOGRECORD_RATEOFVAT_SIZE,1,file)==0){
	    if(feof(file)==0)fatalError("Error ! read in the file fail , end of file ");
        if(ferror(file)==0)fatalError("Error ! read in the file fail , error");
        fatalError("Error ! read content in the file fail !");
    }
    CatalogRecord_setValue_rateOfVAT(record,_valueCatalogRecord);

	/*free the memory who was allocated for the buffer*/
        free(_valueCatalogRecord);

  /*provided_CatalogRecord_read(record, file);*/
#endif

    provided_CatalogRecord_read(record, file);
}

/** Write a record to a file
 * @param record a pointer to a record
 * @param file the file to which the data are written
 */
void IMPLEMENT(CatalogRecord_write)(CatalogRecord * record, FILE * file)
{
#if 0

/*recovery of the different values of the record */
    char * _code = CatalogRecord_getValue_code(record);
    char * _designation = CatalogRecord_getValue_designation(record);
    char * _unity = CatalogRecord_getValue_unity(record);
    char * _basePrice = CatalogRecord_getValue_basePrice(record);
    char * _sellingPrice = CatalogRecord_getValue_sellingPrice(record);
    char * _rateOfVAT = CatalogRecord_getValue_rateOfVAT(record);

/*write each value of the record in the file with each own fixed size*/
    if(fwrite(_code, CATALOGRECORD_CODE_SIZE * sizeof(char), 1, file) <= 1)
    {
        fatalError("Error fwrite, function CatalogRecord_write, file CatalogRecord.c");
    }
    if(fwrite(_designation, CATALOGRECORD_DESIGNATION_SIZE * sizeof(char), 1, file) <= 1)
    {
        fatalError("Error fwrite, function CatalogRecord_write, file CatalogRecord.c");
    }
    if(fwrite(_unity, CATALOGRECORD_UNITY_SIZE * sizeof(char), 1, file) <= 1)
    {
        fatalError("Error fwrite, function CatalogRecord_write, file CatalogRecord.c");
    }
    if(fwrite(_basePrice, CATALOGRECORD_BASEPRICE_SIZE * sizeof(char), 1, file) <= 1)
    {
        fatalError("Error fwrite, function CatalogRecord_write, file CatalogRecord.c");
    }
    if(fwrite(_sellingPrice, CATALOGRECORD_SELLINGPRICE_SIZE * sizeof(char), 1, file) <= 1)
    {
        fatalError("Error fwrite, function CatalogRecord_write, file CatalogRecord.c");
    }
    if(fwrite(_rateOfVAT, CATALOGRECORD_RATEOFVAT_SIZE * sizeof(char), 1, file) <= 1)
    {
        fatalError("Error fwrite, function CatalogRecord_write, file CatalogRecord.c");
    }

/*free all the memory who was allocated by the CatalogRecord_getValue functions*/
        free(_code);
        free(_designation);
        free(_unity);
        free(_basePrice);
        free(_sellingPrice);
        free(_rateOfVAT);

  /*provided_CatalogRecord_write(record, file);*/
#endif

  provided_CatalogRecord_write(record, file);
}

