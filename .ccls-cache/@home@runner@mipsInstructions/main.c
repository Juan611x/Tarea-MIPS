#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int cargarProgramaMemoria(const char *arreglo[], int pc, char *programa){
        FILE *archivo = fopen( programa, "r" );
        if( archivo == NULL ){
                printf("El programa no existe\n");
                return 1;
        }
        else{
                char linea[1024];
                int itera = pc;
                while (fgets(linea, sizeof(linea), archivo) != NULL) {
                        arreglo[itera++] = strdup(linea);
                }
                fclose( archivo );
        }
        return 0;
}

int set( const char *arreglo[], int pc, int tamMax ){
        const char  *instSet[5] = {0};
        char tmp[tamMax], tmp2[tamMax];
        strcpy(tmp, arreglo[pc]);
        char *aux = strtok( tmp, " " );
        int iterador = 0;
        while( aux != NULL ){
                instSet[iterador++] = strdup(aux);
                aux = strtok(NULL, " ");
        }
        if( strcmp( instSet[0], "SET" ) == 0 ){
                strcpy(tmp2, instSet[1]);
                memmove(tmp2, tmp2 + 1, strlen(tmp));
                int index = atoi(tmp2);
                arreglo[index] = strdup(instSet[2]);
                for(int it = pc; arreglo[it] != NULL; it++){
                        arreglo[it] = arreglo[ it + 1 ];
                }
                return 1;
        }
        return 0;
}

int fetch( char *inst, const char *arreglo[] ){
        char *token = strtok(inst, " " );
        int i = 0;
        while( token != NULL ){
                arreglo[i++] = strdup(token);
                token = strtok(NULL, " ");
        }
        return 0;
}

int ldr( int *mar, char mdr[], int *acumulator, const char *inst[], int tamMax, const char *memoria[] ){
        char aux[tamMax];
        strcpy(aux, inst[1]);
        memmove( aux, aux + 1, strlen(aux) );
        (*mar) = atoi(aux);
        mdr = strdup(memoria[(*mar)]);
        (*acumulator) = atoi(mdr);
        return 0;
}

int add( int *acumulator, int *alu, int tamMax, int *mar, char mdr[], const char *inst[], const char *memoria[] ){
        char aux[tamMax];
        (*alu) = (*acumulator);
        strcpy(aux, inst[1]);
        memmove( aux, aux + 1, strlen(aux) );
        (*mar) = atoi(aux);
        mdr = strdup(memoria[(*mar)]);
        (*acumulator) = atoi(mdr);
        (*alu) += (*acumulator);
        (*acumulator) = (*alu);
        return 0;
}

int str( int *acumulator, int *mar, char mdr[], int tamMax, const char *inst[], const char *memoria[] ){
        char aux[tamMax];
        strcpy(aux, inst[1]);
        memmove(aux, aux + 1, strlen(aux));
        (*mar) = atoi(aux);
        sprintf(mdr, "%d", (*acumulator));
        memoria[(*mar)] = strdup(mdr);
        return 0;
}

int   shw( int acumulator, char icr[], int mar, char mdr[], char unidadControl[], int pc, int tamMax, const char *memoria[] ){
        const char  *instShw[5] = {0};
        char tmp[tamMax], tmp2[tamMax];
        strcpy(tmp, memoria[pc]);
        char *aux = strtok( tmp, " " );
        int iterador = 0;
        while( aux != NULL ){
                instShw[iterador++] = strdup(aux);
                aux = strtok(NULL, " ");
        }
        if( strcmp(instShw[0], "SHW") == 0 ){
                if( strcmp(instShw[1], "ACC") == 0 ){
                        printf("%d\n", acumulator);
                }
                else if( strcmp(instShw[1], "ICR") == 0 ){
                        printf("%s\n", icr);
                }
                else if( strcmp( instShw[1], "MAR" ) == 0 ){
                        printf("%d\n", mar);
                }
                else if( strcmp( instShw[1], "MDR" ) == 0 ){
                        printf("%s\n", mdr);
                }
                else if( strcmp( instShw[1], "UC" ) == 0 ){
                        printf("%s\n", unidadControl);
                }
                else{
                        char aux2[tamMax];
                        strcpy(aux2, instShw[1]);
                        memmove( aux2, aux2 + 1, strlen(aux2) );
                        int index = atoi(aux2);
                        printf("%s\n", memoria[index]);
                }
                for(int it = pc; memoria[it] != NULL; it++){
                        memoria[it] = memoria[ it + 1 ];
                }
                return 1;
        }
        return 0;
}

int end( const char *arreglo[], int pc, int tamMax ){
        const char  *instSet[5] = {0};
        char tmp[tamMax], tmp2[tamMax];
        strcpy(tmp, arreglo[pc]);
        char *aux = strtok( tmp, " " );
        int iterador = 0;
        while( aux != NULL ){
                instSet[iterador++] = strdup(aux);
                aux = strtok(NULL, " ");
        }
        if( strcmp( instSet[0], "END" ) == 0 ){
                for(int it = pc; arreglo[it] != NULL; it++){
                        arreglo[it] = NULL;
                }
                return 1;
        }
        return 0;
}

