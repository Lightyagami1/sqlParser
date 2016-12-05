int fileInput(string fileName) {
  ifstream in (fileName);
  if(!in) {
    cout<<"cannot open file\n";
    return 1;
  }
  else {
    struct table* temp = new(table);

    db1->database.push_back(temp);
    cout<<"size of db1"<<db1->database.size()<<endl;

    getline(in, temp->tableName);
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

    for(unsigned int i = 0; i < head.size(); i += 2) {
      temp->headings.push_back(head[i]);
      temp->headingType.push_back(head[i+1]);
    }

    for(auto i = temp->headings.begin(); i != temp->headings.end(); ++i)
    cout<<*i<<"\t\t";
    cout<<endl;

    auto tempit = temp->tuple.begin();
    vector<string> row;
    while(!in.eof()) {
        token.erase(token.begin(), token.end());
        getline(in, heads);
  //      cout<<"hes"<<heads<<endl;
        for (unsigned int i = 0; i < heads.size(); ++i) {
          if(heads[i] != ',')
            token += heads[i];
          else {
            //cerr<<"tok"<<token<<endl;

            row.push_back(token);
  //          cerr<<"row"<<(row.back())<<endl;
            token.erase(token.begin(), token.end());
          }
        }

        temp->tuple.push_back(row);
        row.clear();
      }
        //cout<<"size of tuple->temp"<<temp->tuple.size();
      for(int i = 0 ; i < temp->tuple.size(); ++i) {
        for(int j = 0; j < temp->tuple[i].size(); ++j)
          cout<<temp->tuple[i][j]<<"\t";
        cout<<endl;
    }
  //delete(temp);
  }
  return 0;
}
