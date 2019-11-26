 If the input indicates the beginning of a comment, the shell ignores the comment symbol (‘#’), and the rest of that line.




The order of expansions is:
- brace expansion;
- tilde expansion,
- parameter and variable ex-pansion,
- arithmetic expansion,
- and command substitution (done in a left-to-right fashion);
- word splitting;
- and filename expansion.

Expansion is performed on the command line after it has been split into tokens. 

After all expansions, quote removal is performed.

#### Steps:

- Reads its input 
- Breaks  the  input  into  words  and  operators,  obeying  the  quoting  rules 
- 




control operatorAtokenthat performs a control function. It is anewlineor one of the following:‘||’, ‘&&’, ‘&’, ‘;’, ‘;;’, ‘;&’, ‘;;&’, ‘|’, ‘|&’, ‘(’, or ‘)’.




Scheme:

      ----------------------------------------------------------------------------------------------
     |   for i in a b c; do echo ok; done || ls 2>/dev/null && echo ok | cat -e & commandnotfound   |
      ----------------------------------------------------------------------------------------------
     |        Looping Construct            |   Pipeline 1    |     Pipeline 2   |  Simple command   |
      ----------------------------------------------------------------------------------------------
     |        Compound Commands            |            List of commands        |     na            |
      ----------------------------------------------------------------------------------------------
