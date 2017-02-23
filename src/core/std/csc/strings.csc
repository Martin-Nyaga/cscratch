# STRING MANIPULATION #
# ------------------- #
# Duplicate a string #
{$dupstr$ (dup /__dupstr_l)
  __dupstr_l inc {: __dupstr_l < }
}

# Reverse a string #
# puts a duplicate reverse string on the stack #
{$revstr$ (dup /__revstr_l)
  # Use a counter from 1 #
  1 /__revstr_c

  __revstr_l {:
    __revstr_c <
    __revstr_c inc inc /__revstr_c
  }
  __revstr_l
}

# Concat 2 strings #
# into a duplicate 3rd string #
{$catstr$ (dup /__catstr_l1)
  __catstr_l1 inc < /__catstr_l2

  # Counter #
  __catstr_l1 __catstr_l2 add /__catstr_c

  __catstr_l2 {:
    __catstr_c inc <
  }

  __catstr_l1 {:
    __catstr_c <
  }

  __catstr_c
}

# Compare length of 2 strings #
# Leaves strings intact on the stack #
{$lencmpstr$
  dup
  /__lencmpstr1
  __lencmpstr1 inc < /__lencmpstr2
  __lencmpstr1 __lencmpstr2 eq
}

# Compare 2 strings and return 1 if equal #
# Leaves strings instact on the stack #
{$cmpstr$
  lencmpstr /__cmpstr_l_eq
  
  __cmpstr_l_eq {?

    dup /__cmpstr_l

    __cmpstr_l /__cmpstr_1_acc 
    __cmpstr_l 2 mul inc inc /__cmpstr_2_acc

    __cmpstr_l {:
      __cmpstr_1_acc <
      __cmpstr_2_acc <

      # Increment accessors to accomodate nums #
      __cmpstr_2_acc inc /__cmpstr_2_acc
      __cmpstr_1_acc inc /__cmpstr_1_acc
    }

    1 /__cmpstr_eq 

    __cmpstr_l {:
      neq {? 0 /__cmpstr_eq }
    }

    __cmpstr_eq
  }

  # If strings are not of the same length #
  __cmpstr_l_eq 0 eq {? 0 }
}

# Drop a string from the stack #
{$dropstr$ {: drop }}

# Puts upcased string duplicate on stack #
{$strupper$ (dup /__strupper_l)
  __strupper_l {:
    __strupper_l < /__strupper_ch
    
    96 __strupper_ch gt {?
      123 __strupper_ch lt {?
        __strupper_ch cupper
      }
      123 __strupper_ch gteq {?
        __strupper_ch
      }
    }
    96 __strupper_ch lteq {?
      __strupper_ch
    }
  }

  __strupper_l
}

# upcase single char #
{$cupper$ 32 swap sub}

# Lowercase single char #
{$clower$ 32 add}

# Puts downcased string duplicate on stack #
{$strlower$ (dup /__strlower_l)
  __strlower_l {:
    __strlower_l < /__strlower_ch
    
    64 __strlower_ch gt {?
      90 __strlower_ch lt {?
        __strlower_ch clower
      }
      90 __strlower_ch gteq {?
        __strlower_ch
      }
    }
    64 __strlower_ch lteq {?
      __strlower_ch
    }
  }
  __strlower_l
}

# Print empty newline #
{$pln$ "" pstrln }