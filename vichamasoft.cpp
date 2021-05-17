#include "vichamasoft.hpp"


namespace vichamasoft{
  //SECTION FOR DB WRAPPER
  Database::Database(){
    statusConnection=false;
  }

  Database::~Database(){
    closeDatabase();
  }

  bool Database::openDatabase(string dbname,string path){
    string fullPath= path.append(dbname);
    statusConnection =true;
    int openResult = sqlite3_open(fullPath.c_str(), &connection);
    if (openResult){
      statusConnection=false;
    }
    return statusConnection;
  }

  bool Database::isConnected(){
    return statusConnection;
  }

  void Database::closeDatabase(){
    sqlite3_close(connection);
  }

  void Database::beginTransaction(){
    sqlite3_exec(connection, "BEGIN TRANSACTION", NULL, NULL,NULL);
  }

  void Database::commitTransaction(){
    sqlite3_exec(connection, "COMMIT TRANSACTION", NULL, NULL,NULL);
  }

  int Database::execute(const char *query){
    if(!isConnected()){
      return 0;
    }
    char *errMsg=0;
    int result = sqlite3_exec(connection, query, NULL, 0, &errMsg);
    if( result  != SQLITE_OK){
      fprintf(stderr, "SQL error: %s\n", errMsg);
      sqlite3_free(errMsg);
      return 0;
    }
    return 1;
  }
  
  int Database::execute(std::string query) {  
    int size = query.size()+1;
    char sqlQuery[size];
    query.copy(sqlQuery, size); 
    sqlQuery[query.size()] = '\0';
    if(!isConnected()){
      return 0;
    }
    char *errMsg=0;
    int result = sqlite3_exec(connection, &sqlQuery[0], NULL, 0, &errMsg);
    if( result  != SQLITE_OK){
      fprintf(stderr, "SQL error: %s\n", errMsg);
      sqlite3_free(errMsg);
      return 0;
    }
    return 1;
  }
  
  std::vector<std::string> Database::selectRow(std::string query) {
    sqlite3_stmt* stmt;
    int row = 0;
    std::vector<std::string> valueList;
    int size = query.size()+1;
    char sqlQuery[size];
    query.copy(sqlQuery, size); 
    sqlQuery[query.size()] = '\0';
    if(!isConnected()){
      return valueList;
    }
    sqlite3_prepare(connection, sqlQuery, sizeof sqlQuery, &stmt, NULL);
    bool done = false;
    while (!done) {
        switch (sqlite3_step (stmt)) {
        case SQLITE_ROW:
            {
              std::string rowValue = std::string(reinterpret_cast <const char*> (sqlite3_column_text(stmt, 0)));
              valueList.push_back(rowValue);
              row++;
            }
            break;
        case SQLITE_DONE:
            done = true;
            break;
        default:
            fprintf(stderr, "Failed.\n");
            return valueList;
        }
    }
    sqlite3_finalize(stmt);    
    return valueList;
  }

  Node::Node(){
    value=0;
    left=right=NULL;
  }

  Node::Node(int mValue){
    value = mValue;
    left=right=NULL;
  }

  Node::~Node(){
  }

  int Node::getValue(){
    return value;
  }

  void Node::setRight(Node *mRight){
    right=mRight;
  }

  void Node::setLeft(Node *mLeft){
    left=mLeft;
  }

  Node* Node::getRight(){
    return right;
  }

  Node* Node::getLeft(){
    return left;
  }

  //TREE SECTION
  Tree::Tree(){
    name="default";
  }

  Tree::~Tree(){

  }

  Tree::Tree(string mName){
    name=mName;
  }

  Tree::Tree(string mName, list<int> valueList){
    name=mName;
    list <int>::iterator it;
    rootNode = NULL;
    for(it= valueList.begin();it != valueList.end();++it ){
      rootNode=add(rootNode,*it);
    }
  }

  Node* Tree::add(Node *node, int mValue){
    if (!node){
    return new Node(mValue);
    }
    if (mValue > node->getValue()){
      node->setRight(add(node->getRight(),mValue));
    } else {
      node->setLeft(add(node->getLeft(),mValue));
    }
    return node;
  }

  void Tree::print(){
    if (!rootNode){
      return;
    }
    print(rootNode->getLeft());
    std::cout << rootNode->getValue() <<std::endl;
    print(rootNode->getRight());
  }

  void Tree::print(Node *node){
     if (!node){
       return;
     }
     print(node->getLeft());
     std::cout << node->getValue() <<std::endl;
     print(node->getRight());
  }

  void Tree::generateRecords(){
    if (!rootNode){
      return;
    }
    generateRecords(rootNode,"");
  }

  void Tree::generateRecords(Node* node, string mValue){
    if (!node){
        return;
    }
    string temp = to_string(node->getValue());
    mValue += temp+"/";
    generateRecords(node->getLeft(),mValue);
    PlainNode mPlainNode;
    mPlainNode.treeName=name;
    mPlainNode.nodePath=mValue;
    mPlainNode.value =to_string(node->getValue());
    nodeList.push_back(mPlainNode);
    generateRecords(node->getRight(),mValue);
  }

  void Tree::printRecords(){
    list <PlainNode> :: iterator it;
    for(it= nodeList.begin();it != nodeList.end();++it ){
    }
  }

  list<PlainNode> Tree::getRecords(){
    return nodeList;
  }
}
