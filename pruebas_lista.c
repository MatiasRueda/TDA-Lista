#include "lista.h"
#include "pila.h"
#include "testing.h"
#include <stdio.h>
#include <stdbool.h>

/******************************************************************
 *                      FUNCIONES AUXILIARES                      *
 ******************************************************************/
bool sumar_lista(void* dato, void* extra);
bool sumar_lista_con_corte(void* dato, void* extra);
bool lista_sumar_uno_a_cada_elemento(void* dato, void* extra);
lista_t* agregar_a_la_lista(int lista[], int largo);

bool sumar_lista(void* dato, void* extra) {
    *(int*)extra = *(int*)extra + *(int*)dato;
    return true;
}

bool sumar_lista_con_corte(void* dato, void* extra) {
    if (*(int*)extra >= 6) {
        return false;
    }
    *(int*)extra = *(int*)extra + *(int*)dato;
    return true;
}

bool lista_sumar_uno_a_cada_elemento(void* dato, void* extra) {
    *(int*)dato += 1;
    return true;
}

lista_t* agregar_a_la_lista(int lista[], int largo) {
    lista_t* lista_prueba = lista_crear();
    for (int i = 0; i < largo; i++) {
        lista_insertar_ultimo(lista_prueba,&lista[i]);
    }
    return lista_prueba;
}
/******************************************************************
 *                        PRUEBAS LISTA                           *
 ******************************************************************/
// Comprueba que la lista se crea correctamente
static void prueba_lista_crear(void) {
    printf("INICIO PRUEBA: LISTA CREAR\n");

    lista_t* lista = lista_crear();

    print_test("Chequeando que la lista haya sido creada",lista != NULL);
    print_test("Chequeando que la lista esta vacia", lista_esta_vacia(lista));

    lista_destruir(lista,NULL);
}

// Comprueba que se agreguen y borren elementos de la forma correcta
static void prueba_comportamiento_lista(void) {
    printf("INICIO PRUEBA: COMPORTAMIENTO LISTA\n");

    lista_t* lista = lista_crear();

    int numero1;
    int numero2;
    int numero3;
    int numero4;

    int* dato1 = &numero1;
    int* dato2 = &numero2;
    int* dato3 = &numero3;
    int* dato4 = &numero4;

    print_test("Agrego el dato1 al principio de la lista", lista_insertar_primero(lista,dato1));
    print_test("Verifico que lo primero sea el dato1", lista_ver_primero(lista) == dato1);
    print_test("Chequeo que el largo de la lista sea 1", lista_largo(lista) == 1);

    print_test("Agrego el dato2 a lo ultimo de la lista", lista_insertar_ultimo(lista,dato2));
    print_test("Verifico que lo ultimo sea el dato2", lista_ver_ultimo(lista) == dato2);
    print_test("Chequeo que el largo de la lista sea 2", lista_largo(lista) == 2);

    print_test("Agrego el dato3 al principio de la lista", lista_insertar_primero(lista,dato3));
    print_test("Verifico que lo primero sea el dato3", lista_ver_primero(lista) == dato3);
    print_test("Chequeo que el largo de la lista sea 3", lista_largo(lista) == 3);

    print_test("Agrego el dato4 a lo ultimo de la lista", lista_insertar_ultimo(lista,dato4));
    print_test("Verifico que lo ultimo sea el dato4", lista_ver_ultimo(lista) == dato4);
    print_test("Chequeo que el largo de la lista sea 4", lista_largo(lista) == 4);

    print_test("Elimino el primer elemento de la lista y chequeo que sea el dato3", lista_borrar_primero(lista) == dato3);
    print_test("Verifico que el largo de lista sea 3", lista_largo(lista) == 3);

    print_test("Elimino el primer elemento de la lista y chequeo que sea el dato1", lista_borrar_primero(lista) == dato1);
    print_test("Verifico que el largo de lista sea 2", lista_largo(lista) == 2);

    print_test("Elimino el primer elemento de la lista y chequeo que sea el dato2", lista_borrar_primero(lista) == dato2);
    print_test("Verifico que el largo de lista sea 1", lista_largo(lista) == 1);

    print_test("Elimino el primer elemento de la lista y chequeo que sea el dato4", lista_borrar_primero(lista) == dato4);
    print_test("Verifico que la lista este vacia", lista_esta_vacia(lista));
    lista_destruir(lista,NULL);


}


