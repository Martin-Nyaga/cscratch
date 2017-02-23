# MATH #
# ---- #
# Increment and decrement top of stack #
{$inc$ 1 add}
{$dec$ /__dec_t 1 __dec_t sub}

# Sum upto a certain number #
{$sumto$ (/__sumto_n)
	(__sumto_n inc)
	(2 __sumto_n div)
	mul
}

# Factorial #
{$fact$ (/__fact_n)
  0 __fact_n eq {? 1 }
  0 __fact_n neq {?
    __fact_n numsto
    __fact_n dec {: mul }
  }
}
