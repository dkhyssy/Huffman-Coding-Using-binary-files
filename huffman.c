#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

int isleaf(Node* node) {
    return (node->left == NULL) && (node->right == NULL);
}

void swapNodes(Node** a, Node** b) {
    Node* t = *a;
    *a = *b;
    *b = t;
}

void sortNodes(Node* nodes[], int n) {
    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            if(nodes[i]->freq > nodes[j]->freq)
                swapNodes(&nodes[i], &nodes[j]);
        }
    }
}

Node* buildHuffmanTree(unsigned char symbols[], int frequencies[], int size) {
    Node* nodes[size];

    for(int i = 0; i < size; i++)
        nodes[i] = createNode(symbols[i], frequencies[i]); // Parfait : appelle bt.c

    int n = size;
    while(n > 1) {
        sortNodes(nodes, n);

        Node* left = nodes[0];
        Node* right = nodes[1];

        Node* newNode = createNode(0, left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;

        nodes[0] = newNode;
        for(int i = 1; i < n - 1; i++)
            nodes[i] = nodes[i + 1];
        n--;
    }
    return nodes[0];
}

void printCodes(Node* root, int tabl[], int top) {
    if(root->left) {
        tabl[top] = 0;
        printCodes(root->left, tabl, top + 1);
    }
    if(root->right) {
        tabl[top] = 1;
        printCodes(root->right, tabl, top + 1);
    }
    if(isleaf(root)) {
        printf("%c: ", root->symbol);
        for(int i = 0; i < top; i++)
            printf("%d", tabl[i]);
        printf("\n");
    }
}

void huffmanCodingFromFile(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if(!file) {
        printf("Erreur : impossible d'ouvrir le fichier.\n");
        return;
    }

    int freq[256] = {0};
    unsigned char ch;
    while(fread(&ch, 1, 1, file) == 1) {
        freq[ch]++;
    }
    fclose(file);

    int size = 0;
    for(int i = 0; i < 256; i++) {
        if(freq[i] > 0) size++;
    }

    unsigned char data[size];
    int freqData[size];
    int j = 0;
    for(int i = 0; i < 256; i++) {
        if(freq[i] > 0) {
            data[j] = (unsigned char)i;
            freqData[j] = freq[i];
            j++;
        }
    }

    Node* root = buildHuffmanTree(data, freqData, size);
    int arr[MAX_TREE_HT];
    printCodes(root, arr, 0);
}
