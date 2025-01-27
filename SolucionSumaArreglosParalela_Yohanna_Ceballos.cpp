#include <iostream>
#include <omp.h>

#define N 1500          // Cantidad de elementos a manejar en los arreglos
#define chunk 300       // Tamaño que tendrán los pedazos de los arreglos para que cada hilo creado se encargue de esta cantidad de elementos
#define mostrar 10      // Cantidad de datos a imprimir

// Función que imprime los primeros "mostrar" elementos de un arreglo
void imprimeArreglo(float *d);

int main()
{
    std::cout << "Sumando Arreglos en Paralelo!\n";

    // Declaración de tres arreglos con tamaño N
    float a[N], b[N], c[N];
    int i;

    // Inicialización de los arreglos 'a' y 'b' con valores
    for (i = 0; i < N; i++)
    {
        a[i] = i * 10;
        b[i] = (i + 3) * 5;
    }

    // Almacena en 'pedazos' el tamaño de bloque para la directiva schedule
    int pedazos = chunk;

    // Se utiliza la directiva de OpenMP para paralelizar el bucle for:
    // - parallel for: indica que el for se ejecutará en paralelo
    // - shared(a, b, c, pedazos): estas variables son compartidas entre hilos
    // - private(i): la variable 'i' será privada para cada hilo
    // - schedule(static, pedazos): la división del bucle se reparte en bloques de tamaño 'pedazos'
    #pragma omp parallel for \
    shared(a, b, c, pedazos) private(i) \
    schedule(static, pedazos)

    for (i = 0; i < N; i++)
        c[i] = a[i] + b[i];  // Cada hilo suma el elemento correspondiente de 'a' y 'b', almacenándolo en 'c'


    // Se muestra en pantalla los primeros 'mostrar' valores de cada arreglo
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo a: " << std::endl;
    imprimeArreglo(a);
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo b: " << std::endl;
    imprimeArreglo(b);
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo c: " << std::endl;
    imprimeArreglo(c);
}

// Definición de la función que imprime los primeros 'mostrar' elementos de un arreglo
void imprimeArreglo(float *d)
{
    for (int x = 0; x < mostrar; x++) 
        std::cout << d[x] << " - ";
    std::cout << std::endl;
}

