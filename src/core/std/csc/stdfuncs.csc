# STACK MANIPULATION #
# ------------------ #
# Duplicate top 2 items #
{$dup2$ 
	over over
}

# Print nums up to num #
{$numsto$ /__numsto_n
  0 __numsto_n neq {?
    __numsto_n dec /__numsto_n
    1
    __numsto_n {:
      dup inc
    }
  }
}