// Condición de borde: al borrar todos los elementos hasta que este vacía hace que la lista se comporte como recién creada.
static void prueba_lista_vacia_agregar_y_borrar_elementos(void) {
    printf("INICIO PRUEBA: BORRAR TODOS LOS ELEMENTOS HASTA QUE ESTE VACIA LA LISTA HACE QUE LA LISTA SE COMPORTE COMO RECIEN CREADA\n");

    lista_t* lista = lista_crear();

    int numero1;
    int numero2;

    int* dato1 = &numero1;
    int* dato2 = &numero2;

    print_test("Agrego al principio de la lista el dato1", lista_insertar_primero(lista,dato1));
    print_test("Agrego al final de la lista el dato2", lista_insertar_ultimo(lista,dato2));

    print_test("Saco el primer elemento de la lista y verifico que sea el dato1", lista_borrar_primero(lista) == dato1);
    print_test("Saco el primer elemento de la lista y verifico que sea el dato2", lista_borrar_primero(lista) == dato2);

    print_test("Comprobando que la lista este vacia", lista_esta_vacia(lista));

    print_test("Verifico que NO se pueda borrar elementos en una lista recien creada", lista_borrar_primero(lista) == NULL);
    print_test("Verifico que NO se pueda ver el primer elemento en una lista recien creada", lista_ver_primero(lista) == NULL);
    print_test("Verifico que NO se pueda ver el ultimo elemento en una lista recien creada", lista_ver_ultimo(lista) == NULL);

    print_test("Agrego un dato al principio de la lista",lista_insertar_primero(lista,dato1));
    print_test("Verifico que el dato recien agregado es el primero",lista_ver_primero(lista) == dato1);
    print_test("Borro el primer elemento de la lista",lista_borrar_primero(lista) == dato1);

    print_test("Y por ultimo verifico que la lista este vacia nuevamente",lista_esta_vacia(lista));

    lista_destruir(lista,NULL);
}
// Condición de borde: las acciones de borrar el primero y ver primero en una lista recién creada son inválidas.
static void prueba_lista_vacia_borrar_y_ver_primero(void) {
    printf("INICIO PRUEBA: LAS ACCIONES DE BORRAR UN ELEMENTO , VER EL PRIMERO Y VER EL ULTIMO SON INVALIDAS EN UNA LISTA RECIEN CREADA\n");

    lista_t* lista = lista_crear();

    print_test("Chequeo que la lista haya sido creada", lista != NULL);
    print_test("Verifico que la lista esta vacia",lista_esta_vacia(lista));
    print_test("Verifico que NO se pueda borrar el primer elemento en una lista recien creada", lista_borrar_primero(lista) == NULL);
    print_test("Verifico que NO se pueda ver el primer elemento en una lista recien creada", lista_ver_primero(lista) == NULL);
    print_test("Verifico que NO se pueda ver el ultimo elemento en un lista recien creada", lista_ver_ultimo(lista) == NULL);

    lista_destruir(lista,NULL);
}

// Condición de borde: la acción de lista_esta_vacía en una lista recién creada es verdadero.
static void prueba_lista_vacia(void) {
    printf("INICIO PRUEBA: LA ACCION DE LISTA_ESTA_VACIA EN UN LISTA RECIEN CREADA ES VERDADERO\n");

    lista_t* lista = lista_crear();

    print_test("Creo la lista",lista != NULL);
    print_test("Verificando si la acción de lista_esta_vacía en una lista recién creada es verdadero.", lista_esta_vacia(lista));

    lista_destruir(lista,NULL);
}
// Condición de borde: las acciones de borrar_primero, ver_primero y ver_ultimo en una lista, a la que se le agrego y borro elementos hasta estar vacía son inválidas.
static void prueba_comportamiento_lista_vacia(void) {
    printf("INICIO PRUEBA: BORRAR_PRIMERO, VER_PRIMERO y VER_ULTIMO EN UNA LISTA, A LA QUE SE LE AGREGO Y BORRO ELEMENTOS HASTA ESTAR VACIA SON INVALIDAS\n");

    lista_t* lista = lista_crear();

    int numero1;

    int* dato1 = &numero1;

    print_test("Agrego el dato1 al principio de la lista", lista_insertar_primero(lista,dato1));
    print_test("Elimino el primer elemento de la lista y verifico que sea el dato1", lista_borrar_primero(lista) == dato1);
    print_test("Verifico que NO se pueda borrar el primer elemento en la lista", lista_borrar_primero(lista) == NULL);
    print_test("Verifico que NO se pueda ver el primer elemento en la lista", lista_ver_primero(lista) == NULL);
    print_test("verifico que NO se pueda ver el ultimo elemento en la lista", lista_ver_ultimo(lista) == NULL);

    lista_destruir(lista,NULL);
}

