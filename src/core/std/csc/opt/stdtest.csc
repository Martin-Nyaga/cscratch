{$test.assert$
  # Print test name #
  pstr
  # Check Value and determine whether pass or fail #
  /__t
  __t 1 eq {? " -> PASS" pstr_grn pln }
  __t 0 eq {? " -> FAIL" pstr_red pln exit }
}

{$test.check$
  "CHECK := " pstr_yel pstrln
}