// Busca en el array ordenado por rut, devuelve el índice o -1 si no encontrado.
int buscarInvolucradoPorRUT(struct involucrados **array, int tamInvolucrados, char *rutBuscado) {
    int izq = 0, der = tamInvolucrados - 1; 
    while (izq <= der) { // mientras la izq no haya sobrepasado derecha 
        int medio = (izq + der) / 2; // si el tam es par la division entera dedonde hacia abajo o sea a la izquierda
        int cmp = strcmp(array[medio]->persona->rut, rutBuscado); 
        if (cmp == 0) {
            return medio;  
        } else if (cmp < 0) { // si la comparacion sale negativa, significa que es mayor el que buscamos entonces busca por la derecha
            izq = medio + 1; // ajustamos medio para la derecha
        } else { // si la comparacion resulta positiva, signnifica que es menor el que buscamos entonces busca por la izq
            der = medio - 1; // ajustamos medio para la izq
        }
    }
    return -1; // No encontrado // si sale del ciclo no encontramos 
}


int compactarInvolucrados(struct involucrados **array, int tamInvolucrados) {
    int nuevoTam = 0;

    // Mover todos los elementos no NULL al frente del arreglo
    for (int i = 0; i < tamInvolucrados; i++) {
        if (array[i] != NULL) {
            array[nuevoTam++] = array[i];
        }
    }

    // Rellenar el resto del arreglo con NULL
    for (int i = nuevoTam; i < tamInvolucrados; i++) {
        array[i] = NULL;
    }

    return nuevoTam;
}

int buscarInvolucradoEnCausa(struct causa *causa, char *rutBuscado) {
    if (causa == NULL || causa->involucrados == NULL || causa->tamInvolucrados <= 0) return -1;

    // Compactar para eliminar NULLs
    causa->tamInvolucrados = compactarInvolucrados(causa->involucrados, causa->tamInvolucrados);

    // Ordenar por rut aqui iria el ordenar
    

    // Buscar con búsqueda binaria
    return buscarInvolucradoPorRUT(causa->involucrados, causa->tamInvolucrados, rutBuscado);
}
