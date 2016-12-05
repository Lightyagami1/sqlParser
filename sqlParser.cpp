#include<iostream>
#include<algorithm> //for find method used to check for a value in a vector.
#include<fstream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<vector>
#include<limits>

using namespace std;

struct tableList {                        //this is synonym to database used in sql which contains multiple tables.
  vector<struct table*> database;
};
struct tableList* db1 = new(tableList);  //creating only one database and all tables will be populated in same.

struct table {                           //datastructure for tables.
  string tableName;
  vector<string> headings;
  vector<string> headingType;          //using without the data type for attributes
  vector<vector<string> > tuple;
};


int fileInput(string fileName) {         //the fileName should be present at same
  ifstream in (fileName);                // location where this program is executed.
  if(!in) {
    cout<<"cannot open file\n"<<endl;
    return 1;
  }
  else {
    struct table* temp = new(table);

    db1->database.push_back(temp);
    cout<<"size of db1"<<db1->database.size()<<endl;

    getline(in, temp->tableName);
    cout<<"name for this entered table is "<<temp->tableName<<endl;
    vector<string> head;
    string heads, token;
    getline(in, heads);

    for(unsigned int i = 0; i < heads.size(); ++i) {
      if(heads[i] != ' ')
        token += heads[i];
      else {
        head.push_back(token);
        token.erase(token.begin(), token.end());
      }
    }
    head.push_back(token);    //to get last value which doesnot hava a tailing space

    for(unsigned int i = 0; i < head.size(); i += 2) {
      temp->headings.push_back(head[i]);
 //     cout<<head[i]<<" "<<head[i+1]<<endl;
      temp->headingType.push_back(head[i+1]);
    }

    for(auto i = temp->headings.begin(); i != temp->headings.end(); ++i)
    cout<<*i<<"\t\t";
    cout<<endl;

    vector<string> row;
    while(!in.eof()) {
        token.erase(token.begin(), token.end());
        getline(in, heads);
        for (unsigned int i = 0; i < heads.size(); ++i) {
          if(heads[i] != ',')
            token += heads[i];
          else {
            row.push_back(token);
            token.erase(token.begin(), token.end());
          }
        }
        row.push_back(token);

        temp->tuple.push_back(row);
        row.clear();
      }
      for(unsigned int i = 0 ; i < temp->tuple.size(); ++i) {
        for(unsigned int j = 0; j < temp->tuple[i].size(); ++j)
          cout<<temp->tuple[i][j]<<"\t";
        cout<<endl;
    }
  }
  return 0;
}


int checkPresenceOfTable(string tableName) { // this check if tableName is present in collection.
  struct table* temp;
  for(unsigned int I = 0; I != db1->database.size(); ++I) {
    temp = db1->database[I];
    if(temp->tableName == tableName)
      return 1;
  }
  return 0;
}

struct table* assignTable(string tableName) {  //this returns pointer to an existing table from the collection.
  struct table* temp;
  for(unsigned int I = 0; I != db1->database.size(); ++I) {
    temp = db1->database[I];
    if(temp->tableName == tableName)
      return temp;
  }
  return nullptr;
}


int renameTable(string tableName, string newTableName) {
  struct table* temp;
  for(unsigned int I = 0; I != db1->database.size(); ++I) {
    temp = db1->database[I];
    if(temp->tableName == tableName) {
      temp->tableName = newTableName;
      return 1;
    }
  }
  return 0;
}


