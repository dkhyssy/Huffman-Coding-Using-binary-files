#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "bt.h"

#define MAX_TREE_HT 256


int isleaf(Node* node);
void swapNodes(Node** a, Node** b);
void sortNodes(Node* nodes[], int n);


Node* buildHuffmanTree(unsigned char data[], int freq[], int size);

void printCodes(Node* root, int tabl[], int top);
void huffmanCodingFromFile(const char* filename);

#endif
