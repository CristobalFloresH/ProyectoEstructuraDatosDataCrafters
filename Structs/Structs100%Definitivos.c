#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct denuncia { //Datos denuncia singular.
    struct persona *denunciante; //persona que envio la denuncia
    struct persona *denunciado; //persona que recibio la denuncia
    char *fecha;
    char *descripcion;
    char *ruc;
    char *tipoDeDenuncia;
};

struct nodoDenuncias { //Lista simple Doblemente Enlazada De Denuncias
    struct denuncia *datosDenuncia;
    struct nodoDenuncias *siguiente;
    struct nodoDenuncias *anterior;
};

struct persona { //Datos persona singular
    char *nombre;
    char *apellido;
    char *rut;
    int rol;
    /** 1 = usuario comun, 2 = fiscal, 3 = juez**/

    char *contrasena;

    struct nodoDenuncias *denuncias;
};

struct nodoPersonasABB { //arbol (ABB)
    struct persona *datosPersona;
    struct nodoPersonasABB *izquierda;
    struct nodoPersonasABB *derecha;
};

struct datosImputados {
    char *declaracion;
    int medidasCautelar; /**1 = Prision Preventiva, 2 = Arraígo nacional, 3 = firma periódica,
    4 = orden de alejamiento, 5 = arresto domicilario, 6 = libertad bajo fianza, 7 = ninguna**/
    char *fechaInicioMedida;
    char *fechaFinMedida;

    int estadoProcesal; /**1 = medida cautelar, 2 = formalizado (arrestado), 3 = sobreseido**/
};

struct involucrados {
    int tipoInvolucrado; //1 = victima, 2 = imputado, 3 = fiscal, 4 = juez
    struct datosImputados *datosImputados;
    struct persona *persona;
};

struct causa { //Datos causa singular
    char *ruc; //Rol unico de causa (identificador unico)
    struct denuncia *denuncia; //LA denuncia de esta causa
    struct nodoDatosCarpetas *datosCarpetas; //datos investigativos de la carpeta
    struct involucrados **involucrados; //array de involucrados
    int tamInvolucrados; //tamaño array involucrados

    int estadoCausa; //1 = archivada, 2 = investigacion en progreso, 3 = cerrada, 4 = en juicio

    char *sentencia;
};

struct nodoCausas { //Lista Circular doblemente enlazada
    struct causa *datosCausa;
    struct nodoCausas *siguiente;
    struct nodoCausas *anterior;
};

struct nodoDatosCarpetas { //lista doblemente enlazada
    struct datosCarpeta *datosCarpeta;
    struct nodoDatosCarpetas *siguiente;
    struct nodoDatosCarpetas *anterior;
};

struct datosDiligencias {
    int prioridad; //1 = muy baja, 2 = baja, 3 = media, 4 = alta, 5 = muy alta
    char *fechaInicio;
    char *fechaFin;
    char *descripcion;
    char *estado;
    char *tipoDiligencia;
};

struct datosCarpeta { //datos investigativos (NO PERSONAS) singular de 1 tipo de dato
    char *fecha; //fecha
    char *descripcion; //descripción generica
    struct persona *datosPersona;

    int tipoDeDato; //tipo de dato
    /** 1 = declaraciones, 2 = pruebas generales (Fotos, videos, etc), 3 = diligencias, 4 = denuncia**/

    struct datosDiligencias *datosDiligencias;
    struct denuncia *datosDenuncia;
};

struct ministerio { //el mismisimo ministerio
    struct nodoPersonasABB *personas;
    struct nodoCausas *causas;
};
