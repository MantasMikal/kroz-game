
 // sources: 
 // http://sqlfiddle.com/#!5/d0a2d/6 15/03/2018  
 // https://www.tutorialspoint.com/sqlite/sqlite_c_cpp.htm 15/03/2018  
/*
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <iostream>

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
   
   int i;
   
   for(i = 0; i<argc; i+=2) 
   {
      printf("%s = %s\n", argv[i+1], argv[i] );
   }
 
   return 0;
}

int main(int argc, char* argv[]) 
{
   sqlite3 *db;
   char *zErrMsg = 0;
   int rec;
   char *sqlDB;

   /* Attempt to open database */

/*
   rec = sqlite3_open("DB.db", &db);
   
   if( rec ) 
   {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } 
    
    else 
   {
      fprintf(stderr, "Opened database successfully\n");
   }

    
    //query which returns username and fake Row number by counting player id before and curent player id
    sqlDB = "SELECT a.player_username, (SELECT COUNT(*) FROM Player as b WHERE a.player_id >=b.player_id) as c FROM Player as a";          
   
   /* Execute SQL statement */
  
/*
rec = sqlite3_exec(db, sqlDB, callback, 0, &zErrMsg);
   
   if( rc != SQLITE_OK )
   {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } 
   sqlite3_close(db);
   return 0;
}*/