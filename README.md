# Compilers and Computer Languages

Some basic compilers activities

## Lexical Analysis

Lexical analysis is the extraction of individual words or lexemes from an input stream of symbols and passing corresponding tokens back to the parser.

If we consider a statement in a programming language, we need to be able to recognise the small syntactic units (tokens) and pass this information to the parser. We need to also store the various attributes in the symbol or literal tables for later use, e.g., if we have an variable, the tokeniser would generate the token var and then associate the name of the variable with it in the symbol table - in this case, the variable name is the lexeme.

Other roles of the lexical analyser include the removal of whitespace and comments and handling compiler directives (i.e., as a preprocessor).

The tokenisation process takes input and then passes this input through a keyword recogniser, an identifier recogniser, a numeric constant recogniser and a string constant recogniser, each being put in to their own output based on disambiguating rules.

These rules may include "reserved words", which can not be used as identifiers (common examples include begin, end, void, etc), thus if a string can be either a keyword or an identifier, it is taken to be a keyword. Another common rule is that of maximal munch, where if a string can be interpreted as a single token or a sequence of tokens, the former interpretation is generally assumed.

The lexical analysis process starts with a definition of what it means to be a token in the language with regular expressions or grammars, then this is translated to an abstract computational model for recognising tokens (a non-deterministic finite state automaton), which is then translated to an implementable model for recognising the defined tokens (a deterministic finite state automaton) to which optimisations can be made (a minimised DFA).
