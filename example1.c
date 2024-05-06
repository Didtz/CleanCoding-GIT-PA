#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node* next;
} Node;

typedef struct Graph
{
    int nNumVertices;
    int* visited;
    struct Node** adjacencyLists;
} Graph;

typedef struct Stack
{
    int nTopIndex;
    int capacity;
    int* elements;
} Stack;

Node* create_node(int value)
{
    Node* pNewNode = malloc(sizeof(Node));
    pNewNode->data = value;
    pNewNode->next = NULL;
    return pNewNode;
}

void add_edge(Graph* graph, int src, int dest)
{
    Node* pNewNode = create_node(dest);
    pNewNode->next = graph->adjacencyLists[src];
    graph->adjacencyLists[src] = pNewNode;
    pNewNode = create_node(src);
    pNewNode->next = graph->adjacencyLists[dest];
    graph->adjacencyLists[dest] = pNewNode;
}

Graph* create_graph(int nNumVertices)
{
    Graph* graph = malloc(sizeof(Graph));
    graph->nNumVertices = nNumVertices;
    graph->adjacencyLists = malloc(sizeof(Node*) * nNumVertices);
    graph->visited = malloc(sizeof(int) * nNumVertices);

    for (int i = 0; i < nNumVertices; i++)
    {
        graph->adjacencyLists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

Stack* create_stack(int capacity)
{
    Stack* stack = malloc(sizeof(Stack));
    stack->elements = malloc(capacity * sizeof(int));
    stack->nTopIndex = -1;
    stack->capacity = capacity;

    return stack;
}

void push(int item, Stack* stack)
{
    stack->nTopIndex++;
    stack->elements[stack->nTopIndex] = item;
}

void DFS(Graph* graph, Stack* stack, int nVertexNumber)
{
    Node* pAdjList = graph->adjacencyLists[nVertexNumber];
    Node* pCurrNode = pAdjList;
    graph->visited[nVertexNumber] = 1;
    printf("%d ", nVertexNumber);
    //push(nVertexNumber, stack);
    while (pCurrNode != NULL)
    {
        int nVertexIndex = pCurrNode->data;

        if (graph->visited[nVertexIndex] == 0)
            DFS(graph, stack, nVertexIndex);
        pCurrNode = pCurrNode->next;
    }
}

void insert_edges(Graph* graph, int nNumEdges, int nNumVertices)
{
    int src, dest;
    printf("Enter %d edges (from 0 to %d):\n", nNumEdges, nNumVertices);
    for (int i = 0; i < nNumEdges; i++)
    {
        scanf("%d%d", &src, &dest);
        add_edge(graph, src, dest);
    }
}

void reset_visited(Graph* graph, int nNumVertices)
{
    for (int i = 0; i < nNumVertices; i++)
    {
        graph->visited[i] = 0;
    }
}

void determine_paths(Graph* graph, int nNumVertices, Stack* stack1, Stack* stack2)
{
    int* possible_paths = calloc(5, sizeof(int));

    for (int i = 0; i < nNumVertices; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            DFS(graph, stack1, i);
            reset_visited(graph, nNumVertices);
            DFS(graph, stack2, j);

            for (int j = 0; j < nNumVertices; j++)
                for (int i = 0; i < nNumVertices; i++)
                    *possible_paths = 1;
        }
    }
}

int main()
{
    int nNumVertices;
    int nNumEdges;

    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &nNumVertices);

    printf("Enter the number of edges in the graph: ");
    scanf("%d", &nNumEdges);

    Graph* graph = create_graph(nNumVertices);

    Stack* stack1 = create_stack(2 * nNumVertices);
    Stack* stack2 = create_stack(2 * nNumVertices);

    insert_edges(graph, nNumEdges, nNumVertices);
    DFS(graph, stack1, 0);
    //determine_paths(graph, nNumVertices, stack1, stack2);

    // Free allocated memory
    // (Not shown in the code for brevity)

    return 0;
}
