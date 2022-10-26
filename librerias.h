#ifndef LIBRERIAS_H_INCLUDED
#define LIBRERIAS_H_INCLUDED

typedef struct
{
   char nombreApe[40];
   char materia[40];
   int idMateria;
   int nota;
   int legajo;

} registroArchivo;

typedef struct
{
   int nota;
   int legajo;
   char nombreApe[40];

} notaAlumno;

typedef struct _nodo
{
   notaAlumno dato;
   struct _nodo *sig;
} nodo;

typedef struct {
    int idMateria;
    char materia[40];
    nodo * listaDeNotas;
} celda;





#endif // LIBRERIAS_H_INCLUDED