// Se destruye la lista utilizando NULL
static void prueba_destruir_lista_con_NULL(void) { 
    printf("INICIO PRUEBA: DESTRUIR LISTA NO VACIA USANDO NULL\n");

    lista_t* lista = lista_crear();

    int numero; 

    int* dato = &numero;

    print_test("Agrego un dato a la lista",lista_insertar_primero(lista,dato));
    print_test("Destruyo la lista la funcion lista_destruir con NULL",true);

    lista_destruir(lista,NULL);
}

static void prueba_destruir_lista_vacia_con_NULL(void) { 
    printf("INICIO PRUEBA: DESTRUIR LISTA VACIA USANDO NULL\n");

    lista_t* lista = lista_crear();
    print_test("Destruyo la lista la funcion lista_destruir con NULL",true);

    lista_destruir(lista,NULL);
}

static void prueba_destruir_lista_con_funcion(void) {
    printf("INICIO PRUEBA: DESTRUIR LISTA USANDO UNA FUNCION\n");
    lista_t* lista = lista_crear();
    pila_t* pila = pila_crear();
    int numero;
    int* dato = &numero;
    print_test("Agrego un elemento a la pila", pila_apilar(pila,dato));
    print_test("Verifico que se pueda insertar primero una pila a la lista", lista_insertar_primero(lista,pila));
    print_test("Destruyo la lista",true);
    lista_destruir(lista,pila_destruir);
}

static void prueba_destruir_lista_vacia_con_funcion(void) {
    printf("INICIO PRUEBA: DESTRUIR LISTA VACIA USANDO UNA FUNCION\n");
    lista_t* lista = lista_crear();
    print_test("Destruyo la lista",true);
    lista_destruir(lista,pila_destruir);
}

static void prueba_lista_NULL(void) {
    printf("INICIO PRUEBA: PRUEBAS CON NULL\n");
    lista_t* lista = lista_crear();
    print_test("Agrego al principio de la lista NULL", lista_insertar_primero(lista,NULL));
    print_test("Verifico que la lista deja de estar vacia", !lista_esta_vacia(lista));
    print_test("Borro lo que esta al principio y verifico que sea NULL", lista_borrar_primero(lista) == NULL);
    lista_destruir(lista,NULL);
}

// Pruebas de volumen 1
static void prueba_volumen_lista_alprincipio(void) {
    printf("INICIO PRUEBAS DE VOLUMEN AL PRINCIPIO\n");

    lista_t* lista = lista_crear();
    const int len_arr = 10000;
    int arr[10000];
    for (int i = 0; i < len_arr; i++) {
        arr[i] = i;
    }

    bool ok = true;
    for (int i = 0; i < len_arr; i++) {
        ok = ok && lista_insertar_primero(lista, &arr[i]);
    }
    print_test("Se pudieron guardar todos los elementos", ok);
    print_test("El largo de la lista es el correcto", lista_largo(lista) == len_arr);

    ok = true;
    for (int i = 0; i < len_arr; i++) {
        int *valor = lista_borrar_primero(lista);
        bool comprobar_valor = valor == &arr[len_arr - 1 - i];
        ok = ok && comprobar_valor;
    }
    print_test("Los valores enlistados coinciden con el arreglo original", ok);
    lista_destruir(lista,NULL);
}

