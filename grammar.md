<line>             ::= <or_command>

<or_command>       ::= <and_command> ( "||" <and_command> )*

<and_command>      ::= <pipeline> ( "&&" <pipeline> )*

<pipeline>         ::= <atom> ( "|" <atom> )*

<atom>             ::= <command>
                     | "(" <or_command> ")"

<command>          ::= <simple_command> [ <redirection>* ]

<simple_command>   ::= <word>+


<redirection>      ::= ( ">" | ">>" | "<" | "2>" | "2>>" ) <word>
                     | "<<" <word>

<word>             ::= unquoted_word
                     | '"' <double_quoted_text>? '"'
                     | "'" <single_quoted_text>? "'"
                     | "$" <variable_name>
                     | <escaped_character>


# explanation in plain English without any symbol

# line is the starting point of the grammar, it consists of a command sequence.
# command_sequence is a sequence of pipelines separated by logical operators (&& or ||).
# pipeline is a sequence of atoms separated by pipes.
# atom can be a command or a command sequence enclosed in parentheses.
# command is a simple command that may include variable assignments and redirections.
# simple_command is one or more words.
# redirection specifies how input/output is handled for the command.
# word can be unquoted characters, double-quoted text, single-quoted text, a variable, or an escaped character.
# variable_name is a valid identifier for a variable in the shell.
# double_quoted_text and single_quoted_text are placeholders for the actual content within quotes.
# escaped_character is a placeholder for characters that need to be escaped in the shell.
# variable_assignment allows for setting variables before a command.
# The grammar captures the structure of shell commands, including how they can be combined and how input/output is managed.

