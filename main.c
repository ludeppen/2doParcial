#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
typedef struct
{
char nombreYApellido[30];
int edad;
char departamento[30]; // Finanzas, RRHH, Ventas, etc
float sueldo;
} stEmpleado;
///---------------------------prototipado---------------------------///
int cargarUnEmpleado(stEmpleado *a);
void cargarArchivoEmpleados(char archivo[]);
int validarEdad(int edad);
void mostrarUnEmpleado(stEmpleado a);
void mostrarArchivoEmpleados(char archivo[]);
int verPorcentaje(char archivo[],char dep[]);
int registros(char archivo[]);
int pasarArreglo(char archivo[],stEmpleado array[], int edad);
stEmpleado buscarMenor(stEmpleado empleados[], int dim);
void mostrarArreglo(stEmpleado array[], int dim);
///---------------------------prototipado---------------------------///

int main()
{
    char archivo[] = "datosEmpleado.bin";
    int totalRegistros = registros(archivo);
    stEmpleado* array = (stEmpleado*)malloc(sizeof(stEmpleado) * totalRegistros);
    char control = 's';
    while(control == 's')
    {
        int ejercicio;
        system("cls");
        printf("1. Cargar archivo.\n");
        printf("2. Mostrar archivo.\n");
        printf("3. Ver porcentaje por departamento.\n");
        printf("4. ver empleados por edad.\n");
        printf("5. Ver empleado con menor sueldo.\n");
        fflush(stdin);
        scanf("%d",&ejercicio);
        switch(ejercicio)
        {
        case 1:
             system("cls");
             ///punto 1
             cargarArchivoEmpleados(archivo);
             break;
        case 2:
             system("cls");
             ///punto 2
             mostrarArchivoEmpleados(archivo);
             break;
        case 3:
             system("cls");
             ///punto 3
             char dep[30];
             printf("Ingrese el departamento (finanzas - RRHH - ventas):\n");
             fflush(stdin);
             gets(dep);
             float res = verPorcentaje(archivo,dep);
             printf("El pocentaje del departamento %s es : %.1f",dep,res);
             break;
        case 4:
             system("cls");
             ///Punto 4 y 5
             int edad;
             printf("Ingrese la edad para ver empleados mayores:\t");
             scanf("%d",&edad);
             totalRegistros = pasarArreglo(archivo,array,edad);
             printf("Los empleados mayores a %d son:\n",edad);
             mostrarArreglo(array,totalRegistros);
             break;
        case 5:
             system("cls");
             ///punto 6
             ///Se debe primero cargar el punto 4 para que funcione
             stEmpleado menor = buscarMenor(array,totalRegistros);

             printf("El empleado con menor sueldo es:\n");
             mostrarUnEmpleado(menor);
             break;
        default:
            printf("Error.\n");
            break;
        }
        printf("\nDesea ver otro ejercicio? s / n:\t");
        fflush(stdin);
        scanf("%c",&control);
    }
    return 0;
}

///---------------------------funciones---------------------------///
///Cargar archivos

int cargarUnEmpleado(stEmpleado *a)
{
    printf("Ingrese la edad del empleado:\t");
    scanf("%d",&a->edad);
    int res = validarEdad(a->edad);
    if(res == 1)
    {
        printf("Ingrese el nombre y epellido:\n");
        fflush(stdin);
        gets(a->nombreYApellido);

        printf("Ingrese el departament (finanzas - RRHH - ventas):\t");
        fflush(stdin);
        gets(a->departamento);

        printf("Ingrese el sueldo:\t");
        scanf("%f",&a->sueldo);
        return 1;
    }
    else
    {
        printf("Error, el empleado no es mayor de edad.\n");
    }
return 0;
}
void cargarArchivoEmpleados(char archivo[])
{
    stEmpleado a;
    FILE*buffer = fopen(archivo,"ab");
    if(buffer)
    {
      char control = 's';
      while(control == 's')
      {
        int res = cargarUnEmpleado(&a);
        if(res != 0)
        {
            fwrite(&a,sizeof(stEmpleado),1,buffer);
        }
        printf("\nDesea cargar otro empleado? s / n:\t");
        fflush(stdin);
        scanf("%c",&control);
      }
        fclose(buffer);
    }
    else
    {
        perror("Error.\n");
    }
}
///VALIDAR EDAD
int validarEdad(int edad)
{
    if(edad >=18)
    {
        return 1;
    }
return 0;
}
///MOSTRAR ARCHIVOS
void mostrarUnEmpleado(stEmpleado a)
{
    printf("Departmento: %s\n",a.departamento);
    printf("Nombre y apellido: %s\n",a.nombreYApellido);
    printf("Edad: %d\n",a.edad);
    printf("Sueldo: %.1f\n",a.sueldo);
    puts("---------------------------");
}

void mostrarArchivoEmpleados(char archivo[])
{
    stEmpleado a;
    FILE*buffer = fopen(archivo,"rb");
    if(buffer)
    {
      while(fread(&a,sizeof(stEmpleado),1,buffer) > 0)
      {
          mostrarUnEmpleado(a);
      }
        fclose(buffer);
    }
    else
    {
        perror("Error.\n");
    }
}
///SACAR PORCENTAJE
int verPorcentaje(char archivo[],char dep[])
{
    stEmpleado a;
    int total = 0;
    FILE*buffer = fopen(archivo,"rb");
    if(buffer)
    {
        int cant = 0;
        int totalRegistros = registros(archivo);
        while(fread(&a,sizeof(stEmpleado),1,buffer) > 0)
        {
          if(strcmp(a.departamento,dep) == 0)
          {
            cant ++;
          }
        }
        if(totalRegistros > 0)
       {
             total = (cant *100 ) / totalRegistros;
       }
       else
       {
           printf("Error\n");
       }
        fclose(buffer);
    }
    else
    {
        perror("Error.\n");
    }
return total;
}

int registros(char archivo[])
{
    int totalRegistros = 0;
    FILE*buffer = fopen(archivo,"rb");
    if(buffer)
    {
       fseek(buffer,0,SEEK_END);
       int total = ftell(buffer);
       totalRegistros = total /sizeof(stEmpleado);
        fclose(buffer);
    }
    else
    {
        perror("Error.\n");
    }
return totalRegistros;
}
///PASAR ARREGLO
int pasarArreglo(char archivo[],stEmpleado array[], int edad)
{
    stEmpleado a;
    int i = 0;
    FILE*buffer = fopen(archivo,"rb");
    if(buffer)
    {
      while(fread(&a,sizeof(stEmpleado),1,buffer) > 0)
      {
          if(a.edad > edad)
          {
              array[i] = a;
              i++;
          }
      }
        fclose(buffer);
    }
    else
    {
        perror("Error.\n");
    }
return i;
}

void mostrarArreglo(stEmpleado array[], int dim)
{
    for(int i = 0; i < dim; i++)
    {
       printf("Departmento: %s\n",array[i].departamento);
       printf("Nombre y apellido: %s\n",array[i].nombreYApellido);
       printf("Edad: %d\n",array[i].edad);
       printf("Sueldo: %.1f\n",array[i].sueldo);
       puts("---------------------------");
    }
}

///Buscarmenor
stEmpleado buscarMenor(stEmpleado empleados[], int dim)
{
    stEmpleado aux = empleados[0];
    for(int i = 1; i < dim; i++)
    {
      if(empleados[i].sueldo < aux.sueldo)
      {
        aux = empleados[i];
      }
    }
return aux;
}

