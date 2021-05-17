#include "vichamasoft.hpp"

static bool setupDatabase(vichamasoft::Database *db){
  bool result;
  if (!db->openDatabase("vichamasoft.db","")){
    return false;
  }  
  string createTable="CREATE TABLE IF NOT EXISTS tree (id INTEGER PRIMARY KEY AUTOINCREMENT,name varchar(80),path varchar(255), value int(2));";
  if (db->execute(createTable) > 0){
    result= true;
  } else {
    result= false;
  }
  return result;
}

static std::list<int> parseNodeValues(std::string sValues){
  std::list<int> nodeValues;
  std::stringstream s_stream(sValues);
  while(s_stream.good()) {
    string substr;
    getline(s_stream, substr, ',');
    nodeValues.push_back(std::stoi(substr));
  }
  return nodeValues;
}

static std::vector<int> parseValues2Vector(std::string sValues){
  std::vector<int> nodeValues;
  std::stringstream s_stream(sValues);
  while(s_stream.good()) {
    string substr;
    getline(s_stream, substr, ',');
    nodeValues.push_back(std::stoi(substr));
  }
  return nodeValues;
}

static std::vector<std::string> parseValues2VectorStr(std::string sValues){
  std::vector<std::string> nodeValues;
  std::stringstream s_stream(sValues);
  while(s_stream.good()) {
    string substr;
    getline(s_stream, substr, '/');
    nodeValues.push_back(substr);
  }
  return nodeValues;
}

static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
   fprintf(stderr, "%s: ", (const char*)data);

   for(i = 0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int main(int argc, char *argv[]){
  vichamasoft::Database *db;
  db = new vichamasoft::Database();
  if (!setupDatabase(db)){
    return 1;
  }
  //Parse command line arguments
  std::string treeName;
  std::string nodeValues;
  std::string values2Find;
  int c;
  int MODE_INSERT=10;
  int MODE_FIND=20;
  int MODE_BOTH=30;
  int currentMode=0;
  
  while( ( c = getopt (argc, argv, "t:i:f:") ) != -1 ) {
    switch(c){
      case 't':
        if(optarg) {
          treeName = optarg;
        }
        break;
      case 'i':
        if(optarg) {
          currentMode=currentMode+MODE_INSERT;
          nodeValues = optarg;
        }
        break;
      case 'f':
        if(optarg) {
          currentMode=currentMode+MODE_FIND;
          values2Find = optarg;
        }
        break;
    }
  }

  if (treeName.empty()){
    fprintf(stderr, "Treename is required");
    return 1;
  }
  int result;
  if (currentMode == MODE_INSERT){
    if (nodeValues.empty()){
      fprintf(stderr, "Tree node values are required");
      return 1;
    }
    vichamasoft::Tree binaryTree(treeName,parseNodeValues(nodeValues));
    binaryTree.generateRecords();
    list<vichamasoft::PlainNode> records = binaryTree.getRecords(); 
    list<vichamasoft::PlainNode>::iterator recordsIt;
    string insertRecords="INSERT INTO tree (name,path,value) VALUES ";
    string temp;
    string separator="";
    for(recordsIt= records.begin();recordsIt != records.end();++recordsIt ){
      temp = "('"+ recordsIt->treeName + "','"+  recordsIt->nodePath +"',"+ recordsIt->value +")";
      insertRecords=insertRecords+separator+temp;
      separator=",";
    }
    insertRecords+=";";
    result = db->execute(insertRecords);    
  } else if (currentMode == MODE_FIND){
    if (values2Find.empty()){
      fprintf(stderr, "Tree node values are required");
      return 1;
    }
    std::vector<int> nodes2Find = parseValues2Vector(values2Find);   
    for(int i = 0; i< nodes2Find.size(); i++) {
      //Validate numeric values
    }
    std::string sqlQuery = "SELECT path FROM tree where name='"+ treeName + "' and value in(" + values2Find + ");";
    std::vector<std::string> values2Process = db->selectRow(sqlQuery);
    std::vector<std::string> path2Node1 = parseValues2VectorStr(values2Process.at(0));
    std::vector<std::string> path2Node2 = parseValues2VectorStr(values2Process.at(1));
    int sizePathNode1 = path2Node1.size();
    int sizePathNode2 = path2Node2.size();
    int minPathSize=0;
    if (sizePathNode1<sizePathNode2){
      minPathSize=sizePathNode1;
    } else {
      minPathSize=sizePathNode2;
    }
    std::string lastNode="";    
    for(int counter=0; counter<minPathSize-1;counter++){
      std::string value1=path2Node1.at(counter);
      std::string value2=path2Node2.at(counter);
       if (value1.compare(value2) != 0){
         break;
       } else {
         lastNode=value1;
       }
    }
    std::cout<<"Common Ancestor:"<<lastNode;
  }  
  return 0;
}
