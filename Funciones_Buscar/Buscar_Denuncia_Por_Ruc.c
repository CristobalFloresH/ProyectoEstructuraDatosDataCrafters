struct denuncia *buscarDenunciaPorRuc(struct nodoDenuncias *listaDenuncias, char *rucBuscado){
    struct nodoDenuncias *actual;

    //se recorre la lista mientras queden nodos por revisar
    //y pregunta si el ruc actual es igual al buscado

    actual = listaDenuncias;
    
    while(actual != NULL){

        if(strcmp(actual->datosDenuncia->ruc, rucBuscado) == 0){
            return actual->datosDenuncia;
        }
        actual = actual->siguiente;
    }
    return NULL;
}

