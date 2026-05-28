#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10
#define DELETED_NODE -1  // маркер удалённого узла

// ==================== ВАРИАНТ 1: ЦЕПОЧКА ====================
typedef struct ChainNode {
    int key;
    int value;
    struct ChainNode* next;
} ChainNode;

typedef struct {
    ChainNode** table;
    int size;
} ChainHashMap;

// Хеш-функция
int hash(int key) {
    return key % TABLE_SIZE;
}

// Инициализация
void initChainHashMap(ChainHashMap* map) {
    map->size = TABLE_SIZE;
    map->table = (ChainNode**)calloc(TABLE_SIZE, sizeof(ChainNode*));
}

// Вставка (цепочка)
void chainPut(ChainHashMap* map, int key, int value) {
    int index = hash(key);
    
    // Проверяем, есть ли уже ключ
    ChainNode* current = map->table[index];
    while (current != NULL) {
        if (current->key == key) {
            current->value = value;
            return;
        }
        current = current->next;
    }
    
    // Создаём новый узел и добавляем в начало цепочки
    ChainNode* new_node = (ChainNode*)malloc(sizeof(ChainNode));
    new_node->key = key;
    new_node->value = value;
    new_node->next = map->table[index];
    map->table[index] = new_node;
}

// Поиск (цепочка)
int chainGet(ChainHashMap* map, int key) {
    int index = hash(key);
    ChainNode* current = map->table[index];
    
    while (current != NULL) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    return -1;  // не найдено
}

// Удаление (цепочка)
void chainRemove(ChainHashMap* map, int key) {
    int index = hash(key);
    ChainNode* current = map->table[index];
    ChainNode* prev = NULL;
    
    while (current != NULL) {
        if (current->key == key) {
            if (prev == NULL) {
                map->table[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}