string Union(string table1, string table2) {
  if(table1 == table2) {
    cout<<"Names of both tables are same"<<endl;
    return string();
  }

  if ( checkPresenceOfTable(table1) and checkPresenceOfTable(table2) ) {
    struct table* tab1 = assignTable(table1);
    struct table* tab2 = assignTable(table2);

    if(tab1 == nullptr or tab2 == nullptr) {
      cout<<"memory could not be allocated"<<endl;
      return string();
    }

    struct table* temp = new(table);
    temp->tableName = table1+table2;
    cout<<"new name for newly created table is "<<temp->tableName<<endl;
    
//    cout<<"size of db1"<<db1->database.size()<<endl;
    db1->database.push_back(temp);
//    cout<<"size of db1"<<db1->database.size()<<endl;

// making heading vector for new table by headings of parent table.
// and printing headings for display.
    for(auto i = tab1->headings.begin(); i != tab1->headings.end(); ++i) {
    cout<<*i<<"\t\t";
    temp->headings.push_back(*i);
    }
    cout<<endl;

// making heading type for new table by heading of parent table.
    for(auto i = tab1->headingType.begin(); i != tab1->headingType.end(); ++i)
    temp->headingType.push_back(*i);

    vector<string> row;
      for(unsigned int i = 0 ; i < tab1->tuple.size(); ++i) {
        for(unsigned int j = 0; j < tab1->tuple[i].size(); ++j)
//          cout<<temp->tuple[i][j]<<"\t";
          row.push_back(tab1->tuple[i][j]);
          temp->tuple.push_back(row);
          for(auto it = row.begin(); it != row.end(); ++it)
            cout<<*it<<"\t\t";
          cout<<endl;
        row.clear();
      }
      
      for(unsigned int i = 0 ; i < tab2->tuple.size(); ++i) {
        for(unsigned int j = 0; j < tab2->tuple[i].size(); ++j)
//          cout<<temp->tuple[i][j]<<"\t";
          row.push_back(tab2->tuple[i][j]);
        if (find(temp->tuple.begin(), temp->tuple.end(), row) == temp->tuple.end()) {
          temp->tuple.push_back(row);
          for(auto it = row.begin(); it != row.end(); ++it)
            cout<<*it<<"\t\t";
          cout<<endl;
        }
        row.clear();
      }
      return temp->tableName;
  }
  return string();
}


string intersection(string table1, string table2) {
  if(table1 == table2) {
    cout<<"Names of both tables are same"<<endl;
    return string();
  }

  if ( checkPresenceOfTable(table1) and checkPresenceOfTable(table2) ) {
    struct table* tab1 = assignTable(table1);
    struct table* tab2 = assignTable(table2);

    if(tab1 == nullptr or tab2 == nullptr) {
      cout<<"memory could not be allocated"<<endl;
      return string();
    }

    struct table* temp = new(table);
    temp->tableName = table1+table2;
    cout<<"new name for newly created table is "<<temp->tableName<<endl;
    
    db1->database.push_back(temp);

// making heading vector for new table by headings of parent table.
// and printing headings for display.
    for(auto i = tab1->headings.begin(); i != tab1->headings.end(); ++i) {
    cout<<*i<<"\t\t";
    temp->headings.push_back(*i);
    }
    cout<<endl;

// making heading type for new table by heading of parent table.
    for(auto i = tab1->headingType.begin(); i != tab1->headingType.end(); ++i)
    temp->headingType.push_back(*i);

    vector<string> row;
      for(unsigned int i = 0 ; i < tab2->tuple.size(); ++i) {
        for(unsigned int j = 0; j < tab2->tuple[i].size(); ++j)
          row.push_back(tab2->tuple[i][j]);
        if (find(tab1->tuple.begin(), tab1->tuple.end(), row) != tab1->tuple.end()) {
          temp->tuple.push_back(row);
          for(auto it = row.begin(); it != row.end(); ++it)
            cout<<*it<<"\t\t";
          cout<<endl;
        }
        row.clear();
      }
      return temp->tableName;
  }
  return string();
}



string setDifference(string table1, string table2, string table3) {
  if(table1 == table2) {
    cout<<"Names of both tables are same"<<endl;
    return string();
  }

  if ( checkPresenceOfTable(table1) and checkPresenceOfTable(table2) ) {
    struct table* tab1 = assignTable(table1);
    struct table* tab2 = assignTable(table2);

    if(tab1 == nullptr or tab2 == nullptr) {
      cout<<"memory could not be allocated"<<endl;
      return string();
    }

    struct table* temp = new(table);
    temp->tableName = table3;
    cout<<"new name for newly created table is "<<temp->tableName<<endl;
    
    db1->database.push_back(temp);

// making heading vector for new table by headings of parent table.
    for(auto i = tab1->headings.begin(); i != tab1->headings.end(); ++i) {
    cout<<*i<<"\t\t";
    temp->headings.push_back(*i);
    }
    cout<<endl;
// making heading type for new table by heading of parent table.
    for(auto i = tab1->headingType.begin(); i != tab1->headingType.end(); ++i)
    temp->headingType.push_back(*i);

    vector<string> row;
      for(unsigned int i = 0 ; i < tab1->tuple.size(); ++i) {
        for(unsigned int j = 0; j < tab1->tuple[i].size(); ++j)
//          cout<<temp->tuple[i][j]<<"\t";
          row.push_back(tab1->tuple[i][j]);
          temp->tuple.push_back(row);
          for(auto it = row.begin(); it != row.end(); ++it)
            cout<<*it<<"\t\t";
          cout<<endl;
        row.clear();
      }
      
      for(unsigned int i = 0 ; i < tab2->tuple.size(); ++i) {
        for(unsigned int j = 0; j < tab2->tuple[i].size(); ++j)
//          cout<<temp->tuple[i][j]<<"\t";
          row.push_back(tab2->tuple[i][j]);
        auto iter = find(temp->tuple.begin(), temp->tuple.end(), row);
        if(iter != temp->tuple.end())
          temp->tuple.erase(iter);
        cout<<"deleted";
        for(auto it = row.begin(); it != row.end(); ++it)
          cout<<*it<<"\t\t";
        cout<<endl;
        row.clear();
      }
      cout<<"Remaining lines in newTable"<<temp->tuple.size()<<endl;

        return temp->tableName;
  }
  return string();
}