int inc( int *mar, char mdr[], int *acumulator, int *alu, const char *inst[], int tamMax, const char *memoria[] ){
        char aux[tamMax];
        strcpy(aux, inst[1]);
        memmove( aux, aux + 1, strlen(aux) );
        (*mar) = atoi(aux);
        mdr = strdup(memoria[(*mar)]);
        (*acumulator) = atoi(mdr);
         (*alu) = (*acumulator);
        (*alu) += 1;
        (*acumulator) = (*alu);
        sprintf(mdr, "%d", (*acumulator));
        memoria[(*mar)] = strdup(mdr);
        return 0;
}

int dec( int *mar, char mdr[], int *acumulator, int *alu, const char *inst[], int tamMax, const char *memoria[] ){
        char aux[tamMax];
        strcpy(aux, inst[1]);
        memmove( aux, aux + 1, strlen(aux) );
        (*mar) = atoi(aux);
        mdr = strdup(memoria[(*mar)]);
        (*acumulator) = atoi(mdr);
         (*alu) = (*acumulator);
        (*alu) -= 1;
        (*acumulator) = (*alu);
        sprintf(mdr, "%d", (*acumulator));
        memoria[(*mar)] = strdup(mdr);
        return 0;
}

int pause( int acumulator, int mar, int alu, int pc, int tamMax, char mdr[], char icr[], char unidadControl[], const char *memoria[] ){
        const char  *instShw[5] = {0};
        char tmp[tamMax], tmp2[tamMax];
        strcpy(tmp, memoria[pc]);
        char *aux = strtok( tmp, " " );
        int iterador = 0;
        while( aux != NULL ){
                instShw[iterador++] = strdup(aux);
                aux = strtok(NULL, " ");
        }
        if( strcmp(instShw[0], "PAUSE") == 0 ){
                printf("El valor de todos los registros y memoria es:\n");
                printf( "Acumulator: %d\nMAR: %d\nALU: %d\nPC: %d\nMDR: %s\nICR: %s\nUnidadControl: %s\n", acumulator, mar, alu, pc, mdr, icr, unidadControl );
                printf( "Memorias: [" );
                for(int i = 0; i < 400; i++){
                        printf("%s, ", memoria[i]);
                }
                printf("]\n");
                char continuar[100];
                do{
                        printf( "El programa ha sido pausado para continuar escribe continue: " );
                        scanf("%s", continuar);
                }while(strcmp( continuar, "continue" ) != 0 );
                for(int it = pc; memoria[it] != NULL; it++){
                        memoria[it] = memoria[ it + 1 ];
                }
                return 1;
        }
        return 0;
}

int main(){
        int tamMax = 100;
        char programa[100] = {0};
        do{
                const char *inst[5] = {0}, *memoria[400] = {NULL};
                char mdr[tamMax], icr[tamMax], unidadControl[tamMax], aux[tamMax];
                int saltar3 = 0, acumulator, alu, pc = 200, mar;
                printf("Cual es el nombre del programa que desea ejecutar: ");
                scanf("%s", programa);
                if( strcmp(programa, "0") == 0 ){
                        return 0;
                }
                int existe = cargarProgramaMemoria(memoria, pc, programa);
                if( existe == 0 ){
                        do{
                                int saltar = set( memoria, pc, tamMax );
                                int saltar2 = shw( acumulator, icr, mar, mdr, unidadControl, pc, tamMax ,memoria );
                                int saltar4 = pause( acumulator, mar, alu, pc, tamMax, mdr, icr, unidadControl, memoria );
                                saltar3 = end( memoria, pc, tamMax );
                                if( saltar == 0 && saltar2 == 0 && saltar3 == 0 && saltar4 == 0 ){
                                        mar = pc;
                                        strcpy( mdr, memoria[pc] );
                                        if( strncmp( mdr, "LDR", 3 ) == 0 || strncmp( mdr, "ADD", 3 ) == 0 || strncmp( mdr, "STR", 3 ) == 0 || strncmp( mdr, "INC", 3 ) == 0 || strncmp( mdr, "DEC", 3 ) == 0 ){
                                                strcpy( icr, mdr );
                                                strcpy( unidadControl, icr );
                                                fetch( unidadControl, inst );
                                                if( strcmp(inst[0], "LDR") == 0 ){
                                                        ldr( &mar, mdr, &acumulator, inst, tamMax, memoria );
                                                }
                                                else if( strcmp( inst[0], "ADD" ) == 0 ){
                                                        add( &acumulator, &alu, tamMax, &mar, mdr, inst, memoria );
                                                }
                                                else if( strcmp( inst[0], "STR" ) == 0 ){
                                                        str( &acumulator, &mar, mdr, tamMax, inst, memoria );
                                                }
                                                else if( strcmp( inst[0], "INC" ) == 0 ){
                                                        inc( &mar, mdr, &acumulator, &alu, inst, tamMax, memoria );
                                                }
                                                else if( strcmp( inst[0], "DEC" ) == 0 ){
                                                        dec( &mar, mdr, &acumulator, &alu, inst, tamMax, memoria );
                                                }
                                        }
                                        strcpy(aux, memoria[pc]);
                                        pc++;
                                }
                        }while( memoria[pc] != NULL );
                }
        }while(strcmp(programa, "0") != 0);
        return 0;
}