// Pruebas de volumen 2
static void prueba_volumen_lista_alfinal(void) {
    printf("INICIO PRUEBAS DE VOLUMEN AL FINAL\n");

    lista_t* lista = lista_crear();
    const int len_arr = 10000;
    int arr[10000];
    for (int i = 0; i < len_arr; i++) {
        arr[i] = i;
    }

    bool ok = true;
    for (int i = 0; i < len_arr; i++) {
        ok = ok && lista_insertar_ultimo(lista, &arr[i]);
    }
    print_test("Se pudieron guardar todos los elementos", ok);
    print_test("El largo de la lista es el correcto", lista_largo(lista) == len_arr);

    ok = true;
    for (int i = 0; i < len_arr; i++) {
        int *valor = lista_borrar_primero(lista);
        bool comprobar_valor = valor == &arr[i];
        ok = ok && comprobar_valor;
    }
    print_test("Los valores enlistados coinciden con el arreglo original", ok);
    lista_destruir(lista,NULL);
}

/*
PRUEBAS ITERADOR EXTERNO
*/

static void prueba_iter_ext_recorrer(void) {
    printf("INICIO PRUEBAS RECORRER LISTA CON ITERADOR EXTERNO\n");

    lista_t* lista = lista_crear();
    const int len_arr = 4;
    int arr[4];
    for (int i = 0; i < len_arr; i++) {
        arr[i] = i;
    }

    bool ok = true;
    for (int i = 0; i < len_arr; i++) {
        ok = ok && lista_insertar_ultimo(lista, &arr[i]);
    }
    print_test("Se pudieron guardar todos los elementos", ok);
    print_test("El largo de la lista es el correcto", lista_largo(lista) == len_arr);

    ok = true;
    int j = 0;

    lista_iter_t* iter_lista = lista_iter_crear(lista);

    while (!lista_iter_al_final(iter_lista)) {
        void* dato = lista_iter_ver_actual(iter_lista);
        bool comprobar_valor = dato == &arr[j];
        ok = ok && comprobar_valor;
        j++;
        lista_iter_avanzar(iter_lista);
    }
    lista_iter_destruir(iter_lista);

    print_test("Los elementos de la lista fueron recorridos con exito", ok);
    
    lista_destruir(lista, NULL);
}

static void prueba_iter_ext_insertar_principio(void) {
    printf("INICIO PRUEBAS INSERTAR CON ITERADOR EXTERNO AL PRINCIPIO\n");

    lista_t* lista = lista_crear();
    const size_t largo_arr = 4;
    int arr[largo_arr];
    for (int i = 0; i < largo_arr; i++) {
        lista_insertar_ultimo(lista, &arr[i]);
    }

    int numero1;
    int* dato1 = &numero1;

    lista_iter_t* iter_lista = lista_iter_crear(lista);
    print_test("Se pudo insertar el elemento", lista_iter_insertar(iter_lista, dato1));
    print_test("El largo de la lista se modifico", lista_largo(lista) == largo_arr + 1);
    print_test("El elemento se inserto en el principio de la lista", lista_ver_primero(lista) == dato1);

    lista_iter_destruir(iter_lista);
    lista_destruir(lista, NULL);
}

static void prueba_iter_ext_insertar_lista_vacia(void) {
    printf("INICIO PRUEBAS INSERTAR CON ITERADOR EXTERNO LISTA VACIA\n");

    lista_t* lista = lista_crear();
    int numero1;
    int* dato1 = &numero1;
    lista_iter_t* iter_lista = lista_iter_crear(lista);
    
    print_test("Se pudo insertar en la lista", lista_iter_insertar(iter_lista, dato1));
    print_test("El largo de la lista es 1", lista_largo(lista) == 1);
    print_test("El primero de la lista es el elemento agregado", lista_ver_primero(lista) == dato1);
    print_test("El ultimo de la lista es el elemento agregado", lista_ver_ultimo(lista) == dato1);

    lista_iter_destruir(iter_lista);
    lista_destruir(lista, NULL);
}

