#include "objFile.h"
#include<string>
#include "iostream"

using namespace std;

FILE *open_file()
{
    char nome[100] = "/home/isabela/Documentos/UFF/CG2/obj/gatinho2.obj";

    if (strstr(nome, ".obj") == NULL)
        strcat(nome, ".obj");

    FILE *arq = fopen(nome, "r");

    if (arq == NULL)
    {
        printf("Nao foi possivel abrir o arquivo solicitado!\n");
        return NULL;
    }

    printf("Arquivo aberto com sucesso!\n");
    return arq;
}

void read_file(FILE *arq, int *nvert, int *narest)
{
    int vertice = 0, face = 0;

    printf("relou 1\n");

    char linha1[100];

    try
    {
//        fscanf(arq, "%[^\n]", linha1);
        fscanf(arq, "%[^=] = %d", linha1, &vertice);
        fscanf(arq, "%[^=] = %d", linha1, &face);

//        fscanf(arq, "#v= %d\n", &vertice);
//        fscanf(arq, "#f= %d\n", &face);

        printf("vertice = %d\nface = %d\n", vertice, face);
    } catch (exception err)
    {
        cout << err.what();
    }

    *nvert = vertice;
    *narest = face;
}

vec4 *get_vertices(FILE *arq, int nvert)
{
    vec4 *vertices = (vec4*) malloc(nvert*sizeof(vec4));

    char c;
    for (int i = 0; i < nvert; i++)
    {
        fscanf(arq, "%c %f %f %f\n",  &c, &vertices[i].x, &vertices[i].y, &vertices[i].z);
        vertices[i].w = 1;
//        printf("vertices[%d] = %f %f %f %f\n", i, vertices[i].x, vertices[i].y, vertices[i].z, vertices[i].w);
    }

    return vertices;
}

vec3 *get_arestas(FILE *arq, int narest)
{
    vec3 *arestas = (vec3*) malloc(narest*sizeof(vec3));

    char c;
    for (int i = 0; i < narest; i++)
    {
        fscanf(arq, "%c %f %f %f\n", &c, &arestas[i].x, &arestas[i].y, &arestas[i].z);
//        printf("arestas[%d] = %f %f %f\n", i, arestas[i].x, arestas[i].y, arestas[i].z);
    }

    return arestas;
}

void close_file(FILE *arq)
{
    fclose(arq);
}