string cartesianProduct(vector<string> query) {
  string table1 = query[1];
  string table2 = query[2];

  if(table1 == table2) {
    cout<<"Names of both tables are same"<<endl;
    cout<<"either change the name using renameTable command or check query"<<endl;
    return string();
  }

  if ( checkPresenceOfTable(table1) and checkPresenceOfTable(table2) ) {
    struct table* tab1 = assignTable(table1);
    struct table* tab2 = assignTable(table2);

    if(tab1 == nullptr or tab2 == nullptr) {
      cout<<"memory could not be allocated"<<endl;
      return string();
    }

    struct table* temp = new(table);
    temp->tableName = table1+table2;
    cout<<"new name for newly created table is "<<temp->tableName<<endl;
    
    db1->database.push_back(temp);

// making heading vector for new table by combining two headings of parent tables.
    for(auto i = tab1->headings.begin(); i != tab1->headings.end(); ++i) {
      cout<<*i<<"\t\t";
      temp->headings.push_back(*i);
    }
    for(auto i = tab2->headings.begin(); i != tab2->headings.end(); ++i) {
      cout<<*i<<"\t\t";
      temp->headings.push_back(*i);
    }
    cout<<endl;

// making heading type for new table by combining two headings of parent tables.
    for(auto i = tab1->headingType.begin(); i != tab1->headingType.end(); ++i)
      temp->headingType.push_back(*i);
    for(auto i = tab2->headingType.begin(); i != tab2->headingType.end(); ++i) 
      temp->headingType.push_back(*i);

      for(unsigned int i = 0 ; i < tab1->tuple.size() - 1; ++i)  //-1 is substracted because an extra empty line is present in all tables of collection of tables.
        for(unsigned int ii = 0 ; ii < tab2->tuple.size() - 1; ++ii) {
          vector<string> row;
          for(unsigned int j = 0; j < tab1->tuple[i].size(); ++j) 
              row.push_back(tab1->tuple[i][j]);
            for(unsigned int jj = 0; jj < tab2->tuple[ii].size(); ++jj)
              row.push_back(tab2->tuple[ii][jj]);
            temp->tuple.push_back(row);
      }
      
        for(unsigned int ii = 0 ; ii < temp->tuple.size(); ++ii) {
          for(unsigned int ij = 0 ; ij < temp->tuple[ii].size(); ++ij)
            cout<<temp->tuple[ii][ij]<<"\t";
            cout<<endl;
          }
        return temp->tableName;
  }
  else {
    cout<<"Requested table/tables donot exist"<<endl;
    return string();
  }
}



