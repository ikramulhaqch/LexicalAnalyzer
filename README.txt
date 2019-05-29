It is Generic Lexical Analyzer implemented in C++ that can be used to tokenize any code of any  language. you have to provide transition table of the language automaton and input file having code of language. The program output a file having consice transition table and will provide output of lexemes of relatted classes on console(stdout).

Formet of transition table(input.txt):
	97  98 128
	1   3  -1
	1   2  -1
	-1 -1  101
	4   3  -1
	-1 -1  101

	this is a simple transition table for 5 states(each row except 1st representing a state) and 2 symbols having ASCII 97 and 98 last column is showing that if the state is final or not. if the state is final(accepting) then last column will have non zero value. This will be input file giving information about your language and characters including in it.

Formet of output having transition table(output.txt):

	  -1   1   3  -1
	  -1   1   2  -1
	  -1  -1  -1 101
	  -1   4   3  -1
	  -1  -1  -1 101
	0 column is for:    0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31  32  33  34  35  36  37  38  39  40  41  42  43  44  45  46  47  48  49  50  51  52  53  54  55  56  57  58  59  60  61  62  63  64  65  66  67  68  69  70  71  72  73  74  75  76  77  78  79  80  81  82  83  84  85  86  87  88  89  90  91  92  93  94  95  96  99 100 101 102 103 104 105 106 107 108 109 110 111 112 113 114 115 116 117 118 119 120 121 122 123 124 125 126 127
	1 column is for:   97
	2 column is for:   98
	3 column is for:  128

	above is shown output file that will create a generic transition table for all existing ASCII values(0-127) and will provide all information. you can compare above inout file and this output file to get fare idea about this.

Program input file(input_string.txt):
	this file will contain program of your language for tokenization.