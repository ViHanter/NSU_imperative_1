#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10
#define DELETED_NODE -1  // маркер удалённого узла

typedef struct {
    int key;
    int value;
    int isOccupied;  // 0 - свободно, 1 - занято, -1 - удалено
} DirectNode;

typedef struct {
    DirectNode* table;
    int size;
} DirectHashMap;

int hash(int key) {
    return key % TABLE_SIZE;
}

// Инициализация
void initDirectHashMap(DirectHashMap* map) {
    map->size = TABLE_SIZE;
    map->table = (DirectNode*)malloc(TABLE_SIZE * sizeof(DirectNode));
    for (int i = 0; i < TABLE_SIZE; i++) {
        map->table[i].isOccupied = 0;
    }
}

// Линейное пробирование
int directHash(int key, int attempt) {
    return (hash(key) + attempt) % TABLE_SIZE;
}

// Вставка (прямая адресация)
int directPut(DirectHashMap* map, int key, int value) {
    for (int attempt = 0; attempt < TABLE_SIZE; attempt++) {
        int index = directHash(key, attempt);
        
        if (map->table[index].isOccupied == 0 || 
            map->table[index].isOccupied == DELETED_NODE ||
            map->table[index].key == key) {
            
            map->table[index].key = key;
            map->table[index].value = value;
            map->table[index].isOccupied = 1;
            return index;
        }
    }
    return -1;  // таблица переполнена
}

// Поиск (прямая адресация)
int directGet(DirectHashMap* map, int key) {
    for (int attempt = 0; attempt < TABLE_SIZE; attempt++) {
        int index = directHash(key, attempt);
        
        if (map->table[index].isOccupied == 0) {
            break;  // дальше не ищем
        }
        
        if (map->table[index].isOccupied == 1 && map->table[index].key == key) {
            return map->table[index].value;
        }
    }
    return -1;  // не найдено
}

// Удаление (прямая адресация)
void directRemove(DirectHashMap* map, int key) {
    for (int attempt = 0; attempt < TABLE_SIZE; attempt++) {
        int index = directHash(key, attempt);
        
        if (map->table[index].isOccupied == 0) {
            return;  // не нашли
        }
        
        if (map->table[index].isOccupied == 1 && map->table[index].key == key) {
            map->table[index].isOccupied = DELETED_NODE;
            return;
        }
    }
}