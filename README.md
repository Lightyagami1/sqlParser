       -------------------- SQL PARSER ------------------------------

------> compilation 
  The code uses a lot functionalities of c++11 so when compiling it -std=c++11 clause should also be used.



------> data structure used
  This system allow for adding as many tables as required, but only through use of a pre-structured file format files.
      Required Structure:
      first Line: name of table
      second Line: name of attributes followed by their data types assigned as per follow scheme
          int -> 1
          string -> 0
          float -> 2
  
  This will be useful when comparing values stored in them.
      all values in this lines are seperated by use of only space
  
      from third Line: attributes value seperated by use of "," only. No space should be present any where.


------> Implemented commands
    
    - project
    - rename
    - set difference
    - intersection
    - select
    - union
    - cartesian table


------> syntax and example and limitations

  1. For input from file, file needs to follow a same order:
    * foramt: fileIn fileName
          or fin fileName
    * values should be stored as csv type.
    * NULL values can be stored as all values are stored as string.
    * space should not be used for values of table.
    * all character of each value line should be "," or else the last attribute value will not be considered.
    * name of tables is not checked so it is responsibility of user to provide unique name, as program will simply accept the new recurring table name and then this table can not be accessed from available commands.
    
  
  2. For select command 
    * format: select attr condition value and attr2 condition value2 from tableName
          or  sel attr condition value and attr2 condition value2 from tableName
    * only space is allowed and no use of comma
      and use of and is only implemented and operator =, <, >, != are possible
      eg. select Name = saurav kumar and RollNo = 1232323 from Student_Record
    * in condition clause value having space in them not give result and thus this program is limited to integer, float and strings without space.
    * to overcome above problem, "_" can be used instead of space in such strings and while printing it can be replaced by " ".
  
  
  3. For rename command
    * format: rename oldName newName in TableName
          or  re oldname newname in tableName
    * eg rename Name StudName in Student_Record
  
  4. For project command
    * format: project attr1, attr2, attr3 from [tableName]
          or  proj attr1, attr2, attr3 from [tableName]
  
    * eg project Name, Pointer from Student_Record
      > attributes should be seperated with comma, use of space is optional
    * use of "*" doesnot work hence to get all attributes they needs to specified 
  
  5. For cartesian product
    * format: cartesian product tableName1 tableName2
          or  cp tableName1 tableName1
  
    * only applicable on two tables at an time
      eg. cartesian product Stud_Rec Stud_Sub
  
  6. renameTable
    * format: renameTable oldName newName
          or  reTab oldName newName
    * useful when table name needs to be change as default scheme can get long with small level of nesting.
  
  7. Union
    * format: Union tableName1 tableName2
          or: uni tableName1 tableName2
    * conditions checked are:
        -> name of tables should be different
        -> attribute should be same, only name is checked not their value type
  
  
  8. check
    *format: check tableName
         or: ch tableName
    * Can come handy to check it required table with given tableName exist or not
  
  9. setDifference
    * format: setDifference table1 table2 newTableName
          or: setdiff table1 table2 newTableName
  
  
  -----> Nested Query
  Nested Query can not be executed as per now. But intermediate tables are stored and thus can be used effectively to get required result.
  
   o---->------------>-------- x-o-x -------<-------------------<----o
