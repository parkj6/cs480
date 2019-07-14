CS 480 Translators
MWF, 11:00 – 11:50am (WNGR 153)
http://web.engr.oregonstate.edu/~hessro/teaching/cs480-sp19

// Teacher Info
Rob Hess(hessro@oregonstate.edu) // not recommended
Office Hour
	Tues., 10:00am–12:00pm (KEC 1109)
	Fri., 2:00–3:00pm (KEC 1109)

// Office Hour:
	Rob: Tu 10:00am–12:00pm, 
	Rob: F 2:00–3:00pm (KEC 1109)
	Dezhong Deng - dengde@oregonstate.edu
	Andrew Emmott - emmotta@oregonstate.edu

// Syllabus
https://docs.google.com/document/d/149owrZ3rSCfQ3QmCTXzuxLsBxlncDAEp4Dri-yHI0Ew/edit#

// TextBook:	
Engineering a Compiler, 2nd ed. by Cooper and Torczon

// Grades:
	Assignment:	50%
		Must sign-up for demo with a TA
		errors: talk to TA
	Quiz:		40%
		Every monday
		errors: talk to Teachers
	Final:		10%

/////////////////////////
//  2019-04-01 Wk1 D1  //
/////////////////////////

Scanner generater: flex
parser generator: bison
assm: llvm


Compiler Components:
	Source Code -> [Compiler] -> Target Code
	Source Code -> [Front End] -> [Optimizer]* -> [Back End] -> Target Code
	Source Code -> [Front End] -> Scanner -> Parser -> [Optimizer]* -> [Back End] -> Innstruction Selector -> Register Allocator -> Instruction Scheduler -> Target Code
		Front End: Interpret source code -> Internal Representation (IR)
			deals with what language source is.
			Components:
				Scanner -> Parser -> Optimizer
				Scanner: micro-syntax of src. (parts of speech)
					Scanner is agnostic to the symbols
				Parser: 
					Recognize the syntax and feed it as IR
					interpret comments as well.
				a = b + 2 ;
				a, b: identifier
				=, +: Operation
				2   : Number
				;   : ;

		Optimizer: size, speed, etc. -> Internal Representation
			Does not care for src or tgt. 
		Back End:  Takes IR -> target code.
			Instruction selector -> Register Allocator -> Instruction Scheduler -> Target Code
			IS: Optimize scheduler (memory load scheduler)

	Translating to assm will lose higher level
	Python -> C -> Assmbly
Language


Interpreter -> 

Just In Time (JIT) compiling
	Needs the most performance from interpretive language.

Translation:


/////////////////////////
//  2019-04-03 Wk1 D2  //
/////////////////////////
Front End:
Scanner (Finite Automata) (review from cs321):
	Goal: Read the src code character by character, and which string is set of 

// to read string 'new' or 'not'
-> s0 -> (n) s1 -> (e) s2 -> (w) s3 (Accepted)
	    		-> (o) s4 -> (t) s5 (Accepted) 
//pseudo code
c = nextChar();
if (c == 'n') {
	c = nextChar();
	if (c == 'e'){
		c = nextChar();
		if (c == 'w'){
			//Accepted.
		}
	}
} 

S 		= All States
\Sigma	= Alphabet
\delta 	= Transition function
S_0		= initial State
S_A		= Accepting States


/////////////////////////
//  2019-04-05 Wk1 D3  //
/////////////////////////

// Regular Expressions

ep = \epsilon
c ep Z U {E}, R, S

basic:
	Concatenaton 		-> RS - rs, r ep R, s ep S
	Alternation (Union) -> R|S - x, x ep R or x ep S
	Kleene Closure (Closure) -> R*

combination:
	Finite Closure   -> R^i (\ep|r|rr|rrr|...)
	Positive Closure -> R+ - RR*
	Range 			 ->	[c1...cn] -> c1|c2|c3|...|cn
	Component 		 -> ^c {\Sigma - c}

