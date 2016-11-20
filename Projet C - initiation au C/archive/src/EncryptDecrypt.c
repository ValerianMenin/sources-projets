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
 * $Id: EncryptDecrypt.c 247 2010-09-10 10:23:07Z sebtic $
 */

#include <EncryptDecrypt.h>

void IMPLEMENT(encrypt)(const char * key, char * str) {

    size_t i = 0;
    size_t j = 0;
    /* using vignere methode until the end of the string */
    while(str[i]!='\0')
        {
            if(key[j]=='\0')
            {
                j=0;
            }
            /* encryption of the current charactere of string by the vignere encryption */
            if(str[i]>='a' && str[i]<='z')
            {
                str[i]=(char)(((toLowerChar(key[j])-'a')+(toLowerChar(str[i])-'a'))%26+'a');
            }
            else if(str[i]>='A' && str[i]<='Z')
            {
                str[i]=(char)(((toUpperChar(key[j])-'A')+(toUpperChar(str[i])-'A'))%26+'A');
            }
            i++;
            j++;
        }

    /*provided_encrypt(key,str);*/
}

void IMPLEMENT(decrypt)(const char * key, char * str) {
    size_t i = 0;
    size_t j = 0;
    /* using vignere methode until the end of the string */
    while(str[i]!='\0')
    {
        if(key[j]=='\0')
        {
            j=0;
        }
        /* encryption of the current charactere of string by the vignere decryption */
        if(str[i]>='a' && str[i]<='z')
        {
            str[i]=(char)((toLowerChar(str[i])-toLowerChar(key[j])+26)%26+'a');
        }
        else if(str[i]>='A' && str[i]<='Z')
        {
            str[i]=(char)((toUpperChar(str[i])-toUpperChar(key[j])+26)%26+'A');
        }
        i++;
        j++;
    }

    /*provided_decrypt(key,str);*/
}
