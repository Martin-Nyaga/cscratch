# Add 2 + 2 and print result #
2 2 add print

# Display the first n fibonacci numbers #
{$fib$ (/num ) 
	(1 1)
	(2 num sub) {:
		over over add
	}
	pstack
}

10 fib
dropstack
20 fib
dropstack