string select(vector<string> query) {
  string RequiredTableName;
  vector <string> attributes;

  auto i = query.begin(); ++i; //to move from select to 1st attribute
  for(; i != query.end(); ++i) {
    if(*i != "from") {
      if(*i != "") {
        attributes.push_back(*i);
      }
    }
    else
      break;
  }

  i++;    // to move forward from "from" clause in query vector
  RequiredTableName = *i;
//  cout<<"Using data from tableName "<<*i<<endl;

  bool flag = 0;                //getting the required table from list of all tables present in the tables collection.
  struct table* temp;
  for(unsigned int I = 0; I != db1->database.size(); ++I) {
    temp = db1->database[I];
    if(temp->tableName == RequiredTableName) {
      flag = 1;
      break;
    }
  }

  if(flag == 0) {
    cout<<"Requested table doesnot exist"<<endl;
    return string();
  }
  else {
//    cout<<"yay table exist"<<endl;
    vector <string> clause;
    vector <vector<string> > conditions;

    for(unsigned int i = 0; i < attributes.size(); ++i) {
      if(attributes[i] != "and") {
        clause.push_back(attributes[i]);
        cout<<attributes[i]<<" ";
      }
      else {
        conditions.push_back(clause);
        cout<<endl;
        clause.clear();
      }
    }
    conditions.push_back(clause);   //this is needed to get the last clause which will not pass through else block becuase it doesnot have a "and" after it.
    cout<<endl;

// checking if first entry of each clause is present as valid attribute in the table
    flag = 0;
    for(unsigned int i = 0; i < conditions.size(); ++i)
      for(unsigned int j = 0; j < temp->headings.size(); ++j) {
        if(conditions[i][0] == temp->headings[j]) {
//          cout<<"checked "<<conditions[i][0]<<endl;
          break;
        }
        else if(j == temp->headings.size() && conditions[i][0] != temp->headings[j]) {
          flag = 1;
          //cout<<"problemo at"<<conditions[i][0]<<endl;
        }
      }

    if (flag == 1) {
      cout<<"requested attribute doesnot exist"<<endl;
      return string();
    }

//    cout<<*i<<"check"<<endl;
    struct table* selectedTable = new(table);

    selectedTable->tableName = temp->tableName;
    selectedTable->tableName += "sel";
    cout<<"name of newly created table is "<<selectedTable->tableName<<endl;
    selectedTable->headings = temp->headings;
    selectedTable->headingType = temp->headingType;
    
    db1->database.push_back(selectedTable); // adding new table to collection of tables.

    int flags[temp->tuple.size()];
    fill_n(flags, temp->tuple.size(), -1);

    for(unsigned int i = 0; i < temp->tuple.size(); ++i)
      for(unsigned int k = 0; k < conditions.size(); ++k) {
        for(unsigned int j = 0; j < temp->tuple[i].size(); ++j) {
          if(temp->headings[j] == conditions[k][0]) {
//            cout<<conditions[k][0]<<conditions[k][1]<<endl;
            if(conditions[k][1] == "=") {
//cout<<"it came here for checking with ="<<conditions[k][0]<<"and"<<temp->headings[i]<<endl;
              if(temp->tuple[i][j] == conditions[k][2]) {
                if(flags[i] == -1 or flags[i] == 1) //when it's uninitialized or when it's already valid keep it valid for now.
                  flags[i] = 1;
              }
              else  //when this condition has been already violated.
                flags[i] = 0;
            }
            else if(conditions[k][1] == "!=") {
              if(temp->tuple[i][j] != conditions[k][2]) {
                if(flags[i] == -1 or flags[i] == 1)
                  flags[i] = 1;
                else    // when the given condition was calculated as false, make it false so it's never needed in future to take of. Though with use of "or" this will fail drastically.
                  flags[i] = 0;
              }
            }
//below conditions are fruitful for int and decimal data types only.
            else if(conditions[k][1] == ">" and (temp->headingType[j] == "1" or temp->headingType[j] == "2")) {
                if(stod(temp->tuple[i][j]) > stod(conditions[k][2])) {  //converting to double precision number for proper comparison.
                  if(flags[i] == -1 or flags[i] == 1)
                    flags[i] = 1;
                  else
                    flags[i] = 0;
                }
                else
                  flags[i] = 0;
            }
            else if(conditions[k][1] == "<" and (temp->headingType[j] == "1" or temp->headingType[j] == "2")) {
              if(std::stod(temp->tuple[i][j]) < stod(conditions[k][2])) {
                if(flags[i] == -1 or flags[i] == 1)
                  flags[i] = 1;
                else
                  flags[i] = 0;
              }
              else
                flags[i] = 0;
            }
            else {
              cout<<"conditional not supported"<<endl;
              cout<<temp->headingType[j]<<conditions[k][2]<<endl;
              return string();
            }
          }
        }
      }
    cout<<"after"<<endl;
    for(auto i = 0; i < temp->tuple.size(); ++i) {
      cout<<flags[i]<<" ";
      if(flags[i] ==1)    //inserting all tuples having value of flag as 1
        selectedTable->tuple.push_back(temp->tuple[i]);
    }
    cout<<endl;
    cout<<selectedTable->tuple.size()<<endl;

    return selectedTable->tableName;
  }
}