static void prueba_iter_ext_insertar_final(void) {
    printf("INICIO PRUEBAS INSERTAR CON ITERADOR EXTERNO AL FINAL\n");

    lista_t* lista = lista_crear();
    const size_t largo_arr = 4;
    int arr[largo_arr];
    for (int i = 0; i < largo_arr; i++) {
        lista_insertar_ultimo(lista, &arr[i]);
    }
    int numero1;
    int* dato1 = &numero1;
    lista_iter_t* iter_lista = lista_iter_crear(lista);
    while (!lista_iter_al_final(iter_lista)) {
        lista_iter_avanzar(iter_lista);
    }

    print_test("Se pudo insertar en la lista", lista_iter_insertar(iter_lista, dato1));
    print_test("El largo de la lista cambio", lista_largo(lista) == largo_arr + 1);
    print_test("El elemento se inserto al final de la lista", lista_ver_ultimo(lista) == dato1);

    lista_iter_destruir(iter_lista);
    lista_destruir(lista, NULL);
}

static void prueba_iter_ext_insertar_medio(void) {
    printf("INICIO PRUEBAS INSERTAR CON ITERADOR EXTERNO AL MEDIO\n");

    lista_t* lista = lista_crear();
    const int largo_arr = 3;
    int arr[largo_arr];
    for (int i = 0; i < largo_arr; i++) {
        arr[i] = i;
    }
    for (int i = 0; i < largo_arr; i++) {
        lista_insertar_ultimo(lista, &arr[i]);
    }

    int numero1 = 100;
    int* dato1 = &numero1;
    lista_iter_t* iter_lista = lista_iter_crear(lista);

    print_test("El iterador avanzo hasta el segundo elemento", lista_iter_avanzar(iter_lista));
    print_test("El segundo elemento coincide con el arreglo", lista_iter_ver_actual(iter_lista) == &arr[1]);
    print_test("Se pudo insertar en la lista", lista_iter_insertar(iter_lista, dato1));
    print_test("El largo de la lista cambio", lista_largo(lista) == largo_arr + 1);

    lista_iter_destruir(iter_lista);

    bool ok = true;
    lista_iter_t* iter_lista2 = lista_iter_crear(lista);
    
    ok = ok && (lista_iter_ver_actual(iter_lista2) == &arr[0]);
    lista_iter_avanzar(iter_lista2);
    ok = ok && (lista_iter_ver_actual(iter_lista2) == dato1);
    lista_iter_avanzar(iter_lista2);
    ok = ok && (lista_iter_ver_actual(iter_lista2) == &arr[1]);
    lista_iter_avanzar(iter_lista2);
    ok = ok && (lista_iter_ver_actual(iter_lista2) == &arr[2]);
    lista_iter_avanzar(iter_lista2);

    print_test("Los elementos de la lista son los esperados", ok);
    print_test("El iterador está en el final", lista_iter_al_final(iter_lista2));

    lista_iter_destruir(iter_lista2);
    lista_destruir(lista, NULL);
}


static void prueba_iter_ext_borrar_primero(void) {
    printf("INICIO PRUEBAS BORRAR CON ITERADOR EXTERNO PRIMERO\n");

    lista_t* lista = lista_crear();
    const size_t largo_arr = 4;
    int arr[largo_arr];
    for (int i = 0; i < largo_arr; i++) {
        lista_insertar_ultimo(lista, &arr[i]);
    }
    lista_iter_t* iter_lista = lista_iter_crear(lista);

    print_test("Se elimino correctamente el primer elemento", lista_iter_borrar(iter_lista) == &arr[0]);
    print_test("La lista tiene un elemento menos", lista_largo(lista) == largo_arr - 1);
    print_test("Se modifico el primer elemento de la lista", lista_ver_primero(lista) == &arr[1]);

    lista_iter_destruir(iter_lista);
    lista_destruir(lista, NULL);
}

