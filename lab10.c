#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

struct Trie {
    struct Trie *children[ALPHABET_SIZE];
    int isEndOfWord;
    int count;
};

void insert(struct Trie **ppTrie, char *word) {
    struct Trie *pCurrent = *ppTrie;
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (!pCurrent->children[index]) {
            struct Trie *pNode = (struct Trie *) malloc(sizeof(struct Trie));
            memset(pNode, 0, sizeof(struct Trie));
            pCurrent->children[index] = pNode;
        }
        pCurrent = pCurrent->children[index];
    }
    pCurrent->isEndOfWord = 1;
    pCurrent->count++;
}

int numberOfOccurrences(struct Trie *pTrie, char *word) {
    struct Trie *pCurrent = pTrie;
    for (int i = 0; i < strlen(word); i++) {
        int index = word[i] - 'a';
        if (!pCurrent->children[index]) {
            return 0;
        }
        pCurrent = pCurrent->children[index];
    }
    return pCurrent->count;
}


struct Trie *deallocateTree(struct Trie *pTrie) {
    if (!pTrie) {
        return NULL;
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (pTrie->children[i]) {
            deallocateTree(pTrie->children[i]);
        }
    }
    free(pTrie);
    return NULL;
}

int main(void)
{
    struct Trie *trie = NULL;
    trie = (struct Trie *) malloc(sizeof(struct Trie));
    memset(trie, 0, sizeof(struct Trie));

    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};

    for (int i = 0; i < 5; i++) {
        insert(&trie, pWords[i]);
    }

    for (int i = 0; i < 5; i++) {
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(trie, pWords[i]));
    }

    trie = deallocateTree(trie);
    return 0;
}