ex: regex to 
	floats:	[0...9]+ \. [0..9]*
	quotes: "(^("|\n))*"  // just to close this"
	comments: //(^\n)*\n
	comments: /\* ((^\*) | (\*^/))* \* /

a(b|c)
pseudo code
S = S0
c = nextChar()
while (s != Se && c != eof)
	S = \del[S,c]
	C = nextChar()
if (S in S_A)
	return sucess


/////////////////////////
//  2019-04-12 Wk2 D3  //
/////////////////////////

Flex: Fast LEXical analyzer generator
	successor of Lex: A scanner generator
		Written by Mike Lesk, Eric Schmidt; (Google) in the 1970s


// Syntax
Extension: .l
Input file consists of 3 main sections separated by %%

definition
%%
rules
%%
user code

// Definitions
1. Initial Code Declarations
	- must be closed in a block enclosed "%{" and "%}" and consist of C/C++ code to be copied verbatim to the top of the generated scanner file.
	Init code could be used to declare inits.
	%{
	int num_chars = 0;
	int num_words = 0;
	int num_lines = 0;
	%}
	
2. Name Definitions
	

3. Flex Option Directives





/////////////////////////
//  2019-04-15 Wk3 D1  //
/////////////////////////

//scanner.l

// Def
%{
#include <iostream>
#include <vector>
#include <set>

struct _word {
	std::string lexeme;
	std::string category;
};

std::vector<struct _word> _words;
std::set<std::string> _ids;
bool _error = false;
%}

%option noyywrapp
%option yylineno

void _save_word(std::string lexeme, std::string)


%%
// Rules

[ \t\n]* {} 	//ignore whitespace

[a-z][0-9]? {
				_save_word(yytext, "IDENTIFIER"); //save the identifier
				_ids.insert(yytext);
			}

[0-9]+("."[0-9]+)? {	//trailing # are optional.
				_save_word(yytext, "NUMBER");
				   }

"="					{_save_word(yytext, "EQUALS");}
"+"					{_save_word(yytext, "PLUS");}

.						{				//everything else is a error
					std::cerr << "Invalid symbol on line " << yyline << ":" << yytext << std::endl;
					_err = true;
						}

<<EOF>>			{
							if (_error) {
								return 1;
							} else {
								return 0;
							}
						}


%%
// The CPP file here can be written separately.

int main() {
	if (!yylex()) {			//if no errors
			for (int i = 0; i < _ words.size(); i++) {
				std::cout << _words[i] category << "\t\t" << _words[i].
			}
	}
}




/////////////////////////
//  2019-05-01 Wk5 D2  //
/////////////////////////

parser does the computation and stores the value in the variable.
you can make calculators in parsers

//parser.y
%(
#include <iostream>
#include <map>

std::map<std::string, float> symbols;
void yyerror(const char* err); //use yyerror to check for errors
extern int yylex();	//parser uses yylex, you need to tell it exists.
%)

//write a CFG that will be parsed (term syms,non-term syms)

//we're telling bison that everything is gonna be defined by...
 //%define api.value.type (std ::string*)

// union type is like a struct type except 1 thing per variable.

%union {
// if other value of union is declared, its overwritten.
	std::string* str; //constructor can't do string
	float val;
	int category.
}
	//yystype

%%


%%


/////////////////////////
//  2019-05-06 Wk6 D1  //
/////////////////////////
bison is a bottom up parser

statement
 :	IDENTIFIER EQUALS expression SEMICOLON
 ;

expression 			// this is $$
 : LPAREN expression RPAREN		{ $$ = $2; } // always evaluate this first
 | expression PLUS expression { $$ = $1 + $3; }
 | expression MINUS expression 	{ $$ = $1 - $3; }
 | expression TIMES expression 	{ $$ = $1 * $3; }
 | expression DIVIDEDBY expression {$$ = $1 /$3; }
 | NUMBER { $$ = $1; }
 | IDENTIFIER { $$ = symbols[*$1]; delete $1; }


