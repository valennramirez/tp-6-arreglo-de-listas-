#include "librerias.h"
#include <stdio.h>
#include <stdlib.h>

///archivo

registroArchivo carga()
{
    registroArchivo aux;

    printf ("Ingrese los datos de un alumno\n");

    printf ("Nombre y apellido: ");
    scanf("%s", aux.nombreApe);

    printf ("Legajo: ");
    scanf("%d", &aux.legajo);

    printf ("Materia: ");
    scanf("%s", aux.materia);

    printf ("Id materia: ");
    scanf("%d", &aux.idMateria);

    printf ("Nota: ");
    scanf("%d", &aux.nota);

    return aux;
}

void cargarArchivo (char nombreArchivo[])
{
    FILE *archivo=fopen(nombreArchivo, "wb");

    if (archivo==NULL)
    {
        char seguir='s';

        while (seguir=='s')
        {
            registroArchivo nuevo;

            nuevo=carga();

            fwrite(&nuevo, sizeof(registroArchivo), 1, archivo);

            printf ("Desea continuar? s/n: ");
            fflush(stdin);
            scanf("%c", &seguir);
        }

        fclose(archivo);
    }
}

void mostrarArchivo (char nombreArchivo[])
{
    FILE *archivo=fopen(nombreArchivo, "rb");

    registroArchivo aux;

    if (archivo!=NULL)
    {
        while (fread(&aux, sizeof(registroArchivo), 1, archivo)>0)
        {
            printf ("Nombre y Apeliido: %s", aux.nombreApe);

            printf ("Legajo: %d", aux.legajo);

            printf ("Materia: %s", aux.materia);

            printf ("Id materia: %d", aux.idMateria);

            printf ("Nota: %d", aux.nota);
        }

        fclose(archivo);
    }
}
///listas

nodo *iniclista()
{
    return NULL;
}

nodo *crearNodo (int dato, int legajo, char nombreApe[])
{
    nodo *aux=(nodo*)malloc(sizeof(nodo));

    aux->dato.nota=dato;
    aux->dato.legajo=legajo;

    strcpy(aux->dato.nombreApe, nombreApe);

    aux->sig=NULL;

    return aux;
}

nodo *agregarPrincipio (nodo *lista, nodo *nn)
{
    if(lista==NULL)
    {
        lista=nn;
    }
    else
    {
        nn->sig=lista;
        lista=nn;
    }

    return lista;
}

///arreglo de listas

notaAlumno cargarNotas ()
{
    notaAlumno notaA;

    printf ("Nombre y apellido: ");
    scanf("%s", notaA.nombreApe);

    printf ("Nota: ");
    scanf("%d", &notaA.nota);

    printf ("Legajo: ");
    scanf("%d", &notaA.legajo);

    return notaA;
}

int buscarMateria (celda ADL[], char materia[], int validos)
{
    int i=0, rta=-1;

    while (validos>i && rta==-1)
    {
        if(strcmpi(ADL[i].materia, materia)==0)
        {
            rta=i;
        }
        i++;
    }

    return rta;
}

int agregarMateria (celda ADL[], char materia[], int validos)
{
    strcpy(ADL[validos].materia, materia);

    ADL[validos].listaDeNotas=iniclista();

    validos ++;

    ADL[validos].idMateria=validos;

    return validos;
}

int alta (celda ADL[], char materia[], int dato, int legajo, char nombreApe[], int validos)
{
    nodo *aux=crearNodo(dato, legajo, nombreApe);

    int pos=buscarMateria(ADL, materia, validos);

    if (pos==-1)
    {
        validos=agregarMateria(ADL, materia, validos);
        pos=validos-1;
    }

    ADL[pos].listaDeNotas=agregarPrincipio(ADL[pos].listaDeNotas, aux);

    return validos;
}

int ingresarNotas (celda adl[], int dimension)
{
    int validos=0;
    char seguir='s';
    char materia[50];

    while (seguir=='s' && validos<dimension)
    {
        printf ("Ingrese una materia: ");
        scanf("%s", materia);

        printf ("Ingrese las notas del alumno");

        notaAlumno aux=cargarNotas();

        //validos=alta(adl, materia, aux, validos);

        printf ("Desea seguir? s/n: ");
        scanf("%c", &seguir);
    }

    return validos;
}

/// funciones del tp

int pasarDeArchivoToADL (celda adl[], int dimension, char nombreArchivo[])
{
    FILE *archivo=fopen(nombreArchivo, "rb");

    registroArchivo aux;
    int validos=0;

    if (archivo!=NULL)
    {
        while (fread(&aux, sizeof(registroArchivo), 1, archivo)>0 && validos<dimension)
        {
            validos=alta(adl, aux.materia, aux.nota, aux.legajo, aux.nombreApe, validos);

            validos++;
        }
        fclose(archivo);
    }

    return validos;
}

void pasarDeADLToArchivoDeAprobados (char nombreArchivo[], celda adl[], int validos)
{
    FILE *archivo =fopen(nombreArchivo, "wb");

    if(archivo!=NULL)
    {
        for(int i=0; i<validos; i++) ///cuenta las listas de a celda
        {
            while (adl[i].listaDeNotas!=NULL) ///recorre toda la lista
            {
                if (adl[i].listaDeNotas->dato.nota>=6)
                {
                    fwrite(&adl[i].listaDeNotas->dato, sizeof(notaAlumno), 1, archivo);
                }

                adl[i].listaDeNotas=adl[i].listaDeNotas->sig;
            }
        }

        fclose(archivo);
    }
}

