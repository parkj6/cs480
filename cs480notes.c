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




































