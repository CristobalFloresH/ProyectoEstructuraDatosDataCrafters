#include <stdio.h>

void menuEliminarCausa(struct ministerio *ministerio) {
    int opcion = -1, exito;
    char rut[30];
    char ruc[30];
    struct nodoCausas *encontrado;

    if (ministerio == NULL) {
        printf("Ministerio no inicializado.\n");
        return;
    }

    while (opcion != 0) {
        printf("\n=========== MENU ELIMINAR CAUSA ===========\n");
        printf("1. Eliminar Causa\n");
        printf("2. Eliminar Carpeta\n");
        printf("3. Eliminar Involucrado\n");
        printf("4. Eliminar Sentencia\n");
        printf("0. Volver.\n");
        printf("Ingrese opcion:");
        scanf("%d", &opcion);
        (void)getchar();

        switch (opcion) {
            case 1:
                printf("Ingrese RUC de la causa a eliminar:\n");
                scanf("%s", ruc);
                (void)getchar();
                exito = eliminarCausa(&(ministerio->causas), ruc);
                if (exito == 0)
                    printf("No se pudo eliminar causa.\n");
                else
                    printf("Causa eliminada exitosamente.\n");

                break;

            case 2:
                menuEliminarCarpeta(ministerio);
                break;

            case 3:
                printf("Ingrese RUC de la causa y RUT del involucrado a eliminar.\n");
                scanf("%s", ruc);
                (void)getchar();
                scanf("%s", rut);
                (void)getchar();
                exito = eliminarInvolucrado(&(ministerio->causas), ruc, rut);
                if (exito == 0)
                    printf("No se pudo eliminar el involucrado.\n");
                else
                    printf("Involucrado eliminado exitosamente.\n");
                break;

            case 4:
                printf("Ingrese RUC de la sentencia a eliminar:\n");
                scanf("%s", ruc);
                (void)getchar();
                encontrado = buscarNodoCausa(ministerio->causas, ruc);
                if (encontrado != NULL && encontrado->datosCausa != NULL && encontrado->datosCausa->sentencia != NULL) {
                    free(encontrado->datosCausa->sentencia);
                    encontrado->datosCausa->sentencia = NULL;
                    printf("Sentencia eliminada correctamente.\n");
                } else {
                    printf("No se encontro sentencia para eliminar.\n");
                }
                break;

            case 0:
                return;

            default:
                printf("Opcion no valida.\n");
                break;
        }
    }
}
