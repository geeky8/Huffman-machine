#include <bits/stdc++.h>
using namespace std;

// Huffman node defines the structure of the Huffman tree
class HuffmanNode{
  public:
    // Stores the character of the given string
    // Only child nodes of the tree have the characters
    // Rest of the nodes store a const char '#'
    char data;
    // Frequency of the character
    int freq;
    // Left subtree of a node
    // In case of a character left subtree is NULL
    HuffmanNode* left;
    // Right subtree of a node
    // In case of a character right subtree is NULL
    HuffmanNode* right;

    HuffmanNode(char data, int freq){
      this->data = data;
      this->freq = freq;
      left = right = NULL;
    }
};

// Custom compare operator for making the heap as min-heap
class Comparator{
    public:
      bool operator()(HuffmanNode *a, HuffmanNode *b){
        if(a->freq < b->freq) return false;
        return true;
      }
};

class Huffman{
  public:
    // The base string that needs to be compressed
    string str;
    // pair<int, char> represents character-frequency, character
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Comparator> huffmanQueue;
    // map to get character frequencies from the given string
    unordered_map<char, int> charFrequencies;
    // mapping the characters to individual unique codes
    unordered_map<char, string> codes;
    // The root of your Huffman Tree
    HuffmanNode *root;

    Huffman(string str){
      this->str = str;
      for(auto& i : str) charFrequencies[i]++;
      for(auto& it: charFrequencies) {
        HuffmanNode *node = new HuffmanNode(it.first, it.second);
        huffmanQueue.emplace(node);
      }
    }

    // To generate the required Huffman Tree for encoding and decoding
    void generateHuffmanTree(){
      while(!huffmanQueue.empty()){
        HuffmanNode *left = huffmanQueue.top(); huffmanQueue.pop();
        HuffmanNode *right = huffmanQueue.top(); huffmanQueue.pop();
        HuffmanNode *node = new HuffmanNode('#', left->freq+right->freq);
        if(left->freq <= right->freq) {node->left = left; node->right = right;}
        else {node->right = left; node->left = right;}
        huffmanQueue.emplace(node);
      }

      root = huffmanQueue.top(); huffmanQueue.pop();
    }

    // To get the unique codes for each character
    void generateHuffmanCodes(HuffmanNode *root, string code){
      if(!root) return;
      generateHuffmanCodes(root->left, code+'0');
      generateHuffmanCodes(root->right, code+'1');
      if(root->data != '#') codes[root->data] = code;
    }

    // To encode the given string with huffman codes
    string generateEncodedString(){
      string res = "";
      for(auto& i: str){
        res += codes[i];
      }
      cout<<res<<endl;
      return res;
    }

    // To decode the encoded string back to its original form
    string generateDecodedString(string encodedString){
      string res = "";
      HuffmanNode *curr = root;
      for(auto& i: encodedString){
        if(i == '0') curr = curr->left;
        else curr = curr->right;
        if(!curr->left && !curr->right){res += curr->data; curr = root;}
      }

      return res+'\0';
    }

    // To print the huffman codes for each of the characters
    void printHuffmanCodes(){
      for(auto& it: codes) cout << it.first << " " << it.second << endl;
    }
};




int main() {
  string given = "AAAAABCCCCCCDDD";
  cout<<given<<endl;
  Huffman huffman = Huffman(given);
  huffman.generateHuffmanTree();
  huffman.generateHuffmanCodes(huffman.root, "");
  huffman.printHuffmanCodes();
  cout<<huffman.generateDecodedString(huffman.generateEncodedString())<<endl;
  return 0;
}