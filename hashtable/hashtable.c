#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define M 8

struct Hashtable
{
    struct KeyValuePair** data;
    int size;
};

struct KeyValuePair
{
    char* key;
    int value;
    struct KeyValuePair* next;
};

struct Hashtable* create()
{
    struct Hashtable* hashTable = malloc(sizeof(struct Hashtable));

    hashTable->data = malloc(sizeof(struct KeyValuePair*) * M);

    return hashTable;
}

int hash(char* key)
{
    int keyLength = strlen(key);

    int hash  = 0;

    for (int i = 0; i < keyLength; i++)
    {
        hash += (int)key[i];
    }    

    return hash;
}

int get(struct Hashtable* hashTable, char* key)
{
    int hashCode = hash(key);

    int position = hashCode % M;

    struct KeyValuePair **item = &*&*(hashTable->data + position);

    while (*item)
    {
        // printf("key: %s\n", (*(item))->key);

        if (strcmp((*(item))->key, key) == 0)
            return (*(item))->value;
        
        *item = (*(item))->next;
    }

    return -1;
}

void add(struct Hashtable* hashTable, char* key, int value)
{   
    int hashCode = hash(key);

    int position = hashCode % M;

    struct KeyValuePair **item = &*&*(hashTable->data + position);

    // printf("position: %d\n", position);
    // printf("item: %p\n", item);
    // printf("slot null?: %d\n", *item == NULL);

    struct KeyValuePair* newKeyValuePair = malloc(sizeof(struct KeyValuePair));

    //TODO: handle collisions
    newKeyValuePair->key = key;
    newKeyValuePair->value = value;
    newKeyValuePair->next = *item;
    
    if (!*item)
        *item = newKeyValuePair;
    else
        (*(item))->next = newKeyValuePair;

    hashTable->size++;
}

bool containsKey(struct Hashtable* hashTable, char* key)
{
    // int hashCode = hash(key);

    // int position = hashCode % M;

    // int value = *(hashTable->data + position);

    return true;
}

int size(struct Hashtable* hashTable)
{
    return hashTable->size;
}

bool isEmpty(struct Hashtable* hashTable)
{
    return !hashTable || hashTable->size == 0;
}

void main()
{
    struct Hashtable* hashTable = create();

    add(hashTable, "corinthians", 2);
    add(hashTable, "barcelona", 3);
    add(hashTable, "real madrid", 4);
    add(hashTable, "liverpool", 1);
    add(hashTable, "milan", 1);
    add(hashTable, "bayern munich", 1);
    add(hashTable, "palmeiras", 0);

    printf("corinthians: %d\n", get(hashTable, "corinthians"));
    printf("barcelona: %d\n", get(hashTable, "barcelona"));
    printf("real madrid: %d\n", get(hashTable, "real madrid"));
    printf("liverpool: %d\n", get(hashTable, "liverpool"));
    printf("milan: %d\n", get(hashTable, "milan"));
    printf("bayern munich: %d\n", get(hashTable, "bayern munich"));
    printf("palmeiras: %d\n", get(hashTable, "palmeiras"));
}