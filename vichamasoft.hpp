#include <iostream>
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include <vector>
#include <sstream>
#include <unistd.h>
using namespace std;

namespace vichamasoft{
  //SECTION FOR DB WRAPPER
  class Database {
    private:
    bool statusConnection;
    sqlite3 *connection;
    int result;
    public:
    Database();
    ~Database();
    bool openDatabase(string dbname, string path);
    void closeDatabase();
    bool isConnected();
    void beginTransaction();
    void commitTransaction();
    int execute(const char *query);
    int execute(string query);
    std::vector<std::string> selectRow(std::string query);
  };
  
  //SECTION FOR BINARY TREE
  struct PlainNode{
   string treeName;
   string nodePath;
   string value;
  };

  class Node{
  private:
    int value;
    Node *left, *right;
  public:
    Node();
    Node(int mValue);
    ~Node();
    int getValue();
    void setRight(Node *mRight);
    void setLeft(Node *mLeft);
    Node* getRight();
    Node* getLeft();
  };

  class Tree{
  private:
    string name;
    std::list<PlainNode> nodeList;
    Node *rootNode;
  public:
    Tree();
    Tree(string mName);
    Tree(string mName,list<int> valueList);
    ~Tree();
    Node* add(Node *root, int mValue );
    void print();
    void print(Node *root);
    void generateRecords();
    void generateRecords(Node *node,string mValue);
    void printRecords();
    list<PlainNode> getRecords();
  };
}
