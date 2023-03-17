#include<iostream>
#include<fstream>
#include<string>
#include<stdexcept>
#include<cctype>
#include"Dictionary.h"

using namespace std;

using namespace std;

#define MAX_LEN 300

int main(int argc, char * argv[]){

   int token_count, line_count;
   size_t begin, end, len;
   ifstream in;
   ofstream out;
   string line;
   string tokenBuffer;
   string token;
   
   Dictionary D;
   string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$^&*()-_=+0123456789%";

   // check command line for correct number of arguments
   if( argc != 3 ){
      cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
      return(EXIT_FAILURE);
   }

   // open files for reading and writing 
   in.open(argv[1]);
   if( !in.is_open() ){
      cerr << "Unable to open file " << argv[1] << " for reading" << endl;
      return(EXIT_FAILURE);
   }

   out.open(argv[2]);
   if( !out.is_open() ){
      cerr << "Unable to open file " << argv[2] << " for writing" << endl;
      return(EXIT_FAILURE);
   }

   // read each line of input file, then count and print tokens 
   line_count = 0;
   while( getline(in, line) )  {
      line_count++;
      len = line.length();
      for(size_t i = 0; i < len; i++){
		line[i] = tolower(line[i]);
	  }
      // get tokens in this line
      token_count = 0;
      tokenBuffer = "";

      // get first token
      begin = min(line.find_first_not_of(delim, 0), len);
      end   = min(line.find_first_of(delim, begin), len);
      token = line.substr(begin, end-begin);
      
      while( token!="" ){  // we have a token
         // update token buffer
		 if(token[token.length() -1] == '\n'){
			token.erase(token.length()-1);
		 }
         //tokenBuffer += "   "+token+"\n";
         token_count++;

		
		if(D.contains(token)){
			D.setValue(token, D.getValue(token) + 1);
		} else {
			D.setValue(token, 1);
		}
         // get next token
         begin = min(line.find_first_not_of(delim, end+1), len);
         end   = min(line.find_first_of(delim, begin), len);
         token = line.substr(begin, end-begin);
      }

      // print tokens in this line
      /*out << "line " << line_count << " contains " << token_count;
      out << " token" << (token_count==1?"":"s") << endl;
      out << tokenBuffer << endl;*/
   }

   out << D << endl;

   // close files 
   in.close();
   out.close();

   return(EXIT_SUCCESS);
}