# Compilers and Computer Languages

Some basic compilers activities

## Lexical Analysis

Lexical analysis is the extraction of individual words or lexemes from an input stream of symbols and passing corresponding tokens back to the parser.

If we consider a statement in a programming language, we need to be able to recognise the small syntactic units (tokens) and pass this information to the parser. We need to also store the various attributes in the symbol or literal tables for later use, e.g., if we have an variable, the tokeniser would generate the token var and then associate the name of the variable with it in the symbol table - in this case, the variable name is the lexeme.

Other roles of the lexical analyser include the removal of whitespace and comments and handling compiler directives.

The tokenisation process takes input and then passes this input through a keyword recogniser, an identifier recogniser, a numeric constant recogniser and a string constant recogniser, each being put in to their own output based on disambiguating rules.

These rules may include "reserved words", which can not be used as identifiers (common examples include begin, end, void, etc), thus if a string can be either a keyword or an identifier, it is taken to be a keyword. Another common rule is that of maximal munch, where if a string can be interpreted as a single token or a sequence of tokens, the former interpretation is generally assumed.

The lexical analysis process starts with a definition of what it means to be a token in the language with regular expressions or grammars, then this is translated to an abstract computational model for recognising tokens (a non-deterministic finite state automaton), which is then translated to an implementable model for recognising the defined tokens (a deterministic finite state automaton) to which optimisations can be made (a minimised DFA).


## Syntactic Analysis

Syntactic analysis, or parsing, is needed to determine if the series of tokens given are appropriate in a language - that is, whether or not the sentence has the right shape/form. However, not all syntactically valid sentences are meaningful, further semantic analysis has to be applied for this. For syntactic analysis, context-free grammars and the associated parsing techniques are powerful enough to be used - this overall process is called parsing.

In syntactic analysis, parse trees are used to show the structure of the sentence, but they often contain redundant information due to implicit definitions (e.g., an assignment always has an assignment operator in it, so we can imply that), so syntax trees, which are compact representations are used instead. Trees are recursive structures, which complement CFGs nicely, as these are also recursive (unlike regular expressions).

There are many techniques for parsing algorithms (vs FSA-centred lexical analysis), and the two main classes of algorithm are top-down and bottom-up parsing.

As derivations are ambiguous, a more abstract structure is needed. Parse trees generalise derivations and provide structural information needed by the later stages of compilation.


## Semantic Analysis

Semantic analysis is the process of drawing meaning from text. It allows computers to understand and interpret sentences, paragraphs, or whole documents, by analyzing their grammatical structure, and identifying relationships between individual words in a particular context.

It’s an essential sub-task of Natural Language Processing (NLP) and the driving force behind machine learning tools like chatbots, search engines, and text analysis.

Semantic analysis-driven tools can help companies automatically extract meaningful information from unstructured data, such as emails, support tickets, and customer feedback. 

Semantic analysis or context sensitive analysis is a process in compiler construction, usually after parsing, to gather necessary semantic information from the source code. It usually includes type checking, or makes sure a variable is declared before use which is impossible to describe in the extended Backus–Naur form and thus not easily detected during parsing.
