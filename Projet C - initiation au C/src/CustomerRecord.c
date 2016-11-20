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
 * $Id: CustomerRecord.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <CustomerRecord.h>

void IMPLEMENT(CustomerRecord_setValue_name)(CustomerRecord * record, const char * name)
{
    /*record->name =  (char)realloc(char record->name[0], size_t sizeof(* value)) ;
    record->name = value;*/

    copyStringWithLength(record->name, name, CUSTOMERRECORD_NAME_SIZE);

    /*provided_CustomerRecord_setValue_name(record, value);*/
}

void IMPLEMENT(CustomerRecord_setValue_address)(CustomerRecord * record, const char * address)
{
    copyStringWithLength(record->address, address, CUSTOMERRECORD_ADDRESS_SIZE);

 /* provided_CustomerRecord_setValue_address(record, value);*/
}

void IMPLEMENT(CustomerRecord_setValue_postalCode)(CustomerRecord * record, const char * postalCode)
{
    copyStringWithLength(record->postalCode, postalCode, CUSTOMERRECORD_POSTALCODE_SIZE);

  /*provided_CustomerRecord_setValue_postalCode(record, value);*/
}

void IMPLEMENT(CustomerRecord_setValue_town)(CustomerRecord * record, const char * town)
{
    copyStringWithLength(record->town, town, CUSTOMERRECORD_TOWN_SIZE);

  /*provided_CustomerRecord_setValue_town(record, value);*/
}

char * IMPLEMENT(CustomerRecord_getValue_name)(CustomerRecord * record)
{
    /*char * nameValue = (char *)malloc(sizeof(record->name));
    nameValue = record->name;

    return nameValue;*/

    return duplicateString(record->name);

  /*return provided_CustomerRecord_getValue_name(record);*/
}

char * IMPLEMENT(CustomerRecord_getValue_address)(CustomerRecord * record)
{
    /*char * addressValue = (char *)malloc(sizeof(record->address));
    addressValue = record->address;

    return addressValue;*/


    return duplicateString(record->address);

 /*return provided_CustomerRecord_getValue_address(record);*/
}

char * IMPLEMENT(CustomerRecord_getValue_postalCode)(CustomerRecord * record)
{
    /*char * postalCodeValue = (char *)malloc(sizeof(record->postalCode));
    postalCodeValue = record->postalCode;

    return postalCodeValue;*/

    return duplicateString(record->postalCode);

  /*return provided_CustomerRecord_getValue_postalCode(record);*/
}

char * IMPLEMENT(CustomerRecord_getValue_town)(CustomerRecord * record)
{
    /*char * townValue = (char *)malloc(sizeof(record->town));
    townValue = record->town;

    return townValue;*/

    return duplicateString(record->town);

  /*return provided_CustomerRecord_getValue_town(record);*/
}

void IMPLEMENT(CustomerRecord_init)(CustomerRecord * record)
{
    memset(record->name, '0', CUSTOMERRECORD_NAME_SIZE);
    memset(record->address, '0', CUSTOMERRECORD_ADDRESS_SIZE);
    memset(record->postalCode, '0', CUSTOMERRECORD_POSTALCODE_SIZE);
    memset(record->town, '0', CUSTOMERRECORD_TOWN_SIZE);

  /*provided_CustomerRecord_init(record);*/
}

/** this function doesn't do anything */
void IMPLEMENT(CustomerRecord_finalize)(CustomerRecord * UNUSED(record))
{
 /* provided_CustomerRecord_finalize(record);*/
}

/** read 1 block of size CUSTOMERRECORD_NAME_SIZE, 1 time and check if it read 1 element */
void IMPLEMENT(CustomerRecord_read)(CustomerRecord * record, FILE * file)
{
    if(fread(record->name, sizeof(char) * CUSTOMERRECORD_NAME_SIZE, 1, file) < 1)
    {
        fatalError("Error at function CustomerRecord_read - name - in CustomerRecord.c");
    }
    if(fread(record->address, sizeof(char) * CUSTOMERRECORD_ADDRESS_SIZE, 1, file) < 1)
    {
        fatalError("Error at function CustomerRecord_read - address - in CustomerRecord.c");
    }
    if(fread(record->postalCode, sizeof(char) * CUSTOMERRECORD_POSTALCODE_SIZE, 1, file) < 1)
    {
        fatalError("Error at function CustomerRecord_read - postalCode - in CustomerRecord.c");
    }
    if(fread(record->town, sizeof(char) * CUSTOMERRECORD_TOWN_SIZE, 1, file) < 1)
    {
        fatalError("Error at function CustomerRecord_read - town - in CustomerRecord.c");
    }

  /*provided_CustomerRecord_read(record, file);*/
}

void IMPLEMENT(CustomerRecord_write)(CustomerRecord * record, FILE * file)
{
    if(fwrite(record->name, sizeof(char) * CUSTOMERRECORD_NAME_SIZE, 1, file) < 1)
    {
        fatalError("Error at function CustomerRecord_read - name - in CustomerRecord.c");
    }
    if(fwrite(record->address, sizeof(char) * CUSTOMERRECORD_ADDRESS_SIZE, 1, file) < 1)
    {
        fatalError("Error at function CustomerRecord_read - address - in CustomerRecord.c");
    }
    if(fwrite(record->postalCode, sizeof(char) * CUSTOMERRECORD_POSTALCODE_SIZE, 1, file) < 1)
    {
        fatalError("Error at function CustomerRecord_read - postalCode - in CustomerRecord.c");
    }
    if(fwrite(record->town, sizeof(char) * CUSTOMERRECORD_TOWN_SIZE, 1, file) < 1)
    {
        fatalError("Error at function CustomerRecord_read - town - in CustomerRecord.c");
    }

  /*provided_CustomerRecord_write(record, file);*/
}