ID:b EQUALS ID:a1 PLUS NUM:2 SEMICOLON
  expression:	ID-PLUS-NUM 
  statement: ID-EQ-exp-SEMI

yyparse(); 	// calls
yylex(); 	// in a loop

bison -d -o parcer.cpp parser.y 	//-d produces hpp files.

[a-z][0-9]? 	{
				yylval.str = new std:string(yyytext, yyleng);
				return IDENTIFIER;
				}

[0-9]+("."[0-9]+)? {
					 yylval
					 return NUMBER;
}

{ yylval.category = NUMBER; return yylval.category;}
 






yylex() {
	yypush.parse()
}

%locations  //line, column # for error
%define parse.error verbose // more details on type of error.

YYSTYPE yylval; // 
YYLTYPE YYLLOC; // use to store location (first-last line, column)

#define YY_USER_ACTION \ //allows code (next line) to be executed whenever any rule is fired. 
	yylloc.first_line = yyloc.line = yylineno; // can be defined using macro



symbols are accessed by "$$" or "$#"
location of symbols can be accessed by "@#"  
yylerror needs updated. 
void yyeror (YYLTYPE)
need to include special symbol to recognize all errors.


error SEMICOLON { std:cerr << "ERROR: bad stmt on line " << @1.first_line << std::endl; }; //error: special non-terminal that separates which statement







/////////////////////////
//  2019-05-06 Wk7 D3  //
/////////////////////////

Assignment 3 out https://github.com/osu-cs480-sp19/assignment-3-parkj6.git

focus on passing nodes up the tree (AST)
ID:a = NUM:2 + ID:b 	//$$ = +, $1 = 2, $3 = b

=(a,+);
+(2,b);

While_statement
  : WHILE condition COLON NEWLINE block { $$ = new std::string("while (" + $2 + ") " + *$5 + "\n"); delete $2, delete $%; );

while = $$, $2 = condition  $5 = block.

line 72: root node of the CST
tree = directed graphs
nodes and edges can be declared in any order as long as they''re there.









/////////////////////////
//  2019-05-22 Wk8 D2  //
/////////////////////////

Bottom up parsing and LR(1) Grammars
	Left-to-right scan of the source program
	Rightmost derivation (in reverse)
	1 word of lookahead

LL(1) is a subbset of LR(1) grammar so it is strictly more expensive.

Shift-reduce parsing
	Shieft - read one new input token from scanner







/////////////////////////
//  2019-05-24 Wk8 D3  //
/////////////////////////


Closure Operation -  is a iterative loop operation to add more items until it cant

[Goal -> .List, eof] 	// goal to look for list
[List -> .List Pair eof] 
[List -> .Pair, eof]	// reduce to look for goal
[List -> .List Pair, (]
[List -> .Pair, (]		// all are recognizable from top.
[Pair -> .(Pair), eof]
[Pair -> .(), eof]
[Pair -> .(Pair), (]
[Pair -> .(), (]

// . are placeholders to wait for a pair.



Transition Operation - from this set, where are we gonna go? - start with 1 set (S0), loop through all the symbols in the ground (terminal and nontermial), led by a goto. looking for the next LR1 state.
Copy the list, move the placeholder over one. 
Transision - S0
[Pair -> (.Pair), eof] 	// partial pair to recognize 
[Pair -> (.), eof]
[Pair -> (.Pair),(]
[Pair -> (.),(]
[Pair -> .(Pair, )]
[Pair -> .(),)]

S0, ( -> S1
Transition S1 (
	[Pair -> (.Pair), )]
	[Pair -> (.) , )]
	// and then repeats





/////////////////////////
//  2019-06-03 Wk10 D1  //
/////////////////////////

#define YOU FUCKED UP. Come to class more on time next time. 

alloca
load
store

store after you allocate the space (with alloca)















