fxor performs a keyed xor on every byte of a file.

Usage: fxor -i /in/file/path [-o /out/file/path][-k key][-hex|-bin|-dec|-string]

-i /in/file/path  
	Specify the path of the file you want xor'd.  

-o /out/file/path  
	Specify the path of the file you want the results output to.  
	Defaults to stdout.  

-k key  
	Input the key you want to use to xor.  
	Defaults to FF.  

-hex|-bin|-dec|-string  
	Options for key format.  
	Defaults to hex.  
