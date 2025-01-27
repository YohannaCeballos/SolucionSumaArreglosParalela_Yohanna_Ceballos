#include <iostream>
#include <omp.h>

#define N 1500          // Cantidad de elementos a manejar en los arreglos
#define chunk 300       // Tama�o que tendr�n los pedazos de los arreglos para que cada hilo creado se encargue de esta cantidad de elementos
#define mostrar 10      // Cantidad de datos a imprimir

// Funci�n que imprime los primeros "mostrar" elementos de un arreglo
void imprimeArreglo(float *d);

int main()
{
    std::cout << "Sumando Arreglos en Paralelo!\n";

    // Declaraci�n de tres arreglos con tama�o N
    float a[N], b[N], c[N];
    int i;

    // Inicializaci�n de los arreglos 'a' y 'b' con valores
    for (i = 0; i < N; i++)
    {
        a[i] = i * 10;
        b[i] = (i + 3) * 5;
    }

    // Almacena en 'pedazos' el tama�o de bloque para la directiva schedule
    int pedazos = chunk;

    // Se utiliza la directiva de OpenMP para paralelizar el bucle for:
    // - parallel for: indica que el for se ejecutar� en paralelo
    // - shared(a, b, c, pedazos): estas variables son compartidas entre hilos
    // - private(i): la variable 'i' ser� privada para cada hilo
    // - schedule(static, pedazos): la divisi�n del bucle se reparte en bloques de tama�o 'pedazos'
    #pragma omp parallel for \
    shared(a, b, c, pedazos) private(i) \
    schedule(static, pedazos)

    for (i = 0; i < N; i++)
        c[i] = a[i] + b[i];  // Cada hilo suma el elemento correspondiente de 'a' y 'b', almacen�ndolo en 'c'


    // Se muestra en pantalla los primeros 'mostrar' valores de cada arreglo
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo a: " << std::endl;
    imprimeArreglo(a);
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo b: " << std::endl;
    imprimeArreglo(b);
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo c: " << std::endl;
    imprimeArreglo(c);
}

// Definici�n de la funci�n que imprime los primeros 'mostrar' elementos de un arreglo
void imprimeArreglo(float *d)
{
    for (int x = 0; x < mostrar; x++) 
        std::cout << d[x] << " - ";
    std::cout << std::endl;
}