void rename(vector<string> query) {   //format: rename prevAttr newAttr in tableName
  string RequiredTableName;
  auto i = query.begin(); ++i; //to move from rename to prevAttr
  string prevAttrName = *i;
  
  ++i;
  string newAttrName = *i;

  i++; i++;    // to move forward from "in" clause in query vector
  RequiredTableName = *i;

  bool flag = 0;                //getting the required table from list of all tables present in the tables collection.
  struct table* temp;
  for(unsigned int I = 0; I != db1->database.size(); ++I) {
    temp = db1->database[I];
    if(temp->tableName == RequiredTableName) {
      flag = 1;
      break;
    }
  }

  if(flag == 0) {
    cout<<"Requested table doesnot exist"<<endl;
    return;
  }
  else {
    auto i = temp->headings.begin();
    bool flag = 0;
    for(; i != temp->headings.end(); ++i)
      if(*i == prevAttrName) {
        *i = newAttrName;
        flag = 1;
        cout<<prevAttrName<<" changed to "<<newAttrName<<endl;
        break;
      }
    if(flag == 0)
      cout<<"requested attribute "<<prevAttrName<<" to be changed doesnot exit in "<<RequiredTableName<<endl;
  }
}




string project(vector< string > query) {
  string RequiredTableName;
  vector <string> attributes;

  auto i = query.begin(); ++i; //to move from select to 1st attribute
  for(; i != query.end(); ++i) {
    if(*i != "from") {
      if(*i != "") {
        attributes.push_back(*i);
      }
    }
    else
      break;
  }
  cout<<endl;

  i++;    // to move forward from "from" clause in query vector
  RequiredTableName = *i;
// Checking if table of this name exits in collection 
  bool flag = 0;                //getting the required table from list of all tables present in the tables collection.
  struct table* temp;
  for(unsigned int I = 0; I != db1->database.size(); ++I) {
    temp = db1->database[I];
    if(temp->tableName == RequiredTableName) {
      flag = 1;
      break;
    }
  }

  if(flag == 0) {
    cout<<"Requested table doesnot exist"<<endl;
    return string();
  }
  else {
//    cout<<"table exist"<<endl;
    if(attributes.size() > temp->headings.size()) { //if no. of attributes entered is more than that present in the table
      cout<<"excess attributes asked"<<endl;
      return string();
    }

    struct table* projected = new(table);     //constructing new table for record.
    projected->tableName = RequiredTableName;
    projected->tableName += "proj";
    cout<<"name of new table is "<<projected->tableName<<endl;

   // cout<<"size of db1"<<db1->database.size()<<endl;
    db1->database.push_back(projected);
   // cout<<"size of db1"<<db1->database.size()<<endl;

//comparing entered attributers with attributes present in required table
    for(unsigned int i = 0; i < attributes.size(); ++i)
      if(attributes[i] != "") {
        cout<<attributes[i]<<" \t\t";
        projected->headings.push_back(attributes[i]);
      }
      cout<<endl;

    vector<unsigned> indexes;
    flag = 0;
    for(unsigned int i = 0; i < attributes.size(); ++i)
      for(unsigned int j = 0; j < temp->headings.size(); ++j) {
        if(attributes[i] == temp->headings[j]) {
          projected->headingType.push_back(temp->headingType[j]);     //entering the corresponding value type for attributes.
          indexes.push_back(j);
          break;
        }
        else if(j == temp->headings.size() && attributes[i] != temp->headings[j]) {
          flag = 1;
//          cout<<"problemo at"<<attributes[i]<<endl;
        }
      }

    if(attributes.size() == 1 and attributes[0] == "*")     //special case for "*"
      flag = 0;

    if (flag == 1) {
      cout<<"requested attribute doesnot exist"<<endl;
      return string();
    }

    vector<string> row;
      for(unsigned int i = 0 ; i < temp->tuple.size(); ++i) {
        for(unsigned int j = 0; j < temp->tuple[i].size(); ++j)
          if(find(indexes.begin(), indexes.end(), j) != indexes.end()) {   //find is used to find a particular value in a vector.defined in algorithm header.
//          cout<<temp->tuple[i][j]<<"\t";
          row.push_back(temp->tuple[i][j]);
          }
        if (find(projected->tuple.begin(), projected->tuple.end(), row) == projected->tuple.end()) {
          projected->tuple.push_back(row);
          for(auto it = row.begin(); it != row.end(); ++it)
            cout<<*it<<"\t\t";
          cout<<endl;
        }
        row.clear();
    }
      return projected->tableName;
  }
}