static void prueba_iter_ext_borrar_ultimo(void) {
    printf("INICIO PRUEBAS BORRAR CON ITERADOR EXTERNO ULTIMO\n");

    lista_t* lista = lista_crear();
    const size_t largo_arr = 4;
    int arr[largo_arr];
    for (int i = 0; i < largo_arr; i++) {
        arr[i] = i;
    }
    for (int i = 0; i < largo_arr; i++) {
        lista_insertar_ultimo(lista, &arr[i]);
    }
    lista_iter_t* iter_lista = lista_iter_crear(lista);
    for (int j = 0; j < largo_arr - 1; j++) {
        lista_iter_avanzar(iter_lista);
    }

    print_test("Se elimino correctamente el ultimo elemento", lista_iter_borrar(iter_lista) == &arr[largo_arr - 1]);
    print_test("La lista tiene un elemento menos", lista_largo(lista) == largo_arr - 1);
    print_test("Se modifico el ultimo elemento de la lista", lista_ver_ultimo(lista) == &arr[largo_arr - 2]);

    lista_iter_destruir(iter_lista);
    lista_destruir(lista, NULL);
}

static void prueba_iter_ext_borrar_unico_elemento(void) {
    printf("INICIO PRUEBAS BORRAR CON ITERADOR EXTERNO UNICO ELEMENTO\n");

    lista_t* lista = lista_crear();
    int numero1;
    int* dato1 = &numero1;
    lista_insertar_ultimo(lista, dato1);
    lista_iter_t* iter_lista = lista_iter_crear(lista);

    print_test("Se elimino correctamente el unico elemento", lista_iter_borrar(iter_lista) == dato1);
    print_test("La lista esta vacia", lista_esta_vacia(lista));

    lista_iter_destruir(iter_lista);
    lista_destruir(lista, NULL);
}

static void prueba_iter_ext_borrar_medio(void) {
    printf("INICIO PRUEBAS BORRAR CON ITERADOR EXTERNO MEDIO\n");

    lista_t* lista = lista_crear();
    const size_t largo_arr = 4;
    int arr[largo_arr];
    for (int i = 0; i < largo_arr; i++) {
        lista_insertar_ultimo(lista, &arr[i]);
    }
    lista_iter_t* iter_lista = lista_iter_crear(lista);

    print_test("El iterador avanzo hasta el segundo elemento", lista_iter_avanzar(iter_lista));
    print_test("El segundo elemento coincide con el arreglo", lista_iter_ver_actual(iter_lista) == &arr[1]);
    print_test("Borro el segundo elemento", lista_iter_borrar(iter_lista) == &arr[1]);
    print_test("El largo de la lista cambio", lista_largo(lista) == largo_arr - 1);

    lista_iter_destruir(iter_lista);
    lista_iter_t* iter_lista2 = lista_iter_crear(lista);
    bool ok = true;

    ok = ok && (lista_iter_ver_actual(iter_lista2) == &arr[0]);
    lista_iter_avanzar(iter_lista2);
    ok = ok && (lista_iter_ver_actual(iter_lista2) == &arr[2]);
    lista_iter_avanzar(iter_lista2);
    ok = ok && (lista_iter_ver_actual(iter_lista2) == &arr[3]);
    lista_iter_avanzar(iter_lista2);

    print_test("Los elementos de la lista son los esperados", ok);
    print_test("El iterador está en el final", lista_iter_al_final(iter_lista2));

    lista_iter_destruir(iter_lista2);
    lista_destruir(lista, NULL);
}

/*
PRUEBAS ITERADOR INTERNO
*/

static void prueba_iterador_interno_sin_corte(void) {
    printf("INICIO PRUEBAS DEL ITERADOR INTERNO\n");
    int lista[5] = {1,2,3,4,5};
    int lista2[7] = {1,-1,-1,-1,1,1};
    int lista3[3] = {0,0,0};
    int acum = 0;
    int acum2 = 0;
    int acum3 = 0;
    bool ok = true;
    lista_t* lista_prueba = agregar_a_la_lista(lista,5);
    lista_t* lista_prueba2 = agregar_a_la_lista(lista2,6);
    lista_t* lista_prueba3 = agregar_a_la_lista(lista3,3);
    lista_iterar(lista_prueba, sumar_lista, &acum);
    lista_iterar(lista_prueba2, sumar_lista, &acum2);
    lista_iterar(lista_prueba3, sumar_lista, &acum3);
    ok &= (acum == 15);
    ok &= (acum2 == 0);
    ok &= (acum3 == 0);
    print_test("Comprobando que funcione bien el iterador interno sin ningun corte", ok);
    lista_destruir(lista_prueba, NULL);
    lista_destruir(lista_prueba2, NULL);
    lista_destruir(lista_prueba3, NULL);
}

