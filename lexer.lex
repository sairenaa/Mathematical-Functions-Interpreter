%option noyywrap
%option nounput
%{

  #include <iostream>
  #include <cstdlib>

  using namespace std;

  #include <vector>
  
  #include "function.hpp"
  #include "parser.tab.hpp"

%}


%%
"function"             return function_token;
"sin"                  return sin_token;
"cos"                  return cos_token;
[A-Z]                  {
  yylval.c = *yytext;
  return func_name_token;
}
[a-z]                  {
  yylval.c = *yytext;
  return var_token;
}
[0-9]+(\.[0-9]*)?      {
  yylval.d = atof(yytext);
  return num_token;
}
[(),=\"+*/\n\[\]\'-]         return *yytext;
[ \t]                  { }
. {
  cerr << "Lexical error: Unknown token '" << *yytext << "'" << endl;
  exit(EXIT_FAILURE);
}

%%