string readLine() {
  string line;
  getline(cin, line);
  return line;
}


vector<string> splitLine(string line) {
  vector<string> tokens;
  string token;
  line += " f";   // to overcome error of not getting last chunk of chars

  int t = (line.end() - line.begin())/sizeof(line[0]);
  for(int i = 0; i < t; ++i) {
    if(line[i]!=' ' and line[i]!='(' and line[i]!=')' and line[i]!=',' and line[i]!=';')  {      //this is causing proble when " ," or combination of other such characters is used together, segmentation fault occurs.
      token += line[i];
    }
    else {
      tokens.push_back(token);
      token.erase(token.begin(), token.end());
    }
}
  return tokens;
}

void invalid() {
  cout<<"Invalid syntax"<<endl;
}


int execute(std::vector<string> tokens) {
  if (tokens[0] == "exit") {
    cout<<"bye"<<endl;
    return 0;
  }
  else if (tokens[0] == "fileIn" or tokens[0] == "fin") {
    if(tokens.size() == 2)
      fileInput(tokens[1]);       //assumed file is in same location as this code.
    else
      invalid();
  }
  else if( tokens[0] == "select" or tokens[0] == "sel") {
    if(tokens.size() > 5)
      select(tokens);
    else
      invalid();
  }
  else if (tokens[0] == "rename" or tokens[0] == "re") {
    rename(tokens);
  }
  else if (tokens[0] == "project" or tokens[0] == "proj") {
    project(tokens);
  }
  else if (tokens[0] == "cartesian product" or tokens[0] == "cp") {
    if(tokens.size() == 3)
      cartesianProduct(tokens);
    else 
      invalid();
  }
  else if (tokens[0] == "check" or tokens[0] == "ch") {
    if(tokens.size() == 2 and tokens[1] != "") {
      if(checkPresenceOfTable(tokens[1]))
        cout<<"table exist with name"<<tokens[1]<<endl;
      else
        cout<<"table with name "<<tokens[1]<<" doesnot exist"<<endl;
    }
    else 
      invalid();
  }
  else if (tokens[0] == "renameTable" or tokens[0] == "reTab") {
    if(tokens.size() == 3) {
    if(renameTable(tokens[1], tokens[2]))
      cout<<"rename successful"<<"now its "<<tokens[2]<<endl;
    else
      cout<<"problem when attempting to change of the table"<<endl;
    }
    else
      invalid();
  }
  else if (tokens[0] == "intersection" or tokens[0] == "inter") {
    if(tokens.size() == 3 and tokens[1] != "" and tokens[2] != "")
      intersection(tokens[1], tokens[2]);
    else
      invalid();
  }
  else if (tokens[0] == "union" or tokens[0] == "uni") {
    if(tokens.size() == 3 and tokens[1] != "" and tokens[2] != "")
      Union(tokens[1], tokens[2]);
    else
      invalid();
  }
  else if (tokens[0] == "setDifference" or tokens[0] == "setdiff") {
    if(tokens.size() == 3 and tokens[1] != "" and tokens[2] != "")
      setDifference(tokens[1], tokens[2], tokens[3]);
    else
      invalid();
  }
  else
    return 1;
}

void loop() {
  string line;
  vector<string> args;
  int status = 1;
  do {
    cout<<"> ";
    line = readLine();              //each line is read
    args = splitLine(line);         //split into tokens using(" ",",",";") as seperators.
    status = execute(args);
  } while(status);
}

int main(int argc, char *argv[]) {
  printf("This parser now have following working commands\n");
  printf("  > fileIn\n");
  printf("  > exit\n");
  printf("  > rename\n");
  printf("  > select\n");
  printf("  > project\n");
  printf("  > cartesian product\n");
  printf("  > renameTable \n");
  printf("  > union \n");
  printf("  > setDifference \n");
  printf("  > intersection \n");
  loop();                               //main function to act like command prompt
}
