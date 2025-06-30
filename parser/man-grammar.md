<line>          ::= <pipeline>

<pipeline>      ::= <command> ( "|" <command> )*

<command>       ::= <simple_command> [ <redirection>* ]

<simple_command>::= <word>+

<redirection>   ::= ( ">" | ">>" | "<" | "<<" ) <word>

<word>          ::= unquoted_word
                 | '"' <double_quoted_text>? '"'
                 | "'" <single_quoted_text>? "'"
                 | "$" <variable_name>
                


command simple cat ....

