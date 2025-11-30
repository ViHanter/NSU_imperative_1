#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct Node
{
    struct Node *prev, *next;
    double value;
} Node;

// создаёт пустой список
double *initList()
{
    Node *head = (Node *)malloc(sizeof(Node));
    head->prev = head;
    head->next = head;
    return &(head->value);
}

// полностью освобождает память списка
void freeList(double *head)
{
    Node *node = (Node *)((char *)head - offsetof(Node, value));
    Node *current = node->next;
    
    while (current != node)
    {
        Node *next = current->next;
        free(current);
        current = next;
    }
    
    free(node);
}

// определяет следующий элемент после заданного
double *getNext(double *curr)
{
    Node *node = (Node *)((char *)curr - offsetof(Node, value));
    Node *next_node = node->next;
    
    // Если следующий узел - вспомогательный, возвращаем NULL или value вспомогательного?
    // Согласно условию: для вспом. узла возвращает первый элемент
    if (next_node->next == next_node->prev) // Это вспомогательный узел?
        return &(next_node->next->value); // Возвращаем первый элемент
    
    return &(next_node->value);
}

// определяет предыдущий элемент перед заданным
double *getPrev(double *curr)
{
    Node *node = (Node *)((char *)curr - offsetof(Node, value));
    Node *prev_node = node->prev;
    
    // Если предыдущий узел - вспомогательный, возвращаем последний элемент
    if (prev_node->next == prev_node->prev) // Это вспомогательный узел?
        return &(prev_node->prev->value); // Возвращаем последний элемент
    
    return &(prev_node->value);
}

// создаёт и вставляет узел со значением newval сразу после узла where
double *addAfter(double *where, double newval)
{
    Node *where_node = (Node *)((char *)where - offsetof(Node, value));
    Node *new_node = (Node *)malloc(sizeof(Node));
    
    new_node->value = newval;
    new_node->prev = where_node;
    new_node->next = where_node->next;
    
    where_node->next->prev = new_node;
    where_node->next = new_node;
    
    return &(new_node->value);
}

// создаёт и вставляет узел со значением newval сразу перед узлом where
double *addBefore(double *where, double newval)
{
    Node *where_node = (Node *)((char *)where - offsetof(Node, value));
    Node *new_node = (Node *)malloc(sizeof(Node));
    
    new_node->value = newval;
    new_node->next = where_node;
    new_node->prev = where_node->prev;
    
    where_node->prev->next = new_node;
    where_node->prev = new_node;
    
    return &(new_node->value);
}

// удаляет и освобождает заданный узел
void erase(double *what)
{
    Node *what_node = (Node *)((char *)what - offsetof(Node, value));
    
    // Нельзя удалять вспомогательный узел
    if (what_node->next == what_node->prev && what_node->next == what_node)
        return;
    
    what_node->prev->next = what_node->next;
    what_node->next->prev = what_node->prev;
    
    free(what_node);
}

// Вспомогательная функция для получения указателя на голову списка
Node* getHeadNode(double *head_value)
{
    return (Node *)((char *)head_value - offsetof(Node, value));
}

// Вспомогательная функция для получения первого элемента списка
double* getFirst(double *head_value)
{
    Node *head = getHeadNode(head_value);
    if (head->next == head) // список пуст
        return NULL;
    return &(head->next->value);
}

// Вспомогательная функция для получения последнего элемента списка
double* getLast(double *head_value)
{
    Node *head = getHeadNode(head_value);
    if (head->prev == head) // список пуст
        return NULL;
    return &(head->prev->value);
}

int main()
{
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");
    
    int T;
    fscanf(input, "%d", &T);
    
    for (int t = 0; t < T; t++)
    {
        int Q;
        fscanf(input, "%d", &Q);
        
        double *head = initList();
        double **nodes = (double **)malloc(sizeof(double *) * (Q + 5));
        int node_count = 0;
        
        // Вспомогательный узел имеет индекс -1
        nodes[0] = head; // индекс 0 соответствует вспомогательному узлу
        
        for (int q = 0; q < Q; q++)
        {
            int op_type, index;
            fscanf(input, "%d %d", &op_type, &index);
            
            if (op_type == 1 || op_type == -1) // операция вставки
            {
                double value;
                fscanf(input, "%lf", &value);
                
                if (op_type == 1) // добавление спереди (после вспомогательного)
                {
                    if (index == -1) // спереди от всего списка
                    {
                        nodes[++node_count] = addAfter(head, value);
                    }
                    else // спереди от указанного узла
                    {
                        nodes[++node_count] = addBefore(nodes[index + 1], value);
                    }
                }
                else // op_type == -1, добавление сзади
                {
                    if (index == -1) // сзади от всего списка
                    {
                        nodes[++node_count] = addBefore(head, value);
                    }
                    else // сзади от указанного узла
                    {
                        nodes[++node_count] = addAfter(nodes[index + 1], value);
                    }
                }
            }
            else // op_type == 0, операция удаления
            {
                double *node_to_remove = nodes[index + 1];
                fprintf(output, "%0.3lf\n", *node_to_remove);
                erase(node_to_remove);
                nodes[index + 1] = NULL; // пометить как удалённый
            }
        }
        
        fprintf(output, "===\n");
        
        // Вывод оставшихся узлов в порядке следования
        Node *head_node = getHeadNode(head);
        Node *current = head_node->next;
        
        while (current != head_node)
        {
            fprintf(output, "%0.3lf\n", current->value);
            current = current->next;
        }
        
        fprintf(output, "===\n");
        
        freeList(head);
        free(nodes);
    }
    
    fclose(input);
    fclose(output);
    
    return 0;
}