static void prueba_iterador_interno_con_corte(void) {
    int lista[5] = {1,2,3,4,5};
    int lista2[7] = {1,-1,-1,-1,1,1};
    int lista3[3] = {0,0,0};
    int acum = 0;
    int acum2 = 0;
    int acum3 = 0;
    bool ok = true;
    lista_t* lista_prueba = agregar_a_la_lista(lista,5);
    lista_t* lista_prueba2 = agregar_a_la_lista(lista2,6);
    lista_t* lista_prueba3 = agregar_a_la_lista(lista3,3);
    lista_iterar(lista_prueba, sumar_lista_con_corte, &acum);
    lista_iterar(lista_prueba2, sumar_lista_con_corte, &acum2);
    lista_iterar(lista_prueba3, sumar_lista_con_corte, &acum3);
    ok &= (acum == 6);
    ok &= (acum2 == 0);
    ok &= (acum3 == 0);
    print_test("Comprobando que funcione bien el iterador interno con corte", ok);
    lista_destruir(lista_prueba, NULL);
    lista_destruir(lista_prueba2, NULL);
    lista_destruir(lista_prueba3, NULL);
}

static void prueba_iterador_interno_sin_usar_extra(void) {
    int lista[5] = {1,2,3,4,5};
    int lista2[6] = {1,-1,-1,-1,1,1};
    int lista3[3] = {0,0,0};
    int acum = 0;
    int acum2 = 0;
    int acum3 = 0;
    bool ok = true;
    lista_t* lista_prueba = agregar_a_la_lista(lista,5);
    lista_t* lista_prueba2 = agregar_a_la_lista(lista2,6);
    lista_t* lista_prueba3 = agregar_a_la_lista(lista3,3);
    lista_iterar(lista_prueba, lista_sumar_uno_a_cada_elemento, NULL);
    lista_iterar(lista_prueba2, lista_sumar_uno_a_cada_elemento, NULL);
    lista_iterar(lista_prueba3, lista_sumar_uno_a_cada_elemento, NULL);
    lista_iterar(lista_prueba, sumar_lista, &acum);
    lista_iterar(lista_prueba2, sumar_lista, &acum2);
    lista_iterar(lista_prueba3, sumar_lista, &acum3);
    ok &= (acum == 20);
    ok &= (acum2 == 6);
    ok &= (acum3 == 3);
    print_test("Comprobando que funcione bien el iterador interno sin usar extra", ok);
    lista_destruir(lista_prueba, NULL);
    lista_destruir(lista_prueba2, NULL);
    lista_destruir(lista_prueba3, NULL);
}

void pruebas_lista_estudiante() {
    prueba_lista_crear();
    prueba_comportamiento_lista();
    prueba_lista_vacia_agregar_y_borrar_elementos();
    prueba_lista_vacia_borrar_y_ver_primero();
    prueba_lista_vacia();
    prueba_comportamiento_lista_vacia();
    prueba_destruir_lista_con_NULL();
    prueba_destruir_lista_vacia_con_NULL();
    prueba_destruir_lista_con_funcion();
    prueba_destruir_lista_vacia_con_funcion();
    prueba_lista_NULL();
    prueba_volumen_lista_alprincipio();
    prueba_volumen_lista_alfinal();

    prueba_iter_ext_recorrer();
    prueba_iter_ext_insertar_principio();
    prueba_iter_ext_insertar_lista_vacia();
    prueba_iter_ext_insertar_final();
    prueba_iter_ext_insertar_medio();
    prueba_iter_ext_borrar_primero();
    prueba_iter_ext_borrar_ultimo();
    prueba_iter_ext_borrar_unico_elemento();
    prueba_iter_ext_borrar_medio();

    prueba_iterador_interno_sin_corte();
    prueba_iterador_interno_con_corte();
    prueba_iterador_interno_sin_usar_extra();
}


#ifndef CORRECTOR

int main(void) {
    pruebas_lista_estudiante();
    return 0;
}

#endif