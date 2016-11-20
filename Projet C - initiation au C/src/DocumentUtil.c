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
 * $Id: DocumentUtil.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <DocumentUtil.h>
char * base10To36(int id);

/** Create a new string on the heap which represents the parameter as a number in basis 36.
 * @param id the number to convert
 * @return a new string
 * @note The string is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */


#if 0
static long BaseB2Dec(int base, int numberLength, int * number);
static long Bin2Dec(int * bin);
static void Dec2Bin(short n, int * numbers);

static long BaseB2Dec(int base, int numberLength, int * number)/* (indice 0 : max, indice fin : unite) == (LSB = max, MSB = 0)*/
{
    if(numberLength == 1)
    {
        return number[0];
    }
    else
    {
        return number[numberLength - 1] + (base * BaseB2Dec(base, numberLength - 1, number));
    }
}

static long Bin2Dec(int * bin)/* LSB = max, MSB = 0 */
{
    long dec;
    dec = BaseB2Dec(2, 15, bin + 1);
    if(bin[0] == 1)
        dec = - (1L << 15) + dec; /* "L" is the same as if we use (long) before the expression */
    return dec;
}

static void Dec2Bin(short n, int * numbers) /* LSB = max, MSB = 0 */
{
    int i;
    if(n >= 0)
    {
        for(i = 15; i <= 0 ; i--) /* table in entrance : numbersLength = 16 */
        {
            numbers[i] = n%2;
            n /= 2;
        }
    }
    else
    {
        numbers[0] = 1;
        n = (short)(n + (1L << 15));
    }
}
#endif

char * IMPLEMENT(computeDocumentNumber)(long id) {

   /* char * alphaDigital[10];
    int i;

    alphaDigital[9] = '\0';
    for(i = 8; i >= 0; i--)
    {
        alphaDigital[i] = base10To36(id%36);
        id /= 36;
    }


    return alphaDigital;*/

   return provided_computeDocumentNumber(id);
}

/*char * base10To36(int base10){
    char * base36;


    return base36;
}*/

/** Create a new string on the heap which represents the date in the format DD/MM/YYYY.
 * @param day the day
 * @param month the month
 * @param year the year
 * @return a new string
 * @note The string is allocated using malloc().
 * @warning the user is responsible for freeing the memory allocated for the new string
 */
char * IMPLEMENT(formatDate)(int day, int month, int year) {

   char * date;

    if((date = (char*) malloc(11)) == NULL)
    {
        fatalError("Failed at memory allocation date, function formatDate in file DcumentUtil.c");
    }

    date[0] = (char)(day / 10 + '0');
    date[1] = (char)(day % 10 + '0');
    date[2] = '/';

    date[3] = (char)(month / 10 + '0');
    date[4] = (char)(month % 10 + '0');
    date[5] = '/';

    date[9] = (char)(year % 10 + '0');

    year = year / 10;
    date[8] = (char)(year % 10 + '0');

    year = year / 10;
    date[7] = (char)(year % 10 + '0');

    year = year / 10;
    date[6] = (char)(year % 10 + '0');

    date[10] = '\0';

    return date;

    /*return provided_formatDate(day, month, year);*/
}


/** Write a string in a binary file
 * @param str the string
 * @param file the file
 */
void IMPLEMENT(writeString)(const char * str, FILE * file) {

    size_t size=stringLength(str)+1;
    if(fwrite(&size, sizeof(size_t),1,file)==0)
    {
        fatalError("Error ! Write size in the file fail !");
    }
    if(fwrite(str,sizeof(char)*size,1,file)==0)
    {
        fatalError("Error ! Write content in the file fail !");
    }

   /* if(fwrite(str, size, 1, file) < 1)
    {
        fatalError("Error ! Write size in the file fail !");
    }*/

   /*provided_writeString(str,file);*/
}

/** Read a string from a binary file
 * @param file the file
 * @return a new string created on the heap which contains the read string
 * @see writeString()
 */
char * IMPLEMENT(readString)(FILE * file) {

    char * str;/*the string to get*/
    size_t size;/*the size of the string we want to get*/
    /*first we read the size of the string we want to read*/
    if(fread(&size, sizeof(size_t),1,file) < 1)
    {
        fclose(file);
        fatalError("Error ! Read size in file Fail !");
    }

    str=(char*)malloc(sizeof(char)*(size+1));
    if(str==NULL){
        fclose(file);
        fatalError("Error allocation str !");
    }

    if(fread(str,sizeof(char)*size,1,file)==0)
    {
        fclose(file);
        fatalError("Error ! Read file fail !");
    }

    str[size]='\0';
    return str;

    /*return provided_readString(file);*